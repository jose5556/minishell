/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:36:40 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/29 00:15:06 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(t_prompt *prompt, char **line)
{
	char	*str_prompt;

	str_prompt = NULL;
	str_prompt = get_prompt(prompt);
	*line = readline(str_prompt);
	//parse_line(); TODO ?
	return (*line);
}