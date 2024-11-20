#include <minishell.h>

size_t	ft_count_word(char const *s, char c)
{
	size_t	word;
	size_t	i;

	word = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

char	*ft_strcmp2(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*result;

	i = 0;
	k = 0;
	while ((s1[i] == s2[i]) && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	j = i;
	while (s2[i] != '\0')
	{
		k++;
		i++;
	}
	result = malloc(sizeof(char *) * (k + 1));
	i = j;
	j = -1;
	while (s2[i] != '\0')
		result[++j] = s2[i++];
	result[j + 1] = '\0';
	return (result);
}

void	ft_strcat(char *d, const char *s)
{
	size_t	index;
	size_t	i;

	index = 0;
	while (d[index])
		index++;
	i = 0;
	while (s[i])
	{
		d[index + i] = s[i];
		i++;
	}
	d[index + i + 1] = '\0';
}
void	ft_swap_chr(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// void	sort_env(t_shell *data)
// {
// 	int i = 0;
// 	int n;
// 	int j = 0;

// 	while (data->exprt[i] != NULL)
// 		i ++;
// 	n = i;
// 	i = 0;
// 	while (i < n - 1)
// 	{
// 		j = 0;
// 		while (j < n - 1 - i)
// 		{
// 			if (strcmp(data->exprt[j], data->exprt[j + 1]) > 0)
// 				ft_swap_chr(&data->exprt[j], &data->exprt[j + 1]);
// 			j ++;
// 		}
// 		i ++;
// 	}
// }

char	*current_dir(t_shell *data)
{
	char	pwd[1000];
	char	*tmp;

	data->directory = ft_strcmp2(getenv("HOME"), getcwd(pwd, sizeof(pwd)));
	tmp = data->directory;
	data->directory = ft_strjoin("~", data->directory);
	free (tmp);
	tmp = data->directory;
	data->directory = ft_strjoin(data->directory, "$ ");
	free (tmp);
	return (data->directory);
}

int	strlen_tab(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != NULL)
		i++;
	return (i);
}
char	**re_fill_data(char **str, char *s, int n)
{
	int		i;
	char	**copy;

	if (s == NULL)
		return (NULL);
	copy = malloc(sizeof(char *) * (n + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		copy[i] = ft_strdup(str[i]);
		i++;
	}
	copy[i] = ft_strdup(s);
	copy[i + 1] = NULL;
	return (copy);
}

char	**realloc_tab(char **str, char *s, int concat)
{
	int		i;
	int		n;
	char	*concatenation;
	char	*concate2;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_strncmp(str[i], s, strlen_nvar(s)) == 0)
		{
			if (concat == 1)
			{
				// concatenation;
				concate2 = ft_strchr(s, '=');
				concatenation = ft_strchr(str[i], '=');
				if (!concatenation)
					str[i] = ft_strjoin(str[i], "=");
				str[i] = ft_strjoin(str[i], concate2 + 1);
				return (str);
			}
			else if (concat == 0)
			{
				if (!ft_strchr(s, '='))
					return (str);
				free(str[i]);
				str[i] = ft_strdup(s);
				return (str);
			}
		}
		// free (concatenation);
		i++;
	}
	if (ft_strchr(s, '+'))
	{
		concatenation = ft_substr(s, 0, strlen_nvar(s));
		concatenation = ft_strjoin(concatenation, ft_strchr(s, '='));
		s = ft_strdup(concatenation);
	}
	n = strlen_tab(str) + 1;
	str = re_fill_data(str, s, n);
	return (str);
}

int	free_tab(char **s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	while (s[i] != NULL)
	{
		free(s[i]);
		i++;
	}
	return (0);
}

int	strlen_nvar(char *s)
{
	int	i;

	i = 0;
	while ((s[i] != '=' && s[i] != '+') && s[i] != '\0')
		i++;
	return (i);
}

int	nt_valid_identifier(char *s)
{
	ft_putstr_fd("export : `", 1);
	ft_putstr_fd(s, 1);
	ft_putstr_fd("`: not a valid identifier\n", 1);
	return (0);
}

char	*get_env(char *s, t_shell *data)
{
	int		i;

	i = 0;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp(s, data->env[i], ft_strlen(s)) == 0)
			return (data->env[i]);
		i++;
	}
	return (NULL);
}

int	check_pipe(char **s)
{
	int	i;
	int	pipe;

	i = 0;
	pipe = 0;
	while (s[i] != NULL)
	{
		if (strcmp(s[i], "|") == 0)
			pipe++;
		i++;
	}
	return (pipe);
}

// int	cmd(char **str, t_shell *data)
// {
// 	//if (str[1] == NULL)
// 	//	return (add_export (data, str[0]));
// 	if ((strcmp(str[0],"echo") == 0))
// 		return(ft_echo(str));
// 	else if ((strcmp(str[0],"pwd") == 0))
// 		return (ft_pwd());
// 	else if ((strcmp(str[0],"cd") == 0))
// 		return (ft_cd(str, data));
// 	else if ((strcmp(str[0],"env") == 0))
// 		return (ft_env(data));
// 	else if ((strcmp(str[0],"export") == 0))
// 		return (ft_export(data, str));
// 	else if ((strcmp(str[0],"unset") == 0))
// 		return (ft_unset(data, str));
// 	else if ((strcmp(str[0], "get_env") == 0))
// 		get_env(str[1], data);
// 	else
// 		return (cmd_excve(str, data));
// 	return (0);
// }
int	assign_val(t_shell *data, char *s)
{
	int	i;
	int	concat;

	concat = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isalnum(s[i]) || s[i] == '_')
			i++;
		else
		{
			if (s[i] == '=' || (s[i] == '+' && s[i + 1] == '='))
			{
				if (s[i] == '+' && s[i + 1] == '=')
					concat = 1;
				data->env = realloc_tab(data->env, s, concat);
				break ;
			}
			return (nt_valid_identifier(s));
		}
	}
	data->export = realloc_tab(data->export, s, concat);
	sort_env(data);
	return (0);
}
