/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:55:12 by mbastard          #+#    #+#             */
/*   Updated: 2022/07/26 12:44:44 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "../libft/inc/libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define CYELLOW "\001\e[1;32m\002"
# define RESET   "\001\e[0m\002"

# define PROMPT CYELLOW "minishell$ " RESET

typedef struct s_data
{
	t_list	*cmds;
	char	**export;
	char	**envp;
	char	*pipeline_status;
}			t_data;

typedef struct s_cmd
{
	char	*cmd;
	char	**export;
	char	**arg;

	t_data	*data;
}			t_cmd;

//		main.c functions

void	clear_data(t_data *data);
void	quit(char *error_message, int error_code, int clean);

// init export et envp
void	init(t_data *data, char **envp);

// manage history and add (input) to the history file
void	manage_history(char *cmd);

//		parser.c functions

// Parse the (input) and build the command list in (data)
void	parser(char *input, t_data *data);
// Read the cmd line and thransform them for the parsing
char	*lexique_var(t_data *data, const char *cmd_line);
// Read the input and parse arg (space, simple quote and double quotes)
char	**lexique_arg(const char *input);
// Read the input and parse pipe
char	**lexique_pipe(const char *input);

//	signals.c

// Manage CTRL + C, CTRL + Z, ...
void	signal_controller(int signal);

//	utils.c

void	free_tab(char **tab);

// exec.c

// While(t_list *cmds) in data, execute command
int		exec(t_data *data);

//bin.c

// Use execve() for execute bin command
void	bin(t_cmd *cmd);

// builtin.c

// Return (1) if cmd->cmd is builtin, else return (0)
int		is_builtin(t_cmd *cmd);
// Execute buitin command
int		builtin(t_cmd *cmd);

// Builtin
void    ft_exit(void);
void	echo(t_cmd *cmd);
void	env(t_cmd *cmd);
void	pwd(t_cmd *cmd);
void	export(t_cmd *cmd);
void	cd(t_cmd *cmd);


#endif
