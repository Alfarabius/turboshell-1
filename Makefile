NAME	= minishell
RM		= rm -f

SRCS	=	minishell.c \
			parser.c \
			termcap.c \
			error.c \
			utils.c \
			env_processor.c

all:
	Make -C ./libft/
	gcc -Wall -Werror -Wextra -I ./ $(SRCS) -o $(NAME) ./libft/libft.a -ltermcap

debug:
	Make -C ./libft/
	gcc -Wall -Werror -Wextra -g -I ./ $(SRCS) -o $(NAME) ./libft/libft.a -ltermcap

clean:
	@ echo "clean"
	make clean -C ./libft/

fclean: clean
	@ $(RM) $(NAME)
	make fclean -C ./libft/
