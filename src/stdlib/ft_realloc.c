// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_realloc.c>>

#include "internal/ft_stdlib_int.h"

static inline u8	_resize(chunk_t *chnk, const size_t sz);

void	*ft_realloc(void *ptr, size_t sz) {
	chunk_t	*chnk;
	void	*tmp;

	chnk = __get_chnk(ptr);
	if (!_resize(chnk, sz)) {
		tmp = ft_memcpy(ft_malloc(sz), ptr, sz);
		ft_free(ptr);
		ptr = tmp;
	}
	return ptr;
}

static inline u8	_resize(chunk_t *chnk, const size_t sz) {
	chunk_t	*_chnk;
	chunk_t	*tmp;
	size_t	avail;
	bin_t	*bin;

	if (sz < chnk->size) {
		chnk->asize = sz;
		__cs1_loc(chnk, sz) = __cs;
		return 1;
	}
	for (avail = chnk->size, _chnk = chnk->nxt; _chnk && !_chnk->inuse; _chnk = _chnk->nxt)
		avail += _chnk->size + __chnksize;
	if (avail >= sz) {
		tmp = chnk->nfr;
		bin = __get_bin(chnk);
		while (chnk->nfr && chnk->nfr <= _chnk) {
			chnk->nfr = chnk->nfr->nfr;
			bin->musable += __chnksize;
			bin->fcount--;
		}
		if (bin->free == tmp)
			bin->free = chnk->nfr;
		__cs1_loc(chnk, sz) = __cs;
		chnk->size = avail;
		chnk->nxt = _chnk;
		chnk->asize = sz;
		return 1;
	}
	return 0;
}
