/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:55:41 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/29 11:58:42 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	sort_env(t_shell *data)
{
	int	i;
	int	n;
	int	j;

	i = 0;
	j = 0;
	while (data->export[i] != NULL)
		i++;
	n = i;
	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (strcmp(data->export[j], data -> export[j + 1]) > 0)
				ft_swap_chr(&data->export[j], &data -> export[j + 1]);
			j++;
		}
		i++;
	}
}

int	add_export(t_shell *data, char *s)
{
	int	i;

	i = 0;
	if ((ft_isalpha(s[i]) == 0 && s[i] != '_') || s[i] == '=')
	{
		nt_valid_identifier(s);
		return (1);
	}
	if (!assign_val(data, s))
		return (0);
	return (1);
}

int	length_deleted_env(char **env, char *s)
{
	char	*pth1;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (env[j] != NULL)
	{
		pth1 = ft_substr(env[j], 0, strlen_nvar(env[j]));
		if (my_strcmp(pth1, s) == 0)
			len -= 1;
		if (pth1 != NULL)
			free(pth1);
		len++;
		j++;
	}
	return (len);
}

char	**delete_env(char **env, char *s)
{
	char	**cpy;
	char	*pth1;
	int		len;
	int		j;

	len = length_deleted_env(env, s);
	cpy = malloc(sizeof(char *) * (len + 1));
	len = -1;
	j = 0;
	while (env[j] != NULL)
	{
		pth1 = ft_substr(env[j], 0, strlen_nvar(env[j]));
		if (my_strcmp(pth1, s) == 0)
			j++;
		else
		{
			cpy[++len] = ft_strdup(env[j]);
			j++;
		}
		if (pth1 != NULL)
			free(pth1);
	}
	cpy[len + 1] = NULL;
	free_args(env);
	return (cpy);
}

char	**assing_tab(char **str, char *s, int n)
{
	int		i;
	int		j;
	char	**copy;

	if (s == NULL)
		return (NULL);
	copy = malloc(sizeof(char *) * (n + 2));
	if (!copy)
		return (NULL);
	copy[0] = ft_strdup(s);
	i = 1;
	j = 0;
	while (str != NULL && str[j] != NULL)
	{
		copy[i] = ft_strdup(str[j]);
		i++;
		j++;
	}
	copy[i] = NULL;
	return (copy);
}
