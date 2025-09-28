NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g3
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC_ALL:%.c=%.o))
DEPS = $(OBJ:.o=.d)



SRC_PHILO = src/init.c src/cleanup.c src/utils.c src/philo_actions.c src/philo_routine.c src/monitor_routine.c src/mutex_utils.c

SRC_ALL = $(SRC_PHILO) main.c

GREEN=\033[0;32m
BLUE=\033[38;2;64;224;208m
RED=\033[0;91m
WHITE=\033[2;37m
NC=\033[0m

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR)/%.o: %.c Makefile
	@echo "$(WHITE) mkdir -p $(dir $@) $(NC)"
	@mkdir -p $(dir $@)
	@echo "$(GREEN) $(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -Iinclude $(NC)"
	@$(CC) $(CFLAGS) -MMD -MP -o $@ -c $< -Iinclude

-include $(DEPS)

$(NAME): $(OBJ)
	@echo "$(GREEN) $(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	@echo "$(WHITE) mkdir -p $(OBJ_DIR) $(NC)"
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "$(RED) rm -rf $(OBJ_DIR) $(NC)"
	@echo "$(RED) make -C clean $(NC)"
	@rm -rf $(OBJ_DIR)
	@make -C clean

fclean: clean
	@echo "$(RED) rm -f $(NAME) $(NC)"
	@echo "$(RED) make -C fclean $(NC)"
	@rm -f $(NAME)
	@make -C fclean

re: fclean all

re_bonus: fclean

.PHONY: all clean fclean