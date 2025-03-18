// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_atoi_base.c>>

#include "libft.h"

i64	ft_atoi_base(const char *n, const char *base) {
	char	*nbr;
	i64		out;
	i64		lmt;
	i16		blen;
	i8		sgn;

	blen = ft_strnlen(base, UINT8_MAX);
	while (ft_isspace(*n))
		n++;
	sgn = (*n != '-') ? 1 : -1;
	if ((*n == '+') | (*n == '-'))
		n++;
	for (out = 0, lmt = INT64_MAX / blen, nbr = ft_strchr(base, *n++); nbr; nbr = ft_strchr(base, *n++)) {
		if ((out > lmt) | ((out == lmt) & (pcast(i64, (nbr - base)) > INT64_MAX % blen))) {
			if ((sgn == -1) & ((u64)(out * blen + pcast(i64, (nbr - base))) <= (u64)INT64_MIN)) {
				out = -out * blen - pcast(i64, (nbr - base));
				return out;
			}
			return (sgn == 1) ? -1 : 0;
		}
		out = out * blen + pcast(i64, (nbr - base));
	}
	return out * sgn;
}
