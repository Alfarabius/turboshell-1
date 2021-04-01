# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosie <mrosie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/04 12:55:51 by mrosie            #+#    #+#              #
#    Updated: 2021/03/10 16:20:30 by mrosie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS_PATH	= ./objs

SRCS	= ft_isalpha.c \
		ft_memchr.c \
		ft_putchar_fd.c \
		ft_strchr.c \
		ft_strlen.c \
		ft_strtrim.c \
		ft_atoi.c \
		ft_isascii.c \
		ft_memcmp.c \
		ft_putendl_fd.c \
		ft_strdup.c \
		ft_substr.c \
		ft_bzero.c \
		ft_isdigit.c \
		ft_memcpy.c \
		ft_putnbr_fd.c \
		ft_putnbr_fd_base.c \
		ft_strjoin.c \
		ft_strncmp.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_isprint.c \
		ft_memmove.c \
		ft_putstr_fd.c \
		ft_strlcat.c \
		ft_strnstr.c \
		ft_toupper.c \
		ft_isalnum.c \
		ft_itoa.c \
		ft_itoa_base.c \
		ft_memccpy.c \
		ft_memset.c \
		ft_split.c \
		ft_strlcpy.c \
		ft_strrchr.c \
		ft_strmapi.c \
		ft_lstadd_back.c \
		ft_lstadd_front.c \
		ft_lstclear.c \
		ft_lstdelone.c \
		ft_lstiter.c \
		ft_lstlast.c \
		ft_lstmap.c \
		ft_lstnew.c \
		ft_lstsize.c

CFLAG	= -Wall -Werror -Wextra
HEAD	= libft.h
OBJS	= $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))
ARCHIVE = ar rcs
CC		= gcc
RM		= rm -f
NAME	= libft.a

.PHONY:	all clean fclean re norm

all:	$(OBJS_PATH) $(NAME)

$(OBJS_PATH):
	@ mkdir -p $@

$(OBJS_PATH)/%.o: ./%.c $(HEAD)
	@ echo "compile $@"
	@ $(CC) $(CFLAG) -I ./ -c $< -o $@

$(NAME):	$(OBJS) $(HEAD)
	@ echo "add $? to $@"
	@ $(ARCHIVE) $@ $?

clean:
	@ $(RM) $(OBJS)
	@ rm -rf $(OBJS_PATH)

fclean:	clean
	@ $(RM) $(NAME)

norm:
	@ norminette $(SRCS) $(HEAD)

re:	fclean all
