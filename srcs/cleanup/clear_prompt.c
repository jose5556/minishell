/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:54 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:04 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt_modifier(t_prompt **prompt)
{
	if (!prompt || !*prompt)
		return ;
	if ((*prompt)->final_str)
	{
		free((*prompt)->final_str);
		(*prompt)->final_str = NULL;
	}
	if ((*prompt)->pwd)
	{
		free((*prompt)->pwd);
		(*prompt)->pwd = NULL;
	}
}

void	free_all_prompt(t_prompt **prompt)
{
	free((*prompt)->final_str);
	free((*prompt)->pwd);
	free((*prompt)->logname);
	free((*prompt)->hostname);
	free((*prompt)->home_path);
	free(*prompt);
	*prompt = NULL;
}
