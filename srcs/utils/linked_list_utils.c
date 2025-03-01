/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:05:14 by dzinchen          #+#    #+#             */
/*   Updated: 2025/02/02 12:05:15 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	unlink_node(t_list **list, t_list *target)
{
	t_list	**curr;

	curr = list;
	if (!list || !target)
		return ;
	while (*curr)
	{
		if (*curr == target)
		{
			*curr = target->next;
			return ;
		}
		curr = &(*curr)->next;
	}
}

static void	free_node(t_list *node)
{
	if (!node)
		return ;
	free_token_node(node->content);
	free(node);
}

void	remove_node(t_list **list, t_list *target)
{
	unlink_node(list, target);
	free_node(target);
}
