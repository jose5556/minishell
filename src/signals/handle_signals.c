/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 06:32:14 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/28 00:22:45 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 2;
	}
	if (signum == SIGQUIT)
	{
		ft_printf("%d", signum);
	}
}

void	init_signals()
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1) //INCOMPLETE TODO
		exit(1);
}
