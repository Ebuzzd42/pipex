/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:25:00 by egerin            #+#    #+#             */
/*   Updated: 2025/05/22 16:45:10 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *cmd, char **envp, t_struct *pipex)
{
	char	**tab_cmd;
	char	*path;

	if (!envp || !*envp || path_missing(envp))
		envp = (char *[]){"PATH=/usr/bin:/bin", NULL};
	if (!cmd || !*cmd || cmd[0] == ' ')
		error_exit("error", 127, pipex);
	tab_cmd = ft_split(cmd, ' ');
	path = ft_find_path(tab_cmd[0], envp);
	if (execve(path, tab_cmd, envp) == -1)
	{
		free_tab(tab_cmd);
		perror("pipex");
		if (errno == ENOENT)
			exit(127);
		else if (errno == EACCES)
			exit(126);
		else
			exit(1);
	}
}

void	routine_child(char **av, char **envp, t_struct pipex)
{
	if (pipex.f1 < 0)
		pipex.f1 = open("/dev/null", O_RDONLY);
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.f1);
	close(pipex.pipefd[1]);
	close(pipex.f2);
	close(pipex.pipefd[0]);
	execute(av[2], envp, &pipex);
}

void	routine_parent(char **av, char **envp, t_struct pipex)
{
	dup2(pipex.f2, STDOUT_FILENO);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.f2);
	close(pipex.pipefd[0]);
	close(pipex.f1);
	close(pipex.pipefd[1]);
	execute(av[3], envp, &pipex);
}

void	open_files(char **av, t_struct *pipex)
{
	pipex->f1 = open(av[1], O_RDONLY);
	if (pipex->f1 < 0)
		perror(av[1]);
	pipex->f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->f2 < 0)
	{
		perror(av[4]);
		exit(1);
	}
}

int	main(int ac, char **av, char **envp)
{
	static t_struct	pipex;

	if (ac != 5)
		error_exit("error ./pipex infile cmd1 outfile cmd2\n", 1, &pipex);
	open_files(av, &pipex);
	if (pipe(pipex.pipefd) == -1)
		error_exit("error", 1, &pipex);
	pipex.pid = fork();
	if (pipex.pid < 0)
		error_exit("error", 1, &pipex);
	else if (pipex.pid == 0)
		routine_child(av, envp, pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error_exit("error", 1, &pipex);
	else if (pipex.pid2 == 0)
		routine_parent(av, envp, pipex);
	close_fd(&pipex);
	while (wait(NULL) > 0)
		;
}
