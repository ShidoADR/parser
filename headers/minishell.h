#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../srcs/get_next_line/get_next_line.h"
# include "color.h"
# include "struct.h"

/*
***-----------srcs/error-------------
*/
	/*
	***--------error_handler.c-----------
	*/
void			print_error(char *s, int status);
void			print_custom_error(char *s, int status);

/*
***---------srcs/expander-----------
*/
	/*
	***------expand_variable.c-------
	*/
t_bool			check_space(char *content);
int				first_value_index(char *content);
int				quoted_text_length(char *content, char quote);
void			add_new_token(t_token **token, t_token *new_token);
char			*expand_variable(char **s, char *content, t_token **token,
					int *i);

	/*
	***--------expander.c-----------
	*/
void			expander(t_token **token);
char			*join_string(char **s1, char **s2);
char			*handle_text(char *content, int *index);
char			*expand_token(char *content, t_token **token);
char			*handle_dollar_sign(char *content, int *index);

	/*
	***--------is_variable.c----------
	*/
t_bool			my_isalpha(char c);
void			get_variable(char *content, int *i);

	/*
	***-------quote_utils.c----------
	*/
char			*remove_quote(char *content, char quote);
char			*handle_quote(char *content, int *index);
char			*handle_quoted_text(char *content, int *index);
char			*handle_single_quote(char *content, int *index);
char			*handle_double_quote(char *content, int *index);

/*
***----------srcs/lexer-------------
*/

	/*
	***--------init_struct.c---------
	*/
int				token_size(t_token *token);
void			clear_token(t_token **token);
void			delete_token(t_token **token);
t_token			*new_token(t_token_type type, char *content);
void			add_back(t_token **token, t_token *new_token);

	/*
	***--------lexer_utils.c---------
	*/
t_bool			isquote(char c);
t_token			*last_token(t_token **token);
t_bool			is_special_token(char *prompt);

	/*
	***-----------lexer.c------------
	*/
t_token			*lexer(char *prompt);
t_token_type	get_token_type(char *content);
char			*get_token(char *prompt, int *i);
int				find_next_quote(char *prompt, char quote);

/*
***-------srcs/string_library--------
*/
t_bool			my_isspace(char c);
int				my_strlen(const char *s);
char			*my_strchr(const char *s, int c);
char			**my_split(char const *s);
char			*my_strjoin(const char *s1, const char *s2);
char			*my_substr(const char *s, int start, int len);
int				my_strncmp(const char *s1, const char *s2, size_t n);

#endif
