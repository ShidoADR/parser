/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 10:55:37 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/18 14:01:52 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_error(char *s, int status)
{
	perror (s);
	exit (status >> 8);
}

void	print_custom_error(char *s)
{
	write (2, "Minishell : ", 12);
	write (2, s, my_strlen (s));
}
