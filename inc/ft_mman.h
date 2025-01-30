// ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
// ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
// █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
// ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
// ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
// ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
//
// <<ft_mman.h>>


#ifndef FT_MMAN_H
# define FT_MMAN_H
# include "ft_types.h"
# include "ft_stddef.h"

void	*ft_mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

int		ft_mlock(const void *addr, size_t len);
int		ft_mlockall(int flags);
int		ft_mprotect(void *addr, size_t len, int prot);
int		ft_msync(void *addr, size_t len, int flags);
int		ft_munlock(const void *addr, size_t len);
int		ft_munlockall(void);
int		ft_munmap(void *addr, size_t len);

# define MAP_FAILED	((void *)-1)

// prot

# define PROT_READ	0x1
# define PROT_WRITE	0x2
# define PROT_EXEC	0x4
# define PROT_NONE	0x0

# define PROT_GROWSDOWN	0x01000000
# define PROT_GROWSUP	0x02000000

// flags

# define MAP_SHARED				0x00001
# define MAP_PRIVATE			0x00002
# define MAP_SHARED_VALIDATE	0x00003
# define MAP_TYPE				0x0000F
# define MAP_FIXED				0x00010
# define MAP_FILE				0x00000
# define MAP_ANONYMOUS			0x00020
# define MAP_GROWSDOWN			0x00100
# define MAP_DENYWRITE			0x00800
# define MAP_EXECUTABLE			0x01000
# define MAP_LOCKED				0x02000
# define MAP_NORESERVE			0x04000
# define MAP_POPULATE			0x08000
# define MAP_NONBLOCK			0x10000
# define MAP_STACK				0x20000
# define MAP_HUGETLB			0x40000
# define MAP_SYNC				0x80000
# define MAP_FIXED_NOREPLACE	0x100000

/// HUGETLB

# define MAP_HUGE_SHIFT	26
# define MAP_HUGE_MASK	0x3F
# define MAP_HUDE_16KB	(14U << MAP_HUGE_SHIFT)
# define MAP_HUDE_64KB	(16U << MAP_HUGE_SHIFT)
# define MAP_HUDE_512KB	(19U << MAP_HUGE_SHIFT)
# define MAP_HUDE_1MB	(20U << MAP_HUGE_SHIFT)
# define MAP_HUDE_2MB	(21U << MAP_HUGE_SHIFT)
# define MAP_HUDE_8MB	(23U << MAP_HUGE_SHIFT)
# define MAP_HUDE_16MB	(24U << MAP_HUGE_SHIFT)
# define MAP_HUDE_32MB	(25U << MAP_HUGE_SHIFT)
# define MAP_HUDE_256MB	(28U << MAP_HUGE_SHIFT)
# define MAP_HUDE_512MB	(29U << MAP_HUGE_SHIFT)
# define MAP_HUDE_1GB	(30U << MAP_HUGE_SHIFT)
# define MAP_HUDE_2GB	(31U << MAP_HUGE_SHIFT)
# define MAP_HUDE_16GB	(34U << MAP_HUGE_SHIFT)

/// msync

# define MS_ASYNC		1
# define MS_SYNC		4
# define MS_INVALIDATE	2

/// mlockall

# define MCL_CURRENT	1
# define MCL_FUTURE		2
# define MCL_ONFAULT	4

# define MAP_ANON	MAP_ANONYMOUS

#endif
