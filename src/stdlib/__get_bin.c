// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<__get_bin.c>>

#include "internal/ft_stdlib_int.h"

bin_t	*__get_bin(const chunk_t *chnk) {
	bin_t	*bin;

	for (bin = __heap.sml; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)((uintptr_t)bin + bin->mtotal)))
			return bin;
	for (bin = __heap.med; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)((uintptr_t)bin + bin->mtotal)))
			return bin;
	for (bin = __heap.lrg; bin; bin = bin->next)
		if (__inrange((uintptr_t)chnk, (uintptr_t)bin, (uintptr_t)((uintptr_t)bin + bin->mtotal)))
			return bin;
	return NULL;
}
