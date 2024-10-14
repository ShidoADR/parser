#include "../../headers/minishell.h"

t_command_table init_command(void)
{
	t_command_table	command;

	command.command = NULL;
	command.here_doc = NULL;
	command.input = NULL;
	command.output = NULL;
}

t_bool	check_input(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == REDIR_IN || token->type == HEREDOC)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

t_bool	check_output(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == REDIR_OUT || token->type == APPEND)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

void	handle_redirection(t_token **token, t_command_table *command)
{

}

t_command_table parser(t_token **token)
{
	t_command_table	command;

	command = init_command ();
	return (command);
}
