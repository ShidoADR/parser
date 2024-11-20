#ifndef BUILTIN_H
#define BUILTIN_H
//#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <minishell.h>
#include <struct.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

int	    builtin(char **str, t_shell *data);
size_t	ft_count_word(char const *s, char c);
int	    verify_option(char *s);
char	*ft_strcmp2(const char *s1, const char *s2);
void    ft_strcat(char *d, const char *s);
void	sort_env(t_shell *data);
int	    search_path(t_shell *data);
int     test_path(t_shell *data, char *s);
char 	*current_dir(t_shell *data);
char	**ft_fill_data(char **env);
int	    ft_export(t_shell *data, char **s);
int     strlen_tab(char **s);
char	**re_fill_data(char **str, char *s, int n);
char 	**realloc_tab(char **str, char *s, int concat);
char	**assing_tab (char **str, char *s, int n);
int	    assign_val (t_shell *data, char *s);
int	    strlen_nvar (char *s);
int     nt_valid_identifier(char *s);
int	    free_tab(char **s);
void	ft_swap_chr(char **a, char **b);
char 	*get_env(char *s, t_shell *data);
void	handle_signal(int	sig);
void    my_signal(void);
void	signal_fork(int sig);
int	    check_pipe(char **s);
int	    cmd(t_shell *data, t_command *command);
int     ft_echo(char **s);
int	    ft_env(t_shell *data);
int     ft_pwd(void);
int	    update_pwd(char *old_pwd, t_shell *data);
int	    ft_cd(char **s, t_shell *data);
int	    add_export(t_shell *data, char *s);
int	    ft_export(t_shell *data, char **s);
char    **delete_env(char **env, char *s);
int	    ft_unset(t_shell *data, char **s);
int     cmd_excve(char **s, t_shell *data, t_command *command);
int	    search_path(t_shell *data);
int     test_path(t_shell *data, char *s);
int     cmd_pipe(t_shell *data, t_command **command);

#endif