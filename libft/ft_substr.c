/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 08:49:05 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/07/29 14:18:04 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*mem;
	unsigned int	i;
	unsigned int	length;

	if (s == NULL || start >= ft_strlen(s))
		return (ft_strdup(""));
	length = ft_strlen(s + start);
	if (length < len)
		len = length;
	mem = malloc(sizeof(char) * (len + 1));
	if (!mem)
		return ((char *)0);
	i = start;
	while (i < len + start)
	{
		*(mem + i - start) = *(s + i);
		i++;
	}
	*(mem + i - start) = '\0';
	return (mem);
}
