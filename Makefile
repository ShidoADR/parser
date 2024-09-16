define	loading
	@ echo -n "\033[?25l"
	@ for i in 1 2 3; \
	do \
		echo -n "\r\033[1m$3$1\e[0m"; \
		for j in 1 2 3; \
		do \
			echo -n "."; \
			sleep $2; \
		done; \
		echo -n "\033[2K"; \
	done
	@ echo -n "\033[?25h\r"
endef

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror

MAIN = parser.c

SRCS = $(MAIN)

OBJ_DIR = objs

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

all : $(NAME)

$(OBJ_DIR)/%.o : %.c
	@ mkdir -p $(@D)
	@ $(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(call loading, "Compiling", 0.5, \e[1;35m)
	@ $(CC) $(FLAGS) $(OBJS) -o $(NAME)
	@ echo "\r\e[1;32mBuild success!\e[0m"

clean :
	$(call loading, "cleaning", 0.3, \e[1;36m)
	@ rm -rf $(OBJ_DIR)

fclean : clean
	@ rm -f $(NAME)

re : fclean all

.PHONY :
	all clean fclean re
