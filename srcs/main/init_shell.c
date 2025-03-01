/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:06:06 by dzinchen          #+#    #+#             */
/*   Updated: 2025/02/02 15:14:07 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_prompt(t_shell *shell)
{
	shell->prompt = malloc(sizeof(t_prompt));
	if (!shell->prompt)
	{
		ft_putstr_fd("Error: Memory allocation failed for shell prompt.\n", 2);
		clear_exit(shell, 1);
	}
	ft_bzero(shell->prompt, sizeof(t_prompt));
}

void	init_shell_env(t_shell *shell, char **env_var)
{
	if (!shell)
		exit(1);
	ft_bzero(shell, sizeof(t_shell));
	init_prompt(shell);
	shell->index = malloc(sizeof(t_index));
	if (!shell->index)
	{
		ft_putstr_fd("Error: Memory allocation failed for shell index.\n", 2);
		clear_exit(shell, 1);
	}
	ft_bzero(shell->index, sizeof(t_index));
	if (!env_var[0])
		initialize_empty_env(shell);
	if (env_var)
	{
		build_env_list(shell, env_var);
		shell->envp = linked_list_to_str_array(shell, shell->env_list,
				ENV_VAR_TYPE);
		update_shell_paths(shell);
	}
}
