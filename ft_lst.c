/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnave <tnave@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 11:38:46 by tnave             #+#    #+#             */
/*   Updated: 2021/10/11 11:38:46 by tnave            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/pipex.h"

void	ft_lstadd_back(t_utils_list **alst, t_utils_list *new)
{
	t_utils_list	*end_list;

	if (!alst || !new)
		return ;
	if (*alst)
	{
		end_list = *alst;
		while (end_list->next != NULL)
			end_list = end_list->next;
		end_list->next = new;
	}
	else
		*alst = new;
}

void	ft_lstclear(t_utils_list **lst, void (*del)(void *))
{
	t_utils_list	*end_list;
	t_utils_list	*end_list_two;

	if (!lst || !del)
		return ;
	end_list = *lst;
	while (end_list != NULL)
	{
		end_list_two = end_list->next;
		if (end_list->cmd_opt)
		{
			free_split(end_list->cmd_opt);
			end_list->cmd_opt = NULL;
		}
		ft_free(&end_list->path);
		free(end_list);
		end_list = end_list_two;
	}
	lst = NULL;
}

t_utils_list	*ft_lstnew(char **cmd_opt, char *path)
{
	t_utils_list	*new_list;

	new_list = malloc(sizeof(t_utils_list));
	if (!(new_list))
		return (NULL);
	new_list->cmd_opt = cmd_opt;
	new_list->path = path;
	new_list->next = NULL;
	return (new_list);
}
