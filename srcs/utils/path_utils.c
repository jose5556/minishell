/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:36 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:26 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_command_in_directory(t_shell *shell, char *cmd,
	char *path_dir)
{
	char	*full_path;
	char	*path_with_slash;

	full_path = NULL;
	path_with_slash = ft_strjoin(path_dir, "/");
	full_path = ft_strjoin(path_with_slash, cmd);
	free(path_with_slash);
	if (!full_path)
		clear_exit(shell, 1);
	if (access(full_path, F_OK) != 0)
	{
		free(full_path);
		return (NULL);
	}
	return (full_path);
}

static char	*search_cmd_in_paths(t_shell *shell, char *cmd)
{
	char	*path_command;
	char	**current_path;

	if (!shell->paths)
		return (NULL);
	current_path = shell->paths;
	while (*current_path)
	{
		path_command = check_command_in_directory(shell, cmd, *current_path);
		if (path_command)
			return (path_command);
		current_path++;
	}
	return (NULL);
}

bool	is_directory(char *cmd)
{
	struct stat	info;

	if (stat(cmd, &info) != 0)
		return (false);
	return (S_ISDIR(info.st_mode));
}

char	*resolve_command_path(t_shell *shell, char *command)
{
	if (!command || !*command)
		return (NULL);
	if (ft_strchr(command, '/') != NULL)
		return (ft_strdup(command));
	return (search_cmd_in_paths(shell, command));
}

void	skip_quoted_section(const char *input, int *index, char quote_char)
{
	(*index)++;
	while (input[*index] && input[*index] != quote_char)
		(*index)++;
	if (input[*index] == quote_char)
		(*index)++;
}
