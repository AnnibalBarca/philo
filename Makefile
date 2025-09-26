NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:%.c=%.o))
DEPS = $(OBJ:.o=.d)



SRC_PHILO = src/init.c src/cleanup.c src/utils.c src/philo_actions.c src/philo_routine.c src/monitor_routine.c

SRC_ALL = $(SRC_PHILO) main.c

GREEN=\033[0;32m
BLUE=\033[38;2;64;224;208m
RED=\033[0;91m
WHITE=\033[2;37m
NC=\033[0m

all: $(LIBFT) $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile libft/Makefile
	@echo "$(WHITE) mkdir -p $(dir $@) $(NC)"
	@mkdir -p $(dir $@)
	@echo "$(GREEN) $(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) -Iinclude $(NC)"
	@$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -I$(LIBFT_DIR) -Iinclude

-include $(DEPS)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN) $(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft $(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft

$(OBJ_DIR):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR) $(NC)"
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

libft:
	make -C $(LIBFT_DIR)

clean:
	@echo "$(RED) rm -rf $(OBJ_DIR) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) clean $(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED) rm -f $(NAME) $(NC)"
	@echo "$(RED) make -C $(LIBFT_DIR) fclean $(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

re_bonus: fclean

.PHONY: all clean fclean re libft