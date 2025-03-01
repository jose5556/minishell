/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:13 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:00 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_builtin_args(char **argv)
{
	if (!argv || !argv[0])
		return (true);
	if (!ft_strcmp(argv[0], "cd"))
	{
		if (argv[1] && argv[2])
			return (false);
	}
	if (!ft_strcmp(argv[0], "pwd") && argv[1])
		return (false);
	return (true);
}

int	parent_export_handler(t_shell *shell, t_cmd *cmd)
{
	t_exec_cmd	*exec;

	exec = find_exec_command_node(shell, cmd);
	if (!exec)
		return (0);
	if (cmd->node_type == REDIR_NODE && exec->argv[1])
		return (export(shell, exec, PARENT_PROCESS));
	else if (cmd->node_type != REDIR_NODE)
		return (export(shell, exec, PARENT_PROCESS));
	return (0);
}

void	extract_key_value(const char *input, char **key, char **value)
{
	char	*equals_sign;

	equals_sign = ft_strchr(input, '=');
	if (equals_sign)
	{
		*key = ft_substr(input, 0, equals_sign - input);
		*value = ft_strdup(equals_sign + 1);
	}
	else
	{
		*key = ft_strdup(input);
		*value = NULL;
	}
	if (!*key || (equals_sign && !*value))
	{
		free(*key);
		if (equals_sign)
			free(*value);
		*key = NULL;
		*value = NULL;
	}
}

bool	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	else if (ft_strcmp(cmd, "export") == 0)
		return (true);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	return (false);
}

void	execute_parent_builtin(t_shell *shell, t_list *tmp)
{
	bool		is_builtin;
	t_cmd		*cmd;
	t_exec_cmd	*execcmd;

	is_builtin = is_builtin_parent(get_token_content(tmp)->value);
	if (!is_builtin)
		return ;
	cmd = parse_simple_command(shell, tmp);
	if (!cmd)
		return ;
	execcmd = find_exec_command_node(shell, cmd);
	if (!execcmd || !execcmd->argv || !execcmd->argv[0])
	{
		if (cmd)
			tree_cleanup(cmd);
		return ;
	}
	if (!ft_strcmp(execcmd->argv[0], "export"))
		parent_export_handler(shell, cmd);
	else
		execute_builtin(shell, execcmd, PARENT_PROCESS);
	if (cmd)
		tree_cleanup(cmd);
}
