/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/08 20:04:32 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include <unistd.h>
#include <sys/wait.h>

static void ft_readline(char *line, t_shell *shell)
{
	char	fullpath[1024];
	t_args	args;
	t_shret	shret;

	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_getargs(line, &args)))
	{
		if (args.argc > 1 && !ft_strcmp(args.argv[0], "exit"))
			shell->ison = 0;
		else if (args.argc > 1)
		{
			if (ft_isbuiltin(args.argv[0], &args, shell) == SH_NFOUND)
			{
				shret = ft_getfullpath(args.argv[0], shell, fullpath, 1024);
				if (shret != SH_OK)
					ft_printf("sh: %s: %s\n", ft_strshret(shret), args.argv[0]);
				else
					ft_exec(fullpath, args.argv, shell->envp);
			}
		}
		ft_delargs(&args);
	}
}

int main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*colorpwd;
	t_shell	shell;

	if (argc > 1)
		colorpwd = argv[1];
	else
		colorpwd = "cyan";
	ft_initshell(&shell, envp);
	while (shell.ison)
	{
		ft_printf("%{%s}%s%{0} > ", colorpwd, shell.pwd);
		if (get_next_line(1, &line) == -1)
			exit(EXIT_FAILURE);
		ft_readline(line, &shell);
		free(line);
	}
	return (0);
}
