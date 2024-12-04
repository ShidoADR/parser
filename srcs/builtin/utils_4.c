/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:54:53 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/04 13:18:44 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cmd_excve(char **s, t_shell *data, t_command *command)
{
	pid_t	fork_t;

	fork_t = command->pid;
	s = assing_tab(s, command->command, strlen_tab(s));
	clear_command(&data->command);
	if (fork_t == 0)
	{
		search_path(data);
		if (ft_strchr(s[0], '/') != NULL)
			excute_cmd_with_path(s, data);
		else
			execute_cmd_without_path(s, data);
	}
	free_args(s);
	return (data->status);
}

int	search_path(t_shell *data)
{
	char	*pth;
	int		i;

	i = 0;
	pth = NULL;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp("PATH=", data->env[i], 5) == 0)
		{
			pth = ft_my_strcmp2("PATH=", data->env[i]);
			data->all_path = ft_split(pth, ':');
			free(pth);
			return (1);
		}
		i++;
	}
	return (0);
}

int	executable_path(t_shell *data, char *s, char *pths, int i)
{
	char	*tmp;

	pths = ft_strjoin("/", s);
	tmp = pths;
	pths = ft_strjoin(data->all_path[i], pths);
	free(tmp);
	if (access(pths, X_OK) == 0)
	{
		data->path = ft_strdup(pths);
		free(pths);
		free_args(data->all_path);
		return (0);
	}
	free (pths);
	return (1);
}

int	test_path(t_shell *data, char *s)
{
	int		i;
	char	*pths;

	i = -1;
	pths = NULL;
	if (data->all_path == NULL || s == NULL || s[0] == '\0')
		return (1);
	while (data->all_path[++i] != NULL)
	{
		if (executable_path(data, s, pths, i) == 0)
			return (0);
	}
	return (1);
}

char	**ft_fill_data(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i] != NULL)
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
