/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:55:12 by mbastard          #+#    #+#             */
/*   Updated: 2022/05/18 15:42:38 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H
# include "../libft/inc/libft.h"
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "readline/readline.h"
# include "readline/history.h"
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

typedef struct s_data
{
	t_list	*cmds;
}			t_data;

typedef struct s_cmd
{
	char	*cmd;
	char	**arg;
	char	**envp;
}			t_cmd;

//	main.c
void	clear_data(t_data *data);
void	recover_history(int fd);

//	parser.c

/**
 * @brief Generate a command table while parsing the command line (cmd_line)
 *
 * @param input 	command line to parse
 * @return s_cmd* 	generated command table
 */
void	get_cmds(char *input, t_data *data);

//	signals.c

// Manage CTRL + C, CTRL + Z, ...
void	signal_controller(int signal);

//	utils.c

void	free_tab(char **tab);

// print.c

// Affiche la liste de commandes (temporaire pour débug)
void	print_cmds(t_list *cmds);

// exec.c

// While(t_list *cmds) in data, execute command
int		exec(t_data *data, char **envp);

//bin.c

// Use execve() for execute bin command
void	bin(t_cmd *cmd);

// builtin.c

int		is_builtin(t_cmd *cmd);
// Execute buitin command
int		builtin(t_cmd *cmd);

// Builtin
void	echo(t_cmd *cmd);

#endif
