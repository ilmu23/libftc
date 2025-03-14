## ███████╗████████╗     ██████╗ ██╗   ██╗████████╗ ██████╗██╗  ██╗ █████╗ ██████╗
## ██╔════╝╚══██╔══╝     ██╔══██╗██║   ██║╚══██╔══╝██╔════╝██║  ██║██╔══██╗██╔══██╗
## █████╗     ██║        ██████╔╝██║   ██║   ██║   ██║     ███████║███████║██████╔╝
## ██╔══╝     ██║        ██╔═══╝ ██║   ██║   ██║   ██║     ██╔══██║██╔══██║██╔══██╗
## ██║        ██║███████╗██║     ╚██████╔╝   ██║   ╚██████╗██║  ██║██║  ██║██║  ██║
## ╚═╝        ╚═╝╚══════╝╚═╝      ╚═════╝    ╚═╝    ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝  ╚═╝
##
## <<Makefile>>

NAME	=	libft.a

BUILD	=	normal

CC				=	gcc
cflags.common	=	-Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c17 -nostdlib -nostdinc -I$(INCDIR) -fno-stack-protector
cflags.debug	=	-g
cflags.debugm 	=	$(cflags.debug) -D DEBUG_MSG=1
cflags.fsan		=	$(cflags.debug) -fsanitize=address,undefined
cflags.normal	=	-s -O1
cflags.extra	=	
CFLAGS			=	$(cflags.common) $(cflags.$(BUILD)) $(cflags.extra)

AS				=	as
asmflags.common	=	--fatal-warnings
asmflags.debug	=	-g
asmflags.extra	=	
ASMFLAGS		=	$(asmflags.common) $(asmflags.$(BUILD)) $(asmflags.extra)

SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc

# STD

MMANDIR		=	mman
STDLIBDIR	=	stdlib
UNISTDDIR	=	unistd

MMANFILES	=	ft_mlockall.c \
				ft_mlock.c \
				ft_mmap.c \
				ft_mprotect.c \
				ft_msync.c \
				ft_munlockall.c \
				ft_munlock.c \
				ft_munmap.c

STDLIBFILES	=	ft_exit.c \
				ft_free.c \
				ft_malloc.c \
				__heapinfo.c \
				__heapvis.c

UNISTDFILES	=	ft_sysconf.c \
				ft_write.c

# /STD

# LFT

LFTDIR	=	lft
ISDIR	=	$(LFTDIR)/is
TODIR	=	$(LFTDIR)/to
MEMDIR	=	$(LFTDIR)/mem
PUTDIR	=	$(LFTDIR)/put
STRDIR	=	$(LFTDIR)/str

ISFILES		=	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isblank.c \
				ft_iscntrl.c \
				ft_isdigit.c \
				ft_isgraph.c \
				ft_islower.c \
				ft_isprint.c \
				ft_ispunct.c \
				ft_isspace.c \
				ft_isupper.c \
				ft_isxdigit.c

TOFILES		=	ft_tolower.c \
				ft_toupper.c

PUTFILES	=	ft_putchar.c \
				ft_putchar_fd.c \
				ft_putendl.c \
				ft_putendl_fd.c \
				ft_putsnbr.c \
				ft_putsnbr_fd.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_putunbr.c \
				ft_putunbr_fd.c

MEMFILES	=	ft_bzero.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memrchr.c \
				ft_memset.c

STRFILES	=	ft_stpcpy.c \
				ft_stpncpy.c \
				ft_strcat.c \
				ft_strchr.c \
				ft_strcmp.c \
				ft_strcpy.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncat.c \
				ft_strncmp.c \
				ft_strncpy.c \
				ft_strnlen.c \
				ft_strrchr.c

LFTFILES	=	$(addprefix $(ISDIR)/, $(ISFILES)) \
				$(addprefix $(TODIR)/, $(TOFILES)) \
				$(addprefix $(PUTDIR)/, $(PUTFILES)) \
				$(addprefix $(MEMDIR)/, $(MEMFILES)) \
				$(addprefix $(STRDIR)/, $(STRFILES))

# /LFT

ASMFILES	=	_start.asm \
				syscall.asm

CFILES		=	$(LFTFILES) \
				$(addprefix $(MMANDIR)/, $(MMANFILES)) \
				$(addprefix $(STDLIBDIR)/, $(STDLIBFILES)) \
				$(addprefix $(UNISTDDIR)/, $(UNISTDFILES))

ASMSRCS	=	$(addprefix $(SRCDIR)/, $(ASMFILES))
ASMOBJS	=	$(patsubst $(SRCDIR)/%.asm, $(OBJDIR)/%.o, $(ASMSRCS))

CSRCS	=	$(addprefix $(SRCDIR)/, $(CFILES))
COBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

all: $(NAME)

$(NAME): $(OBJDIR) $(ASMOBJS) $(COBJS)
	@printf "\e[34;1mLIBFT >\e[m Creating %s\n" $@
	@ar -crs $(NAME) $(ASMOBJS) $(COBJS)
	@printf "\e[34;1mLIBFT >\e[m \e[1mDone!\e[m\n"

$(OBJDIR):
	@printf "\e[34;1mLIBFT >\e[m Creating objdirs\n" $@
	@mkdir -p $(OBJDIR)/$(ISDIR)
	@mkdir -p $(OBJDIR)/$(TODIR)
	@mkdir -p $(OBJDIR)/$(PUTDIR)
	@mkdir -p $(OBJDIR)/$(MEMDIR)
	@mkdir -p $(OBJDIR)/$(STRDIR)
	@mkdir -p $(OBJDIR)/$(MMANDIR)
	@mkdir -p $(OBJDIR)/$(STDLIBDIR)
	@mkdir -p $(OBJDIR)/$(UNISTDDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	@printf "\e[34;1mLIBFT >\e[m Assembling %s\n" $<
	@$(AS) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34;1mLIBFT >\e[m Compiling %s\n" $<
	@$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	@rm -f $(COBJS) $(ASMOBJS)

fclean: clean
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

db:
	@printf "\e[34;1mLIBFT >\e[m Creating compilation command database\n"
	@compiledb make --no-print-directory BUILD=$(BUILD) cflags.extra=$(cflags.extra) | sed -E '/^##.*\.\.\.$$|^[[:space:]]*$$/d'
	@printf "\e[34;1mLIBFT >\e[m \e[1mDone!\e[m\n"

.PHONY: all clean fclean re db
