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

/*
** The working of this getopt version is similar to the real, but has
** some differencies.
**
** There can be 5 different return values:
** OPT_END, OPT_MISSING, OPT_UNKNOWN, OPT_ALAST and OPT_OK.
** OPT_END: This means that we, either reached the end of the array, or there
** is no options anymore.
** OPT_MISSING: There are arguments missing for the returned character option.
** OPT_UNKNOWN: The character option is unknown and is not present in the string
** containing the character options.
** OPT_ALAST: When a character option is awaiting arguments it should be alone:
** "-l ..." or at the end of a sequence of options "-xxxl ...", This return
** tells that the character option has not been caught at the end of a sequence
** of options "-xlxx ..." so the argument following the 'l' option are not 'l's
** arguments.
** OPT_OK: No problem has been caught.
**
** [char ***argv] ->
** The first parameter is a pointer to an array of string (the address of
** argv), the function needs it in order to move through the array between The
** calls. The function assume that argv[0] is not a part of the array.
**
** [const char *options] ->
** The second parameter is a string containing each option characters. An
** option character can take a defined number of arguments if it is followed by
** a dot and a number telling how much argument there must be after the
** character: "l.2a.4" <- the 4 arguments that follows 'a' are 'a's arguments,
** and the 2 arguments that follows 'l' are 'l's arguments.
**
** [t_opt *opt]
** The third, and last, parameter is a pointer to a structure where will be
** stored additional, but important, information about the current option.
** -> the 'c' attribute is the character option. If 'l' character option
** is caught, then c is equal to that character.
** -> the 'n' attribute tells how many arguments has been successfully caught
** after the character option. It is equal to zero if the option is not waiting
** any arguments.
** -> the 'ptr' attribute points to the first argument after the character
** option. It is equal to NULL if the option is not waiting any arguments.
*/

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
		if (ft_strequ(**argv, "--"))
			break;
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
		{
			if (!opt->seq)
				opt->seq = 1;
			*--(*argv) = str + 1;
		}
		return (OPT_UNKNOWN);
	}
	else if (*(str + 1) && (*isopt = 1))
	{
		if (!opt->seq)
			opt->seq = 1;
		*--(*argv) = str + 1;
		return (opt->n > 0 && !(opt->n = 0) ? OPT_ALAST : OPT_OK);
	}
	return (!(*isopt = 0) ? getcargs(opt, argv) : OPT_OK);
}

int			ft_getopt(char ***argv, const char *options, t_opt *opt)
{
	static int	isopt;
	static char	**ptr;

	if (ptr != *argv)
		isopt = 0;
	if (**argv)
	{
		ptr = *argv;
		if (!isopt)
			opt->cur = **argv;
		if (***argv == '-' || isopt)
		{
			opt->ptr = ++(*argv);
			opt->n = 0;
			opt->c = 0;
			opt->seq = 0;
			if (isopt)
				opt->seq = (!*(*ptr + 1) ? 3 : 2);
			if (ft_strequ(*(*argv - 1), "--"))
				return (OPT_END);
			return (checkargs(argv, options, opt, &isopt));
		}
	}
	return (OPT_END);
}
