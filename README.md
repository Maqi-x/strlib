# strlib
strlib is a minimal string library for C.
It consists of two main "classes": string view and string buffer.

- **`sv` (string view)** is simply a view into data that exists somewhere else.
It consists of a pointer (`const char* data`) and a length (`size_t len`).
Because of this, it features value semantics.

- **`sb` (string buffer)** is an owned string, which is basically just a dynamic array of characters.

The whole library is written in just two header files and one .c file.

Functions are prefixed with `sv_` and `sb_`, while the corresponding
types are `StringView` and `StringBuf`.

## Why?
These tools are so fundamental (hate null-terminated strings btw) that I need them in a huge number of my personal projects.
Until now, I would just copy-paste the implementation from one project to another and run `%s/old_/new_/g`.

I just got tired of doing that, so this library was born.

And why didn't I use an existing library with this functionality?
Because I couldn't find a single one that I actually liked (who on earth comes up with function names as long as `new_string_view_from_cstr`???).

"Then Why you use C?" because i can.

## Build system
There's no build system. This library is dead simple and, as I mentioned, consists of just 3 files, so I don't think it needs one.

How do you use it then? You add it to your project as a git submodule, create your own `sb.c` file in your
`src/` directory (or wherever you want), integrate it with your build system, and drop this inside:

```c
#include <strlib/sb.c>
```
also add -I<path to submodule>/src to your compiler flags, and you're good to go!

## Usage
**Minimal example:**
```c
#include <strlib/sv.h>
#include <strlib/sb.h>
#include <stdio.h>

int main() {
    StringView str = SV("Hello, World!");
    StringView hello = sv_slice(str, 0, 5);

    sv_print(str, stdout);
    printf("My string printed using printf: "SV_FMT, SV_FARG(hello));

    StringBuf buf;
    sb_init_from(&buf, hello);
    sb_append(&buf, SV(", Universe!"));

    StringView view = sb_view(&buf);
    sv_print(view, stdout);

    sb_free(&buf);
}
```
For all library capabilities just look at the source code.
