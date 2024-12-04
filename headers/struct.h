/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:05:40 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/04 16:18:51 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "variable_types.h"

typedef struct s_token
{
	struct s_shell		*shell;
	char				*content;
	struct s_token		*next;
	struct s_token		*prev;
	t_token_type		type;
}						t_token;

typedef struct s_heredoc
{
	pid_t				pid;
	int					here_doc[2];
}						t_heredoc;

typedef struct s_command
{
	pid_t				pid;
	t_status			status;
	char				*command;
	char				**arguments;
	struct s_token		*redir;
	struct s_token		*input;
	struct s_token		*output;
	struct s_heredoc	here_doc;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_shell
{
	char				*path;
	char				**env;
	int					signal;
	int					status;
	struct s_token		*token;
	char				*prompt;
	struct s_command	*command;
	char				**export;
	char				pwd[4096];
	t_bool				to_restore;
	char				**all_path;
	char				*directory;
	t_bool				is_ambigous;
}						t_shell;

#endif
