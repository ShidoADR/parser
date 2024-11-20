#include <minishell.h>

t_status	handle_redir(t_shell *shell)
{
	t_token	*redir;
	int		in;
	int		out;

	redir = shell->command.redir;
	in = -1;
	out = -1;
	if (redir != NULL)
	{
		while (redir != NULL)
		{
			if (redir->type == REDIR_IN)
			{
					if (in != -1)
						close (in);
					in = open (redir->content, O_RDONLY);
					if (in == -1)
					{
						perror ("Minishell");
						shell->status = 1;
						return (1);
					}
					close(in);
					shell->command.input = redir;

			}
			if (redir->type == REDIR_OUT)
			{

					if (out != -1)
						close (out);
					out = open (redir->content, O_WRONLY | O_CREAT | O_TRUNC, 0777);
					if (out == -1)
					{
						perror ("Minishell");
						shell->status = 1;
						return (1);
					}
					close(out);
					shell->command.output = redir;
			}
			if (redir->type == APPEND)
			{
					if (out != -1)
						close (out);
					out = open (redir->content, O_CREAT | O_RDWR | O_APPEND);
					if (out == -1)
					{
						perror ("Minishell");
						shell->status = 1;
						return (1);
					}
					close(out);
					shell->command.output = redir;
			}
			if (redir->type == HEREDOC)
			{
				shell->command.here_doc.pid = fork ();
				if (shell->command.here_doc.pid == 0)
				{
					if (cmd_here_doc(shell, redir) == 1)
					{
						perror ("heredoc");
						exit (1);
					}
					close (shell->command.here_doc.here_doc[0]);
					exit (shell->status);
				}
				waitpid (shell->command.here_doc.pid, &shell->status, 0);
				if (shell->status != 0)
					return (shell->status);
				shell->command.input = redir;
				if (redir->next != NULL && redir->next->type != HEREDOC)
					close (shell->command.here_doc.here_doc[0]);
			}
			redir = redir->next;
		}
	}
	return (0);
}