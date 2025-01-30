// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_malloc.c>>

#include "internal/ft_stdlib_int.h"

heap_t	__heap;

# define __after(x, n)	((uintptr_t)x + (sizeof(*x) % 16) ? sizeof(*x) + (16 - (sizeof(*bin) % 16)): sizeof(*x) + n)

static inline void	*_new_chunk(const size_t n, const u8 type, bin_t *bin);
static inline void	*_extend_bin(const size_t n, const u8 type, bin_t *bin, const size_t bsize);
static inline void	*_init_bin(const size_t n, const u8 type, bin_t *bin, const size_t bsize);
static inline void	*_alloc_small(const size_t n);
static inline void	*_alloc_medium(const size_t n);
static inline void	*_alloc_large(const size_t n);
static inline void	_shrink_to_fit(chunk_t *chnk, const size_t n, const size_t chnk_min_size, bin_t *bin);
static inline void	_destroy_bin(bin_t **bin, bin_t *prev, const u8 type);

void	*ft_malloc(size_t n) {
	if (n == 0)
		return NULL;
	if (__inrange(n, _MALLOC_SMALL_MIN, _MALLOC_SMALL_MAX))
		return _alloc_small(n);
	if (__inrange(n, _MALLOC_MEDIUM_MIN, _MALLOC_MEDIUM_MAX))
		return _alloc_medium(n);
	return _alloc_large(n);
}

static inline void	*_new_chunk(const size_t n, const u8 type, bin_t *bin) {
	static u64	pgsize;
	bin_t		*newbin;
	size_t		asize;

	if (!pgsize)
		pgsize = ft_sysconf(_SC_PAGESIZE);
	for (asize = 0; asize < n; asize += pgsize)
		;
	newbin = ft_mmap((bin) ? bin + bin->bsize : NULL, asize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (newbin == MAP_FAILED)
		return NULL;
	__heap.mfree += asize;
	__heap.mtotal += asize;
	if (bin && newbin == bin + bin->bsize)
		return _extend_bin(n, type, bin, asize);
	return _init_bin(n, type, newbin, asize);
}

static inline void	*_extend_bin(const size_t n, const u8 type, bin_t *bin, const size_t bsize) {
	chunk_t	*chnk;

	chnk = bin->last;
	if (chnk->inuse) {
		chnk = (chunk_t *)__after(chnk, chnk->size);
		*chnk = (chunk_t){
			.nxt = NULL,
			.nfr = NULL,
			.size = bsize,
			.asize = 0,
			.addr = (void *)__after(chnk, 0),
			.chksum = (uintptr_t)bin,
			.inuse = 0
		};
		bin->last->nxt = chnk;
		bin->last->nfr = chnk;
		bin->last = chnk;
	} else
		chnk->size += bsize;
	switch (type) {
		case _CHNK_SMALL:
			_shrink_to_fit(chnk, n, _CHNK_SMALL_MIN_SIZE, bin);
			break ;
		case _CHNK_MEDIUM:
			_shrink_to_fit(chnk, n, _CHNK_MEDIUM_MIN_SIZE, bin);
			break ;
		case _CHNK_LARGE:
			_shrink_to_fit(chnk, n, _CHNK_LARGE_MIN_SIZE, bin);
			break ;
	}
	chnk->inuse = 1;
	chnk->asize = n;
	bin->bsize += bsize;
	bin->fsize += bsize - chnk->size;
	__heap.mfree -= chnk->size;
	bin->free = chnk->nxt;
	bin->last = chnk->nxt;
	return chnk;
}

static inline void	*_init_bin(const size_t n, const u8 type, bin_t *bin, const size_t bsize) {
	chunk_t	*chnk;
	bin_t	*tmp;

	*bin = (bin_t){
		.bsize = bsize,
		.fsize = bsize,
		.next = NULL
	};
	chnk = (chunk_t *)__after(bin, 0);
	*chnk = (chunk_t){
		.nxt = NULL,
		.nfr = NULL,
		.size = bsize - sizeof(*bin),
		.asize = 0,
		.addr = (void *)__after(chnk, 0),
		.chksum = (uintptr_t)bin,
		.inuse = 0
	};
	bin->first = chnk;
	switch (type) {
		case _CHNK_SMALL:
			_shrink_to_fit(chnk, n, _CHNK_SMALL_MIN_SIZE, NULL);
			for (tmp = __heap.sml; tmp && tmp->next; tmp = tmp->next)
				;
			if (tmp)
				tmp->next = bin;
			else
				__heap.sml = bin;
			break ;
		case _CHNK_MEDIUM:
			_shrink_to_fit(chnk, n, _CHNK_MEDIUM_MIN_SIZE, NULL);
			for (tmp = __heap.med; tmp && tmp->next; tmp = tmp->next)
				;
			if (tmp)
				tmp->next = bin;
			else
				__heap.med = bin;
			break ;
		case _CHNK_LARGE:
			_shrink_to_fit(chnk, n, _CHNK_LARGE_MIN_SIZE, NULL);
			for (tmp = __heap.lrg; tmp && tmp->next; tmp = tmp->next)
				;
			if (tmp)
				tmp->next = bin;
			else
				__heap.lrg = bin;
			break ;
	}
	chnk->inuse = 1;
	chnk->asize = n;
	bin->fsize -= chnk->size;
	__heap.mfree -= chnk->size;
	bin->free = chnk->nxt;
	bin->last = chnk->nxt;
	return chnk;
}

static inline void	*_alloc_small(const size_t n) {
	chunk_t	*prev_chnk;
	chunk_t	*chnk;
	bin_t	*prev_bin;
	bin_t	*bin;

	for (bin = __heap.sml; bin; bin = bin->next) {
		for (prev_chnk = NULL, chnk = bin->free; chnk; prev_chnk = chnk, chnk = chnk->nfr)
			if (chnk->size >= n && !chnk->inuse)
				break ;
	}
	if (!bin || !chnk)
		return _new_chunk(n, _CHNK_SMALL, bin);
	_shrink_to_fit(chnk, n, _CHNK_SMALL_MIN_SIZE, bin);
	if (prev_chnk)
		prev_chnk->nfr = chnk->nfr;
	else
		bin->free = chnk->nfr;
	chnk->inuse = 1;
	chnk->asize = n;
	bin->fsize -= chnk->size;
	__heap.mfree -= chnk->size;
	for (prev_bin = bin, bin = bin->next; bin; prev_bin = bin, bin = bin->next)
		if (bin->fsize == bin->bsize)
			_destroy_bin(&bin, prev_bin, _BIN_SMALL);
	return chnk;
}

static inline void	*_alloc_medium(const size_t n) {
	chunk_t	*prev_chnk;
	chunk_t	*chnk;
	bin_t	*prev_bin;
	bin_t	*bin;

	for (bin = __heap.med; bin; bin = bin->next) {
		for (prev_chnk = NULL, chnk = bin->free; chnk; prev_chnk = chnk, chnk = chnk->nfr)
			if (chnk->size >= n && !chnk->inuse)
				break ;
	}
	if (!bin || !chnk)
		return _new_chunk(n, _CHNK_MEDIUM, bin);
	_shrink_to_fit(chnk, n, _CHNK_MEDIUM_MIN_SIZE, bin);
	if (prev_chnk)
		prev_chnk->nfr = chnk->nfr;
	else
		bin->free = chnk->nfr;
	chnk->inuse = 1;
	chnk->asize = n;
	bin->fsize -= chnk->size;
	__heap.mfree -= chnk->size;
	for (prev_bin = bin, bin = bin->next; bin; prev_bin = bin, bin = bin->next)
		if (bin->fsize == bin->bsize)
			_destroy_bin(&bin, prev_bin, _BIN_MEDIUM);
	return chnk;
}

static inline void	*_alloc_large(const size_t n) {
	chunk_t	*prev_chnk;
	chunk_t	*chnk;
	bin_t	*prev_bin;
	bin_t	*bin;

	for (bin = __heap.lrg, prev_bin = NULL; bin; prev_bin = bin, bin = bin->next) {
		for (prev_chnk = NULL, chnk = bin->free; chnk; prev_chnk = chnk, chnk = chnk->nfr)
			if (chnk->size >= n && !chnk->inuse)
				break ;
		if (bin->fsize == bin->bsize)
			_destroy_bin(&bin, prev_bin, _BIN_LARGE);
	}
	if (!bin || !chnk)
		return _new_chunk(n, _CHNK_LARGE, bin);
	_shrink_to_fit(chnk, n, _CHNK_LARGE_MIN_SIZE, bin);
	if (prev_chnk)
		prev_chnk->nfr = chnk->nfr;
	else
		bin->free = chnk->nfr;
	chnk->inuse = 1;
	chnk->asize = n;
	bin->fsize -= chnk->size;
	__heap.mfree -= chnk->size;
	return chnk;
}

static inline void	_shrink_to_fit(chunk_t *chnk, const size_t n, const size_t chnk_min_size, bin_t *bin) {
	chunk_t	*next;
	chunk_t	oldnext;
	size_t	delta;

	for (delta = 0; chnk->size > _MALLOC_MEDIUM_MAX && chnk->size - n - delta > _MALLOC_MEDIUM_MAX; delta += _MALLOC_MEDIUM_MAX)
		chnk->size -= _MALLOC_MEDIUM_MAX;
	for (delta = 0; chnk->size > _MALLOC_SMALL_MAX && chnk->size - n - delta > _MALLOC_SMALL_MAX; delta += _MALLOC_SMALL_MAX)
		chnk->size -= _MALLOC_SMALL_MAX;
	for (delta = 0; chnk->size > _MALLOC_SMALL_MAX / 2 && chnk->size - n - delta > _MALLOC_SMALL_MAX / 2; delta += _MALLOC_SMALL_MAX / 2)
		chnk->size -= _MALLOC_SMALL_MAX / 2;
	for (delta = 0; chnk->size > 16 && chnk->size - n > 16; delta += 16)
		chnk->size -= 16;
	next = NULL;
	if (chnk->nxt) {
		oldnext = *chnk->nxt;
		next = (chunk_t *)__after(chnk, chnk->size);
		*next = (chunk_t){
			.nxt = oldnext.nxt,
			.nfr = oldnext.nfr,
			.size = oldnext.size + delta,
			.asize = 0,
			.addr = (void *)((uintptr_t)oldnext.addr - delta),
			.chksum = (uintptr_t)bin,
			.inuse = 0
		};
	} else if (delta > chnk_min_size) {
		next = (chunk_t *)__after(chnk, chnk->size);
		*next = (chunk_t){
			.nxt = NULL,
			.nfr = NULL,
			.size = delta - sizeof(*chnk),
			.asize = 0,
			.addr = (void *)__after(next, 0),
			.chksum = (uintptr_t)bin,
			.inuse = 0
		};
	} else
		chnk->size += delta;
	if (bin && next && !next->nxt)
		bin->last = next;
}

static inline void	_destroy_bin(bin_t **bin, bin_t *prev, const u8 type) {
	bin_t	*_bin;

	_bin = *bin;
	*bin = _bin->next;
	if (!prev) {
		switch (type) {
			case _BIN_SMALL:
				prev = __heap.sml;
				break ;
			case _BIN_MEDIUM:
				prev = __heap.med;
				break ;
			case _BIN_LARGE:
				prev = __heap.lrg;
				break ;
		}
	}
	prev->next = *bin;
	if (!*bin)
		*bin = prev;
	__heap.mtotal -= _bin->bsize;
	ft_munmap(_bin, _bin->bsize);
}
