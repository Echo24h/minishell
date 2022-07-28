#include "../inc/minishell.h"

int    srch_line(char *haystack, char *needle)
{
    if (ft_strnstr(haystack, ft_substr(needle, 1,
                ft_strlen(needle) - 1), ft_strlen(haystack) + 1))
        return (1);
    else
        return (0);
}

void    suite_init(t_data *data, char **envp, int i)
{
    data->export[i] = ft_strjoin2("declare -x ",
            insert_quotes_exp(envp[i], NULL), 0, 0);
    data->envp[i] = ft_strjoin2("", envp[i], 0, 0);
}

static void    export_init(t_data *data, char **envp)
{
    int        i;

    i = -1;
    while (envp[++i])
        ;
    data->export = malloc(sizeof(char *) * (i + 3));
    data->envp = malloc(sizeof(char *) * (i + 2));
    i = -1;
    while (envp[++i])
    {
        if (ft_strncmp(envp[i], "OLDPWD=", 7) != 0)
            suite_init(data, envp, i);
    }
	data->envp[i] = NULL;
	data->export[i++] = ft_strjoin2("declare -x OLDPWD", NULL, 0, 0);
	data->export[i] = NULL;
}

void	init(t_data *data, char **envp)
{
    export_init(data, envp);
	data->pipeline_status = ft_itoa(0);
}
