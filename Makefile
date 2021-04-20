NAME	= minishell
RM		= rm -f
CFLAGS	= -Wall -Werror -Wextra

SRCS	=	minishell.c \
			parser.c \
			termcap.c \
			termcap_utils.c \
			error.c \
			utils.c \
			env_processor.c \
			cmd_processor.c \
			history.c \
			get_next_line.c \
			get_next_line_utils.c \
			builtins.c \
			signals.c

all:
	Make -C ./libft/
	gcc $(CFLAGS) -I ./ $(SRCS) -o $(NAME) ./libft/libft.a -ltermcap

debug:
	Make -C ./libft/
	gcc -g -I ./ $(SRCS) -o $(NAME) ./libft/libft.a -ltermcap

clean:
	@ echo "clean"
	@ make clean -C ./libft/

fclean: clean
	@ $(RM) $(NAME)
	@ make fclean -C ./libft/
	@ $(RM) tsh_history
