/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguillot <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 17:56:00 by aguillot          #+#    #+#             */
/*   Updated: 2020/03/10 18:19:43 by aguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


//test de wikipedia via stackoverflow.
/*int toIsometric2D(double x, double y,double z, double *u, double*v){
    *u=(x-z)/sqrt(2);
    *v=(x+2*y+z)/sqrt(6);
    return 0;
}*/

//schakors
static void	ft_draw_line(t_param *params, t_point start, t_point finish)
{
    int tx = start.x - (params->map->xmax / 2);
    int txx = finish.x - (params->map->xmax / 2);
    int ty = start.y - (params->map->ymax / 2);
    int tyy = finish.y - (params->map->ymax / 2);
    int tmpx = (1000 / (params->map->xmax * 2.f)) * tx;
    int tmpxx = (1000 / (params->map->xmax * 2.f)) * txx;
    int tmpy = (1000 / (params->map->ymax * 2.f)) * ty;
    int tmpyy = (1000 / (params->map->ymax * 2.f)) * tyy;
	int x = sqrt(2)/2 * (tmpx - tmpy);
	int xx = sqrt(2)/2 * (tmpxx - tmpyy);
	int y = -(0.8165f * start.z * 2) - (0.4082f) * (tmpx + tmpy);
    int yy = -(0.8165f * finish.z * 2) - (0.4082f) * (tmpxx + tmpyy);
	/*int x = start.x;
	int y = start.y;
	int xx = finish.x;
	int yy = finish.y;*/
	int dx = xx - x;
	int dy = yy - y;
	int incx = (dx > 0) ? 1 : -1;
	int incy = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	int cumul = 0;
	int i = 1;
	printf("x: %d, y: %d, xx: %d, yy: %d\n", x, y, xx, yy);
	printf("dx: %d, dy: %d\n", dx, dy);
	//mlx_pixel_put(params->mlx_ptr, params->win_ptr, x, y, 0xb5f7b4);
	if (dx > dy)
	{
		cumul = dx / 2;
		//printf("dans le if (dx > dy): dx: %f, dy: %f\n", dx, dy);
		while (i <= dx)
		{
			x += incx;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += incy;
			}
			printf("start: x:%d y:%d, finish: x:%d y:%d\n", start.x, start.y, finish.x, finish.y);
			printf("onfx: %d, y: %d\n", x, y);
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 500, y + 500, 0xb5f7b4);
			i++;
		}
	}
	else
	{
		cumul = dy /2;
		//printf("toto\n");
		//printf("i: %d, dx: %f\n", i, dx);
		while (i <= dy)
		{
			y += incy;
			cumul += dx;
			if (cumul >= dy)
			{
				cumul -= dy;
				x += incx;
			}
			printf("infffffx: %d, y: %d\n", x, y);
			mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 500, y + 500, 0xb5f7b4);
			i++;
		}
	}
}

//il faut un algo qui trace les lignes, un qui trace les colonnes
void		ft_draw(t_param *params)
{
	t_point	*points;
	int		i;
	int		point_nb;

	points = params->map->point;
	point_nb = params->map->xmax * params->map->ymax;
	i = 1;
	while (i < point_nb)
	{
		if (points[i - 1].y == points[i].y)
		{
			ft_draw_line(params, points[i - 1], points[i]);
			if ((i + params->map->xmax) < point_nb)
				ft_draw_line(params, points[i - 1], points[i - 1 + params->map->xmax]);
			if ((points[i].x == (params->map->xmax - 1)) && ((i + params->map->xmax) < point_nb))
				ft_draw_line(params, points[i], points[i + params->map->xmax]);	
		}
		i++;
	}
}