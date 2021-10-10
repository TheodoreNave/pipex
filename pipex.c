/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:39:18 by tnave             #+#    #+#             */
/*   Updated: 2021/10/10 18:56:03 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	fd_exist(char **av, int ac, t_utils *utils)
{
	utils->fd_one = open(av[1], O_RDONLY);
	utils->fd_two = open(av[ac], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU
		| S_IRGRP | S_IROTH);
	if (utils->fd_one < 0)
	{
		write(2, "bash: ", 6);
		write(2, av[1], ft_strlen(av[1]));
		write(2, ": No such file or directory\n", 28);
		utils->invalid_fd = 1;
	}
}

int main(int ac, char **av, char **environ)
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
	ft_check_access(&utils, ac, av);
	opt_exec(&utils, av, environ, ac);
	// }
	// ft_error(0, "Missing arguments", &utils);
}