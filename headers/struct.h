/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:52:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/19 13:33:15 by lrasamoe         ###   ########.fr       */
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
	pid_t				pid;
	char				*command;
	char				**arguments;
	struct s_command	*next;
	struct s_command	*prev;
}	t_command;

typedef struct	s_heredoc
{
	int			here_doc[2];
	pid_t		pid;
}	t_heredoc;

typedef struct s_command_table
{
	struct s_token		*redir;
	struct s_token		*input;
	struct s_token		*output;
	struct s_heredoc	here_doc;
	struct s_command	*command;
	
}	t_command_table;

typedef struct s_shell
{
	char					*path;
	char					**env;
	int						status;
	struct s_token			*token;
	char					*prompt;
	struct s_command_table	command;
	char					**export;
	char					**all_path;
	char					*directory;
}	t_shell;

#endif
