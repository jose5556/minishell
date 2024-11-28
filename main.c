/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/28 18:54:37 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_signal;

int	main(void)
{
	char		*line;
	t_prompt	*prompt;

	line = NULL;
	prompt = ft_calloc(sizeof(t_prompt), 1);
	init();
	if (g_signal == 2)
	{
		g_signal = 0;
	}
	while (1)
	{
		line = ft_readline(prompt, &line);
		if (!line)
			exit (EXIT_SUCCESS);
		if (line)
		{
			ft_printf("%s\n", line);
			free(line);
			line = NULL;
		}
	}
	ft_clear_all(prompt);
	return (1);
}
