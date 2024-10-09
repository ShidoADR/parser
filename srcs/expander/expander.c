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
		if (my_isspace (content[i]) == TRUE || isquote (content[i]) == TRUE)
			break ;
		if (my_strchr ("<>|", content[i]) != NULL)
			break ;
		i++;
		if (content[i - 1] >= '0' && content[i - 1] <= '9')
			break ;
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

char	*expand_token(char *content, t_token **token)
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
				tmp = expand_variable (content + i, token, &i);
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
		if ((*token)->type != HEREDOC)
		{
			tmp = (*token)->content;
			(*token)->content = expand_token (tmp, token);
			free (tmp);
			*token = (*token)->next;
		}
		else
		{
			if ((*token)->next != NULL && (*token)->next->type == WORD)
				*token = (*token)->next->next;
			else
				*token = (*token)->next;
		}
	}
	if (first_token->prev == NULL)
		*token = first_token;
	else
		*token = first_token->prev;
}
