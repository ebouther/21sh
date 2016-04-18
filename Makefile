NAME = 21sh

RED_L = \033[1;31m
GREEN_L = \033[1;32m
GREEN = \033[0;32m
BLUE = \033[1;34m
RED = \033[0;31m
GRAY = \033[1;30m
GRAY_L = \033[0;37m
CYAN = \033[0;36m
PURPLE_L = \033[1;35m
CYAN_L = \033[1;36m
NC = \033[0m

CC = gcc 
CFLAGS = -Wall -Wextra -Werror
LFLAGS = -L./libft -lft
IFLAGS = -I./inc/ -I./libft/includes/

LIBFT = libft/libft.a

SRC_DIR = ./src/
INC_DIR = ./inc/
OBJ_DIR = ./obj/

SRC_FILES =	minishell.c \
			builtin.c \
			browser.c \
			env.c \
			input.c \
			redirections.c

OBJ_FILES = $(SRC_FILES:.c=.o)
INC_FILES = minishell.h

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
INC = $(addprefix $(INC_DIR), $(INC_FILES))

.PHONY: all clean fclean re $(LIBFT) 

all: $(OBJ_DIR) $(LIBFT) $(NAME) auteur

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

norme: $(SRC)
	norminette $(SRC) $(INC)

$(NAME): $(OBJ)
	@echo "\n$(BLUE)Linking binary $(RED)$(NAME)$(BLUE).\n"
	@$(CC) -o $@ $^ $(LFLAGS)
	@echo "\t✻ $(GRAY)$(CC) -o $(RED)$(NAME)$(GRAY) object files:$(GREEN) OK! √\n$(NC)"

$(LIBFT):
	@make -C libft/

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
	@echo "$(BLUE)  + $(GRAY)Compiling: $(RED)$<$(GRAY) ... $(GREEN)OK! √$(NC)"

clean:
	@echo "$(BLUE)  - $(GRAY)Removed $(RED)$(NAME) $(GRAY_L)object files$(GRAY).$(NC)"
	@make -C libft/ clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BLUE)  - $(GRAY)Removed $(RED)$(NAME) $(GRAY_L)binary$(GRAY)."
	@rm -f $(NAME) $(LIBFT)
	@echo "$(BLUE)  - $(GRAY)Removed $(RED)$(LIBFT) $(GRAY_L)binary$(GRAY).\n"

re: fclean all
