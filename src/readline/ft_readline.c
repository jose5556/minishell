/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:36:40 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/30 21:35:45 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(t_prompt *prompt, char **line)
{
	*line = readline(get_prompt(prompt));
	//func to check syntax(*line);
	//parse_line(*line);
	add_history(*line);
	return (*line);
}
