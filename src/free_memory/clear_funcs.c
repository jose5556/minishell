/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:42:59 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/28 20:58:24 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_clear_all(t_prompt *prompt)
{
	free(prompt->logname);
	free(prompt->hostname);
	free(prompt->pwd);
	free(prompt->home_path);
	exit(EXIT_SUCCESS);
}
