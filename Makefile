RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
RESET = \033[0m


CC			=	gcc
NAME		=	minishell
LIBFT		=	./inc/libft/libft.a
CFLAGS			= -Wall -Wextra -Werror -I./lib/readline/include -g
LDFLAGS			= -L./lib/readline/lib -lreadline
LIB			=	.minishell

SRCS		= 	src/minishell.c						\
				src/utils/free.c					\
				src/utils/utils.c					\
				src/utils/utils2.c					\
				src/utils/utils3.c					\
				src/signals/signal.c				\
				src/lexer/lexer.c					\
				src/split/split.c					\
				src/split/split2.c					\
				src/split/split3.c					\
				src/parser/parser.c					\
				src/parser/parser2.c				\
				src/executor/executor.c				\
				src/executor/executor_helpers.c		\
				src/executor/executor2.c			\
				src/commands/clear.c				\
				src/commands/pwd.c					\
				src/commands/echo.c					\
				src/commands/env.c					\
				src/commands/exit.c					\
				src/commands/export.c				\
				src/commands/unset.c				\
				src/commands/cd.c

OBJS = $(SRCS:.c=.o)

all:	$(NAME)
$(NAME):	$(OBJS)
			@echo "$(YELLOW)>>>> Compiling Libft Librarys <<<<$(WHITE)"
			@make -sC ./inc/libft
			@echo "$(YELLOW)>>>> Compiling minishell <<<<$(WHITE)"
			@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) -lreadline -lncurses -o $(NAME)
			@echo "$(BLUE)>>>> Done <<<<$(RESET)"

$(LIB):
	@make -C ./lib

clean:
			@@make clean -sC ./inc/libft
			@rm -rf $(OBJS)
			@echo "$(RED)>>>> Deleted <<<<$(RESET)"

fclean:		
			@make fclean -sC ./inc/libft
			@rm -rf $(OBJS)
			@rm -rf $(NAME)
			@echo "$(RED)>>>> Full Deleted <<<<$(RESET)"

ffclean:		
			@make fclean -sC ./inc/libft
			@rm -rf $(OBJS)
			@rm -rf $(NAME)
			@make fclean -C ./lib
			@echo "$(RED)>>>> Full Deleted <<<<$(RESET)"

readline: $(LIB)

re:			fclean all

.PHONY:		all clean fclean re readline norm
