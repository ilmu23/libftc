// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<libft_mem.h>>

#ifndef LIBFT_MEM_H
# define LIBFT_MEM_H
# include "internal/libft_defs.h"

void	*ft_calloc(size_t n, size_t sz);

void	*ft_memchr(const void *s, const i32 c, size_t n);
void	*ft_memrchr(const void *s, const i32 c, size_t n);

void	*ft_memcpy(void * restrict dst, const void * restrict src, size_t n);

void	*ft_memmove(void * dst, const void * src, size_t n);

void	*ft_memset(void *s, const i32 c, size_t n);

void	ft_bzero(void *s, size_t n);

i32		ft_memcmp(const void *s1, const void *s2, size_t n);

#endif
