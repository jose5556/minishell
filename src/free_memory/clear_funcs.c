/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:42:59 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/29 00:04:20 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_necessary(char	**line, t_prompt *prompt)
{
	free(*line);
	free(prompt->final_str);
	free(prompt->pwd);
	*line = NULL;
	prompt->pwd = NULL;
	prompt->final_str = NULL;
}

void	ft_clear_all(t_prompt *prompt)
{
	free(prompt->logname);
	free(prompt->hostname);
	free(prompt->pwd);
	free(prompt->home_path);
	exit(EXIT_SUCCESS);
}
