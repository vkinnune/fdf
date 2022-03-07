/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:35:09 by vkinnune          #+#    #+#             */
/*   Updated: 2022/03/07 11:13:31 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "stdio.h"

void	print(t_data *data, t_vec3 *p)
{
	int	i;

	i = 0;
	data->colors[0] = 0x00AA00 * data->color;
	while (i != data->rows * data->cols)
	{
		printrows(data, p, i);
		printcols(data, p, i);
		i++;
	}
}

void	docords(t_data *data, t_vec3 *p)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while (i != (data->rows + 1) * (data->cols + 1))
	{
		if (x == data->cols)
		{
			x = 0;
			y++;
		}
		p[i].x = x;
		p[i].y = y;
		p[i].z = data->map[j];
		i++;
		x++;
		j++;
	}
}

/*
   Projection 2 is top down projection
   Projection 1 is isometric projection
   Projection 0 is oblique projection
   txyz =
   0 is x
   1 is y
   2 is z
   */

void	iso(t_data *data, t_vec3 p, t_vec3 *r)
{
	double	txyz[3];

	txyz[0] = p.x;
	txyz[1] = p.y;
	txyz[2] = p.z;
	r->x = (txyz[0] - data->c_x);
	r->y = (txyz[1] - data->c_y);
	if (data->project == 1)
	{
		txyz[0] -= data->c_x;
		txyz[1] -= data->c_y;
		r->x = ((txyz[0] - txyz[1]) / sqrtl(2));
		r->y = ((txyz[0] + 2 * txyz[1]) - (txyz[2] * data->c_z)) / sqrtl(6);
	}
	else if (data->project == 0)
	{
		txyz[2] = (p.z - 24) + (data->c_z);
		r->x = txyz[0] + (data->c_x / txyz[2]) + cos(atan(data->c_x / txyz[2]));
		r->y = txyz[1] + (data->c_y / txyz[2]) + sin(atan(data->c_y / txyz[2]));
	}
	r->x *= 300 / data->cols * data->zoom;
	r->y *= 300 / data->cols * data->zoom;
	r->x += data->cols;
	r->y += data->rows + 200;
}

void	printrows(t_data *data, t_vec3 *p, int i)
{
	int		xy[2];
	t_vec3	temp[2];

	data->colors[1] = 0;
	data->fade = false;
	if (p[i + 1].z > 0 && p[i].z > 0)
		data->colors[1] = p[i].z;
	else if ((p[i + 1].z > 0 && p[i].z == 0) || (p[i + 1].z == 0 && p[i].z > 0))
	{
		data->fade = true;
		if (p[i + 1].z > p[i].z)
			data->colors[1] = p[i + 1].z;
		else
			data->colors[1] = p[i].z;
	}
	if (p[i].y == p[i + 1].y)
	{
		iso(data, p[i], &temp[0]);
		iso(data, p[i + 1], &temp[1]);
		xy[0] = temp[1].x;
		xy[1] = temp[1].y;
		drawline(temp[0].x, temp[0].y, xy, data);
	}
}

void	printcols(t_data *data, t_vec3 *p, int i)
{
	int		xy[2];
	t_vec3	temp[2];

	data->colors[1] = 0;
	data->fade = false;
	if (p[i + data->cols].z > 0 && p[i].z > 0)
		data->colors[1] = p[i].z;
	else if ((p[i + data->cols].z > 0 && p[i].z == 0)
		|| (p[i + data->cols].z == 0 && p[i].z > 0))
	{
		data->fade = true;
		if (p[i + data->cols].z > p[i].z)
			data->colors[1] = p[i + data->cols].z;
		else
			data->colors[1] = p[i].z;
	}
	if (p[i].y != (data->rows - 1))
	{
		iso(data, p[i], &temp[0]);
		iso(data, p[i + data->cols], &temp[1]);
		xy[0] = temp[1].x;
		xy[1] = temp[1].y;
		drawline(temp[0].x, temp[0].y, xy, data);
	}
}
