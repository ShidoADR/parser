/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:46:53 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/29 11:33:27 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**re_fill_data(char **str, char *s, int n)
{
	int		i;
	char	**copy;

	if (s == NULL)
		return (NULL);
	copy = malloc(sizeof(char *) * (n + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		copy[i] = ft_strdup(str[i]);
		i++;
	}
	copy[i] = ft_strdup(s);
	copy[i + 1] = NULL;
	free_args (str);
	return (copy);
}

char	*get_env(char *s, t_shell *data)
{
	int	i;
	int	len;

	i = 0;
	while (data->env[i] != NULL)
	{
		len = strlen_nvar(data->env[i]);
		if (len < my_strlen(s))
			len = my_strlen(s);
		if (ft_strncmp(data->env[i], s, len) == 0)
			return ((data->env[i]) + ft_strlen(s) + 1);
		i++;
	}
	return (NULL);
}

int	assign_val(t_shell *data, char *s)
{
	int	i;
	int	concat;

	concat = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else
		{
			if (s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
			{
				if (s[i] == '+' && s[i + 1] == '=')
					concat = 1;
				data->env = realloc_tab(data->env, s, concat);
				break ;
			}
			return (nt_valid_identifier(s));
		}
	}
	data->export = realloc_tab(data->export, s, concat);
	sort_env(data);
	return (0);
}

void	print_var(char c, char b)
{
	ft_putchar_fd(c, 1);
	ft_putchar_fd(b, 1);
}
