// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_atou_base.c>>

#include "libft.h"

u64	ft_atou_base(const char *n, const char *base) {
	char	*nbr;
	u64		out;
	u64		lmt;
	u8		blen;

	blen = ft_strnlen(base, UINT8_MAX);
	while (ft_isspace(*n))
		n++;
	for (out = 0, lmt = UINT64_MAX / blen, nbr = ft_strchr(base, *n++); nbr; nbr = ft_strchr(base, *n++)) {
		if ((out > lmt) | ((out == lmt) & (pcast(u64, (nbr-base)) > UINT64_MAX % blen)))
			return 0;
		out = out * blen + pcast(u64, (nbr - base));
	}
	return out;
}
