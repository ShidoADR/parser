/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:00:38 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 13:18:36 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	my_strcmp(const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return (1);
	while (*str1 != '\0' && *str2 != '\0')
	{
		if (*str1 != *str2)
			return (1);
		str1++;
		str2++;
	}
	if (*str1 == '\0' && *str2 == '\0')
		return (0);
	return (1);
}

int	verify_option(char *s)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (s[i] == '-' && s[i + 1] == 'n')
	{
		i += 2;
		option = 1;
	}
	while (s[i] != '\0')
	{
		if (s[i] == 'n')
			i++;
		else
			return (0);
	}
	return (option);
}

int	strlen_nvar(char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while ((s[i] != '=' && s[i] != '+') && s[i] != '\0')
		i++;
	return (i);
}

int	nt_valid_identifier(char *s)
{
	ft_putstr_fd("export : `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}
