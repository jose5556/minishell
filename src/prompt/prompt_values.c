/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 23:29:05 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/30 21:43:41 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_logname()
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

char	*get_hostname()
{
	int		fd;
	char	*result;

	result = NULL;
	fd = open("/etc/hostname", O_RDONLY);
	if (fd == -1)
		return (ft_strdup("localhost"));
	result = get_next_line(fd);
	if (!result)
		return (ft_strdup("localhost"));
	result = hostname_util(&result);
	close(fd);
	return (result);
}

char	*get_home()
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
	char	*pwd_remains;

	pwd = NULL;
	pwd_remains = NULL;
	pwd = getenv("PWD");
	if (!pwd)
		return (NULL);
	len1 = ft_strlen(pwd);
	len2 = ft_strlen(prompt->home_path);
	if (!(ft_strncmp(prompt->home_path, pwd, len1)))
		return (NULL);
	pwd_remains = ft_substr(pwd + len2, 0, ft_strlen(pwd + len2));
	return (pwd_remains);
}
