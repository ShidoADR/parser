/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:04:49 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/20 14:11:27 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*expand_variable(char **s, char *content, t_token **token, int *i)
{
	char	*tmp;
	char	*result;
	char	**chain;
	t_bool	is_space;

	result = handle_dollar_sign (content, i, *token);
	if (check_space (result) == TRUE)
	{
		chain = my_split (result);
		if (chain != NULL)
		{
			check_token (token, &result, chain, s);
			tmp = chain[chain_len (chain) - 1];
			is_space = my_isspace (result[my_strlen (result) - 1]) == TRUE;
			free (result);
			result = NULL;
			if (is_space)
				add_new_token (token, new_token (WORD, tmp, (*token)->shell));
			else
				result = tmp;
			free (chain);
		}
	}
	return (result);
}
