/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:31:32 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 13:33:47 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_status(t_token *token, int *index)
{
	char	*status;

	status = my_itoa (token->shell->status);
	*index += 2;
	return (status);
}
