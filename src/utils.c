/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:43:49 by egerin            #+#    #+#             */
/*   Updated: 2025/05/22 16:45:39 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	path_missing(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i][5] == '\0');
		i++;
	}
	return (1);
}

void	error_exit(char *str, int n, t_struct *pipex)
{
	if (pipex)
		close_fd(pipex);
	perror(str);
	exit(n);
}

void	close_fd(t_struct *pipex)
{
	if (pipex->f1 >= 0)
		close(pipex->f1);
	if (pipex->f2 >= 0)
		close(pipex->f2);
	if (pipex->pipefd[0] >= 0)
		close(pipex->pipefd[0]);
	if (pipex->pipefd[1] >= 0)
		close(pipex->pipefd[1]);
}
