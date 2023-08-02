https://developers.redhat.com/articles/2021/06/25/use-source-level-annotations-help-gcc-detect-buffer-overflows

https://github.com/SonarSource/sonarlint-vscode/wiki/C-and-CPP-Analysis

https://gcc.gnu.org/onlinedocs/gcc-11.1.0/gcc/Warning-Options.html#index-Warray-parameter

https://devblogs.microsoft.com/cppblog/makefile-tools-december-2021-update-problem-matchers-and-compilation-database-generation/

Static Analyzer Test Results

| Test                | Sonarlint | Clang 16.0.0 | GCC 13.2.0 | icx 2023.1.0 | msvc v19.35 | ChatGPT |
|---------------------|-----------|--------------|------------|--------------|-------------|---------|
| Array Overflow      | ✅        | ✅           | ✅         | ✅           | ✅          | ✅      |
| Concat Overflow     |           |              |            |              | ✅*         | ✅*     |
| Use After Free 1    | ✅        | ✅           | ✅         | ✅           | ✅          | ✅      |
| Use After Free 2    | ✅        | ✅           | ✅*        | ✅           |             | ✅      |
| Null Pointer        | ✅        | ✅           | ✅         | ✅           |             | ✅*     |
| Invalid Pointer     |           |              |            |              |             | ✅*     |
| Uninitialized Value | ✅*       | ✅*          | ✅         | ✅*          |             |         |
| printf Overflow     |           |              |            |              | ✅          |         |
| malloc Error        |           |              | ✅         |              | ✅          |         |
| Quote Overflow 1    | ✅        |              | -          |              |             |         |
| Quote Overflow 2    | ✅        |              |            |              |             |         |
| Quote Overflow 3    |           |              |            |              |             |         |

`*` True Postive and False Positive
`-` Issued Complexity Warning

Sanitizer Test Results

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

    --analyze -Wall -Wextra -Werror -pedantic -std=c99 -O2 -g

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

// "/wd4710" is needed as otherwise a warning is given for the compiler
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

https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lJL6yAngGVG6AMKpaAVxYM9DgDJ4GmADl3ACNMYj0AB1QFQlsGZzcPSOjYgV9/IJZQ8K4LTCsbASECJmICBPdPXMtMazji0oJ0wJCwvQUSsoqk6s6mvxastq4ASgtUV2Jkdg4OMdpOAFZeTw4tUlRORwBqBQmpzG2AUgAmAGYeUgJNObGAaxATjQA6KQB2N8WANjeNN4AORaSf6A/ScSQrG4bTi8BQgDRXG5jOCwGCIEATAgRVwEciUNAsCJ0MIBVgzVT/L4AWi%2Bkm2yAMRm2XC%2Bzxe60w%2BCIxDw6D0/EEIjE7CkMkEihU6jWOj0AHdiEwIpwePMlpDpdCOAB5HHYgjbVBUbYU6m0%2BmM4DM1ns7YQZyE4nEY7nUa8a7SkZjBCYJhYcIQVUcCGkFggRYI1brTazCzwxEe0go9EEon0MgUCApx0oBmGYAsjQIrAANzw0wAanhMLKtRFGMreDRaAQwnCIMEocE/KUAJ4N0hd5jEHta4LaWruy4EtiCLUMWh9jVYYKuYCOMS0OHcXhYFh58RLvDECd4YuYLcc1S1HEzS5%2BFsLDW0PDBBXD5xYKEEHmh7djKgGMACiVtWtb1tuYrCKI4iigK8hKGoUK6LkFogKYxjmM%2BwRwpAYyoBEhQMFuVJUoYYg9gAXocVIAOobtstGYKo35MAxNFhMQJAMXW6CGDYyAMR06BHGcAAiyAAJwSQxWonAxwC8KgZ7EDyWA4QGeQFHE9gME4LiVF4unNJk2TJDEhHdFUpBROZcTGa0OSaSeRR9JZ7T5M5DANGU9lDI5HSNG5vSNL5pmjOMkzTBIgbLKQkaKZwxqUjSdK5kyLJsmytq4IQXGnBcIxuki9wSBJzyAicJySGcJwSScUiLFwZxfGCQa8KG4ZxVC0awnG7paJ6pAPFwZUVVVNV1Q1TUtY%2BZzqlGMLxgNiZokmEBIJiep4pmqAOmmpJsJwJopdswDIAJTXPCcvCcrlqn8rIQowdIcESohGq6CcpDyoqDYxfNCXarqOIGkax1mmdF1nFdtr2qmYTOjVhVLbcpDer6bQaY%2BwYdRG3WLXCCL9XMK3wOtKC7fD6b4pT2bIPmNWkCWZaYCBNZ1qslxNi2xBth2GqDr2/aC8Oo7jtY/bTowBBzguULLqu660Ju/a7vuMzrPgx51GeF43VeyA3v2975FCWFvj2H4a26P5/XwgHAVW7PgVzj3QSKL2yG9UrrJ9%2Bh5mhZj6C%2B6l4QRcTEaRzALlRTq0fRjHMQqbEcVxVI8XxZaCQQwliZJ0lUrJ8mKcpqnnvAYw1HUdgQA4QWkD4AwmcM1kpBZ%2Bk9K3tlpE3DnuVpLmBR3VlV4R3n9BkffBV0w/tH0oXDJX%2BxReFj6xfFmpJaadKQ8y0NyRAOXcojroo4NDxPGyhbXzfN/SNj7VhnjGo9bGRPFUNjzsrfP%2BFvfnBzS6i/RaxNkSrVWhtYGuIMxZn2mSI6yUzRllUNsJ45xXhshulyEgvIHqCndhIT24oEI%2BxlGcb6ColR/lauvfGQMsQg0NFvE6ZYBJoK4M8MqGhYa0zTIjM4yNQFeh9H6SggYcZPyAQtGMhMz6k1gEgWBYRtpKPCMgVh7CJJFkwKWCsTswKc0bHQHmfNOzdmHMLcxI4xwTklrtGcMt5yLk1pgFca4NxbkuGrIwB5NZHhPLrKETFrwtmNoIU2T4XwWytl%2BW21CAJMCAmzAx/Y4JPQ9pBb2SEQDkNQuhTCIcK4bHDgIYidFlYpyTqxRiKk04Z0EFnKkQkRLiSkjJOSVIFIbFLrycuuEnLV08LXXS9dG6Tz8mZVI8RZ65BslMhe/kPKDPHvXUe9R569wmdPcoMyLAbPGWFJekURT/SkYDZhSDzqoI0PVThWVD7YKdPlU%2BQjP6X1/r/f%2BbUQySI3q/WRryL7fw%2BXfVqgC/kgKRPIqAECMRQJUbwkk8COAmm2CwBQxYBLFhGs8M4sVbrclwbkNJBDYJexIdk6QP0qEqhoQDTUOoGH6iYai9FmLtjYrKninhe0Eb5UkIIj%2B6NRFY3BI/TqEKZF9ShWtRRiLqY7V5eETFxhOXGDxcYE0TMdEs2SRzVJxjWyUH5usEWi5LhmrFrYiCUtZxOPlq4xWHjVaYD3D462TN/E63LhqYJhtQkQRNo%2BdY5tewxI1N%2BPAv5aUJKSfo/VEESXCkIZkilH0QD3wDvk4O2Ein4UIluAA9OU2g2xi0AA0y2ynQJIN4XBuGFureGSQiwy1CRQFwLgZayIx0OIW0S2AABCcgADiZaqAKEMLEKiLTfToGPAoBQZaABaeAS4cV6aHAZhEdJ6USFZMZgwwpdymfXOZhEFn908is3ZazB4%2BU2cegKM991zxCo%2BxeEUDjRTpWczerKMVYpxdyh5d0T6Co9CVd5ILQUPx%2BRKuhvV36QbecCmDGgvngsQ2fQM10/2v1ecpGIdhJBAA