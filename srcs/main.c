/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/19 18:27:04 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include "ft_types.h"
#include <unistd.h>
#include <locale.h>

t_shell *g_shell;

static void ft_readline(char *line)
{
	char	fullpath[1024];
	t_args	args;
	t_shret	shret;
	
	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_getargs(line, &args)))
	{
		if (*line != '\0')
			++line;
		if (args.argc >= 1
				&& ft_isbuiltin(args.argv[0], &args) == SH_NFOUND)
		{
			shret = ft_getfullpath(args.argv[0], fullpath, 1024);
			if (shret != SH_OK)
				ft_printf("%s: %s: %s\n", g_shell->name, ft_strshret(shret),
					args.argv[0]);
			else
				ft_exec(fullpath, args.argv, g_shell->envp);
		}
		ft_delargs(&args);
	}
}

#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int	main(int argc, char **argv, char **envp)
{
/*	pid_t	pid;
	int		fd[2];
	char	**ptr = argv++;
	int		i = 0;

	while (*ptr)
	{
		if (ft_strequ(*ptr, "|"))
		{
			++ptr;
			argv[i - 1] = NULL;
			break;
		}
		++i;
		++ptr;
	}
	if (pipe(fd) == -1)
		ft_exit(0, "Failed pipe operation\n");
	if (!(pid = fork()))
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execvp(*argv, argv);
		exit(0);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		if (!(pid = fork()))
		{
			dup2(fd[0], 0);
			execvp(*ptr, ptr);
			exit(0);
		}
		else
			wait(NULL);
		close(fd[0]);
	}
	return (0);*/
	char	line[2048];
	int		c;
	int		x;

	(void)argc;
	(void)argv;
	shell_begin("minishell", envp);
	setlocale(LC_ALL, "");
	ft_bzero(line, 2048);
	while (g_shell->running)
	{
		ft_getcursor(&x, NULL);
		if (x > 1)
			ft_printf("%#{lgrey}%{bold/;0;0;0}%%%{0}\n");
		ft_printf("%S %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ", L"㋜", g_shell->user, g_shell->pwd, L"∴");
		ft_strclr(line);
		if ((c = ft_readraw(line, 2048)) != 3 && c != 4 && line[0] != '\0')
		{
			ft_addhistory(line);
			ft_readline(line);
		}
		else if (c == 4)
			ft_readline("exit");
	}
	ft_makeraw(0);
	shell_end();
	return (0);
}
