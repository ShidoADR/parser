/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:53:06 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/09/18 14:42:25 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*mem;
	size_t	i;
	size_t	j;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2);
	mem = malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		mem[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		mem[i + j] = s2[j];
		j++;
	}
	mem[i + j] = '\0';
	// free((char *)s1);
	return (mem);
}
