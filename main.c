/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 08:28:50 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

//int	g_signal;

int	main(void)
{
	char		*line;
	t_prompt	*prompt;
	t_bash		*bash;

	line = NULL;
	bash = NULL;
	prompt = ft_calloc(sizeof(t_prompt), 1);
	if (!prompt)
		return (1);
	init_signals();
	while (1)
	{
		line = ft_readline(prompt, line, bash);
		if (!line)
			ft_clear_all(prompt);
		else if (line[0])
			ft_printf("%s\n", line);
		free_necessary(&line, prompt);
	}
	return (0);
}
