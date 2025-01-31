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
static inline void	_defrag(bin_t *bin);

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
	if (!bin || (uintptr_t)chnk->chksum != (uintptr_t)bin) {
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
	bin->fsize += chnk->size;
	__heap.mfree += chnk->size;
	_defrag(bin);
}

static inline bin_t	*_get_bin(const chunk_t *chnk) {
	bin_t	*bin;

	for (bin = __heap.sml; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)(bin + bin->bsize)))
			return bin;
	for (bin = __heap.med; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)(bin + bin->bsize)))
			return bin;
	for (bin = __heap.lrg; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)(bin + bin->bsize)))
			return bin;
	return NULL;
}

static inline void	_defrag(bin_t *bin) {
	chunk_t	*chnk;
	chunk_t	*tmp;

	for (chnk = bin->first, tmp = chnk->nxt; tmp; chnk = tmp, tmp = chnk->nxt) {
		if (!chnk->inuse && !tmp->inuse) {
			bin->bsize += __chnksize;
			bin->fsize += __chnksize;
			__heap.mfree += __chnksize;
			__heap.mtotal += __chnksize;
			*chnk = (chunk_t){
				.nxt = tmp->nxt,
				.nfr = tmp->nfr,
				.size = chnk->size + tmp->size + __chnksize,
				.asize = 0,
				.addr = chnk->addr,
				.chksum = chnk->chksum,
				.inuse = 0
			};
		}
	}
	for (chnk = bin->first, tmp = NULL; chnk; chnk = chnk->nxt) {
		if (!chnk->inuse) {
			if (tmp)
				tmp->nfr = chnk;
			else
				bin->free = chnk;
			tmp = chnk;
		}
		if (!chnk->nxt)
			bin->last = chnk;
	}
}
