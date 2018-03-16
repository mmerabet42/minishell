# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/11 18:07:15 by mmerabet          #+#    #+#              #
#    Updated: 2018/03/14 18:29:38 by mmerabet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g -fsanitize=address

LIBFTD		=	libft
LIBFT		=	$(LIBFTD)/libft.a

_NTS	=		main.c ft_getargs.c ft_getpaths.c shell_begin.c \
				ft_getcursor.c builtins.c ft_isbuiltin.c builtin_cd.c ft_env.c \
				ft_readraw.c ft_exec.c history.c ft_getopt.c \

SRCD		=	srcs/
ICLD		=	-Iincludes -I$(LIBFTD)/includes
NTS			=	$(patsubst %,$(SRCD)/%,$(_NTS))
_NTO		=	$(_NTS:.c=.o)
NTO			=	$(NTS:.c=.o)

SRCS		=	$(NTS)
_OBJS		=	$(_NTO)
OBJD		=	objs/
OBJS		=	$(addprefix $(SRCD),$(_OBJS))
OBJB		=	$(addprefix $(OBJD),$(_OBJS))

FRAMEWORKS	=

# COLORS
_GREY=\x1b[30m
_RED=\x1b[38;2;0;255;145m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m
_END=\x1b[0m
_SUCCESS=$(_RED)

all: $(NAME)

$(NAME): includes/shell.h $(LIBFT) $(OBJB)
	@echo "$(_RED)Compiling$(_END) $(NAME)$(_RED)...$(_END)"
	$(CC) $(CFLAGS) $(OBJB) $(LIBFT) $(FRAMEWORKS) -o $(NAME)
	@echo  "$(NAME) : $(_RED)done$(_END)"

$(LIBFT):
	@make -C $(LIBFTD)

$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	@$(CC) $(CFLAGS) -o $@ -c $< $(ICLD)

clean:
	@make -C $(LIBFTD) clean
	@echo "$(NAME) clean: $(_RED)done$(_END)"
	@/bin/rm -f $(OBJB)

fclean: clean
	@make -C $(LIBFTD) fclean
	@echo "$(NAME) fclean: $(_RED)done$(_END)"
	@/bin/rm -f $(NAME)

re:
	@make fclean
	@make

.PHONY: all clean fclean re
