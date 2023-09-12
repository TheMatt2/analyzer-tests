
## Test Descriptions

| Test                      | Severity | Type                  |
|---------------------------|----------|-----------------------|
| Array Overflow            | 3 🔴     | Overflow              |
| Concat Overflow           | 3 🔴     | Overflow              |
| Gets Overflow             | 3 🔴     | Overflow              |
| Printf Format Overflow    | 3 🔴     | Overflow              |
| Printf String Overflow    | 3 🔴     | Overflow              |
| Quote Overflow 1          | 3 🔴     | Overflow              |
| Quote Overflow 2          | 3 🔴     | Overflow              |
| Quote Overflow 3          | 3 🔴     | Overflow              |
| Scanf Overflow            | 3 🔴     | Overflow              |
| Double Free 1             | 3 🔴     | Memory                |
| Double Free 2             | 3 🔴     | Memory                |
| Invalid Pointer           | 2 🟠     | Memory                |
| Memory Leak               | 1 🟡     | Memory                |
| Null Pointer              | 2 🟠     | Memory                |
| Realloc Invalid           | 2 🟠     | Memory                |
| Reallocf Free             | 2 🟠     | Memory                |
| Use After Free 1          | 3 🔴     | Memory                |
| Use After Free 2          | 3 🔴     | Memory                |
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

| Test                      | Sonarlint v3.20.2 | Snyk 1.20.3 | CLion 2023.2 | GCC 13.2.0 | Clang 16.0.0 | icx 2023.1.0 | msvc v19.37 | clang-tidy | ChatGPT |
|---------------------------|-------------------|-------------|--------------|------------|--------------|--------------|-------------|------------|---------|
| Array Overflow            | ✅                |             | ✅           | ✅         | ✅           | ✅           | ✅          | ✅         |         |
| Concat Overflow           |                   |             |              |            |              |              | ✅*         | ✅*         |         |
| Gets Overflow             | ✅*               | ✅*         |              | ✅*        | ✅*          | ✅*          | ✅*         | ✅*         |         |
| Printf Format Overflow    | ✅*               | ✅          | ✅           |            |              |              | ✅*         | ✅          |         |
| Printf String Overflow    |                   |             |              |            |              |              | ✅          |              |        |
| Quote Overflow 1          | ✅                |             |              | ✅&        |              |              |             |              |        |
| Quote Overflow 2          | ✅                |             |              |            |              |              |             |              |        |
| Quote Overflow 3          |                   |             |              |            |              |              |             |              |        |
| Scanf Overflow            | ✅*               |             |              |            |              |              |             |              |        |
| Double Free 1             | ✅                | ✅          | ✅           | ✅         | ✅           | ✅           | ✅          | ✅           |        |
| Double Free 2             | ✅                | ✅          |              | ✅*        | ✅           | ✅           |             | ✅           |        |
| Invalid Pointer           |                   |             |              |            |              |              |             |              |        |
| Memory Leak               | ✅                |             |              |            | ✅           | ✅           | ✅&         | ✅           |        |
| Null Pointer              | ✅                |             |              | ✅         | ✅           | ✅           |             | ✅           |        |
| Realloc Invalid           | ✅                |             |              | ✅         | ✅           | ✅           |             | ✅           |        |
| Reallocf Free             | ✅                |             |              | ✅         | ✅           | ✅           |             | ✅           |        |
| Use After Free 1          | ✅                | ✅          | ✅           | ✅         | ✅           | ✅           | ✅          | ✅           |        |
| Use After Free 2          |                   |             | ✅           | ✅         |              |              | ✅          |              |        |
| Divide By Zero 1          | ✅                |             | ✅           | ✅         | ✅           | ✅           | ✅          | ✅           |        |
| Divide By Zero 2          |                   |             |              |            |              |              |             |              |        |
| Malloc Zero Access        | ✅*               |             |              | ✅         | ✅           | ✅           |             | ✅*          |        |
| Stack Return 1            | ✅                |             | ✅           | ✅         | ✅           | ✅           | ✅          | ✅           |        |
| Stack Return 2            | ✅                |             | ✅           | ✅         | ✅           | ✅           | ✅          | ✅           |        |
| Stack Return 3            | ✅                |             |              | ✅         | ✅           | ✅           |             | ✅           |        |
| String Literal Modify     |                   |             |              | ✅         |              |              |             |              |        |
| Uninitialized Value 1     | ✅                |             |              | ✅         | ✅           | ✅           |             | ✅           |        |
| Uninitialized Value 2     | ✅                |             | ✅           | ✅         | ✅           | ✅           | ✅          | ✅           |        |
| Malloc Error              |                   |             |              | ✅         |              |              | ✅          |              |        |
| Switch Fall Through       | ✅*               |             |              | ✅         |              |              |             |              |        |

`*` True Positive and False Positive
`&` Issued Complexity Warning

### Detection Results

 - Sonarlint v3.20.2 16 / 29 (55%)
   - Quote Overflow 1
   - Quote Overflow 2

 - Snyk 1.20.3 4 / 29 (14%)

 - CLion 2023.2 9 / 29 (31%)

 - GCC 13.2.0 17 / 29 (59%)
   - String Literal Modify
   - Switch Fall Through

 - Clang 16.0.0 15 / 29 (52%)

 - icx 2023.1.0 15 / 29 (52%)

 - msvc v19.37 10 / 29 (34%)
   - Printf String Overflow

 - clang-tidy 15 / 29 (52%)
 - ChatGPT

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

## GCC

Version 13.2.0

```
-fanalyzer -Wanalyzer-too-complex -Wall -Wextra -Werror -pedantic -std=c11 -O2 -g
```

## Clang

Version 16.0.0

```
--analyze -Wall -Wextra -Werror -pedantic -std=c11 -O2 -g
```

## ICX

Version 2023.2.1

```
--analyze -Wall -Wextra -Werror -pedantic -std=c11 -O2 -g
```
## MSVC

Version v19.37

```
/Wall /WX /wd4710 /wd4820 /wd4996 /wd5045 /wd6255 /std:c11 /analyze /DEBUG /Zi
```

 - `/wd4710` is needed as otherwise a warning is given for the compiler
 - `/w35045` is needed to avoid warnings about speculative execution mitigation
 - `/wd4996` is needed to allow `open()` on Windows. Does disable the `scanf()` check.

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

[Goldbolt IDE](https://godbolt.org/#z:OYLghAFBqd5QCxAYwPYBMCmBRdBLAF1QCcAaPECAMzwBtMA7AQwFtMQByARg9KtQYEAysib0QXACx8BBAKoBnTAAUAHpwAMvAFYTStJg1AB9U8lJL6yAngGVG6AMKpaAVxYM9DgDJ4GmADl3ACNMYj0AB1QFQlsGZzcPSOjYgV9/IJZQ8K4LTCsbASECJmICBPdPXMtMazji0oJ0wJCwvQUSsoqk6s6mvxastq4ASgtUV2Jkdg4OMdpOAFZeTw4tUlRORwBqBQmpzG2AUgAmAGYeUgJNObGAawlJADoTgA5FgHYpN8/vgE59JxJCsbhtOLwFCANFcbmM4LAYIgUKgWBE6GFyJQ0Kj0eFkMAuGcTqQsAA3PDTABqeEwAHcAPIRRicS40WgEMKQiDBUHBPylACeLN4fOYxAF9OC2lq124vGxbEE9IYtCFa14WGCrmAjjEtEhcpJmBYhmA4nVJLwxBleFJmAN60wqlqrg5wvIgnyoNoeGCxEFziwoIIxDwLGFYyoBmACmpdMZzMN/EEIjE7CkMkEihU6gtulyBiMIFMxnMPuCkMgY1QEUKDANAFoqIYxAKAF5hbYNgDqLdVHeIDaIqAb2Ii9FUXd7tFoU6dIaYc%2BIxBIXaZ6EMNmQXY66COZwAIsguFwu/STl3gLxUHbl3gsJWIGManU7BAHN0qqQfANMtlkjEdafgBqQMM0f7DHkBT1H0wHVPkNpFH04GtDkFiwS4lTtMhv6oRIz77NM%2BGAhwyykKs6ybBw2yqK8ABsDZ0ZI2zAMg26Ei82wQLghCrqcFwjLwspaCM9yPC87xfJIPxSScAILBwwKkOGizQhR17ghYUIwuqcKIhASATAQESupiEBjriASsDMtEMUxLFsdsHEnLwmD4EQoboHoybCKI4gZj52ZqKC%2BakLS/oRBGJFkepYIcPSromQQ2yoFQNH0YxzGsexZycRAzg4vQxDHOcoxCbCYwIJgTBYOET4kUpKlqaCVEQtpwm3KQDxSBJvzSZJ/wkWcIIWq1OkiaQ8JQPpSAWUVZlzW0bGFgSdEaNCZIUpgcYMkyqysnQHLEFyPIWqKgruud4qStK1jugqjAEMqqqgpq2q6jOBqXFgJpGOa6z4NadR2g6rnOsgrozJcfgcgp6zlv64qBjM6whmGUVRkwMY7Qm%2B28D5qb%2BdIgVKMFeYgMSK3FmY%2Bi%2Bo%2B1a1nEjYNn27aHD2epzqoC5LiuxUNuum4UjuBB7oex6ng256Xtet6efa8DPghr6eO%2BDBOJhPTfurKFDGhUSAXEcGkAboG6/%2B8HQUhjTGy%2BdYNGU5uQR0Nua1%2BLuO7hevEXskxEaM0UjZRnDpXZzHICtTl0U8Ggx1xPEeSVAnlbpYk9TJ3wDdJ8lArwTXkS1mmQtCHV6fABkgEZSULSiaJFVZbCcLZmXbBHppRzHMeue5JD3t5siE%2BmxOyEFubrLoxLhUwkVyvMSxBxp8WJa6KVpc39lt0YHexxoXEFXXnb8ScgnjZ1VU1W09UKY1ICqQXo1F%2B1FVdeJGf9X1clDQvcUpxNU3/7NWuuIa6FSWhSVQJwNDnBOLkTaVIaS7UTAddknJKCnXWFdNUlxME3RlPdFEionoqjVADTAWodR6i%2BhqY0pp/oaitDaEGoInQujdIaGGXoLQIwDBgFGQlQzhlnnwaMsYEG43dATPyQ9MzyFJmPHQIAzj6FNNTUstMKyKw2IzAQzNWYdinJzHs85/S81XALNyQttwNl3PuI8J4zwXgbFeDYct7wKyrFBRCqsPxuy8DrL2FsTYpCAr43Ips6xOzQnbGCrtEju2VvbHCGQ8K9FiVhVJntknewDr7A4xEFIxULtRdezFwHbEgecF4TxTzcR7sVfiZVT6iRfunLOb9P7XzzrfZqD9ZhaRLrCSaM1K7LwICAg%2BxAG42QyvZMpFTconGqd3Xinl%2B4pikY8GRo8QqKLChFKKBTv5UQSsZFeqVQ4tzmVAhZ1S95AKKknM4J9S6VWqrVSgc9FJdLvrFMaxcmlp2eO0tpOcODDXvsHPppchnl2GYtMgFBzL3LaKSZAxhSRcD%2BMYM4HxjC2SNOSeB8Y9oSMOqg7kvJ%2BTikulSiUUo8GGgekqYhr0yHvUoe6H6tC%2BGWiBjYJhFoWEQzYdDT0cNeDcKRrw4MAiMYiJxiSpMA8NkBRHnInZ0gqYljLHTTRNY6wGgAPTTlnMagAGtsQ1tJ0CSC%2BLvK1NrXiQMtdayQfw/h0RdegVSkhFheroicRYfrDW7hQPYw1ejDiGoPNgAAQnIAA4pagAWngWWYR5b008Srew6tjY/iyYE8JRtQlBMNmkAJzsEkxK6KW6J1tMmDECR7codaklNuGARP26ZPmFN6aHbYLAFCou2Biv4TwcXxzqUnRpLyWlAraSChq3yemQragM3SMLYCGVGeMyy1km70UHcO7cY6J0fGWR5PuuRJFpk2STHMGq9nTwOfPCFi8TlJVXgOodI6z2Tvysi%2Bp5xJDPOfufd5V9c7KW6e%2Bn%2B/SAXzt6rJJdClwW/M0tCgByJQEIqxEBlAm9VrrQJVtBVSD8ZkuOmgylYosEilpbgu6jKCGPWeiQ6h5CPr6k5TQv6PLAaMIVoK8GkN3QcPFeoxGApkYyvRkIzG2MxGKtZMqu9qqszqvJosZRRZtXqKzfqpmnAOYzi5jzIxy4zGC0EMLaxotbHIHdQ4mWLiM1uKzfW7xebS0Fo7frYJJa4kgQiZWqJ1aG2tuC5bLxDt%2BiFudhhaL6FGiRJ9oRHtgc4NUQuRvSOXBo47ynSsmdYHU4tNymcKBfxCRVbkrVjQOnOnZcfhuv%2B%2BlhnDloGZUoMZNK9YUMoQw%2BQhAIFQLSPGpB4VTMPWHByOUXiXt7l5G9amiZbK0%2BPW%2BykBBMDQAnEgAAJJgChY2YEYAAQVdKgXGbl3QsF2/tup4jDQPeYGgYo%2BBJu7j8EXUWfghv%2BFoKN8bk2usAEkvJEZsOgAUIZXAMDuM%2BmePBe1HM4ERoc94BRcXh4jkYuXw75cK3HWpJWGmkG2PvXESdFhlZEoC5DmcP70WXTBn5RT11NK3UiLrPXiB9b6QNwHI2xsTfwbhmbHASmt2J53R0dTr0yMHvetVj7tM7fe6gA7xBjunfOwwK7RBbteVe497Xz2VN53N5937hofurAhP9hgIvgdi7B6gFwkOQBCF22QKeKO5hZYwxwX3YpCey/bgV%2BXxXE4U6p0B2n9Oz5vMvp8m%2BHPelc7nd1RYLw6LvC4IsE4BfFhF5OB8L%2BLWoXPwUi5avv9Oq3hiHYSQQA%3D%3D)
