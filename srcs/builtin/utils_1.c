/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 14:04:10 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/04 13:18:26 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_my_strcmp2(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*result;

	i = 0;
	k = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	j = i;
	while (s2[i] != '\0')
	{
		k++;
		i++;
	}
	result = malloc(sizeof(char *) * (k + 1));
	i = j;
	j = -1;
	while (s2[i] != '\0')
		result[++j] = s2[i++];
	result[j + 1] = '\0';
	return (result);
}

void	ft_strcat(char *d, const char *s)
{
	size_t	index;
	size_t	i;

	index = 0;
	while (d[index])
		index++;
	i = 0;
	while (s[i])
	{
		d[index + i] = s[i];
		i++;
	}
	d[index + i + 1] = '\0';
}

void	ft_swap_chr(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	strlen_tab(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != NULL)
		i++;
	return (i);
}

void	free_all_tab(char **s, t_shell *data)
{
	if (s)
		free_args(s);
	if (data->env)
		free_args(data->env);
	if (data->export)
		free_args(data->export);
}
