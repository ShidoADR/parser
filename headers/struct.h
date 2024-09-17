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

typedef struct s_data
{
	char			*prompt;
	struct s_token	*token;
}	t_data;

#endif
