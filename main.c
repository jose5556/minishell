/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/30 16:59:34 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

//int	g_signal;

int	main(void)
{
	char		*line;
	t_prompt	*prompt;

	line = NULL;
	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (1);
	init();
	while (1)
	{
		line = ft_readline(prompt, &line);
		if (!line)
			ft_clear_all(prompt);
		if (line[0])
			ft_printf("%s\n", line);
		free_necessary(&line, prompt);
	}
	return (0);
}
