/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:39:18 by tnave             #+#    #+#             */
/*   Updated: 2021/10/11 13:32:29 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	fd_exist(char **av, int ac, t_utils *utils)
{
	(void)ac;
	utils->fd_one = open(av[1], O_RDONLY);
	utils->fd_two = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU
		| S_IRGRP | S_IROTH);
	if (utils->fd_one < 0)
	{
		write(2, "bash: ", 6);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": No such file or directory\n", 28);
		utils->invalid_fd = 1;
		utils->fd_one = 0;
	}
}

void	opt_exec(int ac, char **av, char **environ, t_utils *utils)
{
	pid_t	pid;
	int		pfd[2];
	(void)ac;

	// Incorporer boucle pour pouvoir iterer sur open fd_two
	dup2(utils->fd_one, STDIN_FILENO);		// 0
	dup2(utils->fd_two, STDOUT_FILENO); 	// 1
	if (pipe(pfd) == -1)
		ft_error(0, strerror(errno) ,utils);
	pid = fork();
	if (ft_strncmp(av[1], "dev/urandom", 12) == 0)
		close(pfd[0]);
	if (pid > 0)
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		if (utils->fd_one == 0)
			exit(1);
		else
		{
			execve(utils->lst->path, utils->lst->cmd_opt, environ);
			exit(127);
		}
	}
	utils->lst = utils->lst->next;
	execve(utils->lst->path, utils->lst->cmd_opt, environ);
}

int	main(int ac, char **av, char **environ)
{
	t_utils		utils;

	ft_memset(&utils, 0, sizeof(t_utils));
	if (ac != 5)
		ft_error(0, "Missing arguments", &utils);
	if (!parse_env(environ, &utils))
		ft_error(0, "Path not found", &utils);
	fd_exist(av, ac, &utils);
	// while (ac >= 5)
	// {
	ft_check_access(ac, av, &utils);
	opt_exec(ac, av, environ, &utils);
	// }
	// ft_error(0, "Missing arguments", &utils);
}