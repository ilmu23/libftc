// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<libft_str.h>>

#ifndef LIBFT_STR_H
# define LIBFT_STR_H
# include "ft_stddef.h"

char	*ft_stpcpy(char * restrict dst, const char * restrict src);
char	*ft_strcat(char * restrict dst, const char * restrict src);
char	*ft_strcpy(char * restrict dst, const char * restrict src);

char	*ft_stpncpy(char * restrict dst, const char * restrict src, size_t n);
char	*ft_strncat(char * restrict dst, const char * restrict src, size_t n);
char	*ft_strncpy(char * restrict dst, const char * restrict src, size_t n);

size_t	ft_strlcat(char * restrict dst, const char * restrict src, size_t n);
size_t	ft_strlcpy(char * restrict dst, const char * restrict src, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t n);

#endif
