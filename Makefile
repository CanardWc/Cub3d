
NAME = cub3d

CC = cc
C_FLAGS = -Wall -Wextra -Werror
FRAM = -framework OpenGL -framework AppKit libraries/minilibx/libmlx.a

LFT_PATH = ./libraries/libft/
LFT_INC_PATH = ./libraries/libft/includes/
MLX_PATH = ./libraries/minilibx/
MLX_INC_PATH = ./libraries/minilibx/
OBJ_PATH = ./objs/
INC_PATH = ./includes/
SRC_PATH = ./srcs/

LFT_NAME = libft.a
MLX_NAME = libmlx.a
OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = cub3d.h
SRC_NAME = cub3d.c \
		   cub_parsing/cub_parsing.c \
		   cub_logic/cub_logic.c \
		   cub_logic/cub_pixel_gestion.c \
		   cub_logic/cub_position.c \
		   cub_logic/cub_ray_logic.c \
		   cub_logic/cub_ui_gestion.c \
		   cub_logic/cub_events/cub_events_capture.c \

LFT = $(addprefix $(LFT_PATH),$(LFT_NAME))
MLX = $(addprefix $(MLX_PATH),$(MLX_NAME))
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LFT_INC = $(addprefix -I,$(LFT_INC_PATH))
MLX_INC = $(addprefix -I,$(MLX_INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LFT_PATH)
	@make -C $(MLX_PATH)
	@$(CC) -o $@ $(FRAM) -L $(LFT_PATH) -lft $^
	@echo "Obj folder & files created"
	@echo "Executable created"
	@echo "Compilation finished"

$(OBJ): | $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(C_FLAGS)  -fsanitize=address -g3 $(INC) $(LFT_INC) $(MLX_INC) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@mkdir $(OBJ_PATH)cub_parsing/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)cub_logic/ 2> /dev/null || true
	@mkdir $(OBJ_PATH)cub_logic/cub_events/ 2> /dev/null || true

clean:
	@make clean -C $(LFT_PATH)
	@make clean -C $(MLX_PATH)
	@rm -rf $(OBJ_PATH) 2> /dev/null || true
	@echo "Obj folder & files suppressed"

fclean: clean
	@make fclean -C $(LFT_PATH)
	@rm -f $(MLX_PATH)/$(MLX_NAME)
	@rm -f $(NAME)
	@echo "Executable suppressed"

re: fclean
	@$(MAKE) all

bonus: all

norme:
	@norminette -R CheckForbiddenSourceHeader $(SRC)
	@echo "C files norme check finished"
	@norminette -R CheckDefine $(INC_PATH)
	@echo "Header files norme check finished"
