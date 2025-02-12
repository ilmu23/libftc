// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_stdlib_int.h>>


#ifndef FT_STDLIB_INT_H
# define FT_STDLIB_INT_H
# include "libft.h"
# include "ft_mman.h"
# include "ft_stdlib.h"
# include "ft_unistd.h"
# include "internal/defs.h"

typedef struct bin	bin_t;
typedef struct heap	heap_t;
typedef struct chnk	chunk_t;

# define __cs			(0xAAAAAAAA)
# define __binsize		((sizeof(bin_t) % 16) ? (sizeof(bin_t) + (16 - (sizeof(bin_t) % 16))) : sizeof(bin_t))
# define __chnksize		((sizeof(chunk_t) % 16) ? (sizeof(chunk_t) + (16 - (sizeof(chunk_t) % 16))) : sizeof(chunk_t))

# define __cs1_loc(x, y)	(*(u32 *)((uintptr_t)x->addr + y))
# define __cs2_loc(x)		(*(u32 *)((uintptr_t)x->addr - sizeof(x->cs2)))

struct heap {
	bin_t	*sml;
	bin_t	*med;
	bin_t	*lrg;
	size_t	mtotal;
	size_t	musable;
	size_t	mfree;
};

struct bin {
	chunk_t	*first;
	chunk_t	*free;
	chunk_t	*last;
	size_t	mtotal;
	size_t	musable;
	size_t	mfree;
	bin_t	*next;
};

struct chnk {
	u32		cs1;
	chunk_t	*nxt;
	chunk_t	*nfr;
	size_t	size;
	size_t	asize;
	void	*addr;
	u8		inuse;
	u32		cs2;
};

extern heap_t	__heap;

void	__heapinfo(void);

# define _MALLOC_SMALL_MIN	1
# define _MALLOC_SMALL_MAX	512
# define _MALLOC_MEDIUM_MIN	513
# define _MALLOC_MEDIUM_MAX	4096

# define _CHNK_SMALL			1
# define _CHNK_MEDIUM			2
# define _CHNK_LARGE			3
# define _CHNK_SMALL_MIN_SIZE	(__chnksize + 16)
# define _CHNK_MEDIUM_MIN_SIZE	(__chnksize + _MALLOC_SMALL_MAX)
# define _CHNK_LARGE_MIN_SIZE	(__chnksize + _MALLOC_MEDIUM_MAX)

# define _BIN_SMALL		1
# define _BIN_MEDIUM	2
# define _BIN_LARGE		3

#endif
