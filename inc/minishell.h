/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbastard <mbastard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 22:55:12 by mbastard          #+#    #+#             */
/*   Updated: 2022/05/08 15:07:01 by mbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

test

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
}			t_cmd;

//	main.c

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
int		exec(t_data *data);

#endif
