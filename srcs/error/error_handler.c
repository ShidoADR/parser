/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 13:19:33 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_custom_error(char *s)
{
	write(2, "Minishell: ", 11);
	write(2, s, my_strlen(s));
}
