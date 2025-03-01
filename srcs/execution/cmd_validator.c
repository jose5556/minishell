/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:19 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:45 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(t_shell *shell, int p[2])
{
	if (pipe(p) <= -1)
		clear_exit(shell, 1);
}

void	setup_pipe_io(t_shell *shell, t_cmd *cmd, int p[2], int child)
{
	if (child == 1 || child == 2)
	{
		if (child == 1)
		{
			dup2(p[1], STDOUT_FILENO);
			close(p[0]);
			close(p[1]);
			exec_tree(shell, ((t_pipe_cmd *)cmd)->left);
		}
		else
		{
			dup2(p[0], STDIN_FILENO);
			close(p[0]);
			close(p[1]);
			exec_tree(shell, ((t_pipe_cmd *)cmd)->right);
		}
	}
}

bool	command_error_handler(t_exec_cmd *excmd)
{
	bool	status;

	status = true;
	if (!excmd->cmd && excmd->argv[0] && !is_builtin(excmd->argv[0]))
	{
		custom_error("minishell: ", excmd->argv[0], ": command not found", 127);
		status = false;
	}
	else
	{
		if (excmd->argv[0] && (is_directory(excmd->argv[0]) == true))
		{
			custom_error("minishell: ", excmd->argv[0],
				": Is a directory", 126);
			status = false;
		}
	}
	return (status);
}

int	safe_fork(t_shell *shell)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		custom_error("Error: Failed to fork process.", NULL, NULL, 1);
		clear_exit(shell, 1);
	}
	shell->pid = pid;
	return (pid);
}

void	exec_pipe(t_shell *shell, t_cmd *cmd)
{
	int	p[2];
	int	pid1;
	int	pid2;
	int	status;

	create_pipe(shell, p);
	setup_parent_shell_signals();
	pid1 = fork_and_setup_child(shell, cmd, p, 1);
	pid2 = fork_and_setup_child(shell, cmd, p, 2);
	close(p[0]);
	close(p[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, &status, 0);
	setup_readline_signals();
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	clear_exit(shell, g_exit_status);
}
