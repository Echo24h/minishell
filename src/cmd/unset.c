#include "../../inc/minishell.h"

int	unset(t_cmd *cmd)
{
    int        i;
    char    *tmp;

    i = -1;
    tmp = NULL;
	while(cmd->arg[1][++i])
		if (ft_isalnum(cmd->arg[1][i]) != 1)
			return printf("unset: \"%s\": not a valid identifier\n", cmd->arg[1]);
	i = -1;
	while (cmd->data->envp[++i])
		if (!srch_line(cmd->data->envp[i], cmd->arg[1]))
				tmp = ft_strjoin_2(tmp, cmd->data->envp[i]);
	free_tab(cmd->data->envp);
	cmd->data->envp = ft_split(tmp, '\n');
	cmd->cmd = "env";
	env(cmd);
	if (tmp != NULL)
		free(tmp);
	return (0);
}
