/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:16 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/09 13:18:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include <unistd.h>
#include <sys/wait.h>
#include "ft_printf.h"

void	ft_initshell(char *name, t_shell *shell, char **envp)
{
	int	i;

	if (!shell)
		return ;
	shell->paths = ft_getpaths(envp);
	shell->ison = 1;
	shell->envp = (char **)malloc(sizeof(char *) *
			(ft_tabsize((const char **)envp) + 1));
	shell->name = name;
	i = 0;
	while (*envp)
	{
		if (ft_strmatch(*envp, "USER=*"))
			shell->user = ft_strchr(*envp, '=') + 1;
		else if (ft_strmatch(*envp, "HOME=*"))
			shell->homepwd = ft_strchr(*envp, '=') + 1;
		else if (ft_strmatch(*envp, "PWD=*"))
			ft_strcpy(shell->pwd, ft_strchr(*envp, '=') + 1);
		if (shell->envp)
			shell->envp[i++] = ft_strdup(*envp);
		++envp;
	}
	if (shell->envp)
		shell->envp[i] = NULL;
}

void	ft_delshell(t_shell *shell)
{
	char	**ptr;

	if ((ptr = shell->paths))
	{
		while (*ptr)
			free(*ptr++);
		free(*ptr);
	}
	free(shell->paths);
	if ((ptr = shell->envp))
	{
		while (*ptr)
			free(*ptr++);
		free(*ptr);
	}
	free(shell->envp);
	ft_bzero(shell, sizeof(t_shell));
}

void	ft_exec(char *filename, char **argv, char **envp)
{
	pid_t	pid;

	if (!(pid = fork()))
		execve(filename, argv, envp);
	else
		wait(NULL);
}
