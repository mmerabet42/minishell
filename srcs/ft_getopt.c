#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_types.h"
#include "ft_printf.h"

char	ft_getopt(char ***argv, const char *options, t_opt *opt)
{
	char	*str;
	char	*cs;
	int		i;

	ft_bzero(opt, sizeof(t_opt));
	while (**argv)
	{
		str = *argv;
		if (*str == '-')
		{
			while (*str)
			{
				if ((cs = ft_strchr(options, *++str)))
				{
					if (*(cs + 1) == ':')
						opt->n = ft_atoi(*(cs + 1));
					i = -1;
					while (++i < opt->n && **argv)
					{
						++(*argv);
						if (i == 0)
							opt->ptr = (*argv);
					}
					if (!**argv && i < opt->n && (opt->n = i))
						ft_printf("missing parameter -- '%s'\n", *str);
				}
				else
				{
					ft_printf("syntax error -- '%c'\n", *str);
					opt->ptr = *argv;
				}
				return (cs ? *str : '?');
			}
		}
		++(*argv);
	}
}
