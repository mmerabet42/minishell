/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 18:40:09 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/12 20:22:31 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "shell.h"
#include "ft_types.h"
#include <unistd.h>
#include <locale.h>

static void ft_readline(char *line, t_shell *shell)
{
	char	fullpath[1024];
	t_args	args;
	t_shret	shret;
	
	ft_bzero(&args, sizeof(t_args));
	while ((line = ft_getargs(line, &args, shell)))
	{
		if (args.argc >= 1
				&& ft_isbuiltin(args.argv[0], &args, shell) == SH_NFOUND)
		{
			shret = ft_getfullpath(args.argv[0], shell, fullpath, 1024);
			if (shret != SH_OK)
				ft_printf("%s: %s: %s\n", shell->name, ft_strshret(shret),
					args.argv[0]);
			else
				ft_exec(fullpath, args.argv, shell->envp, &shell->pid);
		}
		ft_delargs(&args);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	line[2048];
	int		c;

	(void)argc;
	(void)argv;
	ft_initshell("minishell", &shell, envp);
/*	if (argc > 1)
	{
		promptf = ft_strrepstr_clr(ft_strdup(argv[1]), "@user", "%2$s");
		promptf = ft_strrepstr_clr(promptf, "@pwd", "%3$s");
		promptf = ft_strrepstr_clr(promptf, "@sign-jap", "%1$S");
		promptf = ft_strrepstr_clr(promptf, "@sign-3dot", "%4$S");
	}
	else
		promptf = ft_strdup("%S %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ");*/
	setlocale(LC_ALL, "");
	while (shell.running)
	{
		ft_printf("%S %{lred}%s %{lcyan}%s%{0} %{bold}%S%{0} ", L"㋜", shell.user, shell.pwd, L"∴");
		ft_bzero(line, ft_strlen(line));
		if ((c = ft_readraw(line, 2048)) != 3 && c != 4)
			ft_readline(line, &shell);
		else if (c == 4)
			ft_readline("exit", &shell);
	}
	ft_makeraw(0);
	ft_delshell(&shell);
	return (0);
}
