/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:49 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:57 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_unset(int process, int i, char **cmd)
{
	int	j;
	int	status;

	status = 0;
	if (!cmd[i] || !*cmd[i])
		return (1);
	if (cmd[i][0] == '-' && i == 1)
	{
		if (process == CHILD_PROCESS)
			custom_error("minishell: unset: ", cmd[i],
				": invalid option\nunset: usage: unset [name ...]", 2);
		return (2);
	}
	if (ft_strlen(cmd[i]) == 0)
		return (1);
	if (!ft_isalpha(cmd[i][0]) && cmd[i][0] != '_')
		status = 1;
	j = 1;
	while (cmd[i][j])
	{
		if (!ft_isalnum(cmd[i][j]) && cmd[i][j] != '_')
			status = 1;
		j++;
	}
	return (status);
}

int	unset(t_shell *shell, t_exec_cmd *cmd, int procs)
{
	int		i;
	int		status;
	t_list	*node;
	t_env	*env_node;

	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		status = validate_unset(procs, i, cmd->argv);
		if (status == 0)
		{
			node = find_env_by_key(shell->env_list, cmd->argv[i]);
			if (node != NULL)
			{
				env_node = ((t_env *)(node->content));
				env_node->export_status = false;
			}
		}
		if (status == 1 && procs == CHILD_PROCESS)
			custom_error("minishell: ", cmd->argv[i],
				": not a valid identifier", 1);
		i++;
	}
	return (g_exit_status);
}
