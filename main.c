/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 12:24:13 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:11:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 07:39:42 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t	g_sig = 0;

void	exit_with_status(t_command *command, t_shell *shell)
{
	char			*status;
	int				status_sign;
	unsigned long	status_value;

	status = ft_strtrim(command->arguments[0], " ");
	if (is_valid_status(status) == FALSE)
	{
		clear_shell(shell);
		free(status);
		status = NULL;
		exit(2);
	}
	status_value = my_atol(status, &status_sign);
	if (check_status_value(status_value, status, status_sign) == FALSE)
	{
		clear_shell(shell);
		free(status);
		status = NULL;
		exit(2);
	}
	clear_shell(shell);
	free(status);
	status = NULL;
	exit (status_value * status_sign);
}

t_status	exit_with_arg(t_command *command, t_shell *shell)
{
	if (chain_len(command->arguments) != 1)
	{
		if (is_valid_status(command->arguments[0]) == FALSE)
		{
			clear_shell(shell);
			exit(2);
		}
		clear_command(&shell->command);
		print_custom_error("exit : too many arguments\n");
		return (1);
	}
	exit_with_status(command, shell);
	return (0);
}

int	exit_shell(t_command *command, t_shell *shell)
{
	int	status;

	status = shell->status;
	if (command->next == NULL)
		ft_putstr_fd("exit\n", 0);
	if (command->arguments != NULL)
	{
		if (exit_with_arg(command, shell) == 1)
			return (1);
	}
	else
	{
		clear_shell(shell);
		exit(status);
	}
	return (0);
}

void	launch_executor(t_shell *shell)
{
	char	**args;
	char	*cmds;

	if (shell->command != NULL)
	{
		cmds = shell->command->command;
		if (command_size(shell->command) == 1)
		{
			if (builtin(shell->command) == 0)
			{
				args = shell->command->arguments;
				shell->status = exec_builtins(shell, cmds, args);
			}
			else
				shell->status = cmd_pipe(shell, &shell->command);
		}
		else
			shell->status = cmd_pipe(shell, &shell->command);
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell = init_shell(env);
	shell.prompt = NULL;
	while (1)
	{
		my_signal();
		shell.prompt = readline("minishell>> ");
		if (shell.prompt == NULL)
			exit_signal(&shell);
		if (g_sig)
		{
			shell.status = g_sig;
			g_sig = 0;
		}
		if (shell.prompt[0] != '\0')
			add_history(shell.prompt);
		if (to_parse(&shell) == 0)
			launch_executor(&shell);
	}
	return (shell.status);
}
