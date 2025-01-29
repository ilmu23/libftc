// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_stdint.h>>

#ifndef FT_STDINT_H
# define FT_STDINT_H

// exact-width integer types

/// signed

typedef signed char		int8_t;
typedef signed short	int16_t;
typedef signed int		int32_t;
typedef signed long		int64_t;

/// unsigned

typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef unsigned long	uint64_t;

// Minimun-width integer types

/// signed

typedef int8_t		int_least8_t;
typedef int16_t		int_least16_t;
typedef int32_t		int_least32_t;
typedef int64_t		int_least64_t;

/// unsigned

typedef uint8_t		uint_least8_t;
typedef uint16_t	uint_least16_t;
typedef uint32_t	uint_least32_t;
typedef uint64_t	uint_least64_t;

// Fastest minimum-width integer types

/// signed

typedef int8_t		int_fast8_t;
typedef int64_t		int_fast16_t;
typedef	int64_t		int_fast32_t;
typedef int64_t		int_fast64_t;

/// unsigned

typedef uint8_t		uint_fast8_t;
typedef uint64_t	uint_fast16_t;
typedef	uint64_t	uint_fast32_t;
typedef uint64_t	uint_fast64_t;

// Object pointer types

typedef int64_t		intptr_t;
typedef uint64_t	uintptr_t;

// Greates-width integer types

typedef int64_t		intmax_t;
typedef uint64_t	uintmax_t;

// Limits

# define INT8_MIN	-0x80
# define INT16_MIN	-0x8000
# define INT32_MIN	-0x80000000
# define INT64_MIN	-0x8000000000000000

# define INT8_MAX	-(INT8_MIN) - 1
# define INT16_MAX	-(INT16_MIN) - 1
# define INT32_MAX	-(INT32_MIN) - 1
# define INT64_MAX	-(INT64_MIN) - 1

# define UINT8_MAX	0xFF
# define UINT16_MAX	0xFFFF
# define UINT32_MAX	0xFFFFFFFF
# define UINT64_MAX 0xFFFFFFFFFFFFFFFF

# define INT_LEAST8_MIN		INT8_MIN
# define INT_LEAST16_MIN	INT16_MIN
# define INT_LEAST32_MIN	INT32_MIN
# define INT_LEAST64_MIN	INT64_MIN

# define INT_LEAST8_MAX		INT8_MAX
# define INT_LEAST16_MAX	INT16_MAX
# define INT_LEAST32_MAX	INT32_MAX
# define INT_LEAST64_MAX	INT64_MAX

# define INT_FAST8_MIN	INT8_MIN
# define INT_FAST16_MIN	INT16_MIN
# define INT_FAST32_MIN	INT32_MIN
# define INT_FAST64_MIN	INT64_MIN

# define INT_FAST8_MAX	INT8_MAX
# define INT_FAST16_MAX	INT16_MAX
# define INT_FAST32_MAX	INT32_MAX
# define INT_FAST64_MAX	INT64_MAX

# define INTPTR_MIN		INT64_MIN
# define INTPTR_MAX		INT64_MAX
# define UINTPTR_MAX	UINT64_MAX

# define INTMAX_MIN		INT64_MIN
# define INTMAX_MAX		INT64_MAX
# define UINTMAX_MAX	UINT64_MAX

# define SIZE_MAX		UINT64_MAX
# define SSIZE_MAX		INT64_MAX

// Integer constant expression macros

/// signed

# define INT8_C(c)	c
# define INT16_C(c)	c
# define INT32_C(c)	c
# define INT64_C(c)	c ## L

/// unsigned

# define UINT8_C(c)		c ## U
# define UINT16_C(c)	c ## U
# define UINT32_C(c)	c ## U
# define UINT64_C(c)	c ## UL

/// max

# define INTMAX_C(c)	c ## L
# define UINTMAX_C(c)	c ## UL

#endif
