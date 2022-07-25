/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 14:17:07 by gborne            #+#    #+#             */
/*   Updated: 2022/07/25 14:52:00 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**lexique_pipe(const char *input)
{

	char	**cmd_tab;
	//int		i;

	cmd_tab = ft_split(input, '|');
	return (cmd_tab);
}
