/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:51:48 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/28 11:17:47 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t count)

{
	size_t	i;

	i = 0;
	while (i < count)
	{
		*(char *)(str + i) = (char)c;
		i++;
	}
	return (str);
}
