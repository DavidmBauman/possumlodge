# possumlodge 

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
DT_String greeting = STR("Hello, world!");
PrintString(greeting);
```

`DT_ARRAY(i32)` expands to:

```c
typedef struct {
    i32* items;
    i32  length;
    i32  capacity;
} i32Array;

internal i32 i32Array_Get(i32Array array, i32 index)
{
    if (index >= 0 && index < array.length)
        return array.items[index];
    return (i32)0;
}
```
ducttape provides this for all int and float types:
`i8 i16 i32 i64`, `u8 u16 u32 u64`, `f32 f64`.

## Strings
`DT_String` is a length aware string that stores a `char*` and a length rather than relying on a null terminator.\
It's taken from Nic Barker's [Tips For C Programming](https://youtu.be/9UIIMBqq1D4)
## Macros
`internal` / `local_persist` / `global_variable`\
These and the typedefs are taken from Casey Muratori's Handmade Hero

## Naming
Types and functions are unprefixed, the DT_ prefix only applies to the generator macro and DT_String struct.