/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree_nodes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:31 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 17:34:51 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*get_last_redir(t_cmd *cmd)
{
	t_redir_cmd	*redir_cmd;

	while (cmd->node_type == REDIR_NODE)
	{
		redir_cmd = (t_redir_cmd *)cmd;
		if ((redir_cmd->cmd)->node_type != EXEC_NODE)
			cmd = redir_cmd->cmd;
		else
			break ;
	}
	return (cmd);
}

void	append_command_arg(t_shell *shell, t_exec_cmd *cmd, char *arg)
{
	int	i;

	i = 0;
	while (cmd->argv[i])
		i++;
	cmd->argv[i] = ft_strdup(arg);
	if (!cmd->argv[i])
		clear_exit(shell, 1);
	if (i == 0)
		cmd->cmd = resolve_command_path(shell, cmd->argv[0]);
}

t_cmd	*create_exec_node(t_shell *shell, t_list *token_pos)
{
	int			n_args;
	t_exec_cmd	*cmd;

	cmd = NULL;
	n_args = count_command_args(token_pos);
	cmd = malloc(sizeof(t_exec_cmd));
	if (!cmd)
		clear_exit(shell, 1);
	ft_memset(cmd, 0, sizeof(t_exec_cmd));
	cmd->node_type = EXEC_NODE;
	cmd->token_pos = token_pos;
	cmd->argv = ft_calloc(n_args + 1, sizeof(char *));
	if (!cmd->argv)
		clear_exit(shell, 1);
	cmd->cmd = NULL;
	return ((t_cmd *)cmd);
}

t_cmd	*create_redir_node(t_cmd *subcmd, char *file, int mode, int fd)
{
	t_redir_cmd	*cmd;
	t_cmd		*last_redir;

	cmd = ft_calloc(sizeof(t_redir_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->fd = fd;
	cmd->open_flags = mode;
	cmd->file = file;
	cmd->cmd = subcmd;
	cmd->node_type = REDIR_NODE;
	if (fd == 0)
		cmd->permission = 0444;
	else
		cmd->permission = 0644;
	cmd->token_pos = subcmd->token_pos;
	if (subcmd->node_type == EXEC_NODE)
		return ((t_cmd *)cmd);
	last_redir = get_last_redir((t_cmd *)cmd);
	cmd->cmd = ((t_redir_cmd *)last_redir)->cmd;
	((t_redir_cmd *)last_redir)->cmd = (t_cmd *)cmd;
	return (subcmd);
}

t_cmd	*create_pipe_node(t_shell *shell, t_cmd *left, t_cmd *right)
{
	t_pipe_cmd	*cmd;

	cmd = malloc(sizeof(t_pipe_cmd));
	if (!cmd)
		clear_exit(shell, 1);
	ft_memset(cmd, 0, sizeof(t_pipe_cmd));
	cmd->left = left;
	cmd->right = right;
	cmd->node_type = PIPE_NODE;
	return ((t_cmd *)cmd);
}
