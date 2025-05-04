/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:25:00 by egerin            #+#    #+#             */
/*   Updated: 2025/05/04 16:38:24 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *str, int n)
{
	write(2, str, ft_strlen(str));
	exit(n);
}

void	execute(char *cmd, char **envp)
{
	char	**tab_cmd;
	char	*path;

	if (!cmd || !*cmd || cmd[0] == ' ')
		error_exit("error command not found\n", 127);
	tab_cmd = ft_split(cmd, ' ');
	path = ft_find_path(tab_cmd[0], envp);
	if (execve(path, tab_cmd, envp) == -1)
	{
		free_tab(tab_cmd);
		write(2, "error execve\n", 13);
		exit(127);
	}
}

void	routine_child(char **av, char **envp, t_struct pipex)
{
	dup2(pipex.f1, STDIN_FILENO);
	dup2(pipex.pipefd[1], STDOUT_FILENO);
	close(pipex.f1);
	close(pipex.f2);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	execute(av[2], envp);
}

void	routine_parent(char **av, char **envp, t_struct pipex)
{
	dup2(pipex.f2, STDOUT_FILENO);
	dup2(pipex.pipefd[0], STDIN_FILENO);
	close(pipex.f1);
	close(pipex.f2);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
	execute(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	static t_struct	pipex;
	int				status;

	if (ac != 5)
		error_exit("error ./pipex infile cmd1 outfile cmd2\n", 1);
	pipex.f1 = open(av[1], O_RDONLY);
	pipex.f2 = open(av[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex.f1 < 0 || pipex.f2 < 0)
		error_exit("error file or permission denied\n", 0);
	if (pipe(pipex.pipefd) == -1)
		error_exit("error pipe\n", 1);
	pipex.pid = fork();
	if (pipex.pid == -1)
		error_exit("Error\n", 1);
	else if (pipex.pid == 0)
		routine_child(av, envp, pipex);
	else
	{
		waitpid(pipex.pid, &status, 0);
		routine_parent(av, envp, pipex);
	}
	close(pipex.f1);
	close(pipex.f2);
	close(pipex.pipefd[0]);
	close(pipex.pipefd[1]);
}
