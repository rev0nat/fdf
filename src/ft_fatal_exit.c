/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fatal_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:30:25 by schakor           #+#    #+#             */
/*   Updated: 2020/03/10 16:31:35 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_fatal_exit(void)
{
	perror("");
	exit(127);
}

void		ft_fatal_exit_putendl(char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	exit(127);
}
