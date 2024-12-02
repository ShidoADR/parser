/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:43:32 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/23 11:43:35 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*handle_concat_plus(char *s)
{
	char	*concatenation;

	if (ft_strchr(s, '+'))
	{
		concatenation = ft_substr(s, 0, strlen_nvar(s));
		concatenation = ft_strjoin(concatenation, ft_strchr(s, '='));
		s = ft_strdup(concatenation);
	}
	return (s);
}

char	**update_existing_entry(char **str, char *s, int concat, int i)
{
	char	*concatenation;
	char	*concate2;

	if (ft_strncmp(str[i], s, strlen_nvar(s)) == 0)
	{
		if (concat == 1)
		{
			concate2 = ft_strchr(s, '=');
			concatenation = ft_strchr(str[i], '=');
			if (!concatenation)
				str[i] = ft_strjoin(str[i], "=");
			str[i] = ft_strjoin(str[i], concate2 + 1);
		}
		else if (concat == 0)
		{
			if (!ft_strchr(s, '='))
				return (str);
			free(str[i]);
			str[i] = ft_strdup(s);
		}
		return (str);
	}
	return (NULL);
}

char	**create_new_entry(char **str, char *s)
{
	int	n;

	n = strlen_tab(str) + 1;
	str = re_fill_data(str, s, n);
	return (str);
}

char	**realloc_tab(char **str, char *s, int concat)
{
	int		i;
	char	**result;
	char	*modified_s;

	i = 0;
	modified_s = s;
	modified_s = handle_concat_plus(modified_s);
	while (str[i] != NULL)
	{
		result = update_existing_entry(str, modified_s, concat, i);
		if (result != NULL)
			return (result);
		i++;
	}
	str = create_new_entry(str, modified_s);
	return (str);
}
