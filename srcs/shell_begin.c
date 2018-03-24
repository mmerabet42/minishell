/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initshell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:09:16 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/22 14:20:08 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <unistd.h>
#include <sys/signal.h>
#include <locale.h>

extern t_shell	*g_shell;

static void	sign_handler(int sign)
{
	(void)sign;
}

static void	initenvp(char **envp)
{
	int	i;

	if (!(g_shell->envp =
				(char **)malloc(sizeof(char *) * (ft_tabsize(envp) + 1))))
		ft_exit(EXIT_FAILURE, "Failed to copy 'envp'. Exiting");
	i = 0;
	while (*envp)
	{
		if (ft_strmatch(*envp, "USER=*"))
			g_shell->user = ft_strchr(*envp, '=') + 1;
		else if (ft_strmatch(*envp, "HOME=*"))
			g_shell->homepwd = ft_strchr(*envp, '=') + 1;
		if (!(g_shell->envp[i++] = ft_strdup(*envp)))
			ft_exit(EXIT_FAILURE, "Failed to copy 'envp'. Exiting");
		++envp;
	}
	g_shell->envp[i] = NULL;
}

void		shell_begin(char *name, int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (signal(SIGINT, sign_handler) == SIG_ERR)
		ft_exit(EXIT_FAILURE, "Failed to catch 'SIGINT' signal. Exiting.");
	if (!(g_shell = (t_shell *)ft_memalloc(sizeof(t_shell))))
		ft_exit(EXIT_FAILURE, "Failed to begin shell. Exiting");
	if (!(g_shell->paths = ft_getpaths(envp)))
		return ;
	setlocale(LC_ALL, "");
	g_shell->name = name;
	g_shell->running = 1;
	g_shell->ihis = -1;
	ft_getcwd(g_shell->pwd, 2048);
	initenvp(envp);
}

static void	delhistory(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}

void		shell_end(void)
{
	char	**ptr;

	if ((ptr = g_shell->paths))
		while (*ptr)
			free(*ptr++);
	free(g_shell->paths);
	if ((ptr = g_shell->envp))
		while (*ptr)
			free(*ptr++);
	free(g_shell->envp);
	free(g_shell->cline);
	ft_lstdel(&g_shell->history, delhistory);
	free(g_shell);
	g_shell = NULL;
}
