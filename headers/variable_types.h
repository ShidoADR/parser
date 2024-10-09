#ifndef VARIABLE_TYPES_H
# define VARIABLE_TYPES_H

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_token_type;

#endif
