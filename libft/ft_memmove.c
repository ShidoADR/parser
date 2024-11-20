/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:51:38 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/07/23 08:51:45 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			*(d + i) = *(s + i);
			i++;
		}
	}
	if (dest > src)
	{
		i = n - 1;
		while (i < n)
		{
			*(d + i) = *(s + i);
			i--;
		}
	}
	return (dest);
}
