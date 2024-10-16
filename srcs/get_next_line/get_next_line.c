/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:53:48 by hariandr          #+#    #+#             */
/*   Updated: 2024/09/17 14:41:42 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	read_text(int fd, char	**s)
{
	ssize_t	size;

	*s = (char *)malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*s))
		return (0);
	size = read (fd, *s, BUFFER_SIZE);
	if (size <= 0)
	{
		free (*s);
		*s = NULL;
		return (0);
	}
	(*s)[size] = '\0';
	return (1);
}

static char	*return_rest(char **s)
{
	int		i;
	char	*result;

	result = (char *)malloc (sizeof(char) * (count_len(*s) + 1));
	if (!result)
		return (0);
	i = 0;
	while ((*s)[i] != '\0')
	{
		result[i] = (*s)[i];
		i++;
	}
	result[i] = '\0';
	free (*s);
	*s = NULL;
	return (result);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*tmp;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (rest == NULL && (read_text (fd, &rest)) == 0)
		return (NULL);
	while (!(check_new_line (rest)) && (read_text (fd, &tmp)))
	{
		add_text(&rest, tmp);
		free (tmp);
		tmp = NULL;
	}
	if (!(check_new_line (rest)))
		return (return_rest(&rest));
	result = get_result (rest);
	rest = get_rest(&rest);
	return (result);
}
