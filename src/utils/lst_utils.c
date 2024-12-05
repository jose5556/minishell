/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 13:22:33 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 16:08:00 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*ft_newlst(char *content)
{
	t_list	*new_node;

	new_node = (t_list *) malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_back(t_list **lst, char *content)
{
	t_list	*new_node;
	t_list	*temp;

	new_node = ft_newlst(content);
	if (!new_node)
		return ;
	if (!(*lst))
	{
		*lst = new_node;
		new_node->next = *lst;
	}
	else
	{
		temp = *lst;
		while (temp->next != *lst && temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->next = *lst;
	}
}

void	ft_lstclear(t_list **lst)
{
	t_list	*temp;
	t_list	*next_node;

	if (!(*lst))
		return ;
	temp = *lst;
	while (temp->next != *lst)
		temp = temp->next;
	temp->next = NULL;
	temp = *lst;
	while (temp)
	{
		next_node = temp->next;
		free(next_node->content);
		free(temp);
		temp = next_node;
	}
	*lst = NULL;
}

void	print_lst(t_bash *bash)
{
	while (bash->lst_commands)
	{
		ft_printf("%s\n", bash->lst_commands->content);
		bash->lst_commands = bash->lst_commands->next;
	}
}
