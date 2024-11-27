/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:42:41 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/27 04:09:03 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*str_prompt(char **result, char *logname)
{
	*result = ft_strjoin_free("@", *result, 2);
	*result = ft_strjoin_free(logname, *result, 2);
	*result = ft_strjoin_free(*result, ":~$", 1);
	return (*result);
}

static void	free_all(char ***split_result, char **logname, char **session_manager, char **result)
{
	int	i;

	i = 0;
	while ((*split_result)[i])
	{
		free((*split_result)[i]);
		i++;
	}
	free(*split_result);
	*split_result = NULL;
	if (!ft_strlen(*logname))
	{
		free(*logname);
		*logname = NULL;
	}
	if (*session_manager && !ft_strncmp(*session_manager, "localhost\0", 10))
	{
		free(*session_manager);
		*session_manager = NULL;
	}
	free(*result);
}

void	get_prompt(void)
{
	char	*logname;
	char	*session_manager;
	char	**split_result;
	char	*result;
	int		i;

	i = 0;
	split_result = NULL;
	logname = getenv("LOGNAME");
	session_manager = getenv("SESSION_MANAGER");
	if (!logname)
		logname = ft_strdup("");
	if (!session_manager)
		result = ft_strdup("localhost");
	else if ((ft_strchr(session_manager, '.')))
	{
		split_result = ft_split(session_manager, '/');
		while (split_result && split_result[1][i] && split_result[1][i] != '.')
			i++;
		result = ft_substr(split_result[1], 0, i);
	}
	else
		result = ft_strdup(session_manager);
	result = str_prompt(&result, logname);
	ft_printf("%s ", result);
	free_all(&split_result, &logname, &session_manager, &result);
}
