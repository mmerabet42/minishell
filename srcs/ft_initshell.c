#include "shell.h"
#include <unistd.h>

void	ft_initshell(t_shell *shell, char **envp)
{
	if (!shell)
		return ;
	getcwd(shell->pwd, 2048);
	shell->paths = ft_getpaths(envp);
	shell->ison = 1;
	shell->envp = envp;
}
