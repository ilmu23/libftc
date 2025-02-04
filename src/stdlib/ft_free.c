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
	if (!bin || chnk->cs1 != __cs1(bin) || chnk->cs2 != __cs2(bin)) {
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
