NAME		=	minishell
SRCS_PATH	=	./
OBJS_PATH	=	./objs
INC_PATH	=	./
HEAD		=	minishell.h
LIBFT_PATH	=	./Libft
LIBFT		=	$(LIBFT_PATH)/libft.a

SRCS	=	minishell.c \
			parser.c \
			termcap.c \
			term.c \
			error.c \
			utils.c \
			utils2.c \
			utils3.c \
			env_processor.c \
			cmd_processor.c \
			binary_processor.c \
			manual_signals.c \
			get_next_line.c \
			get_next_line_utils.c \
			builtins.c \
			export.c \
			history.c \
			signals.c \
			init.c \
			pipes.c \
			redirects.c \
			cd_built_in.c \
			parser_utils.c \
			parser_utils2.c \
			parser_cases.c \
			preparser.c \
			syntax_checker.c

OBJS		=	$(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))
RM			=	rm -f
RM_DIR		=	rm -rf
CFLAGS		=	-Wall -Werror -Wextra
CC			=	gcc
INC			=	-I $(INC_PATH)

.PHONY: all init clean fclean re debug norm

all: init $(NAME)

$(OBJS_PATH)/%.o:	$(SRCS_PATH)/%.c $(HEAD)
	@ echo "compile $@"
	@ $(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME):	$(HEAD)	$(OBJS)	$(LIBFT)
	@ $(CC) $(CFLAGS) $(INC) $(OBJS) -o $(NAME) $(LIBFT) -ltermcap

init:
	@ mkdir -p $(OBJS_PATH)
	@ make -C $(LIBFT_PATH)

debug:
	Make -C $(LIBFT_PATH)
	$(CC) -g $(INC) $(SRCS) -o $(NAME) $(LIBFT) -ltermcap

clean:
	@ echo "clean"
	@ make clean -C $(LIBFT_PATH)
	@ $(RM) $(OBJS)
	@ $(RM_DIR) $(OBJS_PATH)

fclean: clean
	@ $(RM) $(NAME)
	@ make fclean -C ./libft/
	@ $(RM) ./tsh_history

norm:
	@ norminette $(addprefix $(SRCS_PATH)/, $(SRCS)) $(HEAD)
	@ make norm -C $(LIBFT_PATH)

re: fclean all
