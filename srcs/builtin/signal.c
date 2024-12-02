/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:00:38 by hariandr          #+#    #+#             */
/*   Updated: 2024/12/02 12:22:06 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:08:25 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/23 14:38:09 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_bool	handle_sig(t_status sig)
{
	if (sig == 2 || sig == 131)
	{
		ft_putendl_fd ("", 1);
		return (TRUE);
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
	g_sig = 128 + sig;
	return ;
}

void	signal_fork(int sig)
{
	if (sig == SIGINT)
		g_sig = 128 + sig;
	close(STDIN_FILENO);
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
