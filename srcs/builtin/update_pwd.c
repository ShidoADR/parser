/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_pwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:24:03 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/29 10:37:17 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	update_pwd(char *key, char *value, t_shell *data)
{
	int		a;
	char	*str;
	char	**s;

	s = malloc(sizeof(char *) * 2);
	str = my_strjoin(key, value);
	s[0] = str;
	s[1] = NULL;
	a = ft_export(data, s);
	free_args(s);
	return (a);
}

void	update_and_free(char **oldpwd, t_shell *data)
{
	if (get_env("PWD", data) != NULL)
		update_pwd("OLDPWD=", *oldpwd, data);
	update_pwd("PWD=", getcwd(data->pwd, sizeof(data->pwd)), data);
	if (*oldpwd != NULL)
	{
		free(*oldpwd);
		*oldpwd = NULL;
	}
}
