/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:23:53 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/16 15:42:39 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include <stdlib.h>

char	*join_string(char **s1, char **s2)
{
	char	*result;

	result = my_strjoin (*s1, *s2);
	if ((*s1) != NULL)
		free (*s1);
	if ((*s2) != NULL)
		free (*s2);
	*s2 = NULL;
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
	if (content[1] == '\0')
	{
		*index += 1;
		return (my_substr ("$", 0, 1));
	}
	if (isquote (content[1]) == TRUE)
	{
		*index += 1;
		return (NULL);
	}
	i = 1;
	get_variable (content, &i);
	tmp = my_substr (content, 0, i);
	result = getenv (tmp + 1);
	free (tmp);
	if (i == 1)
		i += 1;
	*index += i;
	if (result == NULL)
		return (NULL);
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
				tmp = expand_variable (&result, content + i, token, &i);
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
	while (first_token != NULL && first_token->prev != NULL)
		first_token = first_token->prev;
	*token = first_token;
}
