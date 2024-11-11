/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:52:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 12:54:54 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "variable_types.h"

typedef struct s_token
{
	struct s_shell	*shell;
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	type;
}	t_token;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_command_table
{
	struct s_token		*redir;
	struct s_command	*command;
}	t_command_table;

typedef struct s_shell
{
	char					**env;
	int						status;
	struct s_token			*token;
	char					*prompt;
	struct s_command_table	command;
}	t_shell;

#endif
