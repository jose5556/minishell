/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:36 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:34 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_argument_count(t_exec_cmd *cmd,
	long long *exit_code, int process)
{
	int	args;

	args = 0;
	while (cmd->argv[args])
		args++;
	if (args >= 3)
	{
		*exit_code = 1;
		if (process == CHILD_PROCESS)
		{
			custom_error("minishell: ", NULL,
				"exit: too many arguments", *exit_code);
		}
		return (false);
	}
	return (true);
}

static bool	validate_numeric_argument(t_exec_cmd *cmd,
	long long *exit_code, int process)
{
	char	*cleaned_arg;
	bool	valid_number;

	cleaned_arg = strip_quotes(cmd->argv[1]);
	valid_number = is_valid_number(cleaned_arg, exit_code);
	free(cleaned_arg);
	if (!cmd->argv[1] || !valid_number)
	{
		*exit_code = 2;
		if (process == CHILD_PROCESS)
		{
			custom_error("minishell: exit: ", cmd->argv[1],
				": numeric argument required", *exit_code);
		}
		return (false);
	}
	return (true);
}

static bool	validate_exit_args(t_shell *shell,
	t_exec_cmd *cmd, long long *exit_code, int process)
{
	(void)shell;
	if (!validate_numeric_argument(cmd, exit_code, process))
		return (true);
	if (!validate_argument_count(cmd, exit_code, process))
		return (false);
	return (true);
}

static int	process_exit_command(t_shell *shell, t_exec_cmd *exit_cmd,
	int procs, long long *exit_status_code)
{
	bool	exit_requested;

	exit_requested = false;
	if (procs == PARENT_PROCESS && shell->num_pipes == 0 && !exit_cmd->argv[1])
	{
		printf("exit\n");
		exit_requested = true;
	}
	else if (exit_cmd->argv[1])
	{
		exit_requested = validate_exit_args(shell, exit_cmd,
				exit_status_code, procs);
		g_exit_status = (unsigned int)(*exit_status_code) % 256;
	}
	else
	{
		*exit_status_code = 0;
		g_exit_status = 0;
	}
	return (exit_requested);
}

int	handle_exit_command(t_shell *shell, t_exec_cmd *exit_cmd, int procs)
{
	long long	exit_status_code;
	bool		exit_requested;

	exit_requested = process_exit_command(shell, exit_cmd,
			procs, &exit_status_code);
	if (procs == PARENT_PROCESS && exit_requested)
	{
		if (shell->cmd)
			tree_cleanup(shell->cmd);
		shell->cmd = NULL;
		if (exit_cmd != NULL)
			tree_cleanup((t_cmd *)exit_cmd);
		clear_exit(shell, g_exit_status);
	}
	return (g_exit_status);
}
