/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:16 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:38 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_open_error_helper(t_shell *shell, t_redir_cmd *redir_cmd)
{
	if (access(redir_cmd->file, R_OK | W_OK) != 0)
	{
		g_exit_status = 1;
		custom_error("minishell: ", redir_cmd->file,
			": Permission denied", g_exit_status);
		clear_exit(shell, g_exit_status);
	}
	else
	{
		g_exit_status = 1;
		custom_error("minishell: ", redir_cmd->file,
			": Error opening file", g_exit_status);
		clear_exit(shell, g_exit_status);
	}
}

static void	handle_open_error(t_shell *shell, t_redir_cmd *redir_cmd)
{
	if (is_directory(redir_cmd->file))
	{
		g_exit_status = 1;
		custom_error("minishell: ", redir_cmd->file,
			": Is a directory", g_exit_status);
		clear_exit(shell, g_exit_status);
	}
	else if (access(redir_cmd->file, F_OK) != 0)
	{
		g_exit_status = 1;
		custom_error("minishell: ", redir_cmd->file,
			": No such file or directory", g_exit_status);
		clear_exit(shell, g_exit_status);
	}
	else
		handle_open_error_helper(shell, redir_cmd);
}

void	execute_shell_command(t_shell *shell, t_exec_cmd *excmd)
{
	setup_child_process_signals();
	if (execve(excmd->cmd, excmd->argv, shell->envp) == -1)
	{
		if (access(excmd->argv[0], F_OK) == -1)
		{
			custom_error("minishell: ", excmd->argv[0],
				": No such file or directory", 127);
			clear_exit(shell, 127);
		}
		else if (access(excmd->argv[0], X_OK) == -1)
		{
			custom_error("minishell: ", excmd->argv[0],
				": Permission denied", 126);
			clear_exit(shell, 126);
		}
		else
		{
			custom_error("minishell: ", excmd->argv[0],
				": command not found", 127);
			clear_exit(shell, 127);
		}
	}
}

void	execute_redirect(t_shell *shell, t_cmd *cmd)
{
	t_redir_cmd	*redir_cmd;
	int			file_descriptor;

	redir_cmd = (t_redir_cmd *)cmd;
	close(redir_cmd->fd);
	if (redir_cmd->file[0] == '$')
	{
		if (get_token_content(cmd->token_pos)->quote_state != SINGLE_QUOTES)
		{
			g_exit_status = 1;
			custom_error("minishell: ", redir_cmd->file,
				": ambiguous redirect", g_exit_status);
			clear_exit(shell, g_exit_status);
		}
	}
	file_descriptor = open(redir_cmd->file, redir_cmd->open_flags,
			redir_cmd->permission);
	if (file_descriptor < 0)
		handle_open_error(shell, redir_cmd);
	exec_tree(shell, redir_cmd->cmd);
}
