// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_free.c>>

#include "internal/ft_stdlib_int.h"

#define __get_chnk(x)	((uintptr_t)x - __chnksize)

static inline bin_t	*_get_bin(const chunk_t *chnk);
static inline void	_update_flist(bin_t *bin, chunk_t *chnk);

void	ft_free(void *ptr) {
	chunk_t	*chnk;
	chunk_t	*tmp;
	bin_t	*bin;

	if (!ptr)
		return ;
	chnk = (chunk_t *)__get_chnk(ptr);
	bin = _get_bin(chnk);
	for (tmp = bin->first; tmp < chnk; tmp = tmp->nxt)
		;
	if (tmp != chnk) {
		ft_write(2, "ft_free(): invalid pointer\n", 27);
		// die
		ft_exit(1);
	}
	if (!bin || __cs1_loc(chnk, chnk->asize) != __cs || __cs2_loc(chnk) != __cs) {
		ft_write(2, "ft_free: heap corruption detected\n", 34);
		// die
		ft_exit(1);
	}
	if (!chnk->inuse) {
		ft_write(2, "ft_free: double free\n", 21);
		// die
		ft_exit(1);
	}
	chnk->inuse = 0;
	chnk->asize = 0;
	bin->mfree += chnk->size;
	__heap.mfree += chnk->size;
	_update_flist(bin, chnk);
}

static inline bin_t	*_get_bin(const chunk_t *chnk) {
	bin_t	*bin;

	for (bin = __heap.sml; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)(bin + bin->mtotal)))
			return bin;
	for (bin = __heap.med; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)(bin + bin->mtotal)))
			return bin;
	for (bin = __heap.lrg; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)(bin + bin->mtotal)))
			return bin;
	return NULL;
}

static inline void	_update_flist(bin_t *bin, chunk_t *chnk) {
	chunk_t	*tmp;

	if (chnk < bin->free) {
		chnk->nfr = bin->free;
		bin->free = chnk;
	} else {
		for (tmp = bin->free; tmp->nfr && tmp->nfr < chnk; tmp = tmp->nfr)
			;
		chnk->nfr = tmp->nfr;
		tmp->nfr = chnk;
	}
}
