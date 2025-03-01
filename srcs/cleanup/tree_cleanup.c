/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_cleanup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:01 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:17 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tree_cleanup(t_cmd *cmd)
{
	int			i;
	t_exec_cmd	*exec_cmd;

	i = 0;
	if (cmd->node_type == EXEC_NODE)
	{
		exec_cmd = (t_exec_cmd *)cmd;
		while (exec_cmd->argv[i])
			free(exec_cmd->argv[i++]);
		free(exec_cmd->argv);
		if (exec_cmd->cmd)
			free(exec_cmd->cmd);
		free(exec_cmd);
	}
	else if (cmd->node_type == PIPE_NODE)
	{
		tree_cleanup(((t_pipe_cmd *)(cmd))->left);
		tree_cleanup(((t_pipe_cmd *)(cmd))->right);
		free((t_pipe_cmd *)(cmd));
	}
	else if (cmd->node_type == REDIR_NODE)
	{
		tree_cleanup(((t_redir_cmd *)(cmd))->cmd);
		free((t_redir_cmd *)(cmd));
	}
}
