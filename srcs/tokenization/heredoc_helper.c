/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:14:01 by cereais           #+#    #+#             */
/*   Updated: 2025/02/01 16:30:22 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc_tempfile(t_shell *shell, int doc_count)
{
	int		hash_value;
	char	*temp_path;
	char	*prefix;
	char	*id;

	temp_path = NULL;
	hash_value = shell->pid + (doc_count * 1000);
	prefix = ft_strdup(".tmp_heredoc_");
	id = ft_itoa(hash_value);
	temp_path = ft_strjoin(prefix, id);
	free(prefix);
	free(id);
	return (temp_path);
}

int	write_heredoc_line(char *filename, char *content)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (0);
	if (write(fd, content, ft_strlen(content)) == -1)
	{
		close(fd);
		return (0);
	}
	if (write(fd, "\n", 1) == -1)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

char	*expand_heredoc_variable(t_shell *shell, char *str)
{
	int		i;
	char	*new_token;
	char	*expanded;

	new_token = ft_strdup("");
	i = 0;
	while (str[i])
	{
		expanded = NULL;
		if (str[i] == '$' && str[i + 1] != '\0')
		{
			i++;
			if (is_valid_expansion_char(str[i]))
				expanded = expand_var(shell, str, &i);
			else
				expanded = ft_strjoin("$", extract_until_dollar(str, &i));
		}
		else
			expanded = extract_until_dollar(str, &i);
		new_token = ft_strjoin_free(new_token, expanded, 1);
		if (expanded)
			free(expanded);
	}
	free(str);
	return (new_token);
}

char	*initialize_heredoc_file(t_shell *shell, int i)
{
	int		fd;
	char	*filename;

	filename = create_heredoc_tempfile(shell, i);
	if (!filename)
	{
		ft_putstr_fd("Error creating temporary file\n", 2);
		return (NULL);
	}
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		ft_putstr_fd("Error opening temporary file\n", 2);
		free(filename);
		return (NULL);
	}
	if (close(fd) == -1)
	{
		ft_putstr_fd("Error closing temporary file\n", 2);
		free(filename);
		return (NULL);
	}
	return (filename);
}

char	*initialize_heredoc(t_shell *shell, int i)
{
	char	*filename;

	filename = initialize_heredoc_file(shell, i);
	if (!filename)
		clear_exit(shell, 1);
	return (filename);
}
