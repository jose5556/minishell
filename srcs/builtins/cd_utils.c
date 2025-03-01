/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:18 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:08 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_consecutive_dots(char *input)
{
	int	consecutive_dots;
	int	i;

	consecutive_dots = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '.')
			consecutive_dots++;
		else
			consecutive_dots = 0;
		if (consecutive_dots >= 3)
		{
			custom_error("minishell: ", "cd: ", \
				"invalid path: too many consecutive dots", 1);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	validate_cd_args(t_shell *shell, char *cmd, char **argv)
{
	(void)shell;
	(void)cmd;
	if (argv[1])
	{
		if (!validate_builtin_args(argv) || !check_consecutive_dots(argv[1]))
			return (false);
	}
	return (true);
}

void	handle_cd_oldpwd(t_shell *shell)
{
	char	*oldpwd;

	oldpwd = get_env_var(shell->env_list, "OLDPWD");
	if (!oldpwd || !*oldpwd)
	{
		custom_error("minishell: ", "cd: ", "OLDPWD not set", 1);
		g_exit_status = 1;
		if (oldpwd)
			free(oldpwd);
		return ;
	}
	printf("%s\n", oldpwd);
	cd_to_path(shell, oldpwd);
	free(oldpwd);
}
