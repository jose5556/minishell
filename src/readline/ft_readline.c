/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 22:36:40 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/30 20:51:14 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*ft_readline(t_prompt *prompt, char **line)
{
	*line = readline(get_prompt(prompt));
	add_history(*line);
	return (*line);
}
