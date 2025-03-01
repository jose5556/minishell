/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:38 by cereais           #+#    #+#             */
/*   Updated: 2025/01/26 10:24:49 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*get_final_str(t_prompt *prompt)
{
	prompt->final_str = ft_strjoin(prompt->logname, "@");
	prompt->final_str = ft_strjoin_free(prompt->final_str, prompt->hostname, 1);
	if (!(prompt->pwd))
		prompt->final_str = ft_strjoin_free(prompt->final_str, ":~$ ", 1);
	else
	{
		prompt->final_str = ft_strjoin_free(prompt->final_str, ":~", 1);
		prompt->final_str = ft_strjoin_free(prompt->final_str, prompt->pwd, 1);
		prompt->final_str = ft_strjoin_free(prompt->final_str, "$ ", 1);
	}
	return (prompt->final_str);
}

char	*get_prompt(t_prompt *prompt)
{
	if (!(prompt->logname))
		prompt->logname = get_logname();
	if (!(prompt->hostname))
		prompt->hostname = get_hostname();
	if (!(prompt->home_path))
		prompt->home_path = get_home();
	prompt->pwd = get_pwd(prompt);
	return (get_final_str(prompt));
}
