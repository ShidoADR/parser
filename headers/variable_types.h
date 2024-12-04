/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 13:44:19 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 10:30:39 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARIABLE_TYPES_H
# define VARIABLE_TYPES_H

typedef int	t_status;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_token_type;

typedef enum e_mode
{
	GET,
	SET,
	RESET
}	t_mode;

#endif
