/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlinecmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 20:27:14 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/01 20:54:40 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ft_str.h"

char	*ft_getcmdf(char *cmd, t_cmdf *cmdf)
{
	if (!cmd || !cmdf)
		return (NULL);
	while (*cmd == ' ')
		++cmd;
	cmdf->cmd = cmd;
	if (!(cmdf->name = ft_strbefore(cmd, ' ')))
		cmdf->name = cmdf->name;
	if ((cmd = ft_strchr(cmd, ' ')))
	{
		while (*++cmd)
		{
			if (*cmd == '"')
		}
	}
	return (cmd);
}

void	ft_cmdfdel(t_cmdf *cmdf)
{
	char	*ptr;

	if (!cmdf)
		return ;
	ptr = cmdf->argv;
	while (*ptr)
		free(*ptr++);
	free(cmdf->argv);
	free(cmdf->name);
	if (cmdf->name != cmdf->cmd)
		free(cmdf->cmd);
	cmdf->name = NULL;
	cmdf->argv = NULL;
	cmdf->cmd = NULL;
}
