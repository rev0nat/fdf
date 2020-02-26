/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 13:06:42 by aguillot          #+#    #+#             */
/*   Updated: 2018/10/22 14:48:30 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "../include/fdf.h"
#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//http://www.irem.univ-mrs.fr/IMG/pdf/Algos_trace_segment_draft_2_-2.pdf
int TraceSegmentNaif(void *mlx_ptr, void *win_ptr)
{
	int		px;
	int 	x = 125;
	int 	y = 125;
	int 	dx = 10;
	int 	dy = 4;
	float 	m = ((float)dy / (float)dx);
	int    	i = 0;

	while (i++ <= dx){
		x = x + i;
		y = round(y + m * i);
		px = mlx_pixel_put(mlx_ptr, win_ptr, x, y, 2392020);
	}
	return (0);
}

//http://www.irem.univ-mrs.fr/IMG/pdf/Algos_trace_segment_draft_2_-2.pdf
int TraceSegmentIncremental(void *mlx_ptr, void *win_ptr)
{
	int 	px;
	int 	x = 100;
	float	y = 100;
	int 	dx = 4;
	int 	dy = 10;
	float	m = ((float)dy / (float)dx);
	int 	xx = x + dx;

	while (x++ <= xx){
		px = mlx_pixel_put(mlx_ptr, win_ptr, x, y, 0xDB4437);
		y = y + m;
	}

	return (0);
}

//https://repo.zenk-security.com/Cryptographie%20.%20Algorithmes%20.%20Steganographie/Les%20algorithmes%20de%20base%20du%20graphisme.pdf
int TraceSegmentSimple(void *mlx_ptr, void *win_ptr)
{
	int x;
	int x0 = 125;
	int x1 = 150;
	int y0 = 125;
	int y1 = 150;

	double dx = x1 - x0;
	double dy = y1 - y0;
	double m = dy / dx;
	//printf("dx: %f, dy:%f, m:%f\n", dx, dy, m);
	double y = y0;
	for(x = x0; x <= x1 ; x++){
		mlx_pixel_put(mlx_ptr, win_ptr, x, (int) (y + 0.5), 0xF4B400);
		y -= m;
	}
	return (0);
}

int TraceSegmentBresenham(void *mlx_ptr, void *win_ptr)
{
	int px = 0;
	int x0 = 125;
	int y0 = 125;
	int x1 = 500;
	int y1 = 500;
	int dx = x1 - x0;
	int dy = y1 - y0;
	int incre = 2 * dy;
	int incrne = 2 * dy - dx;
	int e = 2 * dy - dx;

	while (x0++ <= x1)
	{
		px = mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0x32a8a8);
		if (e >= 0)
		{
			y0++;
			e += incrne;
		}
		else
			e += incre;
	}

	return (0);
}

int TraceSegmentMouse(t_param *params)
{
	int 			px;
	void			*mlx_ptr = params->mlx_ptr;
	void			*win_ptr = params->win_ptr;
	t_coordinates	*coor;

	coor = params->coordinates;
	while ((coor->x)++ <= coor->xx)
	{
		px = mlx_pixel_put(mlx_ptr, win_ptr, coor->x, coor->y, 0x32a8a8);
		if (coor->e >= 0)
		{
			(coor->y)++;
			(coor->e) += coor->incrne;
		}
		else
			coor->e += coor->incre;
	}

	return (0);
}

//fonction qui va tracer un trait d'un clic à l'autre
int FillMouseParams(int x, int y, t_param *params)
{
	if (!(params->coordinates->x) && !(params->coordinates->y))
	{
		params->coordinates->x = x;
		params->coordinates->y = y;
		printf("c->x: %d, c->y: %d\n", params->coordinates->x, params->coordinates->y);
		return (1);
	}
	params->coordinates->xx = x;
	params->coordinates->yy = y;
	params->coordinates->dx = params->coordinates->xx - params->coordinates->x;
	params->coordinates->dy = params->coordinates->yy - params->coordinates->y;
	params->coordinates->incre = 2 * params->coordinates->dy;
	params->coordinates->incrne = 2 * params->coordinates->dy - params->coordinates->dx;
	params->coordinates->e = 2 * params->coordinates->dy - params->coordinates->dx;
	printf("c->XX: %d, c->YY: %d\n", params->coordinates->xx, params->coordinates->yy);
	TraceSegmentMouse(params);

	return (0);
}

//Faire une fonction qui va tracer une droite d'un clic de la souris à l'autre
int ft_mouse_hook(int button, int x,int y, t_param *params)
{
	(void)button;
	if (FillMouseParams(x, y, params) == 0)
	{
		ft_bzero(params->coordinates, sizeof(t_coordinates));
	}
	/*mlx_pixel_put(params->mlx_ptr, params->win_ptr, x, y, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 1, y, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x - 1, y, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x, y + 1, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x, y - 1, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 1, y + 1, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x - 1 , y - 1, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 1, y - 1, 0xe36720);
	mlx_pixel_put(params->mlx_ptr, params->win_ptr, x - 1, y + 1, 0xe36720);*/
	//printf("button: %d, x: %d, y: %d\n", button, x, y);
	return (0);
}

int	main()
{
	void			*mlx_ptr;
	void			*win_ptr;
	int 			sx;
	int 			ret;
	t_param			*params;
	t_coordinates 	*coordinates;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "fdf");
	//LEAK

	if (!(coordinates = (t_coordinates*)malloc(sizeof(t_coordinates))))
	{
		perror("");
		exit(1);
		//errors_controller(MALLOC_ERROR);
	}
	ft_bzero(coordinates, sizeof(t_coordinates));
	if (!(params = (t_param*)malloc(sizeof(t_param))))
	{
		perror("");
		exit(1);
		//errors_controller(MALLOC_ERROR);
	}
	ft_bzero(params, sizeof(t_param));
	params->mlx_ptr = mlx_ptr;
	params->win_ptr = win_ptr;
	params->coordinates = coordinates;
	sx = mlx_string_put(mlx_ptr, win_ptr, 0, 0, 2392020, "tm");
	ret = TraceSegmentNaif(mlx_ptr, win_ptr);
	ret = TraceSegmentIncremental(mlx_ptr, win_ptr);
	ret = TraceSegmentSimple(mlx_ptr, win_ptr);
	ret = TraceSegmentBresenham(mlx_ptr, win_ptr);
	mlx_mouse_hook(win_ptr, ft_mouse_hook, params);
	mlx_loop(mlx_ptr);

	return (0);
}