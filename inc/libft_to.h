// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<libft_to.h>>

#ifndef LIBFT_TO_H
# define LIBFT_TO_H
# include "internal/libft_defs.h"

#define ft_itoa	ft_itoa32
#define ft_utoa	ft_utoa32

char	*ft_itoa8(i8 n);
char	*ft_itoa16(i16 n);
char	*ft_itoa32(i32 n);
char	*ft_itoa64(i64 n);
char	*ft_itoa_base(i64 n, const char *base);

char	*ft_utoa8(u8 n);
char	*ft_utoa16(u16 n);
char	*ft_utoa32(u32 n);
char	*ft_utoa64(u64 n);
char	*ft_utoa_base(u64 n, const char *base);

i32		ft_tolower(const i32 c);
i32		ft_toupper(const i32 c);

#endif
