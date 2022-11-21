export GNUMAKEFLAGS	= --no-print-directory

DEFAULT		= \033[0;39m
RED			= \033[0;91m
GREEN		= \033[0;92m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m

BIN			= minishell
NAME		= $(BIN)

CC			= gcc
CFLAGS		= #-Wall -Wextra -Werror
RM			= rm -f

SRC_DIR		= src
OBJ_DIR		= obj
BIN_DIR		= bin
LIBFT_DIR	= utils/libft/bin/libft.a

SRC			= $(shell find src -type f -name "*.c" | cut -c 5-)
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): create_dirs $(OBJ)
	@if [ -f $(LIBFT_DIR) ]; then \
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR) -lreadline -o $@; \
		echo "$(MAGENTA)$(BIN) compiled!"; \
	else \
		$(MAKE) -C utils/libft; \
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR) -lreadline -o $@; \
		echo "$(MAGENTA)$(BIN) compiled!"; \
	fi
	

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@if [ -f $(LIBFT_DIR) ]; then \
		$(MAKE) -C utils/libft clean; \
	fi
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)$(BIN)$(BLUE) objects removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN) objects already removed."; \
	fi

fclean:
	@if [ -f $(LIBFT_DIR) ]; then \
		$(MAKE) -C utils/libft fclean; \
	fi
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)$(BIN)$(BLUE) objects removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN) objects already removed."; \
	fi
	@if [ -d "$(BIN_DIR)" ]; then \
		$(RM) -r $(BIN_DIR); \
		echo "$(RED)$(BIN)$(BLUE) binary removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN) binary already removed."; \
	fi

re: fclean all

create_dirs:
	@if [ ! -d "$(OBJ_DIR)" ]; then \
		mkdir -p $(OBJ_DIR); \
		echo "$(BLUE)$(BIN) objects directory created."; \
	else \
		echo "$(RED)objects directory already exists."; \
	fi
	@if [ ! -d "$(BIN_DIR)" ]; then \
		mkdir -p $(BIN_DIR); \
		echo "$(BLUE)$(BIN) binary directory created."; \
	else \
		echo "$(RED)binary directory already exists."; \
	fi
	@echo "$(GREEN)$(BIN) compiling...";

.PHONY: all clean fclean re create_dirs