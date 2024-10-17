/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:54:57 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/17 14:37:25 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_token_type	get_token_type(char *content)
{
	if (content[0] == '|')
		return (PIPE);
	if (content[0] && content[1])
	{
		if (content[0] == '>' && content[1] == '>')
			return (APPEND);
	}
	if (content[0] && content[1])
	{
		if (content[0] == '<' && content[1] == '<')
			return (HEREDOC);
	}
	if (content[0] == '>')
		return (REDIR_OUT);
	if (content[0] == '<')
		return (REDIR_IN);
	else
		return (WORD);
}

int	find_next_quote(char *prompt, char quote)
{
	int	len;

	if (prompt == NULL)
		return (0);
	len = 0;
	while (prompt[len] != '\0' && prompt[len] != quote)
		len++;
	if (prompt[len] == '\0')
		return (len - 1);
	return (len + 1);
}

char	*get_token(char *prompt, int *i)
{
	int	j;

	if (my_strchr ("<>|", prompt[0]))
	{
		if (is_special_token (prompt) == TRUE)
		{
			*i += 1;
			return (my_substr (prompt, 0, 2));
		}
		return (my_substr (prompt, 0, 1));
	}
	j = 0;
	while (prompt[j] != '\0' && my_isspace (prompt[j]) == FALSE)
	{
		if (isquote (prompt[j]) == TRUE)
			j += find_next_quote (&prompt[j] + 1, prompt[j]);
		if (my_strchr("<>|", prompt[j]) != NULL)
		{
			*i += j - 1;
			return (my_substr (prompt, 0, j));
		}
		j++;
	}
	*i += j;
	return (my_substr (prompt, 0, j));
}

t_token	*lexer(char *prompt)
{
	int		i;
	char	*tmp;
	t_token	*token;

	if (prompt == NULL)
		return (NULL);
	token = NULL;
	i = 0;
	while (prompt[i] != '\0' && prompt[i] != '\n')
	{
		while (my_isspace (prompt[i]) == TRUE)
			i++;
		if (prompt[i] == '\0')
			return (token);
		tmp = get_token (prompt + i, &i);
		add_back (&token, new_token (get_token_type (tmp), tmp));
		i++;
	}
	return (token);
}
