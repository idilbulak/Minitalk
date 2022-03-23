/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   server.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 15:15:01 by ibulak        #+#    #+#                 */
/*   Updated: 2022/03/23 15:20:45 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minitalk.h"

void	ft_error_server(int pid)
{
	write(1, "ERROR!", 6);
	kill(pid, SIGUSR2);
	exit(EXIT_FAILURE);
}

void	handler_server(int sig, siginfo_t *info, void *context)
{
	static char	c = 0b11111111;
	static int	pid = 0;
	static int	counter = 0;

	(void)context;
	if (info->si_pid)
		pid = info->si_pid;
	if (sig == SIGUSR1)
		c ^= 0b10000000 >> counter;
	else if (sig == SIGUSR2)
		c |= 0b10000000 >> counter;
	if (++counter == 8)
	{
		ft_putchar_fd(c, 1);
		counter = 0;
		c = 0b11111111;
	}
	if (kill(pid, SIGUSR1) == -1)
		ft_error_server(pid);
}

int	main(void)
{
	struct sigaction	sact;

	sigemptyset(&sact.sa_mask);
	sact.sa_handler = 0;
	sact.sa_sigaction = handler_server;
	sact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sact, NULL);
	sigaction(SIGUSR2, &sact, NULL);
	ft_putstr_fd("PID of the calling process is ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
}
