/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:43 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:49 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	invalid_identifier_handler(int process, char *arg)
{
	if (process == CHILD_PROCESS)
	{
		if (arg[0] == '-')
		{
			custom_error("minishell: export: ", arg, ": invalid option\n"
				"export: usage: export [name[=value] ...]", 2);
			return (2);
		}
		custom_error("minishell: export: '", arg,
			"': not a valid identifier", 2);
	}
	return (1);
}

static bool	validate_identifier(char *identifier)
{
	int	i;

	i = 0;
	if (identifier[i] == '=' || ft_isdigit(identifier[i]))
		return (false);
	while (identifier[i] != '=' && identifier[i])
	{
		if (contains_char("\t []/{}-+#?.,!^$%", identifier[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	process_export_arguments(t_shell *shell,
	t_exec_cmd *execcmd, int process)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (execcmd->argv[i])
	{
		if (validate_identifier(execcmd->argv[i]))
		{
			extract_key_value(execcmd->argv[i], &key, &value);
			if (process == PARENT_PROCESS)
			{
				if (value || !find_env_by_key(shell->env_list, key))
					set_env_variable(shell, key, value);
			}
			free_key_pair(key, value);
		}
		else
			return (invalid_identifier_handler(process, execcmd->argv[i]));
		i++;
	}
	return (0);
}

int	export(t_shell *shell, t_exec_cmd *execcmd, int process)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	if (process == CHILD_PROCESS && !execcmd->argv[i])
		print_sorted_env(shell);
	else
		status = process_export_arguments(shell, execcmd, process);
	return (status);
}
