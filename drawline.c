/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:34:46 by vkinnune          #+#    #+#             */
/*   Updated: 2022/03/07 11:48:08 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	getcolor(t_data *data, int up, int i)
{
	int	ret;

	ret = (data->colors[0] + up);
	if (data->fade)
		ret += i * 2;
	ret /= (data->colors[1] + 2);
	return (ret);
}

void	drawx(float x1, float x2, float m_and_b[2], t_data *data)
{
	float	t;
	float	x;
	float	y;
	float	ret;

	y = 0;
	if (x2 < x1)
	{
		t = x1;
		x1 = x2;
		x2 = t;
	}
	x = x1;
	ret = x2 - x;
	while (x <= x2 + 1)
	{
		y = round(m_and_b[0] * x + m_and_b[1]);
		if (x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0)
			my_mlx_pixel_put(data, x, y,
				getcolor(data, ret, x2 - x));
		x++;
	}
}

void	drawy(float y1, float y2, float m_and_b[2], t_data *data)
{
	float	t;
	float	x;
	float	y;
	float	ret;

	x = 0;
	if (y2 < y1)
	{
		t = y1;
		y1 = y2;
		y2 = t;
	}
	y = y1;
	ret = y2 - y;
	while (y <= y2 + 1)
	{
		x = round((y - m_and_b[1]) / m_and_b[0]);
		if (x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0)
			my_mlx_pixel_put(data, x, y,
				getcolor(data, ret, y2 - y));
		y++;
	}
}

void	drawup(float y1, float y2, float x1, t_data *data)
{
	float	y;
	float	t;
	float	ret;

	if (y2 < y1)
	{
		t = y1;
		y1 = y2;
		y2 = t;
	}
	y = y1;
	ret = y2 - y;
	while (y <= y2 + 1)
	{
		if (x1 <= WIDTH && x1 >= 0 && y <= HEIGHT && y >= 0)
			my_mlx_pixel_put(data, x1, y,
				getcolor(data, ret, y2 - y));
		y++;
	}
}

void	drawline(int x1, int y1, int xy2[2], t_data *data)
{
	float	m_and_b[2];
	float	rise;
	float	run;

	rise = xy2[1] - y1;
	run = xy2[0] - x1;
	if (run == 0)
		drawup(y1, xy2[1], x1, data);
	else
	{
		m_and_b[0] = rise / run;
		m_and_b[1] = y1 - m_and_b[0] * x1;
		if (m_and_b[0] <= 1 && m_and_b[0] >= -1)
			drawx(x1, xy2[0], m_and_b, data);
		else
			drawy(y1, xy2[1], m_and_b, data);
	}
}
