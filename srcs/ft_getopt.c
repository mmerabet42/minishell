/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmerabet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 20:36:37 by mmerabet          #+#    #+#             */
/*   Updated: 2018/03/19 21:55:35 by mmerabet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_printf.h"

static int	getnargs(char c, const char *options)
{
	char	*cs;

	if (c != '.' && !ft_isdigit(c) && (cs = ft_strchr(options, c)))
	{
		if (*(cs + 1) == '.')
			return (ft_atoi(cs + 2));
		return (0);
	}
	return (-1);
}

static int	getcargs(t_opt *opt, char ***argv)
{
	int	i;

	i = 0;
	while (i < opt->n && **argv)
	{
		++(*argv);
		++i;
	}
	if (i < opt->n)
	{
		opt->n = i;
		return (OPT_MISSING);
	}
	return (OPT_OK);
}

static int	checkargs(char ***argv, const char *options, t_opt *opt, int *isopt)
{
	char	*str;

	if (*(str = *(*argv - 1)) == '-')
		++str;
	opt->c = *str;
	if ((opt->n = getnargs(*str, options)) == -1)
	{
		if (!*(str + 1))
			*isopt = 0;
		else if ((*isopt = 1))
			*--(*argv) = str + 1;
		return (OPT_UNKNOWN);
	}
	else if (*(str + 1) && (*isopt = 1))
	{
		*--(*argv) = str + 1;
		return (opt->n > 0 && !(opt->n = 0) ? OPT_ALONE : OPT_OK);
	}
	else
		return (!(*isopt = 0) ? getcargs(opt, argv) : OPT_OK);
	return (OPT_OK);
}

int			ft_getopt(char ***argv, const char *options, t_opt *opt)
{
	static	int	isopt;

	ft_bzero(opt, sizeof(t_opt));
	while (**argv)
	{
		if (***argv == '-' || isopt)
		{
			opt->ptr = ++(*argv);
			if (ft_strequ(*(*argv - 1), "--"))
				return (OPT_END);
			return (checkargs(argv, options, opt, &isopt));
		}
		else
			return (OPT_END);
		++(*argv);
	}
	return (OPT_END);
}
