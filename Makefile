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
cflags.common	=	-Wall -Wextra -Werror -Wpedantic -pedantic-errors -std=c17 -nostdlib -nostdinc -I$(INCDIR)
cflags.debug	=	-g
cflags.debugm 	=	$(cflags.debug) -D DEBUG_MSG=1
cflags.fsan		=	$(cflags.debug) -fsanitize=address,undefined
cflags.normal	=	-s -O2
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

ASMFILES	=	_start.asm \
				syscall.asm

CFILES		=	

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
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	@printf "\e[34;1mLIBFT >\e[m Compiling %s\n" $@
	@$(AS) $(ASMFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@printf "\e[34;1mLIBFT >\e[m Compiling %s\n" $@
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
