/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:39:18 by tnave             #+#    #+#             */
/*   Updated: 2021/10/11 17:59:57 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	fd_exist(char **av, int ac, t_utils *utils)
{
	(void)ac;
	utils->fd_one = open(av[1], O_RDONLY);
	utils->fd_two = open(av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU
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

void	opt_exec(char **av, char **environ, t_utils *utils, t_utils_list *tmp)
{
	(void)av;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_error(0, strerror(errno), utils);
	// if (ft_strncmp(av[1], "dev/urandom", 12) == 0)
	// 	close(tmp->pfd[0]);
	if (pid == 0)
	{
		if (!tmp->prev)
			dup2(utils->fd_one, STDIN);
		else
			dup2(tmp->prev->pfd[STDIN], STDIN);
		if (tmp->next)
			dup2(tmp->pfd[STDOUT], STDOUT);
		else
			dup2(utils->fd_two, STDOUT);
		execve(tmp->path, tmp->cmd_opt, environ);
		exit(127);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (tmp->prev)
			close(tmp->prev->pfd[0]);
		close(tmp->pfd[1]);
		if (!tmp->next)
			exit(0);
	}
}

int	main(int ac, char **av, char **environ)
{
	t_utils		utils;
	t_utils_list *tmp;

	ft_memset(&utils, 0, sizeof(t_utils));
	if (ac >= 5)
	{	// ft_error(0, "Missing arguments", &utils);
		if (!parse_env(environ, &utils))
			ft_error(0, "Path not found", &utils);
		fd_exist(av, ac, &utils);
		ft_check_access(ac, av, &utils);
		tmp = utils.lst;
		while (tmp)
		{
			if (tmp->next)
				if (pipe(tmp->pfd) == -1)
					ft_error(0, strerror(errno), &utils);
			opt_exec(av, environ, &utils, tmp);
			tmp = tmp->next;
		}
	}
	ft_error(0, "Missing arguments", &utils);
}