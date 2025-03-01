/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:06 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:22 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*extract_env_key(int equals_sign, char *env_var)
{
	char	*key;

	key = ft_calloc(1, sizeof(char) * (equals_sign + 1));
	if (!key)
		return (NULL);
	ft_strlcpy(key, &env_var[0], equals_sign + 1);
	return (key);
}

static char	*extract_env_value(int equals_sign, char *env_var)
{
	int		len;
	char	*value;

	len = (int)ft_strlen(&env_var[equals_sign + 1]);
	value = ft_calloc(1, sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	ft_strlcpy(value, &env_var[equals_sign + 1], len + 1);
	return (value);
}

static t_env	*create_new_env_node(t_shell *shell, bool visible,
	char *key, char *value)
{
	t_env	*env_node;

	env_node = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!env_node)
		clear_exit(shell, 1);
	env_node->key = ft_strdup(key);
	if (value != NULL)
		env_node->value = ft_strdup(value);
	else
		env_node->value = NULL;
	env_node->export_status = visible;
	return (env_node);
}

void	initialize_empty_env(t_shell *shell)
{
	char	*pwd;
	t_env	*env_node;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		env_node = create_new_env_node(shell, true, "PWD", pwd);
		ft_lstadd_back(&shell->env_list, ft_lstnew(env_node));
		free(pwd);
	}
	else
	{
		env_node = create_new_env_node(shell, true, "PWD", "");
		ft_lstadd_back(&shell->env_list, ft_lstnew(env_node));
	}
	env_node = create_new_env_node(shell, true, "SHLVL", "1");
	ft_lstadd_back(&shell->env_list, ft_lstnew(env_node));
	env_node = create_new_env_node(shell, true, "OLDPWD", NULL);
	ft_lstadd_back(&shell->env_list, ft_lstnew(env_node));
}

void	build_env_list(t_shell *shell, char **env_var)
{
	int		key_len;
	t_env	*env_var_data;
	t_list	*env_list_node;

	while (*env_var)
	{
		key_len = get_key_length(*env_var);
		if (key_len > -1)
		{
			env_var_data = ft_calloc(1, sizeof(t_env));
			if (!env_var_data)
				clear_exit(shell, 1);
			env_var_data->key = extract_env_key(key_len, *env_var);
			env_var_data->value = extract_env_value(key_len, *env_var);
			env_var_data->export_status = true;
			if (!(env_var_data->key) || !(env_var_data->value))
				clear_exit(shell, 1);
			env_list_node = ft_lstnew(env_var_data);
			if (!env_list_node)
				clear_exit(shell, 1);
			ft_lstadd_back(&shell->env_list, env_list_node);
		}
		env_var++;
	}
}
