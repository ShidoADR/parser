#include "../../headers/minishell.h"

char	*remove_quote(char *content, char quote)
{
	int		len;
	char	*result;

	result = NULL;
	if (content != NULL)
	{
		len = 0;
		while (content[len + 1] != '\0')
		{
			if (content[len + 1] == quote)
				break ;
			len++;
		}
		result = my_substr (content, 1, len);
	}
	return (result);
}

char	*join_string(char **s1, char **s2)
{
	char	*result;

	result = my_strjoin (*s1, *s2);
	if ((*s1) != NULL)
		free (*s1);
	*s1 = NULL;
	return (result);
}

char	*handle_single_quote(char *content, int *index)
{
	char	*content_handled;
	int		len;

	len = 1;
	while (content[len] != '\0' && content[len] != '\'')
		len++;
	*index += len;
	content_handled = remove_quote (content, '\'');
	return (content_handled);
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
	return (result);
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

char	*handle_quoted_text(char *content, int *index)
{
	int	i;

	if (content != NULL)
	{
		i = 0;
		while (content[i] != '\0')
		{
			if (content[i] == '$')
				break ;
			i++;
		}
		*index += i;
		return (my_substr (content, 0, i));
	}
	return (NULL);
}

char	*handle_double_quote(char *content, int *index)
{
	int		i;
	char	*tmp;
	char	*content_handled;
	char	*removed_quote;

	removed_quote = remove_quote (content, '\"');
	content_handled = NULL;
	tmp = NULL;
	i = 0;
	while (removed_quote[i] != '\0')
	{
		if (removed_quote[i] == '$')
			tmp = handle_dollar_sign (removed_quote + i, &i);
		else
			tmp = handle_quoted_text (removed_quote + i, &i);
		content_handled = join_string (&content_handled, &tmp);
	}
	*index += my_strlen (content);
	free (removed_quote);
	return (content_handled);
}

char	*handle_quote(char *content, int *index)
{
	int		i;
	char	*result;

	result = NULL;
	if (content != NULL)
	{
		i = 0;
		if (content[i] == '\'')
			result = handle_single_quote (content, &i);
		else
			result = handle_double_quote (content, &i);
		*index += i;
	}
	return (result);
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
			printf ("eto %s\n", result);
			printf ("aty %s\n", content + i);
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
