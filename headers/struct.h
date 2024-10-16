/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:52:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/10/14 12:19:46 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "variable_types.h"

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	struct s_token	*prev;
	t_token_type	type;
}	t_token;

typedef struct s_hdoc
{
	char			*delimiter;
	t_bool			expandable;
	struct s_hdoc	*next;
	struct s_hdoc	*prev;
}	t_hdoc;

typedef struct s_command
{
	char				*command;
	char				**arguments;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct s_command_table
{
	char				*input;
	char				*output;
	struct s_command	*command;
	struct s_hdoc		*here_doc;
}	t_command_table;

#endif
