/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmoura-p <cmoura-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:47:42 by cmoura-p          #+#    #+#             */
/*   Updated: 2024/12/05 13:10:32 by cmoura-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	btw_quotes(char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i])
		i++;
	return (i);
}
static int	err_quotes(char *line)
{
	char quote = 0;
	int i = 0;

	while (line[i])
	{
		if ((line[i] == '\'' || line[i] == '"') && quote == 0)
			quote = line[i]; 			// Aspas abertas
		else if (line[i] == quote)
			quote = 0; 					// Aspas fechadas
		i++;
	}
	if (quote != 0)
	{
		ft_printf("Syntax error: Unmatched '%c'\n", quote);
		return (1);
	}
	return (0);
}
static int	err_pipes(char *line)
{
	int		i;
	int		is_pipe;

	i = 0;
	is_pipe = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = btw_quotes(line, i);
		else
		{
			if (line[i] == '|')
			{
				if (is_pipe)
					return (1);
				is_pipe = 1;
			}
			else
				is_pipe = 0;
			i++;
		}
	}
	if (is_pipe)
		return (1);
	return (0);
}
static int	err_redir(char *line)
{
	int		i;
	int		is_redir;

	i = 0;
	is_redir = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
			i = btw_quotes(line, i);
		else
		{
			if (line[i] == '>' || line[i] == '<')
			{
				if (is_redir)
					return (1);
				is_redir = 1;
			}
			else
				is_redir = 0;
			i++;
		}
	}
	if (is_redir)
		return (1);
	return (0);
}
char	*check_syntax(char *cmd_line)
{
	if (!cmd_line)
		return (0);
	cmd_line = ft_strtrim(cmd_line, " ");
	if (err_quotes(cmd_line))
		return(NULL);
	if (err_pipes(cmd_line))
	{
		ft_printf("Syntax error: wrong use of pipes\n");
		return (NULL);
	}
	if (err_redir(cmd_line))
	{
		ft_printf("Syntax error: wrong use of redirection\n");
		return (NULL);
	}
	return (cmd_line);
}

