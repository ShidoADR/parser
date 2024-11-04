/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 13:51:37 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/04 14:49:34 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_token(t_token *token)
{
	if (token != NULL)
	{
		while (token != NULL)
		{
			printf ("{type = %d, value = %s}\n", token->type, token->content);
			token = token->next;
		}
	}
}

void	print_prompt(void)
{
	printf (VIBRANT_BLUE BOLD_UNDERLINED "MiniShell" RESET " :");
	printf (DARK_GREEN BOLD " %s " RESET "in ", getenv ("USER"));
	printf (LIGHT_BLUE ITALIC "%s\n", getenv ("PWD"));
	printf(RED"->" RESET "\n");
	write (0, "  \033[A", 5);
}

t_command_table	init_command(void)
{
	t_command_table	command;

	command.command = NULL;
	command.redir = NULL;
	return (command);
}

t_bool	check_redir(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == REDIR_IN || token->type == HEREDOC)
			return (TRUE);
		if (token->type == REDIR_OUT || token->type == APPEND)
			return (TRUE);
		token = token->next;
	}
	return (FALSE);
}

t_bool	token_compare(t_token *t1, t_token *t2)
{
	int	len;

	len = my_strlen (t2->content);
	if (t1->type == t2->type)
	{
		if (my_strncmp (t1->content, t2->content, len) == 0)
			return (TRUE);
	}
	return (FALSE);
}

t_token	*token_dup(t_token *t)
{
	int		len;
	char	*content;
	t_token	*token;

	len = my_strlen (t->content);
	content = my_substr (t->content, 0, len);
	token = new_token(t->type, content);
	return (token);
}

t_token	*remove_token(t_token **token, t_token *to_remove)
{
	t_bool	removed;
	t_token	*tmp;
	t_token	*result;

	result = NULL;
	tmp = *token;
	removed = FALSE;
	while (tmp != NULL)
	{
		if (token_compare (tmp, to_remove) == TRUE && removed == FALSE)
			removed = TRUE;
		else
			add_back (&result, token_dup (tmp));
		tmp = tmp->next;
	}
	delete_token (&to_remove);
	clear_token (token);
	return (result);
}

char	*my_strdup(char *s)
{
	int		len;
	char	*result;

	len = my_strlen (s);
	result = my_substr (s, 0, len);
	return (result);
}

t_token	*get_redir(t_token **token)
{
	t_token	*tmp;
	t_token	*next;
	t_token	*redir;

	tmp = *token;
	redir = NULL;
	while (tmp != NULL)
	{
		if (tmp->type > 1)
		{
			next = token_dup (tmp->next);
			redir = new_token (tmp->type, my_strdup (next->content));
			*token = remove_token (token, token_dup (tmp));
			*token = remove_token (token, next);
			return (redir);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_bool	handle_redirection(t_token **token, t_command_table *command)
{
	while (check_redir (*token) == TRUE)
		add_back (&command->redir, get_redir (token));
	return (TRUE);
}

t_command_table	parser(t_token **token)
{
	t_command_table	command;

	command = init_command ();
	handle_redirection (token, &command);
	return (command);
}

int	main(void)
{
	t_shell	shell;

	printf (CLEAR);
	shell.status = 0;
	while (1)
	{
		print_prompt ();
		shell.prompt = get_next_line (0);
		if (my_strncmp (shell.prompt, "exit\n\0", 6) == 0)
		{
			free (shell.prompt);
			exit (EXIT_SUCCESS);
		}
		shell.token = lexer (shell.prompt);
		shell.status = is_valid_token (shell.token);
		if (shell.status == 0)
		{
			expander (&shell.token);
			shell.command = parser (&shell.token);
			printf ("------redir------\n");
			print_token (shell.command.redir);
			clear_token (&shell.command.redir);
		}
		printf ("---------token---------\n");
		print_token (shell.token);
		clear_token(&shell.token);
		free (shell.prompt);
		printf ("status = %d\n", shell.status);
	}
	return (0);
}
