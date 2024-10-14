#include "../../headers/minishell.h"

int	first_value_index(char *content)
{
	int	i;

	i = 0;
	while (content[i] != '\0')
	{
		if (my_isspace (content[i]) == TRUE)
			return (i);
		i++;
	}
	return (i);
}

void	add_new_token(t_token **token, t_token *new_token)
{
	t_token	*tmp;

	tmp = (*token)->prev;
	(*token)->prev = new_token;
	new_token->next = (*token);
	new_token->prev = tmp;
	if (tmp != NULL)
		tmp->next = new_token;
}

void	insert_token(t_token **token, char **chain)
{
	int	i;

	i = 0;
	while (chain[i] != NULL)
	{
		if (chain[i + 1] == NULL)
			break ;
		add_new_token (token, new_token (WORD, chain[i]));
		i++;
	}
}

int	chain_len(char **chain)
{
	int	len;

	len = 0;
	while (chain[len] != NULL)
		len++;
	return (len);
}

void	check_token(t_token **token, char **result, char **chain, char **s)
{
	char	*tmp;

	if (*s != NULL && my_isspace (*result[0]) == TRUE)
	{
		tmp = my_substr (*s, 0, my_strlen (*s));
		free (*s);
		*s = NULL;
		add_new_token (token, new_token (WORD, tmp));
	}
	else if (*s != NULL)
		chain[0] = join_string (s, &chain[0]);
	insert_token (token, chain);
}
