/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:42:59 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 09:05:27 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_necessary(char	**line, t_prompt *prompt, t_bash **bash)
{
	free(*line);
	free(prompt->final_str);
	free(prompt->pwd);
	*line = NULL;
	prompt->pwd = NULL;
	prompt->final_str = NULL;
	ft_bashclear(bash);
}

void	ft_clear_all(t_prompt **prompt, t_bash **bash)
{
	rl_clear_history();
	free((*prompt)->logname);
	free((*prompt)->hostname);
	free((*prompt)->pwd);
	free((*prompt)->home_path);
	ft_bashclear(bash);
	ft_printf("%s\n", EXIT_SUCCESS_MESSAGE);
	exit(EXIT_SUCCESS);
}
