/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:40 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 16:10:35 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 13:19:05 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_shell	init_shell(char **env)
{
	t_shell	shell;

	getcwd (shell.pwd, sizeof(shell.pwd));
	shell.to_restore = TRUE;
	shell.signal = 0;
	shell.is_ambigous = FALSE;
	shell.all_path = NULL;
	shell.path = NULL;
	shell.env = ft_fill_data(env);
	shell.export = ft_fill_data(env);
	shell.command = NULL;
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
		if (shell->is_ambigous == TRUE)
		{
			shell->status = 1;
			print_custom_error("ambiguous redirect\n");
			shell->is_ambigous = FALSE;
		}
		else
			shell->command = handle_command(&shell->token);
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
	if (sign == -2)
	{
		print_custom_error("exit : ");
		write(2, status, my_strlen(status));
		ft_putstr_fd(" : numeric argument required\n", 2);
		return (FALSE);
	}
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
