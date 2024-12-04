/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 13:20:12 by lrasamoe         ###   ########.fr       */
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
		if (my_isspace(content[i]) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_bool	is_chain_null(char **chain, char **result)
{
	if (chain_len(chain) == 0)
	{
		free_args(chain);
		free (*result);
		*result = NULL;
		return (TRUE);
	}
	return (FALSE);
}

void	check_ambiguous(char **s, char *content, t_token **token)
{
	char	*tmp;
	char	*temp;
	char	**c;

	if ((*token)->prev->type != HEREDOC)
	{
		tmp = my_strdup (*s);
		temp = handle_content (content, *token);
		temp = join_string (&tmp, &temp);
		if (temp != NULL)
		{
			c = my_split (temp);
			if (chain_len (c) == 0 || chain_len (c) > 1)
				(*token)->shell->is_ambigous = TRUE;
			free (temp);
			free_args (c);
		}
	}
}

char	*expand_variable(char **s, char *content, t_token **token, int *i)
{
	char	*tmp;
	char	*result;
	char	**chain;
	t_bool	is_space;

	result = handle_dollar_sign(content, i, *token);
	if (check_space(result) == TRUE)
	{
		chain = my_split(result);
		if (check_redir((*token)->prev) == TRUE)
			check_ambiguous (s, content, token);
		if (chain == NULL || is_chain_null(chain, &result) == TRUE)
			return (my_strdup(" "));
		check_token(token, &result, chain, s);
		tmp = chain[chain_len(chain) - 1];
		is_space = my_isspace(result[my_strlen(result) - 1]) == TRUE;
		free(result);
		result = NULL;
		if (is_space == TRUE)
			add_new_token(token, new_token(WORD, tmp, (*token)->shell));
		else
			result = tmp;
		free (chain);
	}
	return (result);
}
