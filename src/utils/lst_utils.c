/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:22:33 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 14:23:08 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_newlst(char *content)
{
	t_list	*new_node;

	new_node = ft_calloc(sizeof(t_list), 1);
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **lst, char *content)
{
	t_list	*new_node;
	t_list	*last;

	new_node = ft_newlst(content);
	if (!new_node)
		return ;
	if (!(*lst))
		*lst = new_node;
	else
	{
		last = get_last_lst(*lst);
		last->next = new_node;
	}
}

t_list	*get_last_lst(t_list *lst)
{
	t_list	*last;

	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;

	temp = *lst;
	if (!(*lst))
		return ;
	while (*lst)
	{
		free(temp);
		*lst = (*lst)->next;
		temp = *lst;
	}
	*lst = NULL;
}
