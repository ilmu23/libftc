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

# define __putstr(x)	(ft_putstr_fd(x, 2))
# define __putchar(x)	(ft_putchar_fd(x, 2))
# define __putunbr(x)	(ft_putunbr_fd(x, 2))

# define __cs1_loc(x, y)	(*(u32 *)((uintptr_t)x->addr + y))
# define __cs2_loc(x)		(*(u32 *)((uintptr_t)x->addr - sizeof(x->cs2)))

#define __get_chnk(x)	((chunk_t *)((uintptr_t)x - __chnksize))

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
	u8		fcount;
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

bin_t	*__get_bin(const chunk_t *chnk);

void	__heapinfo(void);
void	__heapvis(void);

# define _HEAPVIS_SGR_BOLD	"\x1b[1m"
# define _HEAPVIS_SGR_RESET	"\x1b[m"

# define _HEAPVIS_BIN_META	"\x1b[38;5;19m"
# define _HEAPVIS_CHNK_META	"\x1b[38;5;75m"
# define _HEAPVIS_CHNK_FREE	"\x1b[38;5;42m"
# define _HEAPVIS_CHNK_USED	"\x1b[38;5;196m"

# define _MALLOC_SMALL_MIN	1
# define _MALLOC_SMALL_MAX	512 - __binsize - __chnksize
# define _MALLOC_MEDIUM_MIN	_MALLOC_SMALL_MAX + 1
# define _MALLOC_MEDIUM_MAX	4096 - __binsize - __chnksize

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
