/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:17:50 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/03 05:12:24 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_tree	*create_tree(char *command)
{
	t_tree	*tree;

	tree = ft_calloc(sizeof(t_tree), 1);
	if (!tree)
		return (NULL);
	tree->command = strdup(command);
	if (!tree->command)
	{
		free(tree);
		return (NULL);
	}
	return (tree);
}

void	add_tree(t_tree *tree, char *command)
{
	t_tree			*node;
	t_operator_type	operator;
	
	operator = get_command_num(command);
	node = create_tree(command);
	if (operator != COMMAND)
		tree->right = node;
	else 
		tree->left = node;
	node->parent = tree;
}

t_operator_type get_command_num(char *command)
{
	if (!command)
		return (COMMAND);
	else if (!strcmp(command, "|"))
        return PIPE;
    else if (!strcmp(command, "||"))
        return OR;
    else if (!strcmp(command, "&&"))
        return AND;
    return COMMAND;
}
