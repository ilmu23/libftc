// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_split.c>>

#include "libft.h"

static inline size_t	_splitcount(const char *s, const i32 c);

char	**ft_split(const char *s, const i32 c) {
	size_t	start;
	size_t	end;
	size_t	cnt;
	size_t	i;
	char	**out;

	if (!s)
		return NULL;
	cnt = _splitcount(s, c);
	out = ft_malloc((cnt + 1) * sizeof(*out));
	if (out) {
		out[cnt] = NULL;
		for (start = i = 0; i < cnt; i++, start = end) {
			while (s[start] == c)
				start++;
			for (end = start + 1; s[end] && s[end] != c; end++)
				;
			out[i] = ft_substr(s, start, end - start);
			if (!out[i]) {
				while (i--)
					ft_free(out[i]);
				ft_free(out);
				return NULL;
			}
		}
	}
	return out;
}

static inline size_t	_splitcount(const char *s, const i32 c) {
	size_t	n;
	u8		sep;

	if (c == '\0')
		return 1;
	for (n = 0, sep = 1; *s; s++) {
		if (*s == c)
			sep = 1;
		else if (sep) {
			sep = 0;
			n++;
		}
	}
	return n;
}
