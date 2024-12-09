/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 20:59:05 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/09 16:11:45 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_line(char **parsed_command, t_bash **bash)
{
	char	*command;

	command = NULL;
	while (*parsed_command)
	{
		if (get_command_type(*parsed_command) == COMMAND)
		{
			while (get_command_type(*parsed_command) == COMMAND)
			{
				command = ft_strjoin_free(command, *parsed_command, 3);
				if (++(*parsed_command))
					command = ft_strjoin_free(command, " ", 1);
				parsed_command++;
			}
			addback_bash(command, bash);
			free(command);
			command = NULL;
		}
		else if (get_command_type(*parsed_command) != NOTHING)
		{
			command = ft_strjoin_free(command, *parsed_command, 3);
			command = ft_strjoin_free(command, " ", 1);
			parsed_command++;
		}
	}
}
