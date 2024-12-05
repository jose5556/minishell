/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:41:14 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 16:50:30 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init(char **line, t_prompt *prompt, t_bash **bash)
{
	char	**parsed_command;

	parsed_command = NULL;
	*line = readline(get_prompt(prompt));
	add_history(*line);
	parsed_command = ft_split(*line, ' '); //TODO split with the tabs as well
	check_syntax(*line);
	parse_line(parsed_command, bash);
	print_lst(*bash);
}

void	init_signals()
{
	struct sigaction	sa;

	sa.sa_handler = &signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		exit(1);
	signal(SIGQUIT, SIG_IGN);
}
