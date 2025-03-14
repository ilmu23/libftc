// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_strlcat.c>>

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t n) {
	size_t	dlen;
	size_t	slen;

	dlen = ft_strnlen(dst, n);
	if (dlen < n) {
		slen = ft_strnlen(src, n - dlen - 1);
		ft_memcpy((void *)((uintptr_t)dst + dlen), src, slen);
		dst[slen + dlen] = '\0';
	}
	return dlen + ft_strlen(src);
}
