# Duct Tape 

*"Quando omni flunkus, moritati."*

If you're the kind of person who enjoys spending your quality family time programming, you know, by yourself, you're really gonna love the project on this week's Handyman's Corner.

Sure they've got fancy languages, like Rust, Go, or Odin, but are any of them as comfortable as good old C? No sir.
So I say we take some of the comfort out of those languages and put her into C. 

So what we're gonna do is take that new String system and just attach it right to the side of our language here.
Don't forget to tape on the new print function with it.

Then how about we throw in some of those sized typedefs, hey. 

Here's a cheap way to fix those array access issues. We'll just pop on a bounds-checked array access.

And remember, if the women don't find you handsome, they should at least find you handy.

## Overview
`ducttape.c` is a single file, dependency free C utility library. It provides length based strings, bounds checked arrays, sized integer and float typedefs, along with a handful of convenience macros.

It's written in unity build style. Just include `ducttape.c` directly into the file rather than compiling and linking it separately.

## Usage
 
```c
#include "ducttape.c"
 
int main(void)
{
    DT_String greeting = STR("Hello, world!");
    PrintString(greeting);

    return 0;
}
```
 
## Strings
 
`DT_String` is a length-aware string that stores a `char*` and a length rather than relying on a null terminator, so getting the length is O(1) and substrings can be zero-copy views into a bigger buffer.
 
```c
DT_String a = STR("compile-time literal");   // length from sizeof
DT_String b = StringFromCString(runtime_ptr); // length from a strlen-style walk
PrintString(a);                               // prints via %.*s, no terminator needed
```
 
Taken from Nic Barker's [Tips for C Programming](https://youtu.be/9UIIMBqq1D4).
 
## Typed Arrays
 
`DT_ARRAY(T)` generates a fixed-capacity array type plus `Get`, `Set`, and `Push` for one element type. You provide the backing storage; `length` tracks how full it is, `capacity` is the ceiling.
 
```c
DT_ARRAY(i32)   // generates i32Array, i32Array_Get, i32Array_Set, i32Array_Push
```
 
Provided for all integer and float types: `i8 i16 i32 i64`, `u8 u16 u32 u64`, `f32 f64`.
 
Accessors bounds-check with `assert`, so a bad index crashes at the mistake instead of failing silently. The checks compile out under `-DNDEBUG` for release builds.
 
## Macros
 
`internal` / `local_persist` / `global_variable` name the three jobs of `static`. Alongside `Kilobytes`–`Terabytes`, `ArrayCount`, and the sized typedefs, these are taken from Casey Muratori's [Handmade Hero](https://guide.handmadehero.org/).
 
## Naming
 
Types and functions are unprefixed (`DT_String`, `i32Array`, `PrintString`). The `DT_` prefix applies only to the generator macro `DT_ARRAY` and the `DT_String` struct.
 