/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:41 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:40 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_double_quotes(char *value)
{
	int		len;
	char	*new_value;

	if (!value)
		return (NULL);
	len = ft_strlen(value) + 3;
	new_value = (char *)malloc(sizeof(char) * len);
	if (!new_value)
		return (NULL);
	new_value[0] = '"';
	ft_strlcpy(new_value + 1, value, len - 2);
	new_value[len - 2] = '"';
	new_value[len - 1] = '\0';
	return (new_value);
}

static void	format_env_variable(int i, char **array, t_env *env_var)
{
	char	*tmp_key;
	char	*tmp_value;

	if (env_var->export_status && ft_strcmp(env_var->key, "_"))
	{
		tmp_value = add_double_quotes(env_var->value);
		if (tmp_value)
		{
			tmp_key = ft_strjoin(env_var->key, "=");
			if (tmp_key)
			{
				array[i] = ft_strjoin(tmp_key, tmp_value);
				free(tmp_key);
			}
			else
				array[i] = ft_strdup(env_var->key);
			free(tmp_value);
		}
		else
			array[i] = ft_strdup(env_var->key);
	}
	else
		array[i] = ft_strdup("");
}

void	fill_env_array(char **array, t_list *env, int size)
{
	int		i;
	t_list	*current;

	i = 0;
	current = env;
	while (i < size)
	{
		format_env_variable(i, array, current->content);
		current = current->next;
		i++;
	}
	array[i] = NULL;
}
