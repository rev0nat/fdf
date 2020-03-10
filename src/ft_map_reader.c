/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schakor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 14:51:14 by schakor           #+#    #+#             */
/*   Updated: 2020/03/10 16:44:19 by schakor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_xmax_ymax(char *filepath, t_map *map)
{
	int		fd;
	int		size_line;
	char	*line;
	char	**tab;

	if ((fd = open(filepath, O_RDONLY)) == -1)
		ft_fatal_exit();
	map->xmax = 0;
	map->ymax = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		size_line = ft_arrlen(tab);
		if (size_line > map->xmax)
			map->xmax = size_line;
		map->ymax++;
	}
	close(fd);
}

static void	get_coor(char *file, t_map *map)
{

	int		fd;
	char	*line;
	char	**tab;
	int		j;
	int		i;
	int		ind_point;

	if (!(map->point = (t_point *)malloc(sizeof(t_point) * (map->ymax * map->xmax))))
		ft_fatal_exit();
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_fatal_exit();
	j = 0;
	ind_point = 0;
	while (get_next_line(fd, &line) > 0)
	{
		tab = ft_strsplit(line, ' ');
		i = 0;
		while (tab[i])
		{
			map->point[ind_point].x = i;
			map->point[ind_point].y = j;
			map->point[ind_point].z = ft_atoi(tab[i]);
			ind_point++;
			i++;
		}
		j++;
	}
	close(fd);
}

void		ft_map_reader(char *filepath, t_map *map)
{
	get_xmax_ymax(filepath, map);
	get_coor(filepath, map);
	/*int i = 0;
	while (i < map->xmax * map->ymax)
	{
		printf("x = %d , y = %d, z = %d\n", map->point[i].x, map->point[i].y, map->point[i].z);
		i++;
	}*/
}
/*
static void		ft_fill_points(t_point *points, char *line, int x, int y)
{
	int z;

	//proteger atoi??
	z = ft_atoi(line);
	points->x = x;
	points->y = y;
	points->z = z;
}

static void 	ft_create_map(t_point *points, char *line, int y)
{
	int 	i;
	char 	**split;
	int		arrlen;

	i = 0;
	//erreur si split renvoie -1;
	split = ft_strsplit(line, ' ');
	//realloc de points selon le nombre de characs dans line (- espaces et \n)
	arrlen = ft_arrlen(split);
	while (split[i])
	{
		ft_fill_point(points, split[i], i,  y);
		i++;
	}
}

static void		ft_map_parser(char *filepath, t_map *map)
{
	int			fd;
	char		*line;
	int			y;
	t_point		*new_point;

	if (!map->point = (t_point*)malloc(sizeof(t_point)))
	fd = open(filepath, O_RDONLY);
	if (fd == - 1)
		ft_fatal_exit();
	while (get_next_line(fd, &line) > 0)
	{
		ft_create_map(map->point, &line, y);
		y++;
	}
}
*/
