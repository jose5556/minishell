/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:42:59 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 09:27:01 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_necessary(char	**line, t_prompt **prompt, t_bash **bash)
{
	free(*line);
	free((*prompt)->final_str);
	free((*prompt)->pwd);
	*line = NULL;
	(*prompt)->pwd = NULL;
	(*prompt)->final_str = NULL;
	ft_bashclear(bash);
}

void	free_all_prompt(t_prompt **prompt)
{
	free((*prompt)->final_str);
	free((*prompt)->pwd);
	free((*prompt)->logname);
	free((*prompt)->hostname);
	free((*prompt)->home_path);
}

void	ft_clear_all(t_prompt **prompt, t_bash **bash, char	**line)
{
	free(*line);
	free_all_prompt(prompt);
	rl_clear_history();
	ft_bashclear(bash);
	ft_printf("%s", EXIT_SUCCESS_MESSAGE);
	exit(EXIT_SUCCESS);
}
