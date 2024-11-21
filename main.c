/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/21 20:23:44 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./include/minishell.h"

static void	get_prompt()
{
	char *line1;

	line1 = getenv("LOGNAME");
	printf("%s\n", line1);
}
int	main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		get_prompt();
		line = read_line(0, line);
		if (line == NULL)
			ft_printf("NULL\n");
		else
			ft_printf("%s\n", line);
		free(line);
	}
	return (1);
} 
