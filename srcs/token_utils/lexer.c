#include "../../headers/minishell.h"

t_token_type	get_token_type(char *content)
{
	if (my_strncmp (content, "|\0", 2) == 0)
		return (PIPE);
	if (my_strncmp (content, ">>\0", 3) == 0)
		return (APPEND);
	if (my_strncmp (content, "<<\0", 3) == 0)
		return (HEREDOC);
	if (my_strncmp (content, ">\0", 2) == 0)
		return (REDIR_OUT);
	if (my_strncmp (content, "<\0", 2) == 0)
		return (REDIR_IN);
	else
		return (WORD);
}

t_bool	isquote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	else
		return (FALSE);
}

char	*get_token(char *prompt, int *i)
{
	int	j;

	j = 0;
	while (prompt[j] != '\0' && my_isspace (prompt[j]) == FALSE)
	{
		if (isquote (prompt[j]) == TRUE)
			break;
		j++;
	}
	*i += j;
	return (my_substr(prompt, 0, j));
}

int	find_next_quote(char *prompt, char quote)
{
	int	len;

	if (prompt == NULL)
		return (0);
	len = 0;
	while (prompt[len] != '\0' && prompt[len] != quote)
		len++;
	return (len);
}

t_token	*lexer(char *prompt)
{
	int		i;
	char	*tmp;
	t_token	*token;

	if (prompt == NULL)
		return (NULL);
	token = NULL;
	i = 0;
	while (prompt[i] != '\0')
	{
		tmp = get_token(prompt + i, &i);
		add_front(&token, new_token (get_token_type (tmp), tmp));
		i++;
	}
	return (token);
}
