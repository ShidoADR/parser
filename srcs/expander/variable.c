/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:19:05 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 13:25:14 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	my_isalpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (TRUE);
	if (c >= 'A' && c <= 'Z')
		return (TRUE);
	return (FALSE);
}

void	get_variable(char *content, int *i)
{
	if (content[1] != '\0')
	{
		if (my_isalpha (content[1]) == TRUE || content[1] == '_')
		{
			*i += 1;
			while (content[*i] != '\0')
			{
				if (my_isalpha (content[*i]) == TRUE)
					*i += 1;
				else if (content[*i] == '_')
					*i += 1;
				else if (content[*i] >= '0' && content[*i] <= '9')
					*i += 1;
				else
					break ;
			}
		}
	}
}

t_bool	check_var_content(char *content, int *index)
{
	if (content == NULL)
		return (TRUE);
	if (isquote (content[1]) == TRUE)
	{
		*index += 1;
		return (TRUE);
	}
	return (FALSE);
}

char	*process_dollar_sign(char *removed_quote, int *i, t_token *token)
{
	char	*tmp;

	if (removed_quote[*i + 1] == '\'')
	{
		*i += 1;
		tmp = my_substr ("$", 0, 1);
	}
	else
		tmp = handle_dollar_sign (removed_quote + *i, i, token);
	return (tmp);
}

char	*handle_content(char *removed_quote, t_token *token)
{
	int		i;
	char	*tmp;
	char	*content_handled;

	i = 0;
	content_handled = NULL;
	while (removed_quote[i] != '\0')
	{
		if (removed_quote[i] == '$')
			tmp = process_dollar_sign (removed_quote, &i, token);
		else
			tmp = handle_quoted_text (removed_quote + i, &i);
		content_handled = join_string (&content_handled, &tmp);
	}
	return (content_handled);
}
