/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:55:01 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 15:54:01 by joseoliv         ###   ########.fr       */
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

	new_node = create_bash(command);
	if (!new_node)
		return ;
	if (!(*bash))
		*bash = new_node;
	else
	{
		while ((*bash)->lst_commands->next)
			(*bash)->lst_commands = (*bash)->lst_commands->next;
		(*bash)->lst_commands->next = new_node->lst_commands;
		while ((*bash)->next)
			*bash = (*bash)->next;
		(*bash)->next = new_node;	
	}
}
