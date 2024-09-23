#include "../../headers/minishell.h"

t_token	*last_token(t_token **token)
{
	if (*token == NULL)
		return (NULL);
	if ((*token)->next != NULL)
		return (last_token (&(*token)->next));
	return (*token);
}

t_bool	isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	else
		return (FALSE);
}

t_bool	is_special_token(char *prompt)
{
	if (get_token_type (prompt) == APPEND)
		return (TRUE);
	if (get_token_type (prompt) == HEREDOC)
		return (TRUE);
	return (FALSE);
}
