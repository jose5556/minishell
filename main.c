/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/27 06:40:15 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	main(void)
{
	char	*line;

	line = NULL;
	init_signals();    // ctr + d TODO
	while (1)
	{
		get_prompt();
		line = readline(line);
		if (!line)
			exit (EXIT_SUCCESS);
		if (line)
		{
			ft_printf("%s\n", line);
			free(line);
			line = NULL;
		}
	}
	return (1);
}
