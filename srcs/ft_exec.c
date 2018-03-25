/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 17:21:45 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/25 19:17:39 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <sys/wait.h>

t_shell	*g_shell;

int		ft_exec(char *filename, char **argv, char **envp)
{
	pid_t	pidl;
	int		ret;

	ret = -1;
	if (!(pidl = fork()))
	{
		execve(filename, argv, envp);
		exit(-1);
	}
	else if (pidl)
	{
		g_shell->curpid = pidl;
		wait(&ret);
	}
	return (ret == 65280 ? -1 : ret);
}

void	ft_exit(int code, const char *msg)
{
	if (msg)
		ft_putstr(msg);
	exit(code);
}

void	ft_exitf(int code, const char *msgf, ...)
{
	va_list	vp;

	if (msgf)
	{
		va_start(vp, msgf);
		ft_vprintf(msgf, vp);
		va_end(vp);
	}
	exit(code);
}

char	*ft_getcwd(char *pwd, size_t size)
{
	ft_bzero(pwd, size);
	return (getcwd(pwd, size));
}
