#include "../inc/minishell.h"

// init export et env
static void	export_init(t_data *data, char **envp)
{
	int		i;

	i = -1;
	while(envp[++i])
		;
	data->export = malloc(sizeof(char *) * i + 1);
	data->envp = malloc(sizeof(char *) * i + 1);
	i = -1;
	while(envp[++i])
	{
		data->export[i] = ft_strjoin2("declare -x ", envp[i], 0, 0);
		data->envp[i] = ft_strjoin2("", envp[i], 0, 0);
	}
}

void	init(t_data *data, char **envp)
{
    export_init(data, envp);
}