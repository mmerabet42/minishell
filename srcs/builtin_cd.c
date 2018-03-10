#include "shell.h"
#include "ft_str.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <unistd.h>

t_shret	ft_chdir(char *name, t_shell *shell)
{
	t_shret	acc;

	if ((acc = ft_access(name, R_OK)) != SH_OK)
		return (acc);
	else
	{
		chdir(name);
		if (shell)
		{
			ft_setenv("OLDPWD", ft_getenv("PWD", shell), shell);
			ft_setenv("PWD", ft_getcwd(shell->pwd, 2048), shell);
		}
	}
	return (SH_OK);
}

t_shret	builtin_cd(int argc, char **argv, t_shell *shell)
{
	t_shret	acc;

	if (argc == 1 && (acc = ft_chdir(shell->homepwd, shell)) != SH_OK)
		ft_printf("%s: %s: %s\n", argv[0], ft_strshret(acc), shell->homepwd);
	else if (argc > 1 && (acc = ft_chdir(argv[1], shell)) != SH_OK)
		ft_printf("%s: %s: %s\n", argv[0], ft_strshret(acc), argv[1]);
	return (SH_ESUCCESS);
}
