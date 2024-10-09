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
			return (TRUE);
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

int	trim_space(char *content)
{
	int	i;

	i = 0;
	while (content[i] == ' ')
		i++;
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

char	*expand_variable(char **s, char *content, t_token **token, int *i)
{
	int		j;
	int		trim;
	char	*result;
	char	*tmp;

	result = handle_dollar_sign (content, i);
	if (check_space (result) == TRUE)
	{
		trim = 0;
		if (my_isspace (result[0]) == TRUE)
		{
			tmp = my_substr (*s, 0, my_strlen (*s));
			add_new_token (token, new_token (get_token_type (tmp), tmp));
			free (*s);
			*s = NULL;
			trim = trim_space (result);
		}
		j = first_value_index (result + trim);
		tmp = my_substr (result, trim, j);
		if (*s != NULL)
			tmp = join_string (s, &tmp);
		*s = NULL;
		if (my_isspace (result[j + trim]) == TRUE)
		{
			add_new_token(token, new_token (get_token_type (tmp), tmp));
			while (result[j + trim] != '\0' && my_isspace(result[j + trim]) == TRUE)
				j++;
			if (result[j + trim] == '\0')
				tmp = NULL;
			else
				tmp = my_substr (result, j + trim, my_strlen (result + j + trim));
		}
		free (result);
		result = tmp;
	}
	return (result);
}
