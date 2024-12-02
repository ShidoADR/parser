/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 08:55:14 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/28 14:12:04 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_export_variable(const char *var)
{
	int	j;
	int	equal;

	j = 0;
	equal = 0;
	ft_putstr_fd("declare -x ", 1);
	while (var[j] != '\0')
	{
		if (var[j] == '=' && equal == 0)
		{
			equal = 1;
			print_var(var[j], '"');
		}
		else if (var[j] == '"')
			print_var('\\', var[j]);
		else
			ft_putchar_fd(var[j], 1);
		j++;
	}
	if (equal == 1)
		ft_putchar_fd('"', 1);
	ft_putchar_fd('\n', 1);
}

static void	print_all_exports(t_shell *data)
{
	int	k;

	k = 0;
	while (data->export[k] != NULL)
	{
		print_export_variable(data->export[k]);
		k++;
	}
}

static int	add_multiple_exports(t_shell *data, char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		if (add_export(data, s[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_export(t_shell *data, char **s)
{
	if (s == NULL || s[0] == NULL)
		print_all_exports(data);
	else
		return (add_multiple_exports(data, s));
	return (0);
}

int	ft_unset(t_shell *data, char **s)
{
	int	i;

	i = 0;
	if (s == NULL || s[i] == NULL)
		return (0);
	else
	{
		while (s[i] != NULL)
		{
			data->export = delete_env(data->export, s[i]);
			data->env = delete_env(data->env, s[i]);
			i++;
		}
	}
	return (0);
}
