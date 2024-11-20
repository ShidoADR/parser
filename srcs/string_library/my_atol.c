/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:53:24 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/12 11:21:02 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned long	my_atol(const char *str, int *sign)
{
	int i;
	unsigned long long result;

	*sign = 1;
	i = 0;
	result = 0;
	if (str[0] == '+')
		i++;
	if (str[0] == '-')
	{
		*sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}