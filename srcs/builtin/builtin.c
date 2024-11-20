#include <minishell.h>

int	print_echo(char **s, int i)
{
	while (s[i] != NULL)
	{
		if (s[i + 1] == NULL)
			ft_putstr_fd(s[i], 1);
		else
		{
			ft_putstr_fd(s[i], 1);
			write(1, " ", 1);
		}
		i++;
	}
	return (0);
}

int	verify_option(char *s)
{
	int	i;
	int	option;

	i = 0;
	option = 0;
	if (s[i] == '-' && s[i + 1] == 'n')
	{
		i += 2;
		option = 1;
	}
	while (s[i] != '\0')
	{
		if (s[i] == 'n')
			i++;
		else
			return (0);
	}
	return (option);
}

int	ft_echo(char **s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		printf("\n");
		return (0);
	}
	while (s[i] != NULL && (verify_option(s[i]) == 1))
		i++;
	if (s[i] != NULL && verify_option(s[i]) == 0)
	{
		if (i != 0 && verify_option(s[i - 1]) == 1)
			print_echo(s, i);
		else
		{
			print_echo(s, i);
			write(1, "\n", 1);
		}
	}
	return (0);
}

int	ft_env(t_shell *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		ft_putstr_fd(data->env[i], 1);
		write(1, "\n", 1);
		i++;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	pwd[1000];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	return (0);
}

int	update_pwd(char *old_pwd, t_shell *data)
{
	int		i;
	char	pwd[1000];
	char	*current_pwd;

	current_pwd = ft_strdup(getcwd(pwd, sizeof(pwd)));
	i = 0;
	while (data->export[i] != NULL)
	{
		if (ft_strncmp("OLDPWD=", data->export[i], 7) == 0)
			data->export[i] = ft_strjoin("OLDPWD=", old_pwd);
		else if (ft_strncmp("PWD=", data->export[i], 4) == 0)
			data->export[i] = ft_strjoin("PWD=", ft_strdup(current_pwd));
		i++;
	}
	return (0);
}

int	ft_cd(char **s, t_shell *data)
{
	int		i;
	char	pwd[1000];
	char	*current_pwd;

	current_pwd = ft_strdup(getcwd(pwd, sizeof(pwd)));
	i = 0;
	if (s == NULL || s[i] == NULL)
	{
		chdir(getenv("HOME"));
		data->directory = ft_strdup("~$ ");
	}
	else
	{
		if ((strcmp(s[i], "HOME") == 0 || strcmp(s[i], "~") == 0 || strcmp(s[i],
					"~/") == 0) && chdir(getenv("HOME")) == 0)
			data->directory = ft_strdup("~$ ");
		else if (chdir(s[i]) == -1)
		{
			printf("bash: cd: %s: No such file or directory\n", s[i]);
			return (1);
		}
		else
			current_dir(data);
	}
	update_pwd(current_pwd, data);
	return (0);
}

int	add_export(t_shell *data, char *s)
{
	int	i;
	int	concat;

	concat = 0;
	i = 0;
	if (ft_isalpha(s[i]) == 0 || s[i] == '=')
		return (nt_valid_identifier(s));
	assign_val(data, s);
	return (0);
}

int	ft_export(t_shell *data, char **s)
{
	int	i;
	int	j;
	int	equal;
	int	k;

	k = 0;
	j = 0;
	i = 0;
	if (s == NULL || s[i] == NULL)
	{
		while (data->export[k] != NULL)
		{
			j = 0;
			equal = 0;
			ft_putstr_fd("declare -x ", 1);
			while (data->export[k][j] != '\0')
			{
				if (data->export[k][j] == '=')
				{
					equal = 1;
					ft_putchar_fd(data->export[k][j], 1);
					ft_putchar_fd('"', 1);
				}
				else if (data->export[k][j] == '"')
				{
					ft_putchar_fd('\\', 1);
					ft_putchar_fd(data->export[k][j], 1);
				}
				else
					ft_putchar_fd(data->export[k][j], 1);
				j++;
			}
			if (equal == 1)
				ft_putchar_fd('"', 1);
			ft_putchar_fd('\n', 1);
			k++;
		}
	}
	else
	{
		while (s[i] != NULL)
		{
			add_export(data, s[i]);
			i++;
		}
	}
	return (0);
}

char	**delete_env(char **env, char *s)
{
	char	**cpy;
	char	*pth1;
	int		len;
	int		j;

	len = 0;
	j = 0;
	while (env[j] != NULL)
	{
		pth1 = ft_substr(env[j], 0, strlen_nvar(env[j]));
		if (strcmp(pth1, s) == 0)
			len -= 1;
		if (pth1 != NULL)
			free(pth1);
		len++;
		j++;
	}
	cpy = malloc(sizeof(char *) * (len + 1));
	len = -1;
	j = 0;
	while (env[j] != NULL)
	{
		pth1 = ft_substr(env[j], 0, strlen_nvar(env[j]));
		if (strcmp(pth1, s) == 0)
			j++;
		else
		{
			cpy[++len] = ft_strdup(env[j]);
			j++;
		}
		if (pth1 != NULL)
			free(pth1);
	}
	cpy[len + 1] = NULL;
	free_tab(env);
	return (cpy);
}

int	ft_unset(t_shell *data, char **s)
{
	int	i;

	i = 0;
	if (s == NULL || s[i] == NULL)
		return (0);
	else
		while (s[i] != NULL)
		{
			data->export = delete_env(data->export, s[i]);
			data->env = delete_env(data->env, s[i]);
			i++;
		}
	return (0);
}

char	**assing_tab(char **str, char *s, int n)
{
	int		i;
	int		j;
	char	**copy;

	if (s == NULL)
		return (NULL);
	copy = malloc(sizeof(char *) * (n + 2));
	if (!copy)
		return (NULL);
	copy[0] = ft_strdup(s);
	i = 1;
	j = 0;
	while (str != NULL && str[j] != NULL)
	{
		copy[i] = ft_strdup(str[j]);
		i++;
		j++;
	}
	copy[i] = NULL;
	return (copy);
}

void	join_and_print_error(char *s1, char *s2)
{
	char	*tmp;
	char	*tmp2;

	tmp = my_strdup (s2);
	tmp2 = my_strdup (s1);
	tmp = join_string (&tmp2, &tmp);
	if (tmp != NULL)
	{
		ft_putstr_fd (tmp, 2);
		free (tmp);
		tmp = NULL;
	}
}

int	cmd_excve(char **s, t_shell *data, t_command *command)
{
	pid_t	fork_t;

	fork_t = command->pid;
	s = assing_tab(s, command->command, strlen_tab(s));
	clear_command (&data->command.command);
	if (fork_t == 0)
	{
		search_path(data);
		if (test_path(data, s[0]) == 0)
		{
			if (execve(data->path, s, data->env) == -1)
			{
				free_args (s);
				free_args (data->env);
				free_args (data->export);
				perror("execve");
				return (126);
			}
		}
		else
		{
			join_and_print_error (s[0], ": Command not found\n");
			free_args (s);
			free_args (data->env);
			free_args (data->export);
			exit(127);
		}
	}
	free_args (s);
	return (data->status);
}

int	search_path(t_shell *data)
{
	char	*pth;
	int		i;

	i = 0;
	pth = NULL;
	while (data->env[i] != NULL)
	{
		if (ft_strncmp("PATH=", data->env[i], 5) == 0)
		{
			pth = ft_strcmp2("PATH=", data->env[i]);
			data->all_path = ft_split(pth, ':');
			free(pth);
			return (1);
		}
		i++;
	}
	return (0);
}

int	test_path(t_shell *data, char *s)
{
	int		i;
	char	*pths;
	char	*tmp;

	i = 0;
	while (data->all_path[i] != NULL)
	{
		if (access(s, X_OK) == 0)
		{
			free_args (data->all_path);
			data->path = ft_strdup(s);
			return (0);
		}
		else
		{
			pths = ft_strjoin("/", s);
			tmp = pths;
			pths = ft_strjoin(data->all_path[i], pths);
			free (tmp);
			if (access(pths, X_OK) == 0)
			{
				data->path = ft_strdup(pths);
				free(pths);
				free_args (data->all_path);
				return (0);
			}
		}
		if (pths)
			free(pths);
		i++;
	}
	free_args (data->all_path);
	return (1);
}

char	**ft_fill_data(char **env)
{
	int		i;
	char	**copy;

	i = 0;
	while (env[i] != NULL)
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		copy[i] = ft_strdup(env[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}