/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahirov <otahirov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:20:52 by otahirov          #+#    #+#             */
/*   Updated: 2019/01/10 16:48:48 by otahirov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "get_next_line.h"

void		get_size(t_map *map, char *line)
{
	size_t	ln;
	char	**tab;

	ln = 0;
	tab = ft_strsplit(line, ' ');
	while (tab[ln])
	{
		ft_strdel(&tab[ln]);
		ln++;
	}
	if (map->maxrow < ln)
		map->maxrow = ln;
	ft_strdel(&line);
	free(tab);
	map->lines++;
}

void		init_map(t_map *map, t_mlx *mlx)
{
	char	*line;

	line = NULL;
	map->lines = 0;
	map->maxrow = 0;
	while (get_next_line(mlx->fd, &line) > 0)
		get_size(map, line);
	CHECK_NULL(map->blocks = ft_memalloc(map->lines * sizeof(t_block)));
	close(mlx->fd);
	mlx->fd = open(mlx->name, O_RDONLY);
}

void		read_map(t_mlx *mlx)
{
	char	*line;
	char	**tab;
	int		x[3];
	t_map	*map;

	x[1] = 0;
	init_map(&mlx->map, mlx);
	map = &mlx->map;
	while (get_next_line(mlx->fd, &line) > 0)
	{
		x[0] = 0;
		tab = ft_strsplit(line, ' ');
		map->blocks[x[1]] = ft_memalloc(sizeof(t_block) * map->maxrow);
		while (tab[x[0]])
		{
			x[2] = ft_atoi(tab[x[0]]);
			map->blocks[x[1]][x[0]].is_wall = (x[2] > 1) ? 1 : 0;
			map->blocks[x[1]][x[0]].value = x[2];
			free(tab[x[0]++]);
		}
		free(line);
		free(tab);
		x[1]++;
	}
}