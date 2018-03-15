/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 18:25:06 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/14 18:29:55 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"

t_shell	*g_shell;

void	ft_addhistory(char *line)
{
	t_list	*lst;

	if (g_shell->history && !ft_strcmp(line, g_shell->history->content))
		return ;
	lst = ft_lstnew(line, ft_strlen(line) + 1);
	if ((lst->next = ft_lstparent(g_shell->history)))
		lst->next->parent = lst;
	g_shell->history = lst;
}

char	*ft_gethistory(void)
{
	if (g_shell->history)
		return ((char *)g_shell->history->content);
	return (NULL);
}


