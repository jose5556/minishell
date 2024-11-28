/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:36:40 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/27 23:52:49 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(t_prompt *prompt, char **line)
{
	get_prompt(prompt);
	*line = readline(*line);
	//parse_line(); TODO ?
	return (*line);
}