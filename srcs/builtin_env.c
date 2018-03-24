#include "shell.h"
#include "ft_mem.h"
#include "ft_str.h"
#include "ft_io.h"

int	builtin_env(int argc, char **argv)
{
	char	**it;

	(void)argv;
	(void)argc;
	it = g_shell->envp;
	while (*it)
		ft_putendl(*it++);
	return (0);
}
