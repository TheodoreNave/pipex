/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 18:56:34 by tnave             #+#    #+#             */
/*   Updated: 2021/10/11 13:31:11 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

int	parse_env(char **env, t_utils *utils)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			utils->parse_env = ft_split(is_slash(env[i]), ':');
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_check_access(int ac, char **av, t_utils *utils)
{
	int i;
	int j;

	i = 0;
	j = 2;
	while (j < ac - 1)
	{
		ft_check_access_two(av, i, j, utils);
		utils->cmd_ok = 0;
		utils->wrong_cmd = 0;
		j++;
	}
}

void	ft_check_access_two(char **av, int i, int j, t_utils *utils)
{
	while (utils->parse_env && utils->parse_env[i] && !utils->cmd_ok)
	{
		utils->temp = ft_split(av[j], ' ');
		utils->join = ft_strjoin_three(utils->parse_env[i], "/", utils->temp[0]);
		if (access(utils->join, F_OK) == 0)
		{
			ft_lstadd_back(&utils->lst, ft_lstnew(utils->temp,
				ft_strdup(utils->join)));
			utils->cmd_ok = 1;
			utils->p++;
		}
		else
		{
			if (utils->wrong_cmd == 0)
			{
				utils->error_msg = ft_strdup(utils->temp[0]);
				utils->wrong_cmd = 1;
			}
			free_split(utils->temp);
			utils->temp = NULL;
		}
		free(utils->join);
		i++;
	}
	if (!utils->cmd_ok)
	{
		utils->temp =ft_split(av[j], ' ');
		ft_lstadd_back(&utils->lst, ft_lstnew(utils->temp, NULL));
		if (j > 2)
			utils->invalid_fd = 0;
		if (!utils->invalid_fd)
		{
			write(2, "bash: ", 6);
			write(2, utils->error_msg, ft_strlen(utils->error_msg));
			write(2, ": Command not found\n", 20);
			free(utils->error_msg);
		}
		else
			free(utils->error_msg);
	}
	else
		free(utils->error_msg);
}