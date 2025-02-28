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

# define __after(x, n)	((uintptr_t)x + ((sizeof(*x) % 16) ? sizeof(*x) + (16 - (sizeof(*x) % 16)): sizeof(*x)) + n)

static inline chunk_t	*_create_chunk(bin_t *bin, chunk_t *chnk, const size_t size);
static inline void		*_new_chunk(const size_t n, const u8 type, bin_t *bin);
static inline void		*_extend_bin(const size_t n, const u8 type, bin_t *bin, const size_t mtotal);
static inline void		*_init_bin(const size_t n, const u8 type, bin_t *bin, const size_t mtotal);
static inline void		*_alloc_small(const size_t n);
static inline void		*_alloc_medium(const size_t n);
static inline void		*_alloc_large(const size_t n);
static inline void		_shrink_to_fit(chunk_t *chnk, const size_t n, const size_t chnk_min_size, bin_t *bin);
static inline void		_destroy_bin(bin_t **bin, bin_t *prev, const u8 type);
static inline void		_defrag(bin_t *bin);
static inline void		_print_bin(const bin_t *bin, const u32 n, const u8 type);
static inline void		_print_chnk(const chunk_t *chnk, const u32 n);
static inline void		_print_heap(void);

void	*ft_malloc(size_t n) {
	chunk_t	*out;

	if (n == 0)
		return NULL;
	if (__inrange(n, _MALLOC_SMALL_MIN, _MALLOC_SMALL_MAX))
		out = _alloc_small(n);
	else if (__inrange(n, _MALLOC_MEDIUM_MIN, _MALLOC_MEDIUM_MAX))
		out = _alloc_medium(n);
	else
		out =  _alloc_large(n);
	return (out) ? out->addr : NULL;
}

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

static inline chunk_t	*_create_chunk(bin_t *bin, chunk_t *chnk, const size_t size) {
	*chnk = (chunk_t){
		.nxt = NULL,
		.nfr = NULL,
		.size = size,
		.asize = 0,
		.addr = (void *)__after(chnk, 0),
		.inuse = 0,
	};
	__heap.musable -= __chnksize;
	__heap.mfree -= __chnksize;
	bin->musable -= __chnksize;
	bin->mfree -= __chnksize;
	bin->fcount++;
	return chnk;
}

static inline void	*_new_chunk(const size_t n, const u8 type, bin_t *bin) {
	static u64	pgsize;
	bin_t		*newbin;
	size_t		asize;

	if (!pgsize)
		pgsize = ft_sysconf(_SC_PAGESIZE);
	for (asize = 0; asize < n; asize += pgsize)
		;
	asize += (type == _BIN_LARGE && asize - n <= __binsize + __chnksize) ? pgsize : 0;
	newbin = ft_mmap(((bin) ? bin + bin->mtotal : NULL), asize, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	if (newbin == MAP_FAILED)
		return NULL;
	__heap.mtotal += asize;
	__heap.musable += asize - ((!bin || newbin != bin + bin->mtotal) ? __binsize : 0);
	__heap.mfree += asize - ((!bin || newbin != bin + bin->mtotal) ? __binsize : 0);
	if (bin && newbin == bin + bin->mtotal)
		return _extend_bin(n, type, bin, asize);
	return _init_bin(n, type, newbin, asize);
}

static inline void	*_extend_bin(const size_t n, const u8 type, bin_t *bin, const size_t mtotal) {
	chunk_t	*chnk;

	chnk = bin->last;
	bin->mtotal += mtotal;
	bin->musable += mtotal;
	bin->mfree += mtotal;
	if (chnk->inuse) {
		chnk = _create_chunk(bin, (chunk_t *)__after(chnk, chnk->size), mtotal - __chnksize);
		bin->last->nxt = chnk;
		bin->last->nfr = chnk;
		bin->last = chnk;
	} else
		chnk->size += mtotal;
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
	bin->mfree -= chnk->size;
	__heap.mfree -= chnk->size;
	bin->free = chnk->nxt;
	bin->last = chnk->nxt;
	bin->fcount--;
	return chnk;
}

static inline void	*_init_bin(const size_t n, const u8 type, bin_t *bin, const size_t mtotal) {
	chunk_t	*chnk;
	bin_t	*tmp;

	*bin = (bin_t){
		.first = NULL,
		.free = NULL,
		.last = NULL,
		.mtotal = mtotal,
		.musable = mtotal - __binsize,
		.mfree = mtotal - __binsize,
		.next = NULL,
		.fcount = 0
	};
	chnk = _create_chunk(bin, (chunk_t *)__after(bin, 0), mtotal - __binsize - __chnksize);
	bin->first = chnk;
	switch (type) {
		case _CHNK_SMALL:
			_shrink_to_fit(chnk, n, _CHNK_SMALL_MIN_SIZE, bin);
			for (tmp = __heap.sml; tmp && tmp->next; tmp = tmp->next)
				;
			if (tmp)
				tmp->next = bin;
			else
				__heap.sml = bin;
			break ;
		case _CHNK_MEDIUM:
			_shrink_to_fit(chnk, n, _CHNK_MEDIUM_MIN_SIZE, bin);
			for (tmp = __heap.med; tmp && tmp->next; tmp = tmp->next)
				;
			if (tmp)
				tmp->next = bin;
			else
				__heap.med = bin;
			break ;
		case _CHNK_LARGE:
			_shrink_to_fit(chnk, n, _CHNK_LARGE_MIN_SIZE, bin);
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
	bin->mfree -= chnk->size;
	__heap.mfree -= chnk->size;
	bin->free = chnk->nxt;
	bin->fcount--;
	return chnk;
}

static inline void	*_alloc_small(const size_t n) {
	chunk_t	*prev_chnk;
	chunk_t	*chnk;
	bin_t	*prev_bin;
	bin_t	*bin;
	u8		dfrg;

	for (bin = __heap.sml, prev_bin = NULL; bin;) {
		for (dfrg = 0, prev_chnk = NULL, chnk = bin->free; chnk; prev_chnk = chnk, chnk = chnk->nfr)
			if (chnk->size >= n && !chnk->inuse)
				break ;
		if (chnk)
			break ;
		if (!dfrg && bin->free && bin->mfree + (__chnksize * (bin->fcount - 1)) >= n) {
			_defrag(bin);
			dfrg = 1;
		} else {
			prev_bin = bin;
			bin = bin->next;
		}
	}
	if (!bin || !chnk)
		return _new_chunk(n, _CHNK_SMALL, prev_bin);
	_shrink_to_fit(chnk, n, _CHNK_SMALL_MIN_SIZE, bin);
	if (prev_chnk)
		prev_chnk->nfr = chnk->nfr;
	else
		bin->free = chnk->nfr;
	chnk->inuse = 1;
	chnk->asize = n;
	bin->fcount--;
	bin->mfree -= chnk->size;
	__heap.mfree -= chnk->size;
	for (prev_bin = bin, bin = bin->next; bin; prev_bin = bin, bin = bin->next)
		if (bin->mfree == bin->musable)
			_destroy_bin(&bin, prev_bin, _BIN_SMALL);
	return chnk;
}

static inline void	*_alloc_medium(const size_t n) {
	chunk_t	*prev_chnk;
	chunk_t	*chnk;
	bin_t	*prev_bin;
	bin_t	*bin;
	u8		dfrg;

	for (bin = __heap.med, prev_bin = NULL; bin;) {
		for (dfrg = 0, prev_chnk = NULL, chnk = bin->free; chnk; prev_chnk = chnk, chnk = chnk->nfr)
			if (chnk->size >= n && !chnk->inuse)
				break ;
		if (chnk)
			break ;
		if (!dfrg && bin->free && bin->mfree + (__chnksize * (bin->fcount - 1)) >= n) {
			_defrag(bin);
			dfrg = 1;
		} else {
			prev_bin = bin;
			bin = bin->next;
		}
	}
	if (!bin || !chnk)
		return _new_chunk(n, _CHNK_MEDIUM, prev_bin);
	_shrink_to_fit(chnk, n, _CHNK_MEDIUM_MIN_SIZE, bin);
	if (prev_chnk)
		prev_chnk->nfr = chnk->nfr;
	else
		bin->free = chnk->nfr;
	chnk->inuse = 1;
	chnk->asize = n;
	bin->fcount--;
	bin->mfree -= chnk->size;
	__heap.mfree -= chnk->size;
	for (prev_bin = bin, bin = bin->next; bin; prev_bin = bin, bin = bin->next)
		if (bin->mfree == bin->musable)
			_destroy_bin(&bin, prev_bin, _BIN_MEDIUM);
	return chnk;
}

static inline void	*_alloc_large(const size_t n) {
	chunk_t	*prev_chnk;
	chunk_t	*chnk;
	bin_t	*prev_bin;
	bin_t	*bin;
	u8		dfrg;

	for (bin = __heap.lrg, prev_bin = NULL; bin; prev_bin = bin) {
		for (dfrg = 0, prev_chnk = NULL, chnk = bin->free; chnk; prev_chnk = chnk, chnk = chnk->nfr)
			if (chnk->size >= n && !chnk->inuse)
				break ;
		if (chnk)
			break ;
		if (!dfrg && bin->free && bin->mfree + (__chnksize * (bin->fcount - 1)) >= n) {
			_defrag(bin);
			dfrg = 1;
		} else {
			if (bin->mfree == bin->musable)
				_destroy_bin(&bin, prev_bin, _BIN_LARGE);
			bin = bin->next;
		}
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
	bin->fcount--;
	bin->mfree -= chnk->size;
	__heap.mfree -= chnk->size;
	return chnk;
}

static inline void	_shrink_to_fit(chunk_t *chnk, const size_t n, const size_t chnk_min_size, bin_t *bin) {
	chunk_t	*next;
	chunk_t	oldnext;
	size_t	delta;

	for (delta = 0; chnk->size > _MALLOC_MEDIUM_MAX && chnk->size - n > _MALLOC_MEDIUM_MAX; delta += _MALLOC_MEDIUM_MAX)
		chnk->size -= _MALLOC_MEDIUM_MAX;
	for (; chnk->size > _MALLOC_SMALL_MAX && chnk->size - n > _MALLOC_SMALL_MAX; delta += _MALLOC_SMALL_MAX)
		chnk->size -= _MALLOC_SMALL_MAX;
	for (; chnk->size > _MALLOC_SMALL_MAX / 2 && chnk->size - n > _MALLOC_SMALL_MAX / 2; delta += _MALLOC_SMALL_MAX / 2)
		chnk->size -= _MALLOC_SMALL_MAX / 2;
	for (; chnk->size > 16 && chnk->size - n >= 16; delta += 16)
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
			.inuse = 0,
		};
		chnk->nxt = next;
	} else if (delta > chnk_min_size) {
		next = _create_chunk(bin, (chunk_t *)__after(chnk, chnk->size), delta - __chnksize);
		chnk->nxt = next;
		chnk->nfr = next;
	} else
		chnk->size += delta;
	if (bin && next && !next->nxt)
		bin->last = next;
	__cs1_loc(chnk, n) = __cs;
	__cs2_loc(chnk) = __cs;
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
	__heap.mtotal -= _bin->mtotal;
	ft_munmap(_bin, _bin->mtotal);
}

static inline void	_defrag(bin_t *bin) {
	chunk_t	*chnk;
	chunk_t	*tmp;

	for (chnk = bin->first, tmp = chnk->nxt; tmp; tmp = tmp->nxt) {
		if (!chnk->inuse && !tmp->inuse) {
			__heap.musable += __chnksize;
			__heap.mfree += __chnksize;
			bin->musable += __chnksize;
			bin->mfree += __chnksize;
			bin->fcount--;
			*chnk = (chunk_t){
				.nxt = tmp->nxt,
				.nfr = tmp->nfr,
				.size = chnk->size + tmp->size + __chnksize,
				.asize = 0,
				.addr = chnk->addr,
				.inuse = 0,
			};
		} else
			chnk = tmp;
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

static inline void	_print_bin(const bin_t *bin, const u32 n, const u8 type) {
	chunk_t	*chnk;
	u32		_n;

	switch (type) {
		case _BIN_SMALL:
			ft_putstr("\tSMALL BIN ");
			break ;
		case _BIN_MEDIUM:
			ft_putstr("\tMEDIUM BIN ");
			break ;
		case _BIN_LARGE:
			ft_putstr("\tLARGE BIN ");
			break ;
	}
	ft_putunbr(n);
	ft_putstr("\n\t\tTOTAL MEMORY:  ");
	ft_putunbr(bin->mtotal);
	ft_putstr("B\n\t\tUSABLE MEMORY: ");
	ft_putunbr(bin->musable);
	ft_putstr("B\n\t\tFREE MEMORY:   ");
	ft_putunbr(bin->mfree);
	ft_putstr("B\n\t\tFREE CHUNKS:   ");
	ft_putunbr(bin->fcount);
	ft_putstr("\n\n");
	for (chnk = bin->first, _n = 0; chnk; chnk = chnk->nxt, _n++)
		_print_chnk(chnk, _n);
}

static inline void	_print_chnk(const chunk_t *chnk, const u32 n) {
	ft_putstr("\t\tCHUNK ");
	ft_putunbr(n);
	ft_putstr("\n\t\t\tALLOC SIZE: ");
	ft_putunbr(chnk->asize);
	ft_putstr("B\n\t\t\tTOTAL SIZE: ");
	ft_putunbr(chnk->size);
	ft_putstr("B\n\t\t\tIN USE: ");
	ft_putstr((chnk->inuse) ? "YES\n\n" : "NO\n\n");
}

static inline void	_print_heap(void) {
	ft_putstr("---HEAPINFO---\n");
	ft_putstr("\tTOTAL MAPPED MEMORY: ");
	ft_putunbr(__heap.mtotal);
	ft_putstr("B\n\tTOTAL USABLE MEMORY: ");
	ft_putunbr(__heap.musable);
	ft_putstr("B\n\tTOTAL FREE MEMORY:   ");
	ft_putunbr(__heap.mfree);
	ft_putstr("B\n\n");
}
