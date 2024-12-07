/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 09:23:07 by joseoliv         ###   ########.fr       */
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
		if (!(init(&line, prompt, &bash)))
			ft_clear_all(&prompt, &bash, &line);
		else
			print_lst(bash);
		free_necessary(&line, &prompt, &bash);
	}
	return (0);
}
