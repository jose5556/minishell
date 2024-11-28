/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 21:41:14 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/28 00:20:42 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init(t_prompt **prompt)
{
	g_signal = 0;
	init_signals();     // ctr + \ TODO
	ft_bzero(*prompt, sizeof(t_prompt *));
}
