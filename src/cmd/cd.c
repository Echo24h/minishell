/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 04:08:10 by gborne            #+#    #+#             */
/*   Updated: 2022/07/28 03:32:05 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvincent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:03:58 by hvincent          #+#    #+#             */
/*   Updated: 2022/07/23 01:03:59 by hvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void    handle_env_cd(t_cmd *cmd)
{
    int        i;
    char    *tmp;
    char    **cpy;

    i = -1;
	//cmd->data->envp;
    tmp = NULL;
	cpy = cmd->data->envp;
	while (cpy[++i])
		if (ft_strncmp(cpy[i], "PWD=", 4) == 0)
			tmp = ft_strjoin_2(tmp, ft_strjoin_2("OLD", cpy[i]));
    i = -1;
	while (cpy[++i])
		if (ft_strncmp(cpy[i], "PWD=", 4) != 0 && ft_strncmp(cpy[i], "OLDPWD=", 7) != 0)
			tmp = ft_strjoin_2(tmp, cpy[i]);
    tmp = ft_strjoin_2(tmp, cd_pwd(1));
    free_tab(cmd->data->envp);
    cmd->data->envp = ft_split(tmp, '\n');
    free(tmp);
}

char	*search_logname(t_cmd *cmd)
{
	int		i;
	char	**z;

	i = -1;
	z = cmd->data->envp;
	while (z[++i])
		if (ft_strnstr(z[i], "LOGNAME",
				ft_strlen(z[i])))
			return (ft_substr(z[i], ft_sublen(z[i], '=') + 1,
					ft_strlen(z[i]) - ft_sublen(z[i], '=') - 1));
	return (NULL);
}

char	*handle_cd_dollar(t_cmd *cmd)
{
	int		i;
	char	**z;

	i = -1;
	z = cmd->data->envp;
	while (z[++i])
		if (ft_strnstr(z[i], ft_substr(cmd->arg[1], 1,
					ft_strlen(cmd->arg[1]) - 1), ft_strlen(z[i]) + 1))
			return (ft_substr(z[i], ft_sublen(z[i], '=') + 1,
					ft_strlen(z[i]) - ft_sublen(z[i], '=') - 1));
	return (NULL);
}

void	cd_suite(t_cmd *cmd, char *path)
{
	if (cmd->arg[1][0] == '$')
		path = handle_cd_dollar(cmd);
	else
		path = ft_strdup(cmd->arg[1]);
	if (opendir(path) != NULL)
	{
		chdir(path);
		handle_exp_cd(cmd);
		handle_env_cd(cmd);
	}
	else if (!access(path, R_OK))
		printf("%s: Not a directory\n", path);
	else
		printf("%s: No such file or directory\n", path);
}

void	cd(t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->arg[1] == NULL || cmd->arg[1][0] == '~')
	{
		path = search_logname(cmd);
		path = ft_strjoin2("/Users/", path, 0, 0);
		chdir(path);
	}
	else
		cd_suite(cmd, path);
	free(path);
}
