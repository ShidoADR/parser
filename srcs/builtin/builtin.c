/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 12:36:45 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/04 13:17:48 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	cd_to_directory(char **s, int i)
{
	if (s[i] && s[i + 1])
	{
		print_custom_error("cd: too many arguments\n");
		return (1);
	}
	else if (s[i] == NULL || chdir(s[i]) == -1)
	{
		if (ft_strlen(s[i]) == 0)
			print_custom_error("cd: HOME not set\n");
		else
		{
			ft_putstr_fd("cd: ", 2);
			perror(s[i]);
		}
		return (1);
	}
	return (0);
}

int	cd_to_oldpwd(t_shell *data, char **old_pwd)
{
	char	*old;

	old = get_env("OLDPWD", data);
	if (old == NULL || chdir(old) == -1)
	{
		print_custom_error("cd: OLDPWD not set\n");
		if (*old_pwd != NULL)
			free (*old_pwd);
		return (1);
	}
	ft_putendl_fd(get_env("OLDPWD", data), 1);
	return (0);
}

int	cd_to_home(t_shell *data, char **old_pwd)
{
	char	*home;

	home = get_env ("HOME", data);
	if (home == NULL || chdir (home) == -1)
	{
		print_custom_error("cd: HOME not set\n");
		if (*old_pwd != NULL)
			free (*old_pwd);
		return (1);
	}
	return (0);
}

int	ft_cd(char **s, t_shell *data)
{
	int		i;
	char	*old_pwd;

	old_pwd = my_strdup(get_env("PWD", data));
	i = 0;
	if (s == NULL || my_strcmp(s[i], "~") == 0 || my_strcmp(s[i], "~/") == 0
		|| my_strcmp(s[i], "--") == 0)
	{
		if (cd_to_home(data, &old_pwd) == 1)
			return (1);
	}
	else if ((my_strcmp(s[i], "-") == 0))
	{
		if (cd_to_oldpwd(data, &old_pwd) == 1)
			return (1);
	}
	else if (cd_to_directory(s, i) == 1)
	{
		free(old_pwd);
		old_pwd = NULL;
		return (1);
	}
	update_and_free(&old_pwd, data);
	return (0);
}
