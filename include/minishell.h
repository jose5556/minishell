/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:34 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 08:27:40 by joseoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

//extern int	g_signal;

# define EXIT_SUCCESS_MESSAGE "exit"

typedef enum e_operator_type
{
    COMMAND,				// line
    OR,						// ||
    AND,       				// &&
    PIPE,      				// |
    REDIRECT_IN,    		// <
    REDIRECT_OUT,  			// >
    INPUT_REDIRECTION,		// <<
    REDIRECT_APPEND, 		// >>
    GROUP_BEGIN,     		// (
    GROUP_END,     		// )
} t_operator_type;


typedef struct s_bash
{
	int		ignore_exit_status;
	int		exit_status;
	char	**command;
	void	*bash_return;
} t_bash;

typedef struct s_prompt
{
	char	*logname;
	char	*hostname;
	char	*pwd;
	char	*home_path;
	char	*final_str;
} t_prompt;

//promp
char			*get_prompt(t_prompt *prompt);
char			*get_logname();
char			*get_hostname();
char			*get_home();
char			*get_pwd(t_prompt *prompt);

//init
void			init_signals();
void			init();

//signals
void	signal_handler(int signum);

//read_parse_line
char			*ft_readline(t_prompt *prompt, char *line, t_tree *tree);
void			parse_line(char *line, t_tree *tree);

//free_memory
void			ft_clear_all(t_prompt *prompt);
void			free_necessary(char	**line, t_prompt *prompt);

//utils
t_tree			*create_tree(char *command);
void			add_tree(t_tree *tree, char *command);
t_operator_type	get_command_num(char *command);
void			clear_tree(t_tree *tree);

#endif