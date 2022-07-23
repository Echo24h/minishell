/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexique.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:18:55 by gborne            #+#    #+#             */
/*   Updated: 2022/07/23 09:13:53 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  id_var(t_data *data, const char *var)
{
    int len;
    int i;
    char    *export_var;

    export_var = ft_strdup("declare -x ");
    export_var = ft_strjoin(export_var, var);
    len = ft_strlen(export_var);
    i = -1;
    while(data->export[++i])
        if (ft_strncmp(data->export[i], export_var, len) == 0)
            return (i);
    return (-1);
}

static char *add_part(char *dst, const char *src, int start, int end)
{
    char    *new;
	new = (char *)ft_calloc(ft_strlen(dst) + (end - start) + 1, sizeof(char));
    if (new == NULL)
        return (NULL);
    ft_strlcpy(new, dst, ft_strlen(dst) + 1);
	ft_strlcat(new, src + start, ft_strlen(new) + end - start + 1);
    if (dst)
	    free(dst);
    return (new);
}

static char *add_var(t_data *data, char *dst, int id_var)
{
    int     i;
    int     start;

    i = 0;
    start = 0;
    while (data->export[id_var][i] && data->export[id_var][i] != '=')
       i++;
    if (data->export[id_var][i] == '=')
    {
        start = i + 1;
        while (data->export[id_var][i])
            i++;
        if (i != start)
            dst = add_part(dst, data->export[id_var], start, ft_strlen(data->export[id_var]));
    }
    return (dst);
}

static char    *replace_var_env(t_data *data, char *line)
{
    int     i;
    int     i_add;
    int     start;
    char    *var;
    char    *new;

    i = -1;
    i_add = 0;
    new = ft_calloc(1, sizeof(char));
    while (line[++i])
    {
        if (line[i] == '$' && ft_isalnum(line[i + 1]))
        {
            if (i > 0)
                new = add_part(new, line, i_add, i);
            start = i + 1;
            while (ft_isalnum(line[++i]))
                ;
            var = ft_substr(line, start, i - start);
            var = ft_strjoin(var, "=");
            if (id_var(data, var) != -1)
                new = add_var(data, new, id_var(data, var));
            i_add = i;
        }
    }
    if (i != i_add)
        new = ft_strjoin(new, line + i_add);
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