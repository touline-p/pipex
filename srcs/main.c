#include "pipex.h"

int	main(int ac, char **av)
{
	int fds[2];
	int	fd_in;
	int	fd_out;

	if (!open_fds(fds, ac, av))
		return (1);
	ft_execute_commands(fds, ac, av);
}

int	open_fds(int *fds, int ac, char **av)
{
	if (ac < 5)
	{
		ft_putstr_fd("Not enough Arguments", 2);
		return (0);
	}
	fds[0] = open(av[1]);
	fds[1] = open(av[ac - 1]);
	if (fd_in == -1 || fd_out == -1)
	{
		ft_printf_fd("Error : Cant't open %s or %s path", av[1], av[ac - 1]);
		return (0);
	}
	return (1);
}

void	ft_execute_commands(int *fds, int ac, char **av)
{
	int		indx_cmd;
	pid_t	son_pid;

	ft_put_fd_in_stdin(fd[0]);
	indx_cmd = 1;
	while (indx_cmd < ac)
	{
		indx_cmd++;
		son_pid = fork();
		if (son_pid == 0)
		{
			exec
		}
		else
			wait(NULL);
	}
	if (son_pid != 0)
		ft_put_stdin_in_fd(fd[1]);
}
