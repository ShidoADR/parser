/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:30:14 by hariandr          #+#    #+#             */
/*   Updated: 2024/09/18 17:30:54 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*my_strchr(const char *s, int c)
{
	char	*ch;

	ch = (char *)s;
	while (*ch)
	{
		if ((char)c == *ch)
			return (ch);
		ch++;
	}
	if ((char)c == '\0')
		return (ch);
	return (0);
}
