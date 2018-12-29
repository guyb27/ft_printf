# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: qcharpen <marvin@le-101.fr>                +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/06/26 01:24:46 by qcharpen     #+#   ##    ##    #+#        #
#    Updated: 2018/12/02 16:03:36 by qcharpen    ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME = libftprintf.a

FLAGS = -Werror -Wextra -Wall

LIBFT_PATH = ./sources/libft

LIBFT = sources/libft/ft_bzero.c \
		sources/libft/ft_isdigit.c \
		sources/libft/ft_isinstr.c \
		sources/libft/ft_memalloc.c \
		sources/libft/ft_tabset.c \
		sources/libft/ft_memdel.c \
		sources/libft/ft_strchr.c \
		sources/libft/ft_strdup.c \
		sources/libft/ft_strcut.c \
		sources/libft/ft_strlen.c \
		sources/libft/ft_strnjoin.c \
		sources/libft/ft_itoa.c \
		sources/libft/ft_ftoa.c \
		sources/libft/ft_itoa_base.c \
		sources/libft/ft_strisdigit.c \
		sources/libft/ft_strsub.c \
		sources/libft/ft_strnew.c \
		sources/libft/ft_printf.c \
		sources/libft/handle.c \
		sources/libft/handle_percent.c \
		sources/libft/handle_char.c \
		sources/libft/handle_str.c \
		sources/libft/handle_signed_int.c \
		sources/libft/handle_unsigned_int.c \
		sources/libft/handle_hex.c \
		sources/libft/handle_oct.c \
		sources/libft/handle_p.c \
		sources/libft/handle_float.c \
		sources/libft/parse_tests.c \
		sources/libft/parsing.c \
		sources/libft/ft_lstdel.c \
		sources/libft/ft_lstaddend.c \
		sources/libft/ft_lstlen.c \
		sources/libft/ft_lstnew.c \
		sources/libft/ft_lstprint.c \




SRCS = $(LIBFT)

OBJ = $(LIBFT:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(LIBFT_PATH)%.o: $(LIBFT)%.c
	@gcc -c $(FLAGS) $(LIBFT) -I ./includes/ft_printf.h

valgrind:
	@gcc -ggdb3 ./sources/*/*.c test.c -I includes
	@valgrind --leak-check=full --track-origins=yes ./a.out
	@@rm -f $(OBJ) test.o a.out

clean:
	@rm -f $(OBJ)
	@echo "[SUPPRESSION DE LA LIBFT_PRINTF]"

fclean: clean
	@rm -f $(NAME)
	@echo "[SUPPRESSION DES SRCs_PRINTF]"

re: fclean all
