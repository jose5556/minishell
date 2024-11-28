/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:42:41 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/28 21:40:08 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	print_prompt(t_prompt *prompt)
{
	ft_printf("%s@", prompt->logname);
	ft_printf("%s", prompt->hostname);
	if (!(prompt->pwd))
		ft_printf(":~$ ");
	else
	{
		ft_printf(":~%s$ ", prompt->pwd);
		free(prompt->pwd);
		prompt->pwd = NULL;
	}
}

void	get_prompt(t_prompt *prompt)
{
	if (!(prompt->logname))
		prompt->logname = get_logname();
	if (!(prompt->hostname))
		prompt->hostname = get_hostname();
	if (!(prompt->home_path))
		prompt->home_path = get_home();
	prompt->pwd = get_pwd(prompt);
	print_prompt(prompt);
}