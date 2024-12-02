/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:11:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/28 14:37:07 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_delimiter(char *content, t_bool *is_expandable)
{
	int		i;
	char	*tmp;
	char	*delimiter;

	delimiter = NULL;
	i = 0;
	while (content[i] != '\0')
	{
		if (isquote(content[i]) == TRUE)
		{
			tmp = remove_quote(content + i, content[i]);
			i += find_next_quote(content + i + 1, content[i]) + 1;
			*is_expandable = FALSE;
		}
		else
		{
			if (content[i] != '$' || isquote(content[i + 1]) == FALSE)
				tmp = my_substr(content + i, 0, 1);
			else
				tmp = NULL;
			i++;
		}
		delimiter = join_string(&delimiter, &tmp);
	}
	return (delimiter);
}

t_bool	is_expand(char c)
{
	if (ft_strchr("%^&*+;\':\",.<>/", c) == NULL)
		return (TRUE);
	return (FALSE);
}

char	*heredoc_expander(t_token *token, t_bool is_expandable, char *str)
{
	int		i;
	char	*tmp;
	char	*content;

	content = NULL;
	if (str == NULL)
		return (NULL);
	if (is_expandable == TRUE)
	{
		i = 0;
		while (str[i] != '\0')
		{
			if (str[i] == '$' && is_expand(str[i + 1]) == TRUE)
				tmp = handle_dollar_sign(str + i, &i, token);
			else
			{
				tmp = my_substr(str + i, 0, 1);
				i++;
			}
			content = join_string(&content, &tmp);
		}
	}
	else
		content = my_strdup(str);
	return (content);
}

t_bool	break_heredoc(char **str, char *delimiter, t_token *redir,
		t_command **command)
{
	if (g_sig == 130)
	{
		if (str && *str != NULL)
			free(*str);
		close((*command)->here_doc.here_doc[0]);
		return (TRUE);
	}
	if (str == NULL || *str == NULL)
	{
		print_custom_error("warning: here-document delimited");
		ft_putstr_fd("by end-of-file (wanted `", 2);
		ft_putstr_fd(redir->content, 2);
		ft_putendl_fd("\')", 2);
		return (TRUE);
	}
	if (strcmp(*str, delimiter) == 0)
	{
		free(*str);
		return (TRUE);
	}
	return (FALSE);
}

int	cmd_here_doc(t_token *redir_doc, t_command **command)
{
	char	*str;
	char	*delimiter;
	t_bool	is_expandable;
	char	*content;

	is_expandable = TRUE;
	delimiter = get_delimiter(redir_doc->content, &is_expandable);
	while (1)
	{
		str = readline("> ");
		add_history(str);
		if (break_heredoc(&str, delimiter, redir_doc, command) == TRUE)
			break ;
		content = heredoc_expander(redir_doc, is_expandable, str);
		write((*command)->here_doc.here_doc[1], content, ft_strlen(content));
		write((*command)->here_doc.here_doc[1], "\n", 1);
		free(content);
		free(str);
	}
	free(delimiter);
	close((*command)->here_doc.here_doc[1]);
	return (0);
}
