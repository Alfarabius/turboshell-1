NAME	= minishell
RM		= rm -f

all:
	Make -C ./libft/
	gcc -Wall -Werror -Wextra -I ./ minishell.c parser.c -o $(NAME) ./libft/libft.a

debug:
	Make -C ./libft/
	gcc -Wall -Werror -Wextra -g -I ./ minishell.c parser.c -o $(NAME) ./libft/libft.a

clean:
	@ echo "clean"

fclean: clean
	@ $(RM) $(NAME)
