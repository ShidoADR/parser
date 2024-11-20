/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:52:31 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/07/23 08:52:35 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_tab(char **res, int j)
{
	while (j--)
		free(res[j]);
	free(res);
	return (NULL);
}

static size_t	ft_count_word(char const *s, char c)
{
	size_t	word;
	size_t	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

char	**ft_containt(char const *s, char **res, char c)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			count = 0;
			while (s[i + count] && s[i + count] != c)
				count++;
			res[j] = ft_substr(s, i, count);
			if (res[j] == NULL)
				return (free_tab(res, j));
			j++;
			i = i + count;
		}
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	len;

	len = ft_count_word(s, c);
	res = malloc((len + 1) * sizeof(char *));
	if (!s || !res)
		return (NULL);
	return (ft_containt(s, res, c));
}
