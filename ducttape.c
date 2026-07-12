#pragma once

#include <stdint.h>
#include <stdio.h>

#define internal        static
#define local_persist   static
#define global_variable static

#define Kilobytes(Value) ((Value)*1024LL)
#define Megabytes(Value) (Kilobytes(Value)*1024LL)
#define Gigabytes(Value) (Megabytes(Value)*1024LL)
#define Terabytes(Value) (Gigabytes(Value)*1024LL)

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float    f32;
typedef double   f64;
typedef i32      bool32;

typedef struct {
    char* chars;
    i32   length;
} DT_String;

// Runtime constructor of DT_Strings.
// Has to take null terminated char*
internal DT_String StringFromCString(char* cstr)
{
    i32 len = 0;
    while(cstr[len]) len++;
    return(DT_String){ cstr, len };
}

// Compile time definition of DT_Strings
#define STR(literal) (DT_String){ (literal), (i32)(sizeof(literal) - 1) }

/* Usage:
       DT_String greeting = STR("Keep your stick on the ice.");
       PrintString(greeting);        // prints: Keep your stick on the ice.

   Or inline, without a named variable:
       PrintString(STR("Quando omni flunkus moritati\n"));
*/

internal void PrintString(DT_String string)
{
    /* %.*s prints exactly length bytes; no null-terminator needed. */
    printf("%.*s", string.length, string.chars);
}

/* DT_ARRAY(i32) expands to:
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
*/
/* Defines the struct + getter for one element type. */

#define DT_ARRAY(T)                                        \
    typedef struct {                                       \
        T*  items;                                         \
        i32 length;                                        \
        i32 capacity;                                      \
    } T##Array;                                            \
    internal T T##Array_Get(T##Array array, i32 index)     \
    {                                                      \
        if (index >= 0 && index < array.length)            \
            return array.items[index];                     \
        return (T)0;                                        \
    }

DT_ARRAY(i8)
DT_ARRAY(i16)
DT_ARRAY(i32)
DT_ARRAY(i64)
DT_ARRAY(u8)
DT_ARRAY(u16)
DT_ARRAY(u32)
DT_ARRAY(u64)
DT_ARRAY(f32)
DT_ARRAY(f64)