/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:23:19 by egerin            #+#    #+#             */
/*   Updated: 2025/05/13 14:19:41 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	*ft_find_variable(char *str, char **envp)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		tmp = ft_substr(envp[i], 0, j);
		if (ft_strcmp(tmp, str) == 0)
		{
			free(tmp);
			return (envp[i] + j + 1);
		}
		free(tmp);
		i++;
	}
	return (NULL);
}

void	split_commands(t_path *x, char *cmd, char **envp)
{
	if (!cmd || !*cmd || cmd[0] == ' ')
		error_exit("error command not found\n", 127, x->pipex);
	x->path = ft_split(ft_find_variable("PATH", envp), ':');
	x->tab_cmd = ft_split(cmd, ' ');
	if (!x->path || !x->tab_cmd)
	{
		if (x->path)
			free_tab(x->path);
		if (x->tab_cmd)
			free_tab(x->tab_cmd);
		error_exit("error command not found\n", 127, x->pipex);
	}
}

char	*ft_find_path(char *cmd, char **envp)
{
	t_path	x;
	int		i;

	split_commands(&x, cmd, envp);
	i = 0;
	while (x.path[i])
	{
		x.pathjoin = ft_strjoin(x.path[i], "/");
		x.cmd_final = ft_strjoin(x.pathjoin, x.tab_cmd[0]);
		free(x.pathjoin);
		if (access(x.cmd_final, F_OK | X_OK) == 0)
		{
			free_tab(x.tab_cmd);
			free_tab(x.path);
			return (x.cmd_final);
		}
		free(x.cmd_final);
		i++;
	}
	free_tab(x.tab_cmd);
	free_tab(x.path);
	return (cmd);
}
