/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:05:48 by dzinchen          #+#    #+#             */
/*   Updated: 2023/10/18 14:46:18 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delete(t_list *new, t_list *head, void (*del)(void *))
{
	while (head != 0)
	{
		new = head->next;
		del(head->content);
		free(head);
		head = new;
	}
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*prev;
	t_list	*head;

	prev = 0;
	head = 0;
	while (lst != 0)
	{
		new = malloc(sizeof(t_list));
		if (!new)
		{
			delete(new, head, del);
			return (0);
		}
		new->content = f(lst->content);
		new->next = 0;
		if (prev != 0)
			prev->next = new;
		else
			head = new;
		prev = new;
		lst = lst->next;
	}
	return (head);
}
