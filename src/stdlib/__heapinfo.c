// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<__heapinfo.c>>

#include "internal/ft_stdlib_int.h"

static inline void		_print_heap(void);
static inline void		_print_bin(const bin_t *bin, const u32 n, const u8 type);
static inline void		_print_chnk(const chunk_t *chnk, const u32 n);

void	__heapinfo(void) {
	bin_t	*bin;
	u32		n;

	_print_heap();
	for (bin = __heap.sml, n = 0; bin; bin = bin->next, n++)
		_print_bin(bin, n, _BIN_SMALL);
	for (bin = __heap.med, n = 0; bin; bin = bin->next, n++)
		_print_bin(bin, n, _BIN_MEDIUM);
	for (bin = __heap.lrg, n = 0; bin; bin = bin->next, n++)
		_print_bin(bin, n, _BIN_LARGE);
}

static inline void	_print_heap(void) {
	__putstr("---HEAPINFO---\n");
	__putstr("\tTOTAL MAPPED MEMORY: ");
	__putunbr(__heap.mtotal);
	__putstr("B\n\tTOTAL USABLE MEMORY: ");
	__putunbr(__heap.musable);
	__putstr("B\n\tTOTAL FREE MEMORY:   ");
	__putunbr(__heap.mfree);
	__putstr("B\n\n");
}

static inline void	_print_bin(const bin_t *bin, const u32 n, const u8 type) {
	chunk_t	*chnk;
	u32		_n;

	switch (type) {
		case _BIN_SMALL:
			__putstr("\tSMALL BIN ");
			break ;
		case _BIN_MEDIUM:
			__putstr("\tMEDIUM BIN ");
			break ;
		case _BIN_LARGE:
			__putstr("\tLARGE BIN ");
			break ;
	}
	__putunbr(n);
	__putstr("\n\t\tTOTAL MEMORY:  ");
	__putunbr(bin->mtotal);
	__putstr("B\n\t\tUSABLE MEMORY: ");
	__putunbr(bin->musable);
	__putstr("B\n\t\tFREE MEMORY:   ");
	__putunbr(bin->mfree);
	__putstr("B\n\t\tFREE CHUNKS:   ");
	__putunbr(bin->fcount);
	__putstr("\n\n");
	for (chnk = bin->first, _n = 0; chnk; chnk = chnk->nxt, _n++)
		_print_chnk(chnk, _n);
}

static inline void	_print_chnk(const chunk_t *chnk, const u32 n) {
	__putstr("\t\tCHUNK ");
	__putunbr(n);
	__putstr("\n\t\t\tALLOC SIZE: ");
	__putunbr(chnk->asize);
	__putstr("B\n\t\t\tTOTAL SIZE: ");
	__putunbr(chnk->size);
	__putstr("B\n\t\t\tIN USE: ");
	__putstr((chnk->inuse) ? "YES\n\n" : "NO\n\n");
}
