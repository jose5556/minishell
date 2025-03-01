/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:45 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:28 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_child_handler(int signo)
{
	if (signo == SIGQUIT)
	{
		g_exit_status = 131;
		exit(g_exit_status);
	}
	else if (signo == SIGINT)
	{
		g_exit_status = 130;
		ft_putchar_fd('\n', 2);
		exit(g_exit_status);
	}
}

void	sigint_readline_handler(int signo)
{
	if (signo == SIGINT)
	{
		g_exit_status = 130;
		ft_putchar_fd('\n', 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
