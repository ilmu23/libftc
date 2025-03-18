// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_free.c>>

#include "internal/ft_stdlib_int.h"

static inline void	_update_flist(bin_t *bin, chunk_t *chnk);

void	ft_free(void *ptr) {
	chunk_t	*chnk;
	chunk_t	*tmp;
	bin_t	*bin;

	if (!ptr)
		return ;
	chnk = __get_chnk(ptr);
	bin = __get_bin(chnk);
	for (tmp = (bin) ? bin->first : NULL; tmp && tmp < chnk; tmp = tmp->nxt)
		;
	if (tmp != chnk) {
		ft_write(2, "ft_free(): invalid pointer\n", 27);
		ft_exit(1); // replace with abort() once implemented
	}
	if (__cs1_loc(chnk, chnk->asize) != __cs || __cs2_loc(chnk) != __cs) {
		ft_write(2, "ft_free: heap corruption detected\n", 34);
		ft_exit(1); // replace with abort() once implemented
	}
	if (!chnk->inuse) {
		ft_write(2, "ft_free: double free\n", 21);
		ft_exit(1); // replace with abort() once implemented
	}
	chnk->inuse = 0;
	chnk->asize = 0;
	bin->fcount++;
	bin->mfree += chnk->size;
	__heap.mfree += chnk->size;
	_update_flist(bin, chnk);
}

static inline void	_update_flist(bin_t *bin, chunk_t *chnk) {
	chunk_t	*tmp;

	if (chnk < bin->free || !bin->free) {
		chnk->nfr = bin->free;
		bin->free = chnk;
	} else {
		for (tmp = bin->free; tmp->nfr && tmp->nfr < chnk; tmp = tmp->nfr)
			;
		chnk->nfr = tmp->nfr;
		tmp->nfr = chnk;
	}
}
