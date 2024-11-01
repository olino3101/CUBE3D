CXX := gcc
CFLAGS := -Wall -Wextra -fsanitize=address -lglfw -lGL -lm -ldl

COLOR_RESET := \033[0m
COLOR_CXX := \033[1;34m
COLOR_OK := \033[1;32m
COLOR_ERROR := \033[1;31m
COLOR_CLEAN := \033[1;36m
COLOR_RE := \033[1;35m
COLOR_MSG := \033[1;35m

SRCDIR = src
OBJDIR = obj

SRCS := main.c free_err.c init.c input.c raytracing.c raytracing_utils.c
OBJS := $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCDIR = -I includes -I MLX42/includes

MLX = MLX42
GLFW_DIR = $(shell brew --prefix glfw)/lib
GLFW = -lglfw
MLX_LIB = $(MLX)/libmlx42.a
L_FLAGS = -L$(GLFW_DIR) $(GLFW)

TARGET := cub3d

PROGRAM_NAME := cub3d

MESSAGE := "\033[1;35m╭────────────────────────────────╮\n│ 🌟 $(PROGRAM_NAME) Built Successfully 🌟 │\n╰────────────────────────────────╯\033[0m"

all: $(TARGET)

$(MLX):
	@git clone https://github.com/Golubian/MLX42_4b3deda.git MLX42
	@cmake MLX42 -B MLX42 && make -C MLX42 -j4

$(TARGET): $(MLX_LIB) $(OBJS)
	@echo "$(COLOR_CXX)Linking $@...$(COLOR_RESET)"
	@$(CXX) $(CFLAGS) $(L_FLAGS) $(OBJS) $(MLX_LIB) $(INCDIR) -o $@
	@echo "$(COLOR_OK)Build succeeded!$(COLOR_RESET)"
	@echo $(MESSAGE)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(COLOR_CXX)Compiling $<...$(COLOR_RESET)"
	@$(CXX) $(CFLAGS) $(INCDIR) -c $< -o $@

clean:
	@echo "$(COLOR_CLEAN)Cleaning object files...$(COLOR_RESET)"
	@rm -f $(OBJS)

fclean: clean
	@echo "$(COLOR_CLEAN)Cleaning all, including target...$(COLOR_RESET)"
	@rm -f $(TARGET)

re: fclean all

help:
	@echo "$(COLOR_MSG)Available commands:$(COLOR_RESET)"
	@echo "  $(COLOR_OK)make$(COLOR_RESET)       - Build the project"
	@echo "  $(COLOR_CLEAN)make clean$(COLOR_RESET) - Clean object files"
	@echo "  $(COLOR_CLEAN)make fclean$(COLOR_RESET) - Full clean (includes target)"
	@echo "  $(COLOR_RE)make re$(COLOR_RESET)    - Rebuild the project"
	@echo "  $(COLOR_CXX)make help$(COLOR_RESET)  - Show this help message"

.PHONY: all clean fclean re help