/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:34 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:29 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**allocate_str_array(t_shell *shell, int size)
{
	char	**array;

	array = malloc((size + 1) * sizeof(char *));
	if (!array)
		clear_exit(shell, 1);
	return (array);
}

static char	*format_content_as_str(t_shell *shell, void *content,
	t_content_type type)
{
	char	*res;
	char	*key_with_equals;
	t_env	*env_var;

	res = NULL;
	if (type == TOKEN_TYPE)
		res = ft_strdup(((t_token *)content)->value);
	else if (type == ENV_VAR_TYPE)
	{
		env_var = (t_env *)content;
		key_with_equals = ft_strjoin(env_var->key, "=");
		res = ft_strjoin(key_with_equals, env_var->value);
		free(key_with_equals);
	}
	if (!res)
		clear_exit(shell, 1);
	return (res);
}

static void	fill_array(t_shell *sh, t_list *list,
						char **array, t_content_type type)
{
	int		i;
	char	*value;

	i = 0;
	while (list)
	{
		value = format_content_as_str(sh, list->content, type);
		if (!value)
		{
			free_array(array, i);
			clear_exit(sh, 1);
		}
		array[i] = ft_strdup(value);
		free(value);
		if (!array[i])
		{
			free_array(array, i);
			clear_exit(sh, 1);
		}
		list = list->next;
		i++;
	}
}

char	**linked_list_to_str_array(t_shell *shell, t_list *list,
	t_content_type type)
{
	int		len;
	char	**array;

	len = ft_lstsize(list);
	array = allocate_str_array(shell, len);
	if (!shell->env_list)
		return (NULL);
	fill_array(shell, list, array, type);
	array[len] = NULL;
	return (array);
}

void	free_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free (array);
}
