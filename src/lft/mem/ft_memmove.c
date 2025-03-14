// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_memmove.c>>

#include "libft.h"

#define _FWD	0
#define _BCK	1

void	*ft_memmove(void *dst, const void *src, size_t n) {
	size_t	i;
	u8		d;

	if (!dst | !src)
		return dst;
	d = (dst < src) ? _FWD : _BCK;
	for (i = (d == _FWD) ? 0 : n; n >= 8; i = (d == _FWD) ? i + 8 : i - 8, n -= 8)
		*pcast(u64 *, poffset(dst, ((d == _FWD) ? i : i - 8))) = *pcast(u64 *, poffset(src, ((d == _FWD) ? i : i - 8)));
	for (; n; i = (d == _FWD) ? i + 1 : i - 1, n--)
		*pcast(u8 *, poffset(dst, ((d == _FWD) ? i : i - 1))) = *pcast(u8 *, poffset(src, ((d == _FWD) ? i : i - 1)));
	return dst;
}
