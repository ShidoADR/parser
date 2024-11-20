/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 15:31:32 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/09/17 13:54:06 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	size_t			len;
	unsigned char	*string1;
	unsigned char	*string2;

	i = 0;
	string1 = (unsigned char *)(s1);
	string2 = (unsigned char *)(s2);
	len = n - 1;
	if (n == 0)
		return (0);
	while ((i < len) && s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (*(string1 + i) - *(string2 + i));
}
