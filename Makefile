NAME 		= 	minishell
CC			= 	cc
CFLAGS		= 	-Wall -Werror -Wextra
DBFLAG 		=	-g
MEMDBFLAG 	=	-fsanitize=address
RLFLAG		=	-lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
LIBFT 		= 	libft/libft.a
SRCDIR		=	src/
SRCFILES	= 	minishell.c prompt.c prompt_utils.c
OBJ_DIR		= 	obj/
OBJFILES	= 	$(SRCFILES:.c=.o)
INC_DIR		=	include
INC_FILES	=	$(NAME).h prompt.h
HEADER		=	$(INC_DIR)/$(NAME).h $()
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

$(NAME): $(LIBFT) $(OBJS) $(HEADER)
	@echo "Compiling $(RED)minishell$(RESET) binary"
	@$(CC) $(CFLAGS) $(RLFLAG) $(LIBFT) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Finished!$(RESET)"

debug:
	$(CC) $(CFLAGS) $(DBFLAG) $(RLFLAG) -I$(INC_DIR) $(LIBFT) $(SRCS) -o $(NAME)

debugleaks:
	$(CC) $(CFLAGS) $(DBFLAG) $(MEMDBFLAG) $(RLFLAG) -I$(INC_DIR) $(LIBFT)  $(SRCS) -o $(NAME)

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