/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:34:36 by vkinnune          #+#    #+#             */
/*   Updated: 2022/03/01 16:45:05 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	ft_out(char *reason)
{
	char	*p;

	p = reason;
	while (*p)
	{
		write(1, p, 1);
		p++;
	}
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

void	readall(t_data *data, int fd, char *buf)
{
	int	i;

	i = 0;
	if (read(fd, &buf[1000 * i], 1000) == -1)
		ft_out("Not a valid file");
	i++;
	while (read(fd, &buf[1000 * i], 1000) && i != 44)
		i++;
	data->cols = 0;
	data->rows = 1;
	data->height = 0;
}

char	*putnumbers(char *p, t_data *data)
{
	bool	minus;

	minus = false;
	if (*p == '-')
	{
		minus = true;
		p++;
	}
	while (ft_isdigit(*p))
	{
		data->map[(data->cols - 1) + data->rows] *= 10;
		data->map[(data->cols - 1) + data->rows] += *p - '0';
		p++;
	}
	if (minus)
		data->map[(data->cols - 1) + data->rows] *= -1;
	if (data->map[(data->cols - 1) + data->rows] > data->height)
		data->height = data->map[(data->cols - 1) + data->rows];
	return (p);
}

void	makemap(char *buf, t_data *data)
{
	char	*p;

	p = buf;
	while (*p)
	{
		if (*p == ' ')
		{
			while (p[1] == ' ')
				p++;
			data->cols++;
			p++;
		}
		else if (*p == '\n')
		{
			data->rows++;
			p++;
			if (*p == 0 || *p == '\n')
				data->rows--;
		}
		else if (ft_isdigit(*p) || *p == '-')
			p = putnumbers(p, data);
		else
			ft_out("Error on file");
	}
	data->cols = (data->cols / data->rows) + 1;
}
