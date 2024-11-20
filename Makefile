# ------------FLAGS------------------

MAKEFLAGS += --no-print-directory

# ------------FUNCTIONS---------------

define	check_program
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

FLAGS = -Wall -Wextra -Werror -g

LDFLAGS = -lreadline

INCLUDE_DIR = -I srcs/get_next_line/ -I headers/

LIBFT_DIR = libft

LIBFT = $(LIBFT_DIR)/libft.a

LIBRARY =	$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c) \
			$(addprefix expander/, expand_variable.c expander.c insert_token.c variable.c quote_utils.c \
			status_utils.c) \
			$(addprefix error/, error_handler.c lexer_error.c) \
			$(addprefix lexer/, init_struct.c lexer.c lexer_utils.c) \
			$(addprefix string_library/, my_strlen.c my_strncmp.c my_substr.c my_isspace.c my_strchr.c \
			my_strdup.c my_strjoin.c my_split.c my_itoa.c my_atol.c) \
			$(addprefix parser/, init_command.c parser.c parser_utils.c redir_utils.c) \
			$(addprefix builtin/, builtin.c utils.c signal.c) \
			$(addprefix executor/, executor.c) \
			$(addprefix redirection/, redirection.c heredoc.c)

MAIN = main.c

SRCS = $(addprefix srcs/, $(LIBRARY)) $(MAIN)

OBJ_DIR = objs

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)


# ---------------RULES----------------


all : $(NAME)

$(LIBFT) :
	@ $(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o : %.c
	@ mkdir -p $(@D)
	@ $(CC) $(FLAGS) -c $< -o $@ $(INCLUDE_DIR)

$(NAME) : $(OBJS) $(LIBFT)
	$(call loading, "Compiling", 0, \e[1;35m)
	@ $(CC) $(FLAGS) $(LDFLAGS) $(LIBFT) $(OBJS) -o $(NAME) -Llibft -lft $(INCLUDE_DIR)
	$(call check_program, $(NAME))

clean :
	$(call loading, "cleaning", 0, \e[1;36m)
	@ rm -rf $(OBJ_DIR)
	@ make -C $(LIBFT_DIR) clean

fclean : clean
	@ rm -f $(NAME)
	@ make -C $(LIBFT_DIR) fclean

re : fclean all

.PHONY :
	all clean fclean re
