/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:53:24 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 13:58:05 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

unsigned long	my_atol(const char *str, int *sign)
{
	int					i;
	unsigned long long	result;

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
		if (*sign == -1 && result > 9223372036854775808ULL)
			*sign = -2;
		if (*sign == 1 && result > 9223372036854775807ULL)
			*sign = -2;
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}
