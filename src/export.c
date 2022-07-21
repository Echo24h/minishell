#include "../inc/minishell.h"

int	check_if_equal(const char *s)
{
	int	i;

	i = -1;
	if (*s)
	{
		while (s[++i])
			if (s[i] == '=')
				return (1);
	}
	return (0);
}

char	*ft_strdup_mini(const char *s1, int on)
{
	int				k;
	int				j;
	char			*s2;

	k = 0;
	j = 0;
	s2 = malloc(sizeof(char) * ft_strlen(s1) + 3);
	while (*s1)
	{
		if (on && *s1 == '=')
		{
			s2[k] = '=';
			s2[++k] = '"';
			j = 1;
		}
		else
			s2[k] = *s1;
		k++;
		s1++;
	}
	if (j)
		s2[k] = '"';
	s2[++k] = '\0';
	return (s2);
}





void	add_env_line(t_cmd *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = NULL;
	i = -1;
	while(cmd->data->envp[++i])
		printf("before:: env: %s\n", cmd->data->envp[i]);
	printf("\n");
	i = -1;
	while(cmd->data->envp[++i])
		tmp = ft_strjoin_2(tmp, cmd->data->envp[i]);
	tmp = ft_strjoin_2(tmp, cmd->arg[1]);
	// printf("tmp: %s|||\n", tmp);
	free_tab(cmd->data->envp);
	cmd->data->envp = ft_split(tmp, '\n');
	i = -1;
	while(cmd->data->envp[++i])
		printf("env: %s\n", cmd->data->envp[i]);
	
	
}

void	export(t_cmd *cmd)
{
	int 		i;

	if (cmd->arg[1] == NULL)
	{
			i = -1;
			while(cmd->data->envp[++i])
				printf("export: %s\n", cmd->data->export[i]);
	}
	else
	{	
		if (check_if_equal(cmd->arg[1]))
			add_env_line(cmd);
		// add_ex_line(cmd);
	}
}