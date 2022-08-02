/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 05:02:28 by gborne            #+#    #+#             */
/*   Updated: 2022/08/02 02:47:42 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_status(const char *arg)
{
	int	neg;
	int	i;

	neg = 0;
	i = 0;
	while (arg[i])
	{
		while (arg[i] == ' ' || arg[i] == '\t')
			i++;
		if (i == 0 && arg[i] == '-')
		{
			neg++;
			i++;
		}
		else if (i == 0 && arg[i] == '+')
			i++;
		else if (ft_isdigit(arg[i]) == 0)
			return (-1);
		i++;
	}
	if (neg)
		return (256 - (ft_atoi(&arg[1]) % 256));
	return (ft_atoi(arg) % 256);
}

static int	exit_error(int status, char *error)
{
	edit_signal(status);
	if (status == 255)
		printf("Error : %s: numeric argument required\n", error);
	else
		printf("%s\n", error);
	return (1);
}

void	ft_exit(t_cmd *cmd)
{
	int	status;
	int	error;

	status = 0;
	error = 0;
	write(1, "exit\n", 6);
	if (cmd && cmd->arg && cmd->arg[0])
	{
		if (ft_tablen(cmd->arg) > 2)
			error += exit_error(1, "Error : too many arguments");
		else if (cmd->arg[1])
		{
			status = get_status(cmd->arg[1]);
			if (status == -1)
				error += exit_error(255, cmd->arg[1]);
		}
	}
	if (error == 0)
		exit(status);
}
