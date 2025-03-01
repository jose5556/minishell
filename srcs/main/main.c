/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzinchen <dzinchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:05:29 by dzinchen          #+#    #+#             */
/*   Updated: 2025/02/02 15:14:11 by dzinchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static void	execute_shell_commands(t_shell *shell, char *prompt_input,
	int status)
{
	setup_parent_shell_signals();
	lexer(shell, prompt_input);
	add_history(prompt_input);
	handle_heredoc(shell, &shell->token_list, prompt_input);
	free(prompt_input);
	parsing_tree(shell);
	if (safe_fork(shell) == 0)
	{
		setup_child_process_signals();
		exec_tree(shell, shell->cmd);
	}
	waitpid(shell->pid, &status, 0);
	handle_signal_status(status);
	if (shell->num_pipes == 0)
		handle_parent_builtins(shell);
	reinit_shell(shell);
}

void	main_loop(t_shell *shell)
{
	int		status;
	char	*prompt_input;

	status = 0;
	prompt_input = NULL;
	while (true)
	{
		setup_readline_signals();
		prompt_input = read_prompt_input(shell);
		if (!prompt_input)
			break ;
		if (!validate_input_syntax(prompt_input))
		{
			add_history(prompt_input);
			free(prompt_input);
			continue ;
		}
		execute_shell_commands(shell, prompt_input, status);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argv;
	validate_shell_args(argc);
	init_shell_env(&shell, envp);
	main_loop(&shell);
	clear_exit(&shell, 0);
	return (0);
}
