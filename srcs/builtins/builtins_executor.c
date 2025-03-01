/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_executor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:06 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:11:54 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin_parent(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "export")
		|| !ft_strncmp(cmd, "unset", 5) || !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

static int	handle_cd_execution(t_shell *shell, t_exec_cmd *cmd, int procs)
{
	int	status;

	status = 0;
	if (cmd->argv[1] && cmd->argv[1][0] == '-' && cmd->argv[1][1] &&
		(cmd->argv[1][1] != '-' || (cmd->argv[1][1] == '-' && cmd->argv[1][2])))
	{
		if (procs == CHILD_PROCESS)
		{
			custom_error("minishell: cd: ", cmd->argv[1],
				": invalid option\ncd: usage: cd [dir]", 2);
			g_exit_status = 2;
		}
		return (2);
	}
	if (procs == PARENT_PROCESS)
		status = change_dir(shell, cmd);
	else
		status = g_exit_status;
	return (status);
}

t_exec_cmd	*find_exec_command_node(t_shell *shell, t_cmd *node)
{
	(void)shell;
	while (node && node->node_type == REDIR_NODE)
		node = ((t_redir_cmd *)node)->cmd;
	if (node && node->node_type == EXEC_NODE)
		return ((t_exec_cmd *)node);
	return (NULL);
}

void	handle_parent_builtins(t_shell *shell)
{
	t_list	*tmp;

	if (!shell || !shell->token_list)
		return ;
	tmp = shell->token_list;
	while (tmp)
	{
		if (get_token_content(tmp) && get_token_content(tmp)->value)
			execute_parent_builtin(shell, tmp);
		tmp = tmp->next;
	}
}

int	execute_builtin(t_shell *shell, t_exec_cmd *cmd, int procs)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmd->argv[0], "env"))
		status = env(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		status = handle_cd_execution(shell, cmd, procs);
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		status = builtin_pwd(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "echo"))
		status = echo(shell, cmd);
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		status = unset(shell, cmd, procs);
	else if (!ft_strcmp(cmd->argv[0], "export"))
		status = export(shell, cmd, procs);
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		status = handle_exit_command(shell, cmd, procs);
	return (status);
}
