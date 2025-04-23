/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:25:00 by egerin            #+#    #+#             */
/*   Updated: 2025/04/23 16:15:06 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_freesplit(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	routine_child(char **av, char **envp, t_struct pipex)
{
	char	*cmd;
	char	**args;

	close(pipex.pipefd[0]);
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	args = ft_split(av[2], ' ');
	cmd = ft_strdup(args[0]);
	free(args[0]);
	args[0][0] = ' ';
	args[0][1] = '\0';
	execve(cmd, args, envp);
	// ft_freesplit(args);
	// free(cmd);
}

void	routine_parent(char **av, char **envp, t_struct pipex)
{
	char	*cmd;
	char	**args;

	close(pipex.pipefd[1]);
	dup2(pipex.f2, STDOUT_FILENO);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	args = ft_split(av[3], ' ');
	cmd = ft_strdup(args[0]);
	free(args[0]);
	args[0][0] = ' ';
	args[0][1] = '\0';
	execve(cmd, args, envp);
	// ft_freesplit(args);
	// free(cmd);
}

int	main(int ac, char **av, char **envp)
{
	t_struct	pipex;

	if (ac != 5)
		return (1);
	pipex.f1 = open(av[1], O_RDONLY);
	pipex.f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.f1 < 0 || pipex.f2 < 0)
		return (-1);
	if (pipe(pipex.pipefd) == -1)
		return (ft_printf("Error\n"), 1);
	pipex.pid = fork();
	if (pipex.pid == -1)
		return (ft_printf("Error\n"), 1);
	else if (pipex.pid == 0)
		routine_child(av, envp, pipex);
	else
		routine_parent(av, envp, pipex);
}
