/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:19:05 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/16 15:28:12 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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