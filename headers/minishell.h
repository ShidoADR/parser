#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../srcs/get_next_line/get_next_line.h"
# include "color.h"
# include "struct.h"

/*
***---------srcs/expander-----------
*/
void	expander(t_token **token);

/*
***----------srcs/lexer-------------
*/

/*
	***--------init_struct.c---------
*/
int				token_size(t_token *token);
void			add_back(t_token **token, t_token *new_token);
void			delete_token(t_token **token);
void			clear_token(t_token **token);
t_token			*new_token(t_token_type type, char *content);

/*
	***--------lexer_utils.c---------
*/
t_bool			isquote(char c);
t_bool			is_special_token(char *prompt);
t_token			*last_token(t_token **token);

/*
	***-----------lexer.c------------
*/
int				find_next_quote(char *prompt, char quote);
char			*get_token(char *prompt, int *i);
t_token			*lexer(char *prompt);
t_token_type	get_token_type(char *content);

/*
***-------srcs/string_library--------
*/
int				my_strlen(const char *s);
int				my_strncmp(const char *s1, const char *s2, size_t n);
char			*my_strchr(const char *s, int c);
char			*my_strjoin(const char *s1, const char *s2);
char			*my_substr(const char *s, int start, int len);
t_bool			my_isspace(char c);

#endif
