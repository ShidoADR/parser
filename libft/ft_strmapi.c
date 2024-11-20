/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:18:55 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/07/23 08:53:33 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*mem;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	if (!s && !f)
		return (NULL);
	mem = malloc(sizeof(char) * (len + 1));
	if (!mem)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mem[i] = f(i, (s[i]));
		i++;
	}
	mem[i] = '\0';
	return (mem);
}
