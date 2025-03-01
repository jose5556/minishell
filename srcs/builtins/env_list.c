/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:27 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:21 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_underscore_update(t_shell *sh, t_list *last)
{
	t_list	*to_remove;
	t_env	*node_content;

	to_remove = NULL;
	if (!last)
	{
		to_remove = find_env_by_key(sh->env_list, "_");
		if (to_remove)
			((t_env *)to_remove->content)->export_status = false;
		return ;
	}
	node_content = init_env_variable("_", get_token_content(last)->value);
	update_env_list(sh, node_content);
}

void	remove_node_from_list(t_list **list, t_list *node)
{
	t_list	*previous;
	t_list	*current;

	if (list == NULL || node == NULL)
		return ;
	previous = NULL;
	current = *list;
	while (current != NULL)
	{
		if (current == node)
		{
			if (previous == NULL)
			{
				*list = current->next;
			}
			else
			{
				previous->next = current->next;
			}
			ft_lstdelone(current, &free_env_node);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

t_list	*find_env_by_key(t_list *list, char *key)
{
	t_list	*node;
	t_env	*env_content;

	node = list;
	while (node != NULL)
	{
		env_content = node->content;
		if (ft_strcmp(env_content->key, key) == 0)
			return (node);
		node = node->next;
	}
	return (NULL);
}

void	set_env_variable(t_shell *shell, char *key, char *new_value)
{
	t_list	*last;
	t_env	*node_content;

	last = find_last_word_token(shell->token_list);
	if (ft_strcmp(key, "_") == 0)
	{
		handle_underscore_update(shell, last);
	}
	else
	{
		node_content = init_env_variable(key, new_value);
		update_env_list(shell, node_content);
	}
	update_shell_paths(shell);
}
