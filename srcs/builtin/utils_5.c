/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:43:32 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/02 14:44:32 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**update_existing_entry(char **str, char *s, int i)
{
	if (ft_strncmp(str[i], s, strlen_nvar(s)) == 0)
	{
		if (s && !ft_strchr(s, '='))
			return (str);
		free(str[i]);
		str[i] = my_strdup(s);
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

char	**realloc_tab(char **str, char *s)
{
	int		i;
	char	**result;
	char	*modified_s;

	i = 0;
	modified_s = s;
	while (str[i] != NULL)
	{
		result = update_existing_entry(str, modified_s, i);
		if (result != NULL)
			return (result);
		i++;
	}
	str = create_new_entry(str, modified_s);
	return (str);
}
