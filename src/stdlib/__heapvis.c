// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<__heapvis.c>>

#include "internal/ft_stdlib_int.h"

#define _CHARLINE	"||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"

#define _LINELENGTH	sizeof(_CHARLINE) - 1

static inline void	_print(size_t n);
static inline void	_binvis(const bin_t *bin, const size_t n, const u8 btype);
static inline void	_vis_chnk(const chunk_t *chnk);
static inline void	_vis_cmeta(void);
static inline void	_vis_bmeta(void);

void	__heapvis(void) {
	const bin_t	*bin;
	size_t		i;

	__putstr("--HEAPVIS--\n\n");
	for (i = 0, bin = __heap.sml; bin; i++, bin = bin->next)
		_binvis(bin, i, _BIN_SMALL);
	for (i = 0, bin = __heap.med; bin; i++, bin = bin->next)
		_binvis(bin, i, _BIN_MEDIUM);
	for (i = 0, bin = __heap.lrg; bin; i++, bin = bin->next)
		_binvis(bin, i, _BIN_LARGE);
}

static inline void	_print(size_t n) {
	static size_t		i;

	for (; i + n > _LINELENGTH;) {
		ft_write(2, _CHARLINE, _LINELENGTH - i);
		__putchar('\n');
		n -= _LINELENGTH - i;
		i = 0;
	}
	ft_write(2, _CHARLINE, n);
	i += n;
}

static inline void	_binvis(const bin_t *bin, const size_t n, const u8 btype) {
	const chunk_t	*chnk;

	switch (btype) {
		case _BIN_SMALL:
			__putstr("SMALL BIN ");
			break ;
		case _BIN_MEDIUM:
			__putstr("MEDIUM BIN ");
			break ;
		case _BIN_LARGE:
			__putstr("LARGE BIN ");
	}
	__putunbr(n);
	__putstr(":\n");
	_vis_bmeta();
	for (chnk = bin->first; chnk; chnk = chnk->nxt) {
		_vis_cmeta();
		_vis_chnk(chnk);
	}
	__putstr(_HEAPVIS_SGR_RESET "\n\n");
}

static inline void	_vis_chnk(const chunk_t *chnk) {
	size_t	b_written;
	size_t	n;

	__putstr((chnk->inuse) ? _HEAPVIS_CHNK_USED : _HEAPVIS_CHNK_FREE);
	for (n = b_written = 0; b_written < chnk->size; n++, b_written += 16)
		;
	_print(n);
}

static inline void	_vis_cmeta(void) {
	__putstr(_HEAPVIS_CHNK_META);
	_print(__chnksize / 16);
}

static inline void	_vis_bmeta(void) {
	__putstr(_HEAPVIS_SGR_BOLD _HEAPVIS_BIN_META);
	_print(__binsize / 16);
}
