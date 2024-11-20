/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrasamoe <lrasamoe@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:08:25 by lrasamoe          #+#    #+#             */
/*   Updated: 2024/11/19 14:29:37 by lrasamoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("",0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_sig = 128 + sig;
	return ;
}

void	signal_fork(int sig)
{
	g_sig = 128 + sig;
	exit(sig);
}

void	my_signal(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_IGN;
	signal(SIGINT, handle_signal);
	sigaction(SIGQUIT, &sa, NULL);
	return ;
}