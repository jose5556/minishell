/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:13 by joseoliv          #+#    #+#             */
/*   Updated: 2024/11/25 19:07:00 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "./include/minishell.h"

static void	get_prompt()
{
	char	*logname;
	char	*session_manager;
	char	**split_result;
	char	*result;
	int		i;

	i = 0;
	logname = getenv("LOGNAME");
	session_manager = getenv("SESSION_MANAGER");
	if (!session_manager)
		result = ft_strdup("localhost");
	else if ((ft_strchr(session_manager, '.')))
	{
		split_result = ft_split(session_manager, '/');
		while (split_result[1][i] && split_result[1][i] != '.')
			i++;
		result = ft_substr(split_result[1], 0, i);
	}
	else
		result = ft_strdup(session_manager);
	result = ft_strjoin_free("@", result, 2);
	result = ft_strjoin_free(logname, result, 2);
	result = ft_strjoin_free(result, ":~$", 1);
	ft_printf("%s ", result);
	free(result);
}

int	main(void)
{
	char *line;

	line = NULL;
	while (1)
	{
		get_prompt();
		line = read_line(0, line);
		if (line == NULL)
			ft_printf("NULL\n");
		else
			ft_printf("%s\n", line);
		free(line);
	}
	return (1);
}
 */