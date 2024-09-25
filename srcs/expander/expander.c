#include "../../headers/minishell.h"

char	*join_string(char **s1, char **s2)
{
	char	*result;

	result = my_strjoin (*s1, *s2);
	if ((*s1) != NULL)
		free (*s1);
	if ((*s2) != NULL)
		free (*s2);
	*s1 = NULL;
	return (result);
}

char	*handle_dollar_sign(char *content, int *index)
{
	int		i;
	char	*tmp;
	char	*result;

	if (content == NULL)
		return (NULL);
	i = 1;
	while (content[i] != '\0' && content[i] != '$')
	{
		if (my_isspace (content[i]) == TRUE)
			break ;
		if (my_strchr ("<>|", content[i]) != NULL)
			break ;
		if (isquote (content[i]) == TRUE)
			break ;
		i++;
	}
	tmp = my_substr (content, 0, i);
	result = getenv (tmp + 1);
	free (tmp);
	*index += i;
	return (my_substr (result, 0, my_strlen (result)));
}

char	*handle_text(char *content, int *index)
{
	int	i;

	if (content != NULL)
	{
		i = 0;
		while (content[i] != '\0')
		{
			if (isquote (content[i]) == TRUE)
				break ;
			if (content[i] == '$')
				break ;
			i++;
		}
		*index += i;
		return (my_substr (content, 0, i));
	}
	return (NULL);
}

char	*expand_token(char *content)
{
	int		i;
	char	*result;
	char	*tmp;

	result = NULL;
	tmp = NULL;
	if (content != NULL)
	{
		i = 0;
		while (content[i] != '\0')
		{
			if (isquote (content[i]) == TRUE)
				tmp = handle_quote (content + i, &i);
			else if (content[i] == '$')
				tmp = handle_dollar_sign (content + i, &i);
			else
				tmp = handle_text (content + i, &i);
			result = join_string (&result, &tmp);
		}
	}
	return (result);
}

void	expander(t_token **token)
{
	char	*tmp;
	t_token	*first_token;

	first_token = *token;
	while (*token != NULL)
	{
		tmp = (*token)->content;
		(*token)->content = expand_token (tmp);
		free (tmp);
		*token = (*token)->next;
	}
	*token = first_token;
}
