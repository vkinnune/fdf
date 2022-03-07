/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:34:09 by vkinnune          #+#    #+#             */
/*   Updated: 2022/03/07 11:47:57 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	changeprojection(t_data *data)
{
	data->c_x = -10;
	data->c_y = 2;
	data->c_z = 0.1;
	if (data->project == 2)
		data->project = 0;
	else if (data->project == 1)
	{
		data->c_x = -4;
		data->c_y = -4;
		data->project++;
	}
	else if (data->project == 0)
		data->project++;
}

void	put_text(t_data *data)
{
	int	y;

	y = 0;
	mlx_string_put(data->mlx, data->win, 65,
		y += 20, 0xFFFFFF, "How to use?");
	mlx_string_put(data->mlx, data->win, 15,
		y += 35, 0xFFFFFF, "Use arrow keys to move");
	mlx_string_put(data->mlx, data->win, 15,
		y += 30, 0xFFFFFF, "Change projection using 'c' key");
	mlx_string_put(data->mlx, data->win, 15,
		y += 30, 0xFFFFFF, "Change height using + and - keys");
	mlx_string_put(data->mlx, data->win, 15,
		y += 30, 0xFFFFFF, "Adjust color using x and z keys");
	mlx_string_put(data->mlx, data->win, 15,
		y += 30, 0xFFFFFF, "Adjust zoom using a and s keys");
}

void	options(t_data *data, int key)
{
	if (key == 0xff53 || key == 124)
		data->c_x++;
	else if (key == 0xff52 || key == 126)
		data->c_y--;
	else if (key == 0xff51 || key == 123)
		data->c_x--;
	else if (key == 0xff54 || key == 125)
		data->c_y++;
	else if (key == 43 || key == 24)
		data->c_z += 0.1;
	else if (key == 45 || key == 27)
		data->c_z -= 0.1;
	else if (key == 122 || key == 6)
		data->color *= 2;
	else if (key == 120 || key == 7)
		data->color /= 2;
	else if (key == 0 || key == 'a')
		data->zoom *= 2;
	else if (key == 1 || key == 's')
		data->zoom /= 2;
	else if (key == 'v' || key == 9 || key == 53)
		exit(0);
	else if (key == 'c' || key == 8)
		changeprojection(data);
}

int	dokeys(int key, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	options(data, key);
	dopixels(data);
	mlx_clear_window(data->mlx, data->win);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	put_text(data);
	return (1);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n-- > 0)
		*ptr++ = c;
	return (s);
}
