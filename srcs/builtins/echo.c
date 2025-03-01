/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:12:24 by cereais           #+#    #+#             */
/*   Updated: 2025/02/02 15:12:15 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_echo_flag(char *word)
{
	int	i;

	if (!word[1])
		return (false);
	i = 1;
	while (word[i])
	{
		if (word[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

static int	skip_echo_flag(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (argv[i][0] != '-')
			return (i);
		if (!is_echo_flag(argv[i]))
			return (i);
		i++;
	}
	if (!argv[i])
		return (i);
	return (1);
}

static void	print_echo_output(char **argv, int i)
{
	bool	newline_flag;

	newline_flag = false;
	if (i != 1)
		newline_flag = true;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!newline_flag)
		printf("\n");
}

int	echo(t_shell *shell, t_exec_cmd *cmd)
{
	int	arg;

	(void)shell;
	arg = 0;
	g_exit_status = 0;
	arg = skip_echo_flag(cmd->argv);
	print_echo_output(cmd->argv, arg);
	return (g_exit_status);
}
