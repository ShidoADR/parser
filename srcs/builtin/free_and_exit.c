/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 11:19:30 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:46:25 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/02 07:49:35 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	clear_shell(t_shell *shell)
{
	if (shell != NULL)
	{
		if (shell->env != NULL)
			free_args(shell->env);
		shell->env = NULL;
		if (shell->export != NULL)
			free_args(shell->export);
		shell->export = NULL;
		clear_command(&shell->command);
	}
}

void	exit_signal(t_shell *shell)
{
	ft_putendl_fd("exit", 0);
	clear_shell(shell);
	exit(shell->status);
}

void	restore_fd(int backup[2])
{
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close_fd(backup);
}
