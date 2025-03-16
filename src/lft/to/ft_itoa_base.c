// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_itoa_base.c>>

#include "libft.h"

#define _MAXLEN	66

static inline void	_inc(char *out, size_t *end, const char *base);
static inline char	_next(const char c, const char *base);

char	*ft_itoa_base(i64 n, const char *base) {
	size_t	i;
	char	*out;
	i16		blen;
	i8		sgn;

	blen = ft_strnlen(base, UINT8_MAX);
	out = (blen >= 2) ? ft_malloc(_MAXLEN) : NULL;
	if (out) {
		sgn = (n >= 0) ? 1 : (n != INT64_MIN) ? -1 : -2;
		n = (sgn != -2) ? n * sgn : (n + 1) * -1;
		for (i = 0; n >= blen; n /= blen, i++)
			out[i] = base[n % blen];
		out[i++] = base[n];
		if (sgn < 0) {
			out[i++] = '-';
			if (sgn == -2)
				_inc(out, &i, base);
		}
		out[i] = '\0';
		out = ft_realloc(out, ft_strlen(out) + 1);
		ft_strrev(out);
	}
	return out;
}

static inline void	_inc(char *out, size_t *end, const char *base) {
	size_t	i;

	out[0] = _next(out[0], base);
	for (i = 1; i < *end && out[i - 1] == base[0] && ft_strchr(base, out[i]); i++)
		out[i] = _next(out[i], base);
	if (out[i - 1] == base[0]) {
		out[i++] = base[1];
		out[(*end)++] = '-';
	}
}

static inline char	_next(const char c, const char *base) {
	size_t	i;

	for (i = 0; base[i] && base[i] != c; i++)
		;
	return (base[++i]) ? base[i] : base[0];
}
