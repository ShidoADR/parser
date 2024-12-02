/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:31:32 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/29 12:02:09 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_status(t_token *token, int *index)
{
	char	*status;

	status = my_itoa(token->shell->status);
	*index += 2;
	return (status);
}

t_bool	is_special_var(char *content, int *index,
			char **result, t_token *token)
{
	if (content[1] == '?')
	{
		*result = get_status(token, index);
		return (TRUE);
	}
	if (content[1] == '\0' || my_isspace(content[1]) == TRUE)
	{
		*index += 1;
		*result = my_substr("$", 0, 1);
		return (TRUE);
	}
	if (ft_strchr("%^&*+;\':\",.<>/", content[1]) != NULL)
	{
		*index += 2;
		*result = my_substr(content, 0, 2);
		return (TRUE);
	}
	return (FALSE);
}
