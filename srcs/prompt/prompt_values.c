/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:13:41 by cereais           #+#    #+#             */
/*   Updated: 2025/01/26 10:30:11 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_logname(void)
{
	char	*logname;
	char	*temp;

	logname = NULL;
	temp = NULL;
	temp = getenv("LOGNAME");
	if (!temp)
		logname = ft_strdup("");
	else
		logname = ft_strdup(temp);
	return (logname);
}

static char	*hostname_util(char **result)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	if (ft_strchr(*result, '.'))
	{
		while ((*result)[i] && (*result)[i] != '.')
			i++;
		temp = ft_substr(*result, 0, i);
	}
	else if (ft_strchr(*result, '\n'))
	{
		while ((*result)[i] && (*result)[i] != '\n')
			i++;
		temp = ft_substr(*result, 0, i);
	}
	free(*result);
	return (temp);
}

char	*get_hostname(void)
{
	int		fd;
	char	*hostname;
	int		size_read;

	hostname = NULL;
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (close(fd), ft_strdup("localhost"));
	hostname = ft_calloc(sizeof(char), 256);
	if (!hostname)
	{
		free(hostname);
		return (close(fd), ft_strdup("localhost"));
	}
	size_read = read(fd, hostname, 255);
	close(fd);
	if (size_read > 0)
	{
		hostname = hostname_util(&hostname);
		return (hostname);
	}
	free(hostname);
	return (ft_strdup("localhost"));
}

char	*get_home(void)
{
	char	*home_path;

	home_path = NULL;
	home_path = getenv("HOME");
	if (home_path)
		return (ft_strdup(home_path));
	return (NULL);
}

char	*get_pwd(t_prompt *prompt)
{
	char	*pwd;
	int		len1;
	int		len2;
	char	*trimmed_pwd;

	pwd = NULL;
	trimmed_pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (NULL);
	len1 = ft_strlen(pwd);
	len2 = ft_strlen(prompt->home_path);
	if (!(ft_strncmp(prompt->home_path, pwd, len1)))
	{
		free(pwd);
		return (NULL);
	}
	trimmed_pwd = ft_substr(pwd + len2, 0, ft_strlen(pwd + len2));
	free(pwd);
	if (!trimmed_pwd)
		return (NULL);
	return (trimmed_pwd);
}
