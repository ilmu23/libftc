// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<libft_defs.h>>

#ifndef LIBFT_DEFS_H
# define LIBFT_DEFS_H
# include "ft_stddef.h"
# include "ft_stdint.h"

// swap values of x and y
# define swap(x, y)	(x ^= y, y ^= x, x ^= y)

// cast to/from pointer types
# define pcast(t, x)	((t)(uintptr_t)x)

// offset pointer by n bytes
# define poffset(p, n)	((void *)((uintptr_t)p + (n)))

// check if x is between y and z
# define inrange(x, y, z)	(((x >= y) & (x <= z)) ? 1 : 0)

typedef int8_t		i8;
typedef	int16_t		i16;
typedef	int32_t		i32;
typedef	int64_t		i64;

typedef uint8_t		u8;
typedef	uint16_t	u16;
typedef	uint32_t	u32;
typedef	uint64_t	u64;

#endif
