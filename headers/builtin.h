/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 12:22:25 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:11:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/30 07:50:26 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <minishell.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "struct.h"
# include <sys/stat.h>
# include <sys/wait.h>

/*
***--------------builtin.c---------------
*/

int		ft_echo(char **s);
int		ft_env(t_shell *data);
int		ft_pwd(t_shell *data);
int		ft_cd(char **s, t_shell *data);
int		ft_export(t_shell *data, char **s);
int		ft_unset(t_shell *data, char **s);
int		cath_signal(void);
int		builtin(t_command *command);
int		verify_option(char *s);
int		assign_val(t_shell *data, char *s);
int		strlen_nvar(char *s);
int		nt_valid_identifier(char *s);
int		strlen_tab(char **s);
int		cmd(t_shell *data, t_command *command);
int		update_pwd(char *key, char *value, t_shell *data);
int		cd_to_directory(char **s, int i);
int		cd_to_oldpwd(t_shell *data, char **old_pwd);
int		cd_to_home(t_shell *data, char **old_pwd);
int		add_export(t_shell *data, char *s);
int		cmd_excve(char **s, t_shell *data, t_command *command);
int		search_path(t_shell *data);
int		test_path(t_shell *data, char *s);
int		cmd_pipe(t_shell *data, t_command **command);
char	*handle_concat_plus(char *s);
char	**update_existing_entry(char **str, char *s, int concat, int i);
int		my_strcmp(const char *str1, const char *str2);
char	**create_new_entry(char **str, char *s);
char	*ft_my_strcmp2(const char *s1, const char *s2);
char	**ft_fill_data(char **env);
char	**re_fill_data(char **str, char *s, int n);
char	**realloc_tab(char **str, char *s, int concat);
char	**assing_tab(char **str, char *s, int n);
char	*get_env(char *s, t_shell *data);
void	ft_swap_chr(char **a, char **b);
void	ft_strcat(char *d, const char *s);
void	sort_env(t_shell *data);
void	handle_signal(int sig);
t_bool	handle_sig(t_status sig);
void	my_signal(void);
void	my_signal_heredoc(void);
void	signal_fork(int sig);
char	**delete_env(char **env, char *s);
void	print_var(char c, char b);
void	free_all_tab(char **s, t_shell *data);
void	excute_cmd_with_path(char **s, t_shell *data);
void	execute_cmd_without_path(char **s, t_shell *data);
void	join_and_print_error(char *s0, char *s1, char *s2);
void	free_error_exec(char **s, t_shell *data);
void	update_and_free(char **oldpwd, t_shell *data);

#endif