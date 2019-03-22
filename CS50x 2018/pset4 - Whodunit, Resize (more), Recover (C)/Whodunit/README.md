# Questions

## What's `stdint.h`?

stdint.h is a header file used to specfically define the bit length of integers, independant of the system's specifications. This makes the programs more
portable, as for differing computer architectures, the bit length will remain constant(and thus the range of values represented also remains unchanged).

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

uint8_t - is a datatype that represents an unsigned integer having size 8 bits. The '_t' indicates that the representation of the data type will be in two's complement.
uint32_t - is a datatype that represents an unsigned integer having size 32 bits. The '_t' indicates that the representation of the data type will be in two's complement.
int32_t - is a datatype that represents a signed integer having size 32 bits. The '_t' indicates that the representation of the data type will be in two's complement.
uint8_t - is a datatype that represents an unsigned integer having size 16 bits. the '_t' indicates that the representation of the data type will be in two's complement.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE - 1 byte
DWORD - 4 bytes
LONG - 4 bytes
WORD - 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

ASCII - BM
Decimal - 66 77
Hexadecimal - 42 4d

## What's the difference between `bfSize` and `biSize`?

bfSize - tells us the size(in bytes) of the entire bitmap file.
biSize - tells us the size(in bytes) of the BITMAPINFOHEADER structure only.

## What does it mean if `biHeight` is negative?

biHeight is a variable that tells us the height of the bitmap file, in terms of pixels.
If biHeight is negative, it indicates that the bitmap is a top-down type DIB(Device Independent Bitmap), whose origin is the top-left.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

The 'biBitCount' specifies the BMP's colour depth.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

fopen returns NULL when the file open operation is unsuccessful.
In line 24, when we are trying to open the file in read mode(by specifiying "r" in the parameters in the fopen call statement), fopen will return null
if the file does not exist or cannot be read.
In line 32, fopen will return NULL if, for whatever reason, the specified file cannot be opened for writing.

## Why is the third argument to `fread` always `1` in our code?

The third argument of fread tells us the number of elements (of the size mentioned in the second argument) to be read.
Since the size mentioned in the second argument is the size of the structure itself, we want to read only 1 element of the size equal to that of the
structure.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

padding will be assigned the value 3.

## What does `fseek` do?

Syntax of fseek:
int var = fseek(FILE *stream, long int offset, int origin)

fseek moves the position indicator in the file mentioned in the first parameter from the position 'origin' by 'offset' number of positions.
origin can take values SEEK_SET, SEEK_CUR and SEEK_END, which seeks the position indicator to the beginning of the file, its current position, or the
end of the file, respectively.

## What is `SEEK_CUR`?

Sets the reference position for offset to the current position of the position indicator of the file.

## Whodunit?

It was Professor Plum with the candlestick in the library.
