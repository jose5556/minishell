/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joseoliv <joseoliv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:58:34 by joseoliv          #+#    #+#             */
/*   Updated: 2024/12/05 15:57:44 by joseoliv         ###   ########.fr       */
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

# define EXIT_SUCCESS_MESSAGE "exit\n"

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
    GROUP_END,     			// )
	NOTHING,				//NULL
} t_operator_type;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
} t_list;

typedef struct s_bash
{
	int				exit_status;
	void			*bash_return;
	t_operator_type	operator;
	struct s_list	*lst_commands;
	struct s_bash	*next;
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
void			init(char **line, t_prompt *prompt, t_bash **bash);
void			init_signals();

//signals
void			signal_handler(int signum);

//parse
void			parse_line(char **parsed_command, t_bash **bash);

//free_memory
void			ft_clear_all(t_prompt *prompt);
void			free_necessary(char	**line, t_prompt *prompt);

//utils
t_operator_type	get_command_type(char *command);

t_bash			*create_bash(char *command);
void			addback_bash(char *command, t_bash **bash);

t_list			*ft_newlst(char *content);
void			ft_lstadd_back(t_list **lst, char *content);
void			ft_lstclear(t_list **lst);
void			print_lst(t_bash *bash);

#endif