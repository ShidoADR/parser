/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:08:25 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/12/04 13:18:22 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	is_signaled(t_command **command)
{
	t_command	*tmp;

	tmp = *command;
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->status == 2)
			return (TRUE);
		if (tmp->status == 131)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	here_is_a_signal(sig, SET);
}

int	here_is_a_signal(int sig, t_mode mode)
{
	static int	var = 0;

	if (mode == SET)
		var = sig + 128;
	if (mode == RESET)
		var = 0;
	return (var);
}

void	my_signal(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	signal(SIGINT, handle_signal);
	sigaction(SIGQUIT, &sa, NULL);
}

void	my_signal_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	signal(SIGINT, signal_fork);
	sigaction(SIGQUIT, &sa, NULL);
}
