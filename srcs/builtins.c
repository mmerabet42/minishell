/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 19:29:29 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/29 17:00:04 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_io.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_printf.h"

int	builtin_exit(int argc, char **argv)
{
	if (argc > 1)
		g_shell->exitcode = ft_atoi(argv[1]);
	g_shell->running = 0;
	return (0);
}

int	builtin_history(int argc, char **argv)
{
	int		i[3];
	t_list	*it;
	t_opt	opt;

	(argc ? ft_bzero(i, sizeof(int) * 3) : ft_bzero(i, sizeof(int) * 3));
	++argv;
	while ((i[2] = ft_getopt(&argv, "c;clear", &opt)) != OPT_END)
	{
		if (i[2] == OPT_UNKNOWN)
			return (ft_printf("illegal option -- %c\n", opt.c) ? 1 : 1);
		else if (opt.c == 'c'
				|| (opt.c == '-' && ft_strequ(opt.clong, "clear")))
			i[1] = 1;
	}
	if (i[1])
		clearhistory();
	else if ((it = ft_lstend(g_shell->history)))
	{
		while (it)
		{
			ft_printf("%d %s\n", i[0]++, it->content);
			it = it->parent;
		}
	}
	return (0);
}
