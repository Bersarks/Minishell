export GNUMAKEFLAGS	= --no-print-directory

DEFAULT = \033[0;39m
RED		= \033[0;91m
GREEN	= \033[0;92m
BLUE	= \033[0;94m
MAGENTA	= \033[0;95m

BIN		= get_next_line.a
NAME	= $(BIN_DIR)/$(BIN)
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
AR		= ar rcs

SRC_DIR	= src
OBJ_DIR	= obj
INC_DIR	= inc
BIN_DIR	= bin

SRC		= get_next_line.c get_next_line_utils.c
OBJ		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all:
	@if [ ! -d "$(OBJ_DIR)" ]; then \
		make $(NAME); \
		echo "$(MAGENTA)$(BIN) created$(DEFAULT)"; \
	else \
		echo "$(MAGENTA)$(BIN) already exists$(DEFAULT)"; \
	fi

$(NAME): create_dirs $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I inc/ -c $< -o $@

clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)GNL$(BLUE) objects removed.$(GREEN)"; \
	else \
		echo "$(RED)GNL$(BLUE) objects already removed.$(GREEN)"; \
	fi

fclean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)GNL$(BLUE) objects removed.$(GREEN)"; \
	else \
		echo "$(RED)GNL$(BLUE) objects already removed.$(GREEN)"; \
	fi
	@if [ -d "$(BIN_DIR)" ]; then \
		$(RM) -r $(BIN_DIR); \
		echo "$(RED)$(BIN)$(BLUE) removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN)$(BLUE) already removed.$(GREEN)"; \
	fi

re: fclean all

create_dirs:
	@echo "$(BLUE)Creating GNL directories...$(GREEN)"
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)
	@echo "$(GREEN)Compiling GNL...$(BLUE)"

.PHONY: all clean fclean re create_dirs
