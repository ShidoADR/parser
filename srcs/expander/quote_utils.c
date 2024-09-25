#include "../../headers/minishell.h"

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

char	*handle_single_quote(char *content, int *index)
{
	char	*content_handled;
	int		len;

	len = 1;
	while (content[len] != '\0' && content[len] != '\'')
		len++;
	*index += len + 1;
	content_handled = remove_quote (content, '\'');
	return (content_handled);
}

char	*handle_double_quote(char *content, int *index)
{
	int		i;
	char	*tmp;
	char	*content_handled;
	char	*removed_quote;

	removed_quote = remove_quote (content, '\"');
	if (removed_quote && removed_quote[0] == '\0')
	{
		*index += 2;
		free (removed_quote);
		return (NULL);
	}
	content_handled = NULL;
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
