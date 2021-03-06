/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:47:49 by schakor           #+#    #+#             */
/*   Updated: 2020/03/10 14:57:53 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int ac, char **av)
{
	char	*filepath;

	filepath = av[1];
	if (ac != 2)
		ft_fatal_exit_putendl("usage: ./fdf filename");
	ft_fdf(filepath);
	return (0);
}
