/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:14 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:35 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_builtin_command(t_shell *shell, t_exec_cmd *excmd)
{
	if (!ft_strcmp(excmd->argv[0], "cd"))
	{
		if (!validate_builtin_args(excmd->argv))
		{
			custom_error("minishell: ", "cd: ", "too many arguments", 2);
			g_exit_status = 1;
			return (1);
		}
	}
	g_exit_status = execute_builtin(shell, excmd, CHILD_PROCESS);
	return (0);
}

static void	handle_external_command(t_shell *shell, t_exec_cmd *excmd, int *pid)
{
	int	status;

	*pid = safe_fork(shell);
	if (*pid == 0)
		execute_shell_command(shell, excmd);
	if (waitpid(*pid, &status, 0) != -1)
		handle_signal_status(status);
	else if (*pid != 0)
		custom_error("minishell: ", NULL,
			": Failed to wait for child process", 1);
}

static void	execute_command(t_shell *shell, t_exec_cmd *excmd)
{
	int	pid;

	pid = 0;
	setup_parent_shell_signals();
	if (is_builtin(excmd->argv[0]))
		handle_builtin_command(shell, excmd);
	else
		handle_external_command(shell, excmd, &pid);
	setup_readline_signals();
}

void	handle_signal_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			ft_putstr_fd("Quit (core dumped)\n", 2);
			g_exit_status = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
		{
			g_exit_status = 130;
		}
		else
			g_exit_status = 128 + WTERMSIG(status);
	}
	else if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
}

void	run_exec(t_shell *shell, t_cmd *cmd)
{
	t_exec_cmd	*exec_cmd;

	exec_cmd = (t_exec_cmd *)cmd;
	if (exec_cmd->argv[0] && command_error_handler(exec_cmd))
	{
		if (!is_directory(exec_cmd->argv[0]))
			execute_command(shell, exec_cmd);
	}
	else if (exec_cmd->argv[0])
	{
		if (!ft_strcmp(exec_cmd->argv[0], "exit") && shell->num_pipes == 0)
			g_exit_status = 0;
	}
	clear_exit(shell, g_exit_status);
}
