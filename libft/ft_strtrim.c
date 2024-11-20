/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 07:04:50 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/16 17:25:00 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(char s, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	size_t	start;
	size_t	end;

	if (s1 == NULL || s1[0] == '\0')
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (*(s1 + start) != '\0' && ft_is_set(*(s1 + start), set))
		start++;
	while (end > 0 && ft_is_set(s1[end], set))
		end--;
	return (ft_substr(s1, start, end - start + 1));
}
