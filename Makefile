NAME 		= 	minishell
CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra
DBFLAG 		=	-g
MEMDBFLAG 	=	-fsanitize=address
RLFLAG		=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT 		= 	libft/libft.a
SRCDIR		=	src/
SRCFILES	=   main.c cleanup.c utils.c prompt.c signals.c env_var.c env_var_utils.c executor.c exec_utils.c \
				builtins.c builtin_echo.c builtin_exit.c builtin_cd.c builtin_export.c \
				heredoc.c heredoc_expand.c parser.c parser_utils.c parser_rd_utils.c pipes.c\
				lexer.c lexer_dmh.c lexer_executables.c lexer_libft_mods.c lexer_pipes_redirects.c lexer_specials.c \
				lexer_tokenizer.c lexer_words_utils.c lexer_words.c lexer_expandables.c	error.c
OBJ_DIR		= 	obj/
OBJFILES	= 	$(SRCFILES:.c=.o)
INC_DIR		=	include/
INC_FILES	=	$(NAME).h lexer.h parser.h
HEADER		=	$(addprefix $(INC_DIR), $(INC_FILES))
SRCS 		=	$(addprefix $(SRCDIR), $(SRCFILES))
OBJS		=	$(addprefix $(OBJ_DIR), $(OBJFILES))
RED 		:= 	\033[0;31m
GREEN 		:= 	\033[0;32m
MAGENTA		:= 	\033[0;35m
CYAN		:=	\033[0;36m
RESET 		:= 	\033[0m

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(LIBFT):
	@make -C libft
	
$(OBJ_DIR): 
	@echo "Creating directory $(CYAN)$(OBJ_DIR)$(RESET)"
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRCDIR)%.c $(HEADER)
	@echo "Building object file: $(CYAN)$@$(RESET) from source file $(MAGENTA)$<$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) $< -c -o $@

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS) $(HEADER)
	@echo "Compiling $(RED)minishell$(RESET) binary"
	@$(CC) $(CFLAGS) $(RLFLAG) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Finished!$(RESET)"

clean:
	@make clean -C libft
	@echo "Deleting $(CYAN)object$(RESET) files"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files deleted!$(RESET)"

fclean: clean
	@make fclean -C libft
	@echo "Deleting $(RED)minishell$(RESET) binary"
	@rm -rf $(NAME)
	@echo "$(GREEN)Minishell binary deleted!$(RESET)"

re: fclean all

.PHONY: all clean fclean re debug  debugleaks