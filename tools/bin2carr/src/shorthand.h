#ifndef MIC_SHORTHAND_H
#define MIC_SHORTHAND_H

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

//
// This simple header just typedefs the basic C define types to a shorter name,
// loads the quality of life bool macro for _Bool and defines shorthand macros
// for byte sizes.  We need that the targeted architecture uses the floating
// point representation as described on the IEEE-754 standard.
//

_Static_assert(sizeof(double) == 8, "no support for IEEE-754");
_Static_assert(sizeof(float) == 4, "no support for IEEE-754");

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef float f32;
typedef double f64;

#define KB(N) ((u64)(N) * 1024)
#define MB(N) ((u64)KB(N) * 1024)
#define GB(N) ((u64)MB(N) * 1024)
#define TB(N) ((u64)GB(N) * 1024)

#endif // MIC_SHORTHAND_H
