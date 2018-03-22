#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_io.h"

static void	printecho(char **argv, int ops[2], char *sep)
{
	char	*l;

	while (*argv)
	{
		if (ops[1])
			ft_printf("%.*r", ft_strlenk(*argv), (l = ft_strdupk(*argv)));
		else
			ft_putstr((l = ft_strdup(*argv)));
		free(l);
		if (*++argv)
			ft_putstr(sep);
	}
	if (!ops[0])
		ft_putchar('\n');
}

static int	checkerror(t_opt *opt, char **argv, int ret)
{
	if (opt->seq == 1)
	{
		while (*++opt->cur)
			if (!ft_strchr("neEc", *opt->cur))
				break;
		if (*opt->cur && (*argv -= 2))
			return (0);
	}
	else if (opt->cur == 0 && ret == OPT_UNKNOWN)
		return (0);
	return (1);
}

int			builtin_echo(int argc, char **argv)
{
	t_opt	opt;
	int		ret;
	int		ops[2];
	char	*sep;

	(void)argc;
	++argv;
	ops[0] = 0;
	ops[1] = 1;
	sep = " ";
	while ((ret = ft_getopt(&argv, "neEc.1", &opt)) != OPT_END)
	{
		if (!checkerror(&opt, argv, ret))
			break;
		if (opt.c == 'n')
			ops[0] = 1;
		else if (opt.c == 'e')
			ops[1] = 1;
		else if (opt.c == 'E')
			ops[1] = 0;
		else if (opt.c == 'c' && opt.n == 1)
			sep = *opt.ptr;
	}
	printecho(argv, ops, sep);
	return (0);
}

