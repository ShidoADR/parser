#include "../../headers/minishell.h"

int	quoted_text_length(char *content, char quote)
{
	int	len;

	len = 1;
	while (content[len] != '\0' && content[len] != quote)
		len++;
	return (len + 1);
}

t_bool	check_space(char *content)
{
	int	i;

	if (content == NULL)
		return (FALSE);
	i = 0;
	while (content[i] != '\0')
	{
		if (my_isspace (content[i]) == TRUE)
		{
			while (my_isspace(content[i]) == TRUE)
				i++;
			if (content[i] != '\0')
				return (TRUE);
			else
				return (FALSE);
		}
		i++;
	}
	return (FALSE);
}

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

char	*expand_variable(char *content, t_token **token, int *index)
{
	int		i;
	char	*result;
	char	*tmp;

	result = handle_dollar_sign (content, index);
	if (check_space (result) == TRUE)
	{
		i = first_value_index (result);
		tmp = my_substr (result, 0, i);
		add_new_token(token, new_token (get_token_type (tmp), tmp));
		while (my_isspace(result[i]) == TRUE)
			i++;
		tmp = my_substr (result, i, my_strlen (result + i));
		free (result);
		result = tmp;
	}
	return (result);
}
