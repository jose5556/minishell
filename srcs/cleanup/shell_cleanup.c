/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:59 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:13 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reinit_shell(t_shell *shell)
{
	if (shell->cmd)
	{
		tree_cleanup(shell->cmd);
		shell->cmd = NULL;
	}
	free_token_list(&shell->token_list);
	ft_bzero(shell->index, sizeof(t_index));
	shell->num_pipes = 0;
}

static void	cleanup_prompt(t_prompt *prompt)
{
	if (!prompt)
		return ;
	if (prompt->logname)
		free(prompt->logname);
	if (prompt->hostname)
		free(prompt->hostname);
	if (prompt->home_path)
		free(prompt->home_path);
	if (prompt->pwd)
		free(prompt->pwd);
	if (prompt->final_str)
		free(prompt->final_str);
	free(prompt);
}

void	clear_exit(t_shell *shell, int status)
{
	if (!shell)
		exit(EXIT_FAILURE);
	rl_clear_history();
	if (rl_line_buffer)
		rl_free_line_state();
	if (shell->prompt)
		cleanup_prompt(shell->prompt);
	free_env_list(&shell->env_list);
	free_token_list(&shell->token_list);
	free(shell->index);
	if (shell->paths)
		free_path(shell->paths);
	if (shell->envp)
		free_path(shell->envp);
	if (shell->cmd)
	{
		tree_cleanup(shell->cmd);
		shell->cmd = NULL;
	}
	rl_clear_history();
	rl_clear_signals();
	exit(status);
}

void	custom_error(char *prefix, char *context, char *message, int exit_code)
{
	if (prefix)
		ft_putstr_fd(prefix, 2);
	if (context)
		ft_putstr_fd(context, 2);
	if (message)
	{
		ft_putstr_fd(message, 2);
		ft_putstr_fd("\n", 2);
	}
	else if (!message)
		ft_putstr_fd("\n", 2);
	if (exit_code)
		g_exit_status = exit_code;
}
