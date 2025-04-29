/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:25:00 by egerin            #+#    #+#             */
/*   Updated: 2025/04/29 22:04:21 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void	execute(char *cmd, char **envp)
{
	char	**tab_cmd;
	char	*path;

	tab_cmd = ft_split(cmd, ' ');
	path = ft_find_path(tab_cmd[0], envp);
	if (execve(path, tab_cmd, envp) == -1)
	{
		free_tab(tab_cmd);
		ft_printf("error\ncommande not found\n");
		exit(0);
	}
}

void	routine_child(char **av, char **envp, t_struct pipex)
{
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.pipefd[0]);
	execute(av[2], envp);
}

void	routine_parent(char **av, char **envp, t_struct pipex)
{
	dup2(pipex.f2, STDOUT_FILENO);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.pipefd[1]);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	static t_struct	pipex;

	if (ac != 5)
		error_exit("error\n./pipex infile cmd1 outfile cmd2\n");
	pipex.f1 = open(av[1], O_RDONLY);
	pipex.f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.f1 < 0 || pipex.f2 < 0)
		error_exit("error file\n");
	if (pipe(pipex.pipefd) == -1)
		error_exit("Error\n");
	pipex.pid = fork();
	if (pipex.pid == -1)
		error_exit("Error\n");
	else if (pipex.pid == 0)
		routine_child(av, envp, pipex);
	else
		routine_parent(av, envp, pipex);
}
