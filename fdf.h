/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkinnune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:34:18 by vkinnune          #+#    #+#             */
/*   Updated: 2022/03/07 11:42:42 by vkinnune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx/mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>

# define WIDTH			1920
# define HEIGHT			1080

typedef struct s_data {
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	void	*mlx;
	void	*win;
	void	*img;
	int		map[40000];
	int		rows;
	int		cols;
	int		height;
	int		fd;
	int		project;
	int		c_y;
	int		c_x;
	double	zoom;
	double	c_z;
	double	color;
	int		colors[2];
	bool	fade;
}				t_data;

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec3;

void	drawline(int x1, int y1, int xy2[2], t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	clearscreen(t_data *data);
void	docords(t_data *data, t_vec3 *p);
void	iso(t_data *data, t_vec3 p, t_vec3 *temp);
void	print(t_data *data, t_vec3 *p);
void	makemap(char *buf, t_data *data);
void	readall(t_data *data, int fd, char *buf);
int		dokeys(int key, void *param);
void	changeprojection(t_data *data);
void	put_text(t_data *data);
void	options(t_data *data, int key);
void	dopixels(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_out(char *reason);
int		ft_isdigit(int c);
void	printcols(t_data *data, t_vec3 *p, int i);
void	printrows(t_data *data, t_vec3 *p, int i);
void	*ft_memset(void *s, int c, size_t n);
#endif

