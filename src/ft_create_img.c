//name ft_manage_img.c
#include "fdf.h"

/*nb = x + 4 * 1000 * y;
			if (nb > 1000000 ||  nb < 0)
				break ;
			printf("nb1: %d\n", nb);
			img_data[nb] = 0xb5f7b4;
			printf("nb2: %d\n", nb);*/

static void	ft_pxl_to_img(t_param *params, t_point start, t_point finish, int *img_data)
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
	int dx = xx - x;
	int dy = yy - y;
	int incx = (dx > 0) ? 1 : -1;
	int incy = (dy > 0) ? 1 : -1;
	dx = abs(dx);
	dy = abs(dy);
	int cumul = 0;
	int i = 1;
	int nb;
	printf("x: %d, y: %d, xx: %d, yy: %d\n", x, y, xx, yy);
	printf("dx: %d, dy: %d\n", dx, dy);
	//mlx_pixel_put(params->mlx_ptr, params->win_ptr, x, y, 0xb5f7b4);
	if (dx > dy)
	{
		cumul = dx / 2;
		while (i <= dx)
		{
			x += incx;
			cumul += dy;
			if (cumul >= dx)
			{
				cumul -= dx;
				y += incy;
			}
			nb = x + 1000 * y;
			if (nb < 1000000 && nb > 0)
				img_data[nb] = 0xb5f7b4;
			//mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 250, y + 250, 0xb5f7b4);
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
			nb = x + 1000 * y;
			if (nb < 1000000 && nb > 0)
				img_data[nb] = 0xb5f7b4;
			//mlx_pixel_put(params->mlx_ptr, params->win_ptr, x + 250, y + 250, 0xb5f7b4);
			i++;
		}
	}
}

void	ft_fill_img(t_param *params, int *img_data)
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
			ft_pxl_to_img(params, points[i - 1], points[i], img_data);
			if ((i + params->map->xmax) < point_nb)
				ft_pxl_to_img(params, points[i - 1], points[i - 1 + params->map->xmax], img_data);
			if ((points[i].x == (params->map->xmax - 1)) && ((i + params->map->xmax) < point_nb))
				ft_pxl_to_img(params, points[i], points[i + params->map->xmax], img_data);	
		}
		i++;
	}
}

void	ft_create_img(t_param *params)
{
	int 	bpp;
	int 	size_line;
	int 	endian;
	void 	*img_ptr = mlx_new_image(params->mlx_ptr, 1000, 1000);
	int 	*img_data = (int*)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

	ft_bzero(img_data, 1000*1000);
	printf("line size: %d\n", size_line);
	ft_fill_img(params, img_data);
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, img_ptr, 0, 0);
}