/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:21:11 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/19 12:09:38 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>


 int	cmd_here_doc(t_shell *data, t_token *redir_doc)
 {
	char	*str;
	// int child;

	signal(SIGINT, signal_fork);
	if (data->command.here_doc.here_doc[0] != -1)
		close (data->command.here_doc.here_doc[0]);
	if (pipe (data->command.here_doc.here_doc) == -1)
	{
		perror ("pipe");
		return (1);
	}
	while (1)
	{
		str = readline("> ");
		add_history(str);
		if (str == NULL)
		{
			printf ("heredoc\n");
			break ;
		}
		if (strcmp(str, redir_doc->content) == 0)
		{
			if (str)
				free (str);
			break ;
		}
		else
		{
			write (data->command.here_doc.here_doc[1], str, ft_strlen(str));
			write (data->command.here_doc.here_doc[1], "\n", 1);
		}
		if (str)
			free(str);
	}
	close (data->command.here_doc.here_doc[1]);

	return (0);
 }