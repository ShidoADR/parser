/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:31:12 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/02 08:24:40 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	exec_path_null(char **s, t_shell *data)
{
	struct stat	statbuf;

	if (lstat(s[0], &statbuf) == 0 && execve(s[0], s, data->env) == -1)
	{
		if (my_strcmp(s[0], ".") == 0)
		{
			join_and_print_error("Minishell", s[0],
				": filename argument required\n");
			free (data->path);
			free_all_tab (s, data);
			exit(2);
		}
		join_and_print_error("Minishell:", s[0], ": Permission denied\n");
		free_all_tab(s, data);
		exit(126);
	}
	else
	{
		join_and_print_error("Minishell: ", s[0],
			": No such file or directory\n");
		free_all_tab(s, data);
		exit(127);
	}
}

void	exec_path_not_null(char **s, t_shell *data)
{
	if (execve(data->path, s, data->env) == -1)
	{
		if (my_strcmp(s[0], ".") == 0)
		{
			join_and_print_error("Minishell", s[0],
				": filename argument required\n");
			free (data->path);
			free_all_tab (s, data);
			exit(2);
		}
		join_and_print_error(NULL, s[0], ": Command not found\n");
		free (data->path);
		free_all_tab(s, data);
		exit(127);
	}
}
