################################################################################
#                                  SYSTEM DETECTION                            #
################################################################################

UNAME := $(shell uname)
OS := $(shell uname -s)
ARCH := $(shell uname -m)

################################################################################
#                                 DIRECTORIES                                  #
################################################################################

SRC_DIR = srcs
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = include
LIB_DIR = lib

################################################################################
#                                 LIBRARIES                                    #
################################################################################

# Mlx paths
MLX_LINUX = $(LIB_DIR)/minilibx-linux
MLX_NAME = libmlx_Linux.a
MLX = $(MLX_LINUX)/$(MLX_NAME)

# Libftprintf (libft)path
LIBFT_DIR = $(LIB_DIR)/libftprintf
LIBFT = $(LIBFT_DIR)/libftprintf.a

################################################################################
#                              SOURCE FILES                                    #
################################################################################

CONTROLS_SRC = $(wildcard $(SRC_DIR)/controls/*.c)

CORE_SRC = $(wildcard $(SRC_DIR)/core/*.c)

DRAWER_SRC = $(wildcard $(SRC_DIR)/drawer/*.c) \
			 $(wildcard $(SRC_DIR)/drawer/map/*.c) \
			 $(wildcard $(SRC_DIR)/drawer/sidebar/*.c)

EVENTS_SRC = $(wildcard $(SRC_DIR)/events/*.c)

PARSER_SRC = $(wildcard $(SRC_DIR)/parser/*.c)

PRINTER_SRC = $(wildcard $(SRC_DIR)/printer/*.c)

RENDER_SRC = $(wildcard $(SRC_DIR)/render/*.c)

TRANSFORM_SRC = $(wildcard $(SRC_DIR)/transform/*.c)

UTILS_SRC = $(wildcard $(SRC_DIR)/utils/*.c)

MAIN_SRC = $(SRC_DIR)/fdf.c

SRC = $(RENDER_SRC) $(EVENTS_SRC) $(CORE_SRC) $(PARSER_SRC) $(UTILS_SRC) \
	  $(CONTROLS_SRC) $(TRANSFORM_SRC) $(MAIN_SRC) $(DRAWER_SRC) $(PRINTER_SRC)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

################################################################################
#                             COMPILER OPTIONS                                 #
################################################################################

# Headers
INC = -I$(INC_DIR) -I$(INC_DIR)/utils

# Compiler and flags
CC = cc
INCLUDES = $(INC) -I$(MLX_LINUX)
LIBS = -L$(MLX_LINUX) -lmlx_Linux -L$(LIBFT_DIR) -lftprintf -lXext -lX11 -lm -lbsd
CFLAGS = -Wall -Wextra -Werror $(INCLUDES)
NAME = $(BIN_DIR)/fdf

################################################################################
#                                COLORS                                        #
################################################################################

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m
BOLD = \033[1m

################################################################################
#                              MAIN TARGETS                                    #
################################################################################

all: init $(MLX) $(LIBFT) $(NAME)

init:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)/core
	@mkdir -p $(OBJ_DIR)/drawer
	@mkdir -p $(OBJ_DIR)/drawer/map
	@mkdir -p $(OBJ_DIR)/drawer/sidebar
	@mkdir -p $(OBJ_DIR)/parser/
	@mkdir -p $(OBJ_DIR)/printer

	@mkdir -p $(OBJ_DIR)/utils
	@mkdir -p $(OBJ_DIR)/events
	@mkdir -p $(OBJ_DIR)/controls
	@mkdir -p $(OBJ_DIR)/transform
	@mkdir -p $(OBJ_DIR)/render

	@echo "$(GREEN)Project structure initialized$(RESET)"

$(MLX):
	@echo "$(YELLOW)Compiling MinilibX...$(RESET)"
	@$(MAKE) -C $(MLX_LINUX) >/dev/null
	@echo "$(GREEN)MinilibX compiled!$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled!$(RESET)"

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	@echo "$(YELLOW)Linking $@...$(RESET)"
	@$(CC) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Build complete! Binary: $(BOLD)$(NAME)$(RESET)"
	@echo "$(CYAN)Run with: ./$(NAME)$(RESET)"

################################################################################
#                              OBJECT FILES                                    #
################################################################################

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

################################################################################
#                               CLEANING                                       #
################################################################################

clean:
	@echo "$(RED)Cleaning build files...$(RESET)"
	@$(MAKE)  -C $(MLX_LINUX) clean >/dev/null
	@$(MAKE)  -C $(LIBFT_DIR) clean >/dev/null
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files cleaned$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executables and binaries...$(RESET)"
	@$(MAKE)  -C $(LIBFT_DIR) fclean >/dev/null
	@rm -f $(NAME)
	@rm -f $(BIN_DIR)/*
	@rm -rf $(BIN_DIR)
	@echo "$(GREEN)All binaries cleaned$(RESET)"

re: fclean all

################################################################################
#                              INFORMATION                                     #
################################################################################

show:
	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== System Information =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "OS" "$(OS)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Architecture" "$(ARCH)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Compiler" "$(shell $(CC) --version | head -n1)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "MLX Path" "$(MLX_LINUX)"
	
	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== Project Structure =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Source Files" "$(SRC)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Object Files" "$(OBJ)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Include Paths" "$(INC)"
	
	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== Libraries =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "MLX Library" "$(MLX)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "LIBFT" "$(LIBFT)"

	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== Compilation Flags =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "CFLAGS" "$(CFLAGS)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n\n" "LIBS" "$(LIBS)"

help:
	@printf "$(BOLD)$(BLUE)\n%33s$(RESET)\n\n" "====Available commands:===="
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make or make all" "Compile the project"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make clean" "Remove object files"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make fclean" "Remove object files and executable"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make re" "Recompile the project"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make show" "Display project information"
	@printf "$(CYAN)%-18s$(RESET) - %s\n\n" "make help" "Display this help message"

################################################################################
#                                 PHONY                                        #
################################################################################

.PHONY: all init clean fclean re show help
