/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:24:43 by egerin            #+#    #+#             */
/*   Updated: 2025/05/22 16:46:01 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_struct
{
	pid_t		pid;
	pid_t		pid2;
	int			pipefd[2];
	int			f1;
	int			f2;
}				t_struct;

typedef struct s_path
{
	char		*cmd_final;
	char		*pathjoin;
	char		**path;
	char		**tab_cmd;
	t_struct	*pipex;
}				t_path;

void			free_tab(char **tab);
char			*ft_find_path(char *cmd, char **envp);
void			error_exit(char *str, int n, t_struct *pipex);
void			close_fd(t_struct *pipex);
char			*ft_find_variable(char *str, char **envp);
int				path_missing(char **envp);
void			error_exit(char *str, int n, t_struct *pipex);
void			close_fd(t_struct *pipex);

#endif
