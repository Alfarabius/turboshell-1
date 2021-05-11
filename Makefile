NAME		= minishell
RM			= rm -f
CFLAGS		= -Wall -Werror -Wextra
SRCS_PATH	= ./
HEAD		= minishell.h

SRCS	=	minishell.c \
			parser.c \
			termcap.c \
			term.c \
			error.c \
			utils.c \
			utils2.c \
			env_processor.c \
			cmd_processor.c \
			manual_signals.c \
			get_next_line.c \
			get_next_line_utils.c \
			builtins.c \
			builtins_2.c \
			history.c \
			signals.c \
			init.c \
			pipes.c

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

norm:
	@ norminette $(addprefix $(SRCS_PATH)/, $(SRCS)) $(HEAD)
	@ make norm -C $(LIBFT_PATH)
