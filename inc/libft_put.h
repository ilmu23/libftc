// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<libft_put.h>>

#ifndef LIBFT_PUT_H
# define LIBFT_PUT_H
# include "ft_types.h"
# include "internal/libft_defs.h"

ssize_t	ft_putstr(const char *s);
ssize_t	ft_putstr_fd(const char *s, const i32 fd);

ssize_t	ft_putsnbr(const i64 n);
ssize_t	ft_putsnbr_fd(const i64 n, const i32 fd);

ssize_t	ft_putunbr(const u64 n);
ssize_t	ft_putunbr_fd(const u64 n, const i32 fd);

ssize_t	ft_putchar(const u8 c);
ssize_t	ft_putchar_fd(const u8 c, const i32 fd);

ssize_t	ft_putendl(const char *s);
ssize_t	ft_putendl_fd(const char *s, const i32 fd);

#endif
