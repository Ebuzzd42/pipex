/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:25:00 by egerin            #+#    #+#             */
/*   Updated: 2025/05/13 16:42:07 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *str, int n, t_struct *pipex)
{
	if (pipex)
		close_fd(pipex);
	write(2, str, ft_strlen(str));
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

void	execute(char *cmd, char **envp, char **av, t_struct *pipex)
{
	char	**tab_cmd;
	char	*path;

	if (!envp)
	{
		printf("salut");
	}
	if (!cmd || !*cmd || cmd[0] == ' ')
		error_exit("error command not found\n", 127, pipex);
	tab_cmd = ft_split(cmd, ' ');
	path = ft_find_path(tab_cmd[0], envp);
	close_fd(pipex);
	if (execve(path, tab_cmd, envp) == -1)
	{
		free_tab(tab_cmd);
		error_exit("error execve failed\n", 127, pipex);
	}
}

void	routine_child(char **av, char **envp, t_struct pipex)
{
	close(pipex.f2);
	close(pipex.pipefd[0]);
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close_fd(&pipex);
	if (!envp)
	{
		execve(av[2], av, envp);
		perror("execve failed\n");
		exit(127);
	}
	execute(av[2], envp, &pipex);
}

void	routine_parent(char **av, char **envp, t_struct pipex)
{
	close(pipex.f1);
	close(pipex.pipefd[1]);
	dup2(pipex.f2, STDOUT_FILENO);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close_fd(&pipex);
	if (!envp)
	{
		execve(av[3], av, envp);
		perror("execve failed\n");
		exit(127);
	}
	execute(av[3], envp, &pipex);
}

int	main(int ac, char **av, char **envp)
{
	static t_struct	pipex;
	int				status;
	int				status1;

	if (ac != 5)
		error_exit("error ./pipex infile cmd1 outfile cmd2\n", 1, &pipex);
	pipex.f1 = open(av[1], O_RDONLY);
	pipex.f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.f1 < 0 || pipex.f2 < 0)
		error_exit("error file or permission denied\n", 0, &pipex);
	if (pipe(pipex.pipefd) == -1)
		error_exit("error pipe\n", 1, &pipex);
	pipex.pid = fork();
	if (pipex.pid < 0)
		error_exit("error fork\n", 1, &pipex);
	else if (pipex.pid == 0)
		routine_child(av, envp, pipex);
	pipex.pid2 = fork();
	if (pipex.pid2 < 0)
		error_exit("error fork\n", 1, &pipex);
	else if (pipex.pid2 == 0)
		routine_parent(av, envp, pipex);
	close_fd(&pipex);
	waitpid(pipex.pid, &status, 0);
	waitpid(pipex.pid2, &status1, 0);
}
