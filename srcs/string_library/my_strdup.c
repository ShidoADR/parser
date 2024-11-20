/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:39:25 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 12:44:09 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*my_strdup(char *s)
{
	int		len;
	char	*result;

	len = my_strlen(s);
	result = my_substr(s, 0, len);
	return (result);
}
