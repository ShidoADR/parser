/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 10:52:33 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 12:22:57 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:11:42 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/30 10:47:36 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <../libft/libft.h>
# include <builtin.h>
# include <errno.h>
# include <fcntl.h>

/*
***-----------srcs/error-------------
*/
/*
***--------error_handler.c-----------
*/

void							print_custom_error(char *s);

/*
***-----------lexer_error.c----------
*/
t_status						check_word(char *content);
t_status						is_valid_pipe(t_token *token);
t_status						is_valid_token(t_token *token);
t_status						is_valid_redir(t_token *token);
t_bool							is_quote_closed(char *content, char quote,
									int *i);

/*
***---------srcs/expander-----------
*/
/*
***------expand_variable.c-------
*/
t_bool							check_space(char *content);
int								first_value_index(char *content);
int								quoted_text_length(char *content, char quote);
void							add_new_token(t_token **token,
									t_token *new_token);
char							*expand_variable(char **s, char *content,
									t_token **token, int *i);

/*
***--------expander.c-----------
*/
void							expander(t_token **token);
char							*join_string(char **s1, char **s2);
char							*handle_text(char *content, int *index);
char							*expand_token(char *content, t_token **token);
char							*handle_dollar_sign(char *content, int *index,
									t_token *token);

/*
***-------insert_token.c---------
*/
int								chain_len(char **chain);
int								first_value_index(char *content);
void							insert_token(t_token **token, char **chain);
void							add_new_token(t_token **token,
									t_token *new_token);
void							check_token(t_token **token, char **result,
									char **chain, char **s);

/*
***-------quote_utils.c----------
*/
char							*remove_quote(char *content, char quote);
char							*handle_quote(char *content, int *index,
									t_token *token);
char							*handle_quoted_text(char *content, int *index);
char							*handle_single_quote(char *content, int *index);
char							*handle_double_quote(char *content, int *index,
									t_token *token);

/*
***--------variable.c----------
*/
char							*get_status(t_token *token, int *index);

/*
***--------variable.c----------
*/
t_bool							my_isalpha(char c);
void							get_variable(char *content, int *i);
char							*handle_content(char *removed_quote,
									t_token *token);
t_bool							check_var_content(char *content, int *index);
char							*process_dollar_sign(char *removed_quote,
									int *i, t_token *token);

/*
***----------srcs/lexer-------------
*/
/*
***--------init_struct.c---------
*/
int								token_size(t_token *token);
void							clear_token(t_token **token);
void							delete_token(t_token **token);
t_token							*new_token(t_token_type type, char *content,
									t_shell *shell);
void							add_back(t_token **token, t_token *new_token);

/*
***--------lexer_utils.c---------
*/
t_bool							isquote(char c);
t_token							*last_token(t_token **token);
t_bool							is_special_token(char *prompt);

/*
***-----------lexer.c------------
*/
t_token							*lexer(char *prompt, t_shell *shell);
t_token_type					get_token_type(char *content);
char							*get_token(char *prompt, int *i);
int								find_next_quote(char *prompt, char quote);

/*
***----------srcs/parser------------
*/
/*
 ***-----------init_command.c------------
 */
int								command_size(t_command *command);
void							clear_command(t_command **command);
t_command						*new_command(char *cmd, char **arg,
									t_token *redir);
void							delete_command(t_command **command);
void							add_command(t_command **cmd,
									t_command *new_command);

/*
***-----------parser_utils.c------------
*/

char							**get_args(t_token **token);
t_command						*get_command(t_token **token);
t_command						*handle_command(t_token **token);
void							add_args(int *i, char **args, t_token **token);

/*
***-----------parser_utils.c------------
*/
void							free_args(char **args);
int								arg_size(t_token *token);
t_command						*last_command(t_command **command);
t_token							*handle_redirection(t_token **token);

/*
***-----------redir_utils.c------------
*/
t_token							*get_redir(t_token *token);
t_bool							check_redir(t_token *token);

/*
***-------srcs/string_library--------
*/
char							*my_itoa(int n);
t_bool							my_isspace(char c);
char							*my_strdup(char *s);
int								my_strlen(const char *s);
char							**my_split(char const *s);
char							*my_strchr(const char *s, int c);
unsigned long					my_atol(const char *str, int *sign);
char							*my_strjoin(const char *s1, const char *s2);
char							*my_substr(const char *s, int start, int len);
int								my_strncmp(const char *s1, const char *s2,
									size_t n);

/*
***--------------parser.c---------------
*/

void							clear_shell(t_shell *shell);
void							print_command(t_command *command);

/*
***--------------redirection.c---------------
*/

t_status						handle_redir(t_shell *shell,
									t_command *command);
int								cmd_here_doc(t_token *redir_doc,
									t_command **command);
void							launch_executor(t_shell *shell);
int								get_exit_status(int exit_status);
extern volatile sig_atomic_t	g_sig;
int								signal_captured(int sig);
t_status						here_doc(t_command *command, t_shell *shell);
void							redirect_stdin(t_command *command);
void							close_fd(int fd[2]);
void							print_token(t_token *token);
t_bool							check_next_redir(t_token *redir);
void							exec_child(t_command *command, t_shell *shell,
									int backup[2], int pipe_fd[2]);
void							exec_parent(int pipe_fd[2], t_command *command);
void							builtin_redirection(t_command *command);
t_status						redir_builtins(t_shell *shell);
t_status						to_parse(t_shell *shell);
t_bool							is_numeric(char *s);
t_bool							is_valid_status(char *status);
t_bool							check_status_value(unsigned long status_value,
									char *status, int sign);
int								exit_shell(t_command *command, t_shell *shell);
void							dup_fd_builtins(int backup[2], char *command);
void							dup_fd(int backup[2]);
void							restore_fd(int backup[2]);
t_status						exec_builtins(t_shell *shell, char *command,
									char **args);
void							exit_signal(t_shell *shell);
t_shell							init_shell(char **env);
t_status						init_backup_heredoc(t_command **command,
									t_shell *data, int backup[2]);
t_bool							is_special_var(char *content, int *index,
									char **result, t_token *token);
void							exec_path_null(char **s, t_shell *data);

void							exec_path_not_null(char **s, t_shell *data);

#endif
