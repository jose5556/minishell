/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:21 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:12 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_to_path(t_shell *shell, char *dest_folder)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
	{
		perror("getcwd");
		g_exit_status = 1;
		return ;
	}
	if (chdir(dest_folder) != 0)
	{
		custom_error("minishell: cd: ", dest_folder, \
			": No such file or directory", 1);
		g_exit_status = 1;
		return ;
	}
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("getcwd");
		g_exit_status = 1;
		return ;
	}
	set_env_variable(shell, "OLDPWD", old_pwd);
	set_env_variable(shell, "PWD", new_pwd);
}

static int	change_to_home_directory(char *home_path, char *old_pwd)
{
	if (getcwd(old_pwd, sizeof(char) * PATH_MAX) == NULL)
	{
		perror("getcwd");
		g_exit_status = 1;
		return (1);
	}
	g_exit_status = chdir(home_path);
	if (g_exit_status != 0)
	{
		custom_error("minishell: ", "cd", ": Error in changing directory",
			g_exit_status);
		return (1);
	}
	return (0);
}

void	cd_home(t_shell *shell, char *home_path)
{
	t_list	*home_node;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	home_node = find_env_by_key(shell->env_list, "HOME");
	if (!home_node || !((t_env *)home_node->content)->export_status)
	{
		custom_error("minishell: ", "cd", ": HOME not set", 1);
		return ;
	}
	if (change_to_home_directory(home_path, old_pwd))
		return ;
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
	{
		perror("getcwd");
		g_exit_status = 1;
		return ;
	}
	set_env_variable(shell, "OLDPWD", old_pwd);
	set_env_variable(shell, "PWD", new_pwd);
}

void	cd_command_handler(t_shell *shell, char **argv)
{
	char	*home_path;

	home_path = get_env_var(shell->env_list, "HOME");
	if (home_path == NULL)
	{
		custom_error("minishell: ", "cd", "HOME not set", 1);
		return ;
	}
	if (!argv[1] || !ft_strcmp(argv[1], home_path) || !ft_strcmp(argv[1], "--"))
		cd_home(shell, home_path);
	else if (!ft_strcmp(argv[1], "-"))
		handle_cd_oldpwd(shell);
	else
		cd_to_path(shell, argv[1]);
	free(home_path);
}

int	change_dir(t_shell *shell, t_exec_cmd *cmd)
{
	g_exit_status = 0;
	if (!validate_cd_args(shell, cmd->argv[0], cmd->argv))
	{
		g_exit_status = 1;
		return (g_exit_status);
	}
	cd_command_handler(shell, cmd->argv);
	return (g_exit_status);
}
