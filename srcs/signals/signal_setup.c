/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:47 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:26 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_heredoc_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		g_exit_status = 130;
		exit(g_exit_status);
	}
}

void	setup_heredoc_signals(void)
{
	signal(SIGINT, sigint_heredoc_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_child_process_signals(void)
{
	signal(SIGINT, sigint_child_handler);
	signal(SIGQUIT, sigint_child_handler);
}

void	setup_parent_shell_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	setup_readline_signals(void)
{
	signal(SIGINT, sigint_readline_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
