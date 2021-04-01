NAME	= minishell
RM		= rm -f

all:
	gcc -Wall -Werror -Wextra -I ./ minishell.c -o $(NAME)

clean:
	@ echo "clean"

fclean: clean
	@ $(RM) $(NAME)
