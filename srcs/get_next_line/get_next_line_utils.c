/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:53:48 by hariandr          #+#    #+#             */
/*   Updated: 2024/09/17 14:41:55 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_new_line(char	*s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		return (1);
	return (0);
}

int	count_len(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	add_text(char **s1, char *s2)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = count_len (*s1) + count_len (s2);
	result = (char *)malloc (sizeof(char) * (len + 1));
	if (!result)
		return ;
	i = 0;
	while ((*s1)[i] != '\0')
	{
		result[i] = (*s1)[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	free (*s1);
	*s1 = result;
}

char	*get_result(char *s)
{
	int		len;
	int		i;
	char	*result;

	len = 0;
	while (s[len] != '\n')
		len++;
	result = (char *)malloc (sizeof(char) * (len + 2));
	if (!result)
		return (0);
	i = 0;
	while (s[i] != '\n')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\n';
	result[i + 1] = '\0';
	return (result);
}

char	*get_rest(char **s)
{
	int		len;
	int		i;
	char	*rest;

	len = 0;
	while ((*s)[len] != '\n')
		len++;
	if ((*s)[len + 1] != '\0')
	{
		rest = (char *)malloc (sizeof(char) * (count_len (*s) - len));
		i = 0;
		len++;
		while ((*s)[len] != '\0')
		{
			rest[i] = (*s)[len];
			i++;
			len++;
		}
		rest[i] = '\0';
		free (*s);
		return (rest);
	}
	free (*s);
	return (NULL);
}
