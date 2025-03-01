/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:09 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:26 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shell_paths(t_shell *shell)
{
	char	*path_value;

	if (shell->paths != NULL)
	{
		free_path(shell->paths);
		shell->paths = NULL;
	}
	path_value = get_env_var(shell->env_list, "PATH");
	if (path_value != NULL)
	{
		shell->paths = ft_split(path_value, ':');
		free(path_value);
	}
	else
		shell->paths = NULL;
}

int	get_key_length(const char *env_var)
{
	char	*equals_sign;

	equals_sign = ft_strchr(env_var, '=');
	if (!equals_sign)
		return (-1);
	return ((int)(equals_sign - env_var));
}
