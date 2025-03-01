/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:38 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:37 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env_vars(int len, char **env_array)
{
	int		i;
	int		swapped;

	i = 0;
	swapped = 0;
	if (len == 1)
		return ;
	while (i < len - 1)
	{
		if (ft_strcmp(env_array[i], env_array[i + 1]) > 0)
		{
			swap(&env_array[i], &env_array[i + 1]);
			swapped = 1;
		}
		i++;
	}
	if (swapped)
		sort_env_vars(len - 1, env_array);
}

static void	sort_env_ascii(char **array, int size)
{
	sort_env_vars(size, array);
}

static char	**order_envp(t_list *env_lst)
{
	int		len;
	char	**env_array;

	len = 0;
	env_array = list_to_array_export(env_lst);
	while (env_array[len])
		len++;
	sort_env_ascii(env_array, len);
	return (env_array);
}

char	**list_to_array_export(t_list *env)
{
	int		size;
	char	**array;

	size = ft_lstsize(env);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	fill_env_array(array, env, size);
	return (array);
}

void	print_sorted_env(t_shell *shell)
{
	int		i;
	char	**ordered_envp;

	i = 0;
	ordered_envp = order_envp(shell->env_list);
	while (ordered_envp[i])
	{
		if (*ordered_envp[i])
			printf("declare -x %s\n", ordered_envp[i]);
		i++;
	}
	free_array(ordered_envp, i);
}
