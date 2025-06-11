# filetocbytes

A small tool I wrote to shoehorn arbitrary binary data into AVR programs. Alternatively, this is good for getting binary or textual data from external files into C/C++ programs without using third-party libraries or macros.

## Arguments

filetocbytes supports the following arguments:

- `-e`: The C-style array shall be defined with `extern "C"` linkage.
- `-t`: The input file is a text file. This will cause a `\0` to be appended to the byte array.
- `-n arrayName`: The C-style array shall be named `arrayName`.
- `-i inputfile`: The input file is `inputfile` (required).
- `-o outputfile`: The output file is `outputfile`.

## Examples

- Make me a C-style array of `foo.bin`:

```bash
./filetocbytes -i "foo.bin"
```

```c
#include <stdint.h>

uint8_t bytes[123] =
{
    ...
}
```

- Make me a C-style array called bar of `foo.bin`:

```bash
./filetocbytes -n bar -i "foo.bin"
```

```c
#include <stdint.h>

uint8_t bar[123] =
{
    ...
}
```

- Make me a C-style array of `foo.txt`, which is a text file:

```bash
./filetocbytes -t -i "foo.txt"
```

```c
#include <stdint.h>

uint8_t bytes[124] =
{
    ..., 0x00
}
```

- Make me a C-style array of `foo.bin` with extern linkage:

```bash
./filetocbytes -e -i "foo.bin"
```

```c
#include <stdint.h>

extern "C" uint8_t bytes[123] =
{
    ...
}
```