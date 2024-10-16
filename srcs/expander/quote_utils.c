/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:20:23 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/16 15:28:35 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	*index += quoted_text_length (content, '\'');
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
		return (removed_quote);
	}
	if (removed_quote == NULL)
		return (NULL);
	content_handled = NULL;
	i = 0;
	while (removed_quote[i] != '\0')
	{
		if (removed_quote[i] == '$')
		{
			if (removed_quote[i + 1] == '\'')
			{
				i += 1;
				tmp = my_substr ("$", 0, 1);
			}
			else
				tmp = handle_dollar_sign (removed_quote + i, &i);
		}
		else
			tmp = handle_quoted_text (removed_quote + i, &i);
		content_handled = join_string (&content_handled, &tmp);
	}
	*index += quoted_text_length (content, '\"');
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
