/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:07:56 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/30 10:58:48 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	error_type(int type, char **s, t_shell *data)
{
	if (type == 1)
	{
		join_and_print_error("Minishell: ", s[0],
			": No such file or directory\n");
		free_args (data->all_path);
		free_all_tab (s, data);
	}
	if (type == 2)
	{
		join_and_print_error("Minishell: ", s[0], ": Is a directory\n");
		free_args (data->all_path);
		free_all_tab (s, data);
	}
	if (type == 3)
	{
		free_args (data->all_path);
		free_all_tab (s, data);
	}
	if (type == 4)
	{
		join_and_print_error("Minishell: ", s[0], ": Permission denied\n");
		free_args (data->all_path);
		free_all_tab (s, data);
	}
}

void	excute_cmd_with_path(char **s, t_shell *data)
{
	struct stat	statbuf;

	if (execve(s[0], s, data->env) == -1)
	{
		if (lstat(s[0], &statbuf) == -1)
		{
			error_type (1, s, data);
			exit(127);
		}
		if (S_ISDIR(statbuf.st_mode))
			error_type (2, s, data);
		else if (access(s[0], X_OK) == 0)
		{
			error_type (3, s, data);
			exit (EXIT_SUCCESS);
		}
		else
			error_type (4, s, data);
		exit(126);
	}
}

void	execute_cmd_without_path(char **s, t_shell *data)
{
	if (get_env("PATH", data) == NULL)
		exec_path_null(s, data);
	if (test_path(data, s[0]) == 0)
		exec_path_not_null(s, data);
	else
		free_error_exec(s, data);
}

void	join_and_print_error(char *s0, char *s1, char *s2)
{
	char	*minishell;
	char	*tmp;
	char	*tmp2;

	minishell = my_strdup(s0);
	tmp = my_strdup(s2);
	tmp2 = my_strdup(s1);
	tmp = join_string(&tmp2, &tmp);
	tmp = join_string(&minishell, &tmp);
	if (tmp != NULL)
	{
		ft_putstr_fd(tmp, 2);
		free(tmp);
		tmp = NULL;
	}
}

void	free_error_exec(char **s, t_shell *data)
{
	join_and_print_error(NULL, s[0], ": Command not found\n");
	if (s)
		free_args(s);
	if (data->env)
		free_args(data->env);
	if (data->export)
		free_args(data->export);
	exit(127);
}
