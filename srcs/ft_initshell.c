/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:16 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 21:09:38 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include <unistd.h>
#include <sys/wait.h>

void	ft_initshell(char *name, t_shell *shell, char **envp)
{
	if (!shell)
		return ;
	shell->paths = ft_getpaths(envp);
	shell->ison = 1;
	shell->envp = envp;
	shell->name = name;
	while (*envp)
	{
		if (ft_strmatch(*envp, "USER=*"))
			shell->user = ft_strchr(*envp, '=') + 1;
		else if (ft_strmatch(*envp, "HOME=*"))
			shell->homepwd = ft_strchr(*envp, '=') + 1;
		else if (ft_strmatch(*envp, "PWD=*"))
			ft_strcpy(shell->pwd, ft_strchr(*envp, '=') + 1);
		++envp;
	}
}

void	ft_exec(char *filename, char **argv, char **envp)
{
	pid_t	pid;

	if (!(pid = fork()))
		execve(filename, argv, envp);
	else
		wait(NULL);
}
