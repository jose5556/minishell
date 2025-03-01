/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:30 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:25 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(t_shell *shell)
{
	t_env	*env_content;
	t_list	*tmp;

	tmp = shell->env_list;
	while (tmp)
	{
		env_content = tmp->content;
		if (env_content->export_status == true && env_content->value)
			printf("%s=%s\n", env_content->key, env_content->value);
		tmp = tmp->next;
	}
}

t_list	*find_last_word_token(t_list *token_list)
{
	t_list	*current;
	t_list	*last;
	bool	is_first_word;

	current = token_list;
	last = NULL;
	is_first_word = false;
	while (current)
	{
		if (get_token_content(current)->type == TOKEN_WORD)
		{
			if (is_first_word == true)
				last = current;
			else
			{
				is_first_word = true;
				last = current;
			}
		}
		current = current->next;
	}
	return (last);
}

t_env	*init_env_variable(char *key, char *value)
{
	t_env	*node_data;

	node_data = ft_calloc(1, sizeof(t_env));
	if (!node_data)
		return (NULL);
	node_data->key = ft_strdup(key);
	if (!node_data->key)
	{
		free(node_data);
		return (NULL);
	}
	if (value)
	{
		node_data->value = ft_strdup(value);
		if (!node_data->value)
		{
			free(node_data->key);
			free(node_data);
			return (NULL);
		}
	}
	else
		node_data->value = NULL;
	node_data->export_status = true;
	return (node_data);
}

void	update_env_list(t_shell *shell, t_env *node_content)
{
	t_list	*to_rm;

	to_rm = find_env_by_key(shell->env_list, node_content->key);
	if (to_rm)
		remove_node_from_list(&shell->env_list, to_rm);
	ft_lstadd_back(&shell->env_list, ft_lstnew(node_content));
	if (shell->envp)
		free_path(shell->envp);
	shell->envp = linked_list_to_str_array(shell,
			shell->env_list, ENV_VAR_TYPE);
}

int	env(t_shell *shell, t_exec_cmd *cmd)
{
	if (!shell->env_list)
		return (1);
	if (cmd->argv[1])
	{
		if (cmd->argv[1][0] == '-')
			custom_error("minishell: env: invalid option: ",
				cmd->argv[1], NULL, 125);
		else
			custom_error("minishell: env: ", cmd->argv[1], \
				": No such file or directory", 127);
		return (g_exit_status);
	}
	print_env(shell);
	return (g_exit_status);
}
