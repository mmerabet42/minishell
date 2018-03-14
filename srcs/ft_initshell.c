/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:16 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/14 18:24:58 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <unistd.h>
#include <sys/wait.h>

t_shell		*g_shell;

char		*ft_getcwd(char *pwd, size_t size)
{
	ft_bzero(pwd, size);
	return (getcwd(pwd, size));
}

static void	sign_handler(int sign)
{
	(void)sign;
}

void		ft_initshell(char *name, t_shell *shell, char **envp)
{
	int	i;

	if (!shell)
		return ;
	shell->paths = ft_getpaths(envp);
	shell->running = 1;
	shell->envp = (char **)malloc(sizeof(char *) * (ft_tabsize(envp) + 1));
	shell->name = name;
	i = 0;
	while (*envp)
	{
		if (ft_strmatch(*envp, "USER=*"))
			shell->user = ft_strchr(*envp, '=') + 1;
		else if (ft_strmatch(*envp, "HOME=*"))
			shell->homepwd = ft_strchr(*envp, '=') + 1;
		if (shell->envp)
			shell->envp[i++] = ft_strdup(*envp);
		++envp;
	}
	if (shell->envp)
		shell->envp[i] = NULL;
	ft_getcwd(shell->pwd, 2048);
	if (signal(SIGINT, sign_handler) == SIG_ERR)
		ft_exit(EXIT_FAILURE, "Failed to catch 'SIGINT' signal. Exiting.");
	g_shell = shell;
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
