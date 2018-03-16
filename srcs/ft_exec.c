/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:21:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/15 21:44:31 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include <sys/wait.h>

void	ft_exec(char *filename, char **argv, char **envp)
{
	pid_t	pidl;

	if (!(pidl = fork()))
	{
		execve(filename, argv, envp);
		exit(0);
	}
	else
		wait(NULL);
}

void	ft_exit(int code, const char *msg)
{
	if (msg)
		ft_putstr(msg);
	exit(code);
}

char	*ft_getcwd(char *pwd, size_t size)
{
	ft_bzero(pwd, size);
	return (getcwd(pwd, size));
}
