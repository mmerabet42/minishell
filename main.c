#include <stdio.h>

int main()
{
	printf("KO\n");
	return (0);
/*	char	**args;
	int	ret;
	t_opt	opt;
	int	i;

	args = argv + 1;
	while ((ret = ft_getopt(&args, "lq", &opt)) != OPT_END)
	{
		if (ret == OPT_UNKNOWN)
			ft_printf("Unknown option : %c %d '%s'\n", opt.c, opt.seq, opt.cur);
		else
			ft_printf("%d -> Option : %c '%s' %d %d '%s'\n", ret, opt.c, opt.clong, opt.n, opt.seq, opt.cur);
		if (opt.n > 0)
		{
			i = 0;
			while (i < opt.n)
				ft_printf("Argument: '%s'\n", opt.ptr[i++]);
		}
	}
	while (*args)
		ft_printf("End argument: '%s'\n", *args++);
	return (0);*/
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
	while (1)
	{
		
	}
	return (0);
}
