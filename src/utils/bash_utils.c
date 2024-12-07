/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 08:55:01 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/07 14:23:14 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_bash	*create_bash(char *command)
{
	t_bash	*bash;

	bash = NULL;
	if (!command)
		return (NULL);
	bash = malloc(sizeof(t_bash));
	if (!bash)
		return (NULL);
	bash->raw_command = ft_strdup(command);
	bash->exit_status = 0;
	bash->bash_return = NULL;
	bash->next = NULL;
	return (bash);
}

void	addback_bash(char *command, t_bash **bash)
{
	t_bash	*new_node;
	t_bash	*last;

	if (!command)
		return ;
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
	while (bash && bash->next)
		bash = bash->next;
	return (bash);
}

void	ft_bashclear(t_bash **bash)
{
	t_bash	*temp;
	t_bash	*next_node;

	if (!(*bash) || !bash)
		return ;
	temp = *bash;
	while (temp)
	{
		next_node = temp->next;
		free(temp);
		temp = next_node;
	}
	*bash = NULL;
}

void	print_bash(t_bash *bash)
{
	while (bash)
	{
		ft_printf("%s\n", bash->raw_command);
		bash = bash->next;
	}
}
