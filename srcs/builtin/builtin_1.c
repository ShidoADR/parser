/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 07:39:58 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/29 07:41:58 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_echo(char **s, int i)
{
	while (s[i] != NULL)
	{
		if (s[i + 1] == NULL)
			ft_putstr_fd(s[i], 1);
		else
		{
			ft_putstr_fd(s[i], 1);
			write(1, " ", 1);
		}
		i++;
	}
	return (0);
}

int	ft_echo(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "\n", 1);
		return (0);
	}
	while (s[i] != NULL && (verify_option(s[i]) == 1))
		i++;
	if (s[i] != NULL && verify_option(s[i]) == 0)
	{
		if (i != 0 && verify_option(s[i - 1]) == 1)
			print_echo(s, i);
		else
		{
			print_echo(s, i);
			write(1, "\n", 1);
		}
	}
	return (0);
}

int	ft_env(t_shell *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_putstr_fd(data->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	ft_pwd(t_shell *data)
{
	ft_putendl_fd(data->pwd, 1);
	return (0);
}
