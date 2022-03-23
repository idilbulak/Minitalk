/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minitalk.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ibulak <ibulak@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/23 15:14:40 by ibulak        #+#    #+#                 */
/*   Updated: 2022/03/23 15:14:56 by ibulak        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"

void	ft_error(void);
int		send_message(int pid, char *str);
void	handler_client(int sig, siginfo_t *info, void *context);
void	ft_error_server(int pid);
void	handler_server(int sig, siginfo_t *info, void *context);

#endif