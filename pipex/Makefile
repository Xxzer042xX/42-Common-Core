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

# Libftprintf (libft)path
LIBFT_DIR = $(LIB_DIR)/libftprintf
LIBFT = $(LIBFT_DIR)/libftprintf.a

################################################################################
#                                 MANDATORY                                    #
################################################################################
SRC_FILE =  $(SRC_DIR)/mandatory/pipex.c \
			 $(SRC_DIR)/mandatory/cmd_utils.c \
			 $(SRC_DIR)/mandatory/init_app.c \
			 $(SRC_DIR)/mandatory/process.c \
			 $(SRC_DIR)/mandatory/path_utils.c \
			 $(SRC_DIR)/mandatory/clean_up.c \
			 $(SRC_DIR)/mandatory/files_utils.c \
			 $(SRC_DIR)/mandatory/heredoc.c \

SRC = $(SRC_FILE)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

NAME = $(BIN_DIR)/pipex
################################################################################
#                                   BONUS                                      #
################################################################################
BONUS_FILE = $(SRC_DIR)/bonus/pipex_bonus.c \
			 $(SRC_DIR)/bonus/cmd_utils_bonus.c \
			 $(SRC_DIR)/bonus/init_app_bonus.c \
			 $(SRC_DIR)/bonus/process_bonus.c \
			 $(SRC_DIR)/bonus/path_utils_bonus.c \
			 $(SRC_DIR)/bonus/clean_up_bonus.c \
			 $(SRC_DIR)/bonus/files_utils_bonus.c \
			 $(SRC_DIR)/bonus/heredoc_bonus.c \
			 $(SRC_DIR)/bonus/extract_token_bonus.c \
			 $(SRC_DIR)/bonus/token_utils_bonus.c \

BONUS_SRC = $(BONUS_FILE)

BONUS_OBJ = $(BONUS_SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

BONUS_NAME = $(BIN_DIR)/pipex_bonus
################################################################################
#                             COMPILER OPTIONS                                 #
################################################################################

# Headers
INC = -I$(INC_DIR) -I$(INC_DIR)/mandatory -I$(INC_DIR)/bonus

CC = cc
INCLUDES = $(INC)
LIBS = -L$(LIBFT_DIR) -lftprintf
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -g

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

all: init $(LIBFT) $(NAME)

bonus: init $(LIBFT) $(BONUS_NAME)

init:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)/mandatory
	@mkdir -p $(OBJ_DIR)/bonus
	@echo "$(GREEN)Project structure initialized$(RESET)"

$(LIBFT):
	@echo "$(YELLOW)Compiling Libft...$(RESET)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled!$(RESET)"

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(YELLOW)Linking $@...$(RESET)"
	@$(CC) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Build complete! Binary: $(BOLD)$(NAME)$(RESET)"
	@echo "$(CYAN)Run with: ./$(NAME)$(RESET)"

$(BONUS_NAME): $(LIBFT) $(BONUS_OBJ)
	@echo "$(YELLOW)Linking $@...$(RESET)"
	@$(CC) $(BONUS_OBJ) $(LIBS) -o $(BONUS_NAME)
	@echo "$(GREEN)Bonus Build complete! Binary: $(BOLD)$(BONUS_NAME)$(RESET)"
	@echo "$(CYAN)Run with: ./$(BONUS_NAME)$(RESET)"

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
	@$(MAKE)  -C $(LIBFT_DIR) clean >/dev/null
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)Object files cleaned$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executables and binaries...$(RESET)"
	@$(MAKE)  -C $(LIBFT_DIR) fclean >/dev/null
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@rm -f $(BIN_DIR)/*
	@rm -rf $(BIN_DIR)
	@echo "$(GREEN)All binaries cleaned$(RESET)"

re: fclean all

bonus_re: fclean bonus

################################################################################
#                              INFORMATION                                     #
################################################################################

show:
	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== System Information =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "OS" "$(OS)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Architecture" "$(ARCH)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Compiler" "$(shell $(CC) --version | head -n1)"
	
	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== Project Structure =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Source Files" "$(SRC)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Bonus Files" "$(BONUS_SRC)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Object Files" "$(OBJ)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "Include Paths" "$(INC)"
	
	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== Libraries =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "LIBFT" "$(LIBFT)"

	@printf "\n$(BOLD)$(BLUE)%50s$(RESET)\n\n" "========== Compilation Flags =========="
	@printf "$(PURPLE)%-20s$(RESET): %s\n" "CFLAGS" "$(CFLAGS)"
	@printf "$(PURPLE)%-20s$(RESET): %s\n\n" "LIBS" "$(LIBS)"

help:
	@printf "$(BOLD)$(BLUE)\n%33s$(RESET)\n\n" "====Available commands:===="
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make init" "Initialize project structure"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make or make all" "Compile the project"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make clean" "Remove object files"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make fclean" "Remove object files and executable"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make re" "Recompile the project"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make bonus" "Compile the bonus part"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make bonus_re" "Recompile the bonus part"
	@printf "$(CYAN)%-18s$(RESET) - %s\n" "make show" "Display project information"
	@printf "$(CYAN)%-18s$(RESET) - %s\n\n" "make help" "Display this help message"

################################################################################
#                                 PHONY                                        #
################################################################################

.PHONY: all init clean fclean re show help bonus bonus_re
