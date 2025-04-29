/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egerin <egerin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:24:43 by egerin            #+#    #+#             */
/*   Updated: 2025/04/29 19:31:37 by egerin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_struct
{
	pid_t	pid;
	int		pipefd[2];
	int		f1;
	int		f2;
}			t_struct;

void		free_tab(char **tab);
char		*ft_find_path(char *cmd, char **envp);

#endif
