/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:17:50 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 15:20:04 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_operator_type get_command_type(char *command)
{
	if (!command)
		return (NOTHING);
	else if (!ft_strncmp(command, "|", 2))
		return PIPE;
	else if (!ft_strncmp(command, "||", 3))
		return OR;
	else if (!ft_strncmp(command, "&&", 3))
		return AND;
	else if (!ft_strncmp(command, ">", 2))
		return REDIRECT_OUT;
	else if (!ft_strncmp(command, "<", 2))
		return REDIRECT_IN;
	else if (!ft_strncmp(command, ">>", 3))
		return REDIRECT_APPEND;
	else if (!ft_strncmp(command, "<<", 3))
		return INPUT_REDIRECTION;
	else if (ft_strchr(command, '('))
		return GROUP_BEGIN;
	else if (ft_strchr(command, ')'))
		return GROUP_END;
	return COMMAND;
}
