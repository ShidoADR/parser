/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 13:47:50 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 12:21:56 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_quote_closed(char *content, char quote, int *i)
{
	int	len;

	if (content == NULL)
		return (0);
	len = 0;
	while (content[len] != '\0' && content[len] != quote)
		len++;
	*i += len + 2;
	if (content[len] == '\0')
		return (FALSE);
	return (TRUE);
}

t_status	check_word(char *content)
{
	int		i;
	char	quote;

	if (content != NULL)
	{
		i = 0;
		while (content[i] != '\0')
		{
			if (isquote (content[i]) == TRUE)
			{
				quote = content[i];
				if (is_quote_closed (content + i + 1, quote, &i) == FALSE)
				{
					print_custom_error ("unexpected EOF while looking");
					write (2, " for matching `", 15);
					write (2, &quote, 1);
					write (2, "\'\n", 2);
					return (2);
				}
			}
			else
				i++;
		}
	}
	return (0);
}

t_status	is_valid_redir(t_token *token)
{
	t_token		*next;

	if (token->next == NULL)
	{
		print_custom_error ("syntax error near unexpected token `newline\'\n");
		return (2);
	}
	next = token->next;
	if (token->type == REDIR_IN && token->next->type == REDIR_OUT)
		return (0);
	if (token->next->type != WORD)
	{
		print_custom_error("syntax error near unexpected token `");
		write (2, next->content, my_strlen (next->content));
		write (2, "\'\n", 2);
		return (2);
	}
	return (0);
}

t_status	is_valid_pipe(t_token *token)
{
	if (token->next == NULL || token->prev == NULL)
	{
		print_custom_error ("syntax error near unexpected token `|\'\n");
		return (2);
	}
	if (token->next->type != WORD || token->prev->type != WORD)
	{
		print_custom_error ("syntax error near unexpected token `|\'\n");
		return (2);
	}
	return (0);
}

t_status	is_valid_token(t_token *token)
{
	if (token != NULL)
	{
		while (token != NULL)
		{
			if (token->type > 1 && is_valid_redir(token) == 2)
				return (2);
			if (token->type == PIPE && is_valid_pipe(token) == 2)
				return (2);
			if (token->type == WORD && check_word (token->content) != 0)
				return (2);
			token = token->next;
		}
	}
	return (0);
}
