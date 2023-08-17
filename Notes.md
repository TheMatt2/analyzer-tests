
## Test Descriptions

| Test                      | Severity | Type                  |
|---------------------------|----------|-----------------------|
| Array Overflow            | 3 🔴     | Overflow              |
| Concat Overflow           | 3 🔴     | Overflow              |
| Gets Overflow             | 3 🔴     | Overflow              |
| Printf Sting Overflow     | 3 🔴     | Overflow              |
| Printf Format Overflow    | 3 🔴     | Overflow              |
| Quote Overflow 1          | 3 🔴     | Overflow              |
| Quote Overflow 2          | 3 🔴     | Overflow              |
| Quote Overflow 3          | 3 🔴     | Overflow              |
| Scanf Overflow            | 3 🔴     | Overflow              |
| Invalid Pointer           | 2 🟠     | Memory                |
| Null Pointer              | 2 🟠     | Memory                |
| Realloc Invalid           | 2 🟠     | Memory                |
| Reallocf Free             | 2 🟠     | Memory                |
| Double Free 1             | 3 🔴     | Memory                |
| Double Free 2             | 3 🔴     | Memory                |
| Divide By Zero 1          | 2 🟠     | Logical               |
| Divide By Zero 2          | 2 🟠     | Logical               |
| Malloc Zero Access        | 2 🟠     | Undefined Behavior    |
| Stack Return 1            | 3 🔴     | Undefined Behavior    |
| Stack Return 2            | 3 🔴     | Undefined Behavior    |
| Stack Return 3            | 3 🔴     | Undefined Behavior    |
| String Literal Modify     | 2 🟠     | Undefined Behavior    |
| Uninitialized Value 1     | 2 🟠     | Undefined Behavior    |
| Uninitialized Value 2     | 2 🟠     | Undefined Behavior    |
| Malloc Error              | 1 🟡     | Common User Error     |
| Switch Fall Through       | 1 🟡     | Common User Error     |

<br>

| Severity Score | Description                              |
|----------------|------------------------------------------|
| 3 🔴           | There are security implications.         |
| 2 🟠           | Your code may/will crash.                |
| 1 🟡           | It's an issue, but the code may run.     |

## Static Analyzer Test Results

| Test                | Sonarlint v3.19.2 | Snyk 1.20.3 | CLion 2023.2 | Clang 16.0.0 | GCC 13.2.0 | icx 2023.1.0 | msvc v19.35 | ChatGPT |
|---------------------|-------------------|-------------|--------------|--------------|------------|--------------|-------------|---------|
| Array Overflow      | ✅                |             | ✅           | ✅           | ✅         | ✅           | ✅          | ✅      |
| Concat Overflow     |                   |             |              |              |            |              | ✅*         | ✅*     |
| Use After Free 1    | ✅                | ✅          | ✅           | ✅           | ✅         | ✅           | ✅          | ✅      |
| Use After Free 2    | ✅                | ✅          | ✅*          | ✅           | ✅*        | ✅           |             | ✅      |
| Null Pointer        | ✅                |             |              | ✅           | ✅         | ✅           |             | ✅*     |
| Invalid Pointer     |                   |             |              |              |            |              |             | ✅*     |
| Uninitialized Value | ✅*               |             |              | ✅*          | ✅         | ✅*          |             |         |
| printf Overflow     |                   |             |              |              |            |              | ✅          |         |
| malloc Error        |                   |             |              |              | ✅         |              | ✅          |         |
| String Literal      |                   |             |              |              | ✅         |              |             | ✅*     |
| Divide by Zero 1    | ✅                |             | ✅           | ✅           | ✅         | ✅           | ✅          |         |
| Divide by Zero 2    |                   |             |              |              |            |              |             | ✅*     |
| Quote Overflow 1    | ✅                |             |              |              | -          |              |             |         |
| Quote Overflow 2    | ✅                |             |              |              |            |              |             |         |
| Quote Overflow 3    |                   |             |              |              |            |              |             |         |

`*` True Postive and False Positive
`-` Issued Complexity Warning

## Sanitizer Test Results

| Test                | No San | Clang 11.0.3 | Clang 14.0.0 | GCC 13.2.0 |
|---------------------|--------|--------------|--------------|------------|
| Array Overflow      |        | ✅           | ✅           | ✅         |
| Concat Overflow     | ✅     | ✅           | ✅           | ✅         |
| Use After Free      | ✅     | ✅           | ✅           | ✅         |
| Null Pointer        | ✅     | ✅           | ✅           | ✅         |
| Invalid Pointer     | ✅     | ✅           | ✅           | ✅         |
| Uninitialized Value |        |              |              |            |
| printf Overflow     |        | ✅           | ✅           | ✅         |
| malloc Error        |        |              |              |            |

## Clang

Version 14.0.0

    --analyze --analyzer-output text -Xanalyzer -analyzer-checker=unix -Xanalyzer -analyzer-checker=security -Wall -Wextra -Werror -pedantic -std=c99 -O2 -g

```
docker run -it --rm -v $(pwd):/magic -w /magic ubuntu
> apt-get install clang make
```

## GCC

Version 13.2.0

    -fanalyzer -Wanalyzer-too-complex -Wall -Wextra -Werror -pedantic -std=c99 -O2 -g

```
docker run -it --rm -v $(pwd):/magic -w /magic gcc
```

## ICX

    --analyze -Wall -Wextra -Werror -pedantic -std=c99 -O2 -g

## MSVC

    "/wd4710" is needed as otherwise a warning is given for the compiler
    // not inlining printf
    // "/w35045" is needed to avoid warnings about speculative execution mitigation
    // https://learn.microsoft.com/en-us/cpp/error-messages/compiler-warnings/c5045?view=msvc-170
    /Wall /WX /wd4710 /wd5045 /std:c11 /analyze /DEBUG /fsanitize=address /Zi

## ChatGPT

Check the following C code for any security issues, or other issues that would cause it to crash.
If the program has no serious issues, please say so.

```
*** All comments removed
```

Analyzing on the first few sentences of its answer
So long as it get the point, it counts as a pass, even if it
did state incorrect information about the code.

## Goldbolt

Godbolt was used to evaluate compilers

[Goldbolt IDE](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lJL6yAngGVG6AMKpaAVxYM9DgDJ4GmADl3ACNMYj0AB1QFQlsGZzcPSOjYgV9/IJZQ8K4LTCsbASECJmICBPdPXMtMazji0oJ0wJCwvQUSsoqk6s6mvxastq4ASgtUV2Jkdg4OMdpOAFZeTw4tUlRORwBqBQmpzG2AUgAmAGYeUgJNObGAaxATjQA6KQB2N8WANjeNN4AORaSf6A/ScSQrG4bTi8BQgDRXG5jOCwGCIEATAgRVwEciUNAsCJ0MIBVgzVT/L4AWi%2Bkm2yAMRm2XC%2Bzxe60w%2BCIxDw6D0/EEIjE7CkMkEihU6jWOj0AHdiEwIpwePMlpDpdCOAB5HHYgjbVBUbYU6m0%2BmM4DM1ns7YQZyE4nEY7nUa8a7SkZjBCYJhYcIQVUcCGkFggRYI1brTazCzwxEe0go9EEon0MgUCApx0oBmGYAsjQIrAANzw0wAanhMLKtRFGMreDRaAQwnCIMEocE/KUAJ4N0hd5jEHta4LaWruy4EtiCLUMWh9jVYYKuYCOMS0OHcXhYFh58RLvDECd4YuYLcc1S1HEzS5%2BFsLDW0PDBBXD5xYKEEHmh7djKgGMACiVtWtb1tuYrCKI4iigK8hKGoUK6LkFogKYxjmM%2BwRwpAYyoBEhQMFuVJUoYYg9gAXocVIAOobtstGYKo35MAxNFhMQJAMXW6CGDYyAMR06BHGcAAiyAAJwSQxWonAxwC8KgZ7EDyWA4QGeQFHE9gME4LiVF4unNJk2TJDEhHdFUpBROZcTGa0OSaSeRR9JZ7T5M5DANGU9lDI5HSNG5vSNL5pmjOMkzTBIgbLKQkaKZwxqUjSdK5kyLJsmytq4IQXGnBcIxuki9wSBJzyAicJySGcJwSScUiLFwZxfGCQa8KG4ZxVC0awnG7paJ6pAPFwZUVVVNV1Q1TUtY%2BZzqlGMLxgNiZokmEBIJiep4pmqAOmmpJsJwJopdswDIAJTXPCcvCcrlqn8rIQowdIcESohGq6CcpDyoqDYxfNCXarqOIGkax1mmdF1nFdtr2qmYTOjVhVLbcpDer6bQaY%2BwYdRG3WLXCCL9XMK3wOtKC7fD6b4pT2bIPmNWkCWZaYCBNZ1qslxNi2xBth2GqDr2/aC8Oo7jtY/bTowBBzguULLqu660Ju/a7vuMzrPgx51GeF43VeyA3v2975FCWFvj2H4a26P5/XwgHAVW7PgVzj3QSKL2yG9UrrJ9%2Bh5mhZj6C%2B6l4QRcTEVQZELlRTq0dHlFhFSRCoFSKb0KobH0YxzEKmxHFcVSPF8WWgkEMJYmSdJVKyfJinKap57wGMNR1HYEAOEFpA%2BAMJnDNZKQWfpPQD7ZaS9w57laS5gXD1ZreEd5/QZJPwVdHP7R9KFwwt/sUXhY%2BsXxZqSWmnSkPMtDckQDl3KI66KODQ8TxsoWb/v%2B/0jY%2B1YZ4xqPWxiJsVIajx2Qf3AYWL%2BnA5pdX/otYmyJVqrQ2sDXEGYsz7TJEdZKZoyyZyeOcV4bIbpchILyB6gp3YSE9uKBCPsZRnG%2BgqJUf5WpH3xkDLEINDSnxOng7YBDoZcCynaWmaZEZnGRggr0Po/SUEDDjX%2BsCFoxkJo/UmsAkAYLCNtbR4RkB4MEVwIsmBSwVidmBTmjY6A8z5p2bsw5hYOJHGOCcktdozhlvORcmtMArjXBuLclw1ZGAPJrI8J5dZQiYteFsxtBCmyfC%2BC2Vsvy21YQBJgQE2aWP7HBJ6HtILeyQiARhqF0KYRDs3DY4cBDETosrfOudWKMRUoXYughS5UiEiJcSUkZJySpApDYDdeRN1wk5NungO66S7j3FefkzKpHiBvXINllnb38h5KZS8u4L3qFvCeiy17lFWRYQ5Cywq70iiKf6yjAa8NwcgfBGhCHCI0NlUhTp8oP2kSAl%2BECIFQLaiGJRx8AFqL%2Bc/MBgLP6tRgeC%2BBSINFQGQRiVBuixEkiwRwE02wWAKGLAJYsI1nhnFirdbk5Dcj5KobBL2dCSnSB%2BiwlUbCAaah1Fw/UPC8UEqJdsElZVyWwyxd884kgpHAPRnIrG4If6dURaovqyK1paLFZivabQiXGCFcYclxgTRM1MSzHJHM8k2NbJQfm6wRaLkuHasWbiIJS1nN4%2BWfjFaBNVpgPcoTrZMwiTrJuGoYmGziRBE2j51jm17KkjU348C/jZZk7JFjzUQVpcKahRTGUfRAF/AOFTg7YWqfhQiW4AD0DTaDbGrQADTrbKdAkg3jGKbegcMkhFh1qEigLgXA60JyonW0S2AABCcgADidaqAKEMLEKivTfToGPAoBQdaABaeB64cTGaHSZhEdJ6USFZeZgwwqj2WV3dZhFNlT08rss5%2ByZ4%2BSOZegK69T2bxCu%2BneEUDjRXZfck%2BfLCXEtJSKm%2BXz75So9CVAFsK4Xf1BYqjhvUgHwf%2BTCpDGhgUIvQ4/QM10QMAL%2BcpGIdhJBAA%3D)

<!-- https://learn.snyk.io/lesson/use-after-free/?loc=ide -->
