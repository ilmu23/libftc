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
# include "internal/libft_defs.h"

char	*ft_strdup(const char *s);
char	*ft_strndup(const char *s, size_t n);

char	*ft_substr(const char *s, u64 start, size_t len);

char	*ft_strjoin(const char *s1, const char *s2);

char	*ft_strtrim(const char *s, const char *set);

char	*ft_stpcpy(char * restrict dst, const char * restrict src);
char	*ft_strcat(char * restrict dst, const char * restrict src);
char	*ft_strcpy(char * restrict dst, const char * restrict src);

char	*ft_stpncpy(char * restrict dst, const char * restrict src, size_t n);
char	*ft_strncat(char * restrict dst, const char * restrict src, size_t n);
char	*ft_strncpy(char * restrict dst, const char * restrict src, size_t n);

char	*ft_strchr(const char *s, const i32 c);
char	*ft_strrchr(const char *s, const i32 c);

char	*ft_strstr(const char *s1, const char *s2);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

size_t	ft_strlcat(char * restrict dst, const char * restrict src, size_t n);
size_t	ft_strlcpy(char * restrict dst, const char * restrict src, size_t n);

size_t	ft_strlen(const char *s);
size_t	ft_strnlen(const char *s, size_t n);

void	ft_strmod(char *s, i32 (*f)(const i32));

void	ft_strrev(char *s);

i32		ft_strcmp(const char *s1, const char *s2);
i32		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
