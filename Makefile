export GNUMAKEFLAGS	= --no-print-directory

DEFAULT		= \033[0;39m
RED			= \033[0;91m
GREEN		= \033[0;92m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m

BIN			= minishell
NAME		= $(BIN)

CC			= gcc -g
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

SRC_DIR		= src
RUN_DIR		= src/run
OBJ_DIR		= obj
BIN_DIR		= bin
LIBFT_DIR	= utils/libft/bin/libft.a
GNL_DIR		= utils/gnl/bin/get_next_line.a
PRINTFD_DIR	= utils/print_fd/bin/print_fd.a
READL		= -L ~/goinfre/.brew/opt/readline/lib
READI		= -I ~/goinfre/.brew/opt/readline/include

SRC			= $(shell find src -type f ! -name "run_*.c" -name "*.c" | cut -c 5-)
RUN			= $(shell find src/run -type f -name "*.c" | cut -c 9-)
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
RUN_OBJ		= $(addprefix $(OBJ_DIR)/, $(RUN:.c=.o))

all: $(NAME)

$(NAME): create_dirs $(OBJ) $(RUN_OBJ)
	@make -C utils/libft
	@make -C utils/gnl
	@make -C utils/print_fd
	@$(CC) $(CFLAGS) $(READI) $(READL) $(OBJ) $(RUN_OBJ) $(LIBFT_DIR) $(GNL_DIR) $(PRINTFD_DIR) -lreadline -o $@
	@echo "$(MAGENTA)$(BIN) compiled!"

# $(READL) kullanılmamasının sebebi kullanılmayan arşiv dosyaları olduğundan warning atıyor. "warning: argument unused during compilation"
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(READI) $(CFLAGS) -c $< -o $@
$(OBJ_DIR)/%.o: $(RUN_DIR)/%.c
	@$(CC) $(READI) $(CFLAGS) -c $< -o $@

clean:
	@if [ -f $(LIBFT_DIR) ]; then \
		make -C utils/libft clean; \
	fi
	@if [ -f $(GNL_DIR) ]; then \
		make -C utils/gnl clean; \
	fi
	@if [ -f $(PRINTFD_DIR) ]; then \
		make -C utils/print_fd clean; \
	fi
	@if [ -d "$(OBJ_DIR)" ]; then \
		$(RM) -r $(OBJ_DIR); \
		echo "$(RED)$(BIN)$(BLUE) objects removed.$(GREEN)"; \
	else \
		echo "$(RED)$(BIN) objects already removed."; \
	fi

fclean:
	@if [ -f $(LIBFT_DIR) ]; then \
		make -C utils/libft fclean; \
	fi
	@if [ -f $(GNL_DIR) ]; then \
		make -C utils/gnl fclean; \
	fi
	@if [ -f $(PRINTFD_DIR) ]; then \
		make -C utils/print_fd fclean; \
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