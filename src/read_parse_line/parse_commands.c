/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:59:05 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 08:29:30 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_line(char *line, t_bash bash)
{
	char	**parsed_command;
	int		i;

	i = 0;
	parsed_command = NULL;
	parsed_command = ft_split(line, ' ');
	while (parsed_command[i])
	{
		if (get_command_num(parsed_command[i]) == COMMAND)
		
	}
}

