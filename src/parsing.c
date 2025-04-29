/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 12:23:19 by egerin            #+#    #+#             */
/*   Updated: 2025/04/29 19:57:05 by egerin           ###   ########.fr       */
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

char	*ft_find_path(char *cmd, char **envp)
{
	int i;
	char *cmd_final;
	char *path2;
	char **path;
	char **tab_cmd;

	path = ft_split(ft_find_variable("PATH", envp), ':');
	tab_cmd = ft_split(cmd, ' ');
	i = 0;
	while (path[i])
	{
		path2 = ft_strjoin(path[i], "/");
		cmd_final = ft_strjoin(path2, tab_cmd[0]);
		free(path2);
		if (access(cmd_final, F_OK | X_OK) == 0)
		{
			free_tab(tab_cmd);
			return (cmd_final);
		}
		free(cmd_final);
		i++;
	}
	free_tab(path);
	free_tab(tab_cmd);
	return (cmd);
}