/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 11:58:05 by dzinchen          #+#    #+#             */
/*   Updated: 2025/02/02 15:13:42 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_tree(t_shell *shell, t_cmd *cmd)
{
	if (!cmd)
		clear_exit(shell, 1);
	if (cmd->node_type == EXEC_NODE)
		run_exec(shell, cmd);
	else if (cmd->node_type == REDIR_NODE)
		execute_redirect(shell, cmd);
	else if (cmd->node_type == PIPE_NODE)
		exec_pipe(shell, cmd);
}

int	fork_and_setup_child(t_shell *shell, t_cmd *cmd, int *p, int pipe_id)
{
	int	pid;

	pid = safe_fork(shell);
	if (pid == 0)
	{
		setup_child_process_signals();
		setup_pipe_io(shell, cmd, p, pipe_id);
	}
	return (pid);
}
