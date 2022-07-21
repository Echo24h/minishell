/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:18:55 by gborne            #+#    #+#             */
/*   Updated: 2022/07/21 05:53:35 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  is_exist(t_data *data, const char *var)
{
    int len;
    int i;

    len = ft_strlen(var);
    i = -1;
    while(data->envp[++i])
        if (ft_strncmp(data->envp[i], var, len) == 0)
            return (1);
    i = -1;
    while(data->export[++i])
        if (ft_strncmp(data->export[i], var, len) == 0)
            return (2);
    return (0);
}

static char    *replace_var_env(t_data *data, char *line)
{
    int     i;
    int     start;
    char    *var;
    char    *new;

    i = -1;
    while (line[++i])
    {
        if (line[i] == '$')
        {
            start = i + 1;
            while (ft_isalnum(line[++i]))
                ;
            var = ft_substr(line, start, i - start);
            var = ft_strjoin(var, "=");
            if (is_exist(data, var))
                printf("var=%s is exist !\n", var);
        }
    }
    new = ft_strdup(line);
    free(line);
    return (new);
}

char    *lexique(t_data *data, const char *cmd_line)
{
    char *line;
    
    line = ft_strdup(cmd_line);
    line = replace_var_env(data, line);
    return (line);
}