// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_memset.c>>

#include "libft.h"

void	*ft_memset(void *s, const i32 c, size_t n) {
	size_t	i;
	u64		c64;

	for (i = 0; n % 8; i++, n--)
		*pcast(u8 *, poffset(s, i)) = (u8)c;
	if (n) {
		c64 = (u8)c;
		c64 |= c64 << 8;
		c64 |= c64 << 16;
		c64 |= c64 << 32;
		for (; n; i += 8, n -= 8)
			*pcast(u64 *, poffset(s, i)) = c64;
	}
	return s;
}
