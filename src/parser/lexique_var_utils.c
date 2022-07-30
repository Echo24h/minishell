/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique_var_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 15:49:57 by gborne            #+#    #+#             */
/*   Updated: 2022/07/30 15:52:36 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	id_var(t_data *data, const char *var)
{
	int		len;
	int		i;
	char	*export_var;

	export_var = ft_strdup("declare -x ");
	export_var = ft_strjoin(export_var, var);
	len = ft_strlen(export_var);
	i = -1;
	while (data->export[++i])
	{
		if (ft_strncmp(data->export[i], export_var, len) == 0)
		{
			free(export_var);
			return (i);
		}
	}
	free(export_var);
	return (-1);
}
