/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:46 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:53 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	validate_pwd_args(t_shell *shell, char *cmd, char **argv)
{
	(void)shell;
	(void)cmd;
	if (!argv[1])
		return (true);
	if (validate_builtin_args(argv))
		return (true);
	if (argv[1][0] == '-' && argv[1][1])
	{
		custom_error("minishell: pwd: ", argv[1],
			": invalid option\npwd: usage: pwd", 2);
		g_exit_status = 2;
		return (false);
	}
	else
		return (true);
}

static void	exec_pwd(void)
{
	char	pwd[PATH_MAX];
	char	*status;

	status = getcwd(pwd, sizeof(pwd));
	if (status == NULL)
	{
		perror("pwd error:");
		g_exit_status = 2;
	}
	else
		printf("%s\n", pwd);
}

int	builtin_pwd(t_shell *shell, t_exec_cmd *cmd)
{
	(void)shell;
	(void)cmd;
	g_exit_status = 0;
	if (!validate_pwd_args(shell, cmd->argv[0], cmd->argv))
		return (g_exit_status);
	else
		exec_pwd();
	return (g_exit_status);
}
