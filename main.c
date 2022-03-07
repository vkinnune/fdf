/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:34:28 by vkinnune          #+#    #+#             */
/*   Updated: 2022/03/07 11:48:02 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	dopixels(t_data *data)
{
	t_vec3	p[50000];

	clearscreen(data);
	docords(data, p);
	print(data, p);
}

int	main(int argc, char **argv)
{
	t_data	data;
	char	buf[50000];

	if (argc == 1)
		ft_out("Give a file");
	else if (argc > 2)
		ft_out("Too many files");
	ft_memset(buf, 0, 50000);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "FdF");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	data.c_x = -4;
	data.c_y = -4;
	data.c_z = 0.1;
	data.project = 2;
	data.height = 0;
	data.color = 32;
	data.zoom = 1;
	readall(&data, open(argv[1], O_RDONLY), buf);
	makemap(buf, &data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_key_hook(data.win, dokeys, &data);
	mlx_loop(data.mlx);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	clearscreen(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y != 1080)
	{
		x = 0;
		while (x != 1920)
			my_mlx_pixel_put(data, x++, y, 0);
		y++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
