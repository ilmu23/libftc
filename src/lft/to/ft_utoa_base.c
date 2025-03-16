// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_utoa_base.c>>

#include "libft.h"

#define _MAXLEN	65

char	*ft_utoa_base(u64 n, const char *base) {
	size_t	i;
	char	*out;
	u8		blen;

	blen = ft_strnlen(base, UINT8_MAX);
	out = (blen >= 2) ? ft_malloc(_MAXLEN) : NULL;
	if (out) {
		blen = ft_strnlen(base, UINT8_MAX);
		for (i = 0; n >= blen; n /= blen, i++)
			out[i] = base[n % blen];
		out[i++] = base[n];
		out[i] = '\0';
		out = ft_realloc(out, ft_strlen(out) + 1);
		ft_strrev(out);
	}
	return out;
}
