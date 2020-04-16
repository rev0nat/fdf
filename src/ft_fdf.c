/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:58:06 by schakor           #+#    #+#             */
/*   Updated: 2020/03/10 15:31:00 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void ft_init(t_param *params, t_map *map)
{
	void			*mlx_ptr;
	void			*win_ptr;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "fdf");
	params->mlx_ptr = mlx_ptr;
	params->win_ptr = win_ptr;
	params->map = map;
	//mlx_key_hook;
	//mlx_loop_hook(win_ptr, ft_mous_hook, params);
}

void		ft_fdf(char *filepath)
{
	t_map	map;
	t_param params;

	ft_map_reader(filepath, &map);
	ft_init(&params, &map);
	ft_create_img(&params);
	//ft_draw(&params);
	mlx_loop(params.mlx_ptr);
}
