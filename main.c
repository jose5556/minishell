/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/21 17:42:52 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./include/minishell.h"

// FINAL

int	main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		get_prompt()
		line = read_line(0, line);
		if (line == NULL)
			ft_printf("NULL\n");
		else
			ft_printf("%s\n", line);
		free(line);
		return 0;
	}
	return (1);
} 

void	get_promt()
{
	char *line1;
	char *line2;

	line1 = getenv("LOGNAME");
	line2 = getenv("LOGNAME");
}

int	main(void)
{
	char *line;

	line = NULL;
	line = getenv("LOGNAME");
	if (!line)
		return (0);
	printf("%s\n", line);
}
