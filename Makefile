# ------------FUNCTIONS---------------

define check_program
	@ if [ -f $1 ]; \
	 then \
		echo "\r\n\e[1;32m  Build success!\e[0m"; \
	 else \
		echo "\r\n\e[1;31m  Build failure!\e[0m"; \
	 fi
endef

define	loading
		@ echo -n "\033[?25l"
		@ for i in 1 2 3; \
		do \
			echo -n "\033[2K\r"; \
			echo -n "\033[1m$3$1\e[0m"; \
			for j in 1 2 3; \
			do \
				echo -n "."; \
				sleep $2; \
			done; \
		done
		@ echo -n "\033[?25h\r"
endef

# -------------VARIABLES--------------

NAME = minishell

CC = cc

FLAGS = -Wall -Wextra -Werror

INCLUDE_DIR = -I srcs/get_next_line/ -I headers/

LIBRARY = $(addprefix get_next_line/, get_next_line.c get_next_line_utils.c)

MAIN = parser.c

SRCS = $(MAIN) $(addprefix srcs/, $(LIBRARY))

OBJ_DIR = objs

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)


# ---------------RULES----------------


all : $(NAME)

$(OBJ_DIR)/%.o : %.c
	@ mkdir -p $(@D)
	@ $(CC) $(FLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(NAME) : $(OBJS)
	$(call loading, "Compiling", 0.3, \e[1;35m)
	@ $(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDE_DIR)
	$(call check_program, $(NAME))

clean :
	$(call loading, "cleaning", 0.3, \e[1;36m)
	@ rm -rf $(OBJ_DIR)

fclean : clean
	@ rm -f $(NAME)

re : fclean all

.PHONY :
	all clean fclean re
