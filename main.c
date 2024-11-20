/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:37 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/20 13:06:26 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t g_sig = 0;

void	print_token(t_token *token)
{
	if (token != NULL)
	{
		while (token != NULL)
		{
			printf("{type = %d, value = %s}\n", token->type, token->content);
			token = token->next;
		}
	}
}

void	print_args(char **args)
{
	int	i;

	if (args != NULL)
	{
		i = 0;
		while (args[i] != NULL)
		{
			printf("%s ", args[i]);
			i++;
		}
	}
}

void	print_command(t_command *command)
{
	if (command != NULL)
	{
		while (command != NULL)
		{
			printf("{command = %s, arg = ", command->command);
			print_args(command->arguments);
			printf("}\n");
			command = command->next;
		}
	}
}

void	print_prompt(void)
{
	printf(VIBRANT_BLUE BOLD_UNDERLINED "MiniShell" RESET " :");
	printf(DARK_GREEN BOLD " %s " RESET "in ", getenv("USER"));
	printf(LIGHT_BLUE ITALIC "%s\n", getenv("PWD"));
	printf(RED "->" RESET "\n");
	write(0, "  \033[A", 5);
}

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

t_shell	init_shell(char **env)
{
	t_shell	shell;

	shell.env = ft_fill_data(env);
	shell.export = ft_fill_data(env);
	sort_env(&shell);
	shell.status = 0;
	return (shell);
}

t_status	to_parse(t_shell *shell)
{
	t_status	valid;

	valid = 0;
	shell->token = lexer(shell->prompt, shell);
	if (is_valid_token(shell->token) == 0)
	{
		expander(&shell->token);
		shell->command = parser(&shell->token);
	}
	else
	{
		shell->status = 2;
		valid = 2;
	}
	clear_token(&shell->token);
	free(shell->prompt);
	return (valid);
}

void	clear_command_table(t_command_table *table)
{
	if (table != NULL)
	{
		clear_token(&table->redir);
		clear_command(&table->command);
		table->redir = NULL;
		table->command = NULL;
	}
}

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
		clear_command_table(&shell->command);
	}
}

t_bool	is_numeric(char *s)
{
	int	i;

	if (s == NULL)
		return (FALSE);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (FALSE);
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	is_valid_status(char *status)
{
	if (is_numeric(status) == FALSE)
	{
		print_custom_error("exit : ");
		write(2, status, my_strlen(status));
		ft_putstr_fd(" : numeric argument required\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	check_status_value(unsigned long status_value, char *status, int sign)
{
	if (sign == -1 && status_value > 9223372036854775808ULL)
	{
		print_custom_error("exit : ");
		write(2, status, my_strlen(status));
		ft_putstr_fd(" : numeric argument required\n", 2);
		return (FALSE);
	}
	if (sign == 1 && status_value > 9223372036854775807ULL)
	{
		print_custom_error("exit : ");
		write(2, status, my_strlen(status));
		ft_putstr_fd(" : numeric argument required\n", 2);
		return (FALSE);
	}
	return (TRUE);
}

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
	exit(status_value * status_sign);
}

int	exit_shell(t_command *command, t_shell *shell)
{
	int	status;

	printf("exit\n");
	status = shell->status;
	if (command->arguments != NULL)
	{
		if (chain_len(command->arguments) != 1)
		{
			if (is_valid_status(command->arguments[0]) == FALSE)
			{
				clear_shell(shell);
				exit(2);
			}
			clear_command_table (&shell->command);
			print_custom_error("exit : too many arguments\n");
			return (1);
		}
		else
			exit_with_status(command, shell);
	}
	else
	{
		clear_shell(shell);
		exit(status);
	}
	return (0);
}

int	cmd(t_shell *data, t_command *command)
{
	char	**args;

	args = command->arguments;
	if ((strcmp(command->command, "echo") == 0))
		return (ft_echo(args));
	else if ((strcmp(command->command, "pwd") == 0))
		return (ft_pwd());
	else if ((strcmp(command->command, "cd") == 0))
		return (ft_cd(args, data));
	else if ((strcmp(command->command, "env") == 0))
		return (ft_env(data));
	else if ((strcmp(command->command, "export") == 0))
		return (ft_export(data, args));
	else if ((strcmp(command->command, "unset") == 0))
		return (ft_unset(data, args));
	else if ((strcmp(command->command, "exit") == 0))
		return (exit_shell(command, data));
	else
		return (cmd_excve(args, data, command));
	return (0);
}

void	launch_executor(t_shell *shell)
{
	// if (command_size(shell->command.command) == 1 
	// && shell->command.redir == NULL)
	// {
	// 	shell->status = cmd(shell, shell->command.command);
	// }
	// else 
	shell->status = cmd_pipe(shell, &shell->command.command);
}


int	main(int ac, char **av, char **env)
{
	t_shell	shell;
	// int		signal;

	(void)ac;
	(void)av;
	shell = init_shell(env);
	shell.prompt = NULL;
	while (1)
	{
		my_signal();
		shell.prompt = readline(">>");
		if (shell.prompt == NULL)
			break;
		if (g_sig)
		{
			shell.status = g_sig;
			g_sig = 0;
		}
		add_history(shell.prompt);
		if (to_parse(&shell) != 0)
			shell.status = 2;
		else
		{
			if (handle_redir (&shell) == 0)
				launch_executor(&shell);
		}
	}
	return (shell.status);
}
