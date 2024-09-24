#ifndef STRUCT_H
# define STRUCT_H

# include "variable_types.h"

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	type;
}	t_token;

typedef struct s_command
{
	char				*command;
	char				*arguments;
	struct s_command	*left;
	struct s_command	*right;
	struct s_command	*parent;
}	t_command;

typedef struct s_command_table
{
	struct s_command	*command;
	char				*input;
	char				*output;
}	t_command_table;

#endif
