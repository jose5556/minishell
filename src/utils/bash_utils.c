/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:55:01 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 09:02:55 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bash	*create_bash(char *command)
{
	t_bash	*bash;
	t_list	*list;

	bash = NULL;
	list = NULL;
	bash = ft_calloc(sizeof(t_bash), 1);
	list = ft_calloc(sizeof(t_list), 1);
	if (!bash || !list)
		return (NULL);
	list->content = ft_strdup(command);
	bash->lst_commands = list;
	return (bash);
}

void	addback_bash(char *command, t_bash **bash)
{
	t_bash	*new_node;
	t_bash	*last;

	new_node = create_bash(command);
	if (!new_node)
		return ;
	if (!(*bash))
		*bash = new_node;
	else
	{
		last = get_last_bash(*bash);
		last->next = new_node;
	}
}

t_bash	*get_last_bash(t_bash *bash)
{
	t_bash	*last;

	last = bash;
	while (last->next)
		last = last->next;
	return (last);
}

void	ft_bashclear(t_bash **bash)
{
	t_bash	*temp;

	temp = *bash;
	if (!(*bash))
		return ;
	ft_lstclear(&(*bash)->lst_commands);
	while (*bash)
	{
		free(temp);
		*bash = (*bash)->next;
		temp = *bash;
	}
	bash = NULL;
}
