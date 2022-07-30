/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gborne <gborne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 01:03:58 by hvincent          #+#    #+#             */
/*   Updated: 2022/07/30 20:19:25 by gborne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_env_cd(t_cmd *cmd)
{
	int		i;
	char	*tmp;
	char	**cpy;

	i = -1;
	tmp = NULL;
	cpy = cmd->data->envp;
	while (cpy[++i])
		if (ft_strncmp(cpy[i], "PWD=", 4) == 0)
			tmp = ft_strjoin_3(tmp, ft_strjoin2("OLD", cpy[i], 0, 0));
	i = -1;
	while (cpy[++i])
		if (ft_strncmp(cpy[i], "PWD=", 4) != 0
			&& ft_strncmp(cpy[i], "OLDPWD=", 7) != 0)
			tmp = ft_strjoin_2(tmp, cpy[i]);
	tmp = ft_strjoin_3(tmp, cd_pwd(1));
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
	DIR	*dir;

	if (cmd->arg[1][0] == '$')
		path = handle_cd_dollar(cmd);
	else
		path = ft_strdup(cmd->arg[1]);
	dir = opendir(path);
	if (dir != NULL)
	{
		chdir(path);
		handle_exp_cd(cmd);
		handle_env_cd(cmd);
		free(dir);
	}
	else if (!access(path, R_OK))
		printf("%s: Not a directory\n", path);
	else
		printf("%s: No such file or directory\n", path);
	if (path)
		free(path);
}

void	cd(t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->arg[1] == NULL || cmd->arg[1][0] == '~')
	{
		path = search_logname(cmd);
		path = ft_strjoin2("/Users/", path, 0, 1);
		chdir(path);
		free(path);
	}
	else
		cd_suite(cmd, path);
}
