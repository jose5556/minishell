/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:11 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:13:00 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_home_path(char *home_path, char *original_value)
{
	char	*status;
	char	*path_suffix;

	if (!ft_strcmp("~", original_value))
		return (ft_strdup(home_path));
	if (!ft_strcmp("~+/-", original_value))
		return (ft_strjoin(home_path, "/-"));
	if (!ft_strcmp("~-/+", original_value))
		return (ft_strjoin(home_path, "/+"));
	path_suffix = ft_strdup(&original_value[1]);
	if (!path_suffix)
		return (NULL);
	status = ft_strjoin(home_path, path_suffix);
	free(path_suffix);
	return (status);
}

static char	*handle_pwd_cases(char *original_value, char *pwd)
{
	char	*status;

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (ft_strdup(""));
	if (!ft_strcmp("~+", original_value))
		status = ft_strdup(pwd);
	else if (!ft_strcmp("~+/-", original_value))
		status = ft_strjoin(pwd, "/-");
	else if (!ft_strncmp("~+/", original_value, 3))
		status = ft_strjoin(pwd, original_value + 2);
	else
		status = ft_strjoin(pwd, "/-");
	free(original_value);
	return (status);
}

static char	*handle_oldpwd_cases(t_shell *shell, char *original_value)
{
	char	*status;
	char	*oldpwd;

	oldpwd = get_env_var(shell->env_list, "OLDPWD");
	if (!oldpwd || !*oldpwd)
	{
		if (oldpwd)
			free(oldpwd);
		status = ft_strdup(original_value);
		free(original_value);
		return (status);
	}
	if (!ft_strcmp("~-", original_value))
		status = ft_strdup(oldpwd);
	else
		status = ft_strjoin(oldpwd, "/+");
	free(oldpwd);
	free(original_value);
	return (status);
}

char	*resolve_home_directory(t_shell *shell, t_list *tmp)
{
	char	*status;
	char	*home_path;
	char	*original_value;
	char	pwd[PATH_MAX];

	original_value = get_token_content(tmp)->value;
	if (!ft_strcmp("~+", original_value) || !ft_strcmp("~+/-", original_value)
		|| !ft_strncmp("~+/", original_value, 3))
		return (handle_pwd_cases(original_value, pwd));
	if (!ft_strcmp("~-", original_value) || !ft_strcmp("~-/+", original_value))
		return (handle_oldpwd_cases(shell, original_value));
	home_path = get_env_var(shell->env_list, "HOME");
	if (!home_path)
		return (NULL);
	status = create_home_path(home_path, original_value);
	free(home_path);
	free(original_value);
	get_token_content(tmp)->value = NULL;
	if (!status)
		clear_exit(shell, 1);
	return (status);
}
