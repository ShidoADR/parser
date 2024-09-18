#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../srcs/get_next_line/get_next_line.h"
# include "color.h"
# include "struct.h"

/*
***--------srcs/token_utils----------
*/

/*
	***--------init_struct.c---------
	*** FUNCTIONS = 5
	*** All functions are used for token manipulation.
*/
int		token_size(t_token *token);
void	add_front(t_token **token, t_token *new_token);
void	delete_token(t_token **token);
void	clear_token(t_token **token);
t_token	*new_token(t_token_type type, char *content);

/*
	***-----------lexer.c------------
*/
t_token	*lexer(char *prompt);

/*
***-------srcs/string_library--------
***	All functions are used for String manipulation
*/
int		my_strlen(const char *s);
int		my_strncmp(const char *s1, const char *s2, size_t n);
char	*my_substr(const char *s, int start, int len);
t_bool	my_isspace(char c);

#endif
