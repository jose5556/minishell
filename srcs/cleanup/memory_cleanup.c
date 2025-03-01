/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:56 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:08 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(void *content)
{
	t_env	*env_var;

	env_var = (t_env *)(content);
	if (!env_var)
		return ;
	free(env_var->key);
	free(env_var->value);
	free(env_var);
}

void	free_token_node(void *content)
{
	t_token	*env_var;

	env_var = (t_token *)(content);
	if (!env_var)
		return ;
	if (env_var->type == TOKEN_DELIMITER)
		unlink(env_var->value);
	if (env_var->value)
		free(env_var->value);
	free(env_var);
}

void	free_env_list(t_list **env_list)
{
	ft_lstclear(env_list, free_env_node);
}

void	free_token_list(t_list **token_list)
{
	ft_lstclear(token_list, free_token_node);
}

void	free_path(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
