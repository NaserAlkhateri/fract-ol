/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naser <naser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:29:13 by naser          #+#    #+#             */
/*   Updated: 2024/07/20 18:26:30 by naser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	render_mandelbrot(t_data *fractol)
{
	int	x;
	int	y;

	if (ft_strncmp("julia", fractol->title, 5) == 0)
		render_julia(fractol);
	y = 0;
	while (y < HEIGHT - 1)
	{
		x = 0;
		while (x < WIDTH - 1)
		{
			handle_pixel(x, y, fractol);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->mlx, fractol->mlx_win, fractol->img, 0, 0);
	mlx_key_hook(fractol->mlx_win, handle_key, fractol);
	mlx_hook(fractol->mlx_win, 17, 1L << 17, handle_close, fractol);
	mlx_hook(fractol->mlx_win, 4, 1L << 2, handle_button, fractol);
	mlx_loop(fractol->mlx);
}

void	window_setup(t_data *fractol)
{
	fractol->mlx = mlx_init();
	if (!fractol->mlx)
		return (perror("mlx init Malloc error"), exit(1));
	fractol->mlx_win = mlx_new_window(fractol->mlx, WIDTH,
			HEIGHT, fractol->title);
	if (!fractol->mlx_win)
	{
		if (fractol->mlx)
			free(fractol->mlx);
		return (perror("mlx window Malloc error"), exit(1));
	}
	fractol->img = mlx_new_image(fractol->mlx, WIDTH, HEIGHT);
	if (!fractol->img)
	{
		mlx_destroy_window(fractol->mlx, fractol->mlx_win);
		if (fractol->mlx)
			free(fractol->mlx);
		return (perror("mlx img Malloc error"), exit(1));
	}
	fractol->addr = mlx_get_data_addr(fractol->img, &fractol->bpp,
			&fractol->size_line, &fractol->endian);
	fractol->x_shift = 0.0;
	fractol->y_shift = 0.0;
	fractol->zoom = 1.0;
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	handle_pixel(int x, int y, t_data *fractol)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	z.x = 0.0;
	z.y = 0.0;
	i = 0;
	c.x = (map(x, -2, 2, WIDTH) * fractol->zoom) + fractol->x_shift;
	c.y = (map(y, 2, -2, HEIGHT) * fractol->zoom) + fractol->y_shift;
	while (i < (fractol->max_iterations))
	{
		z = sum_complex(square_complex(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractol->escape_value)
		{
			color = map(i, BLACK, WHITE, (fractol->max_iterations));
			my_mlx_pixel_put(fractol, x, y, color);
			return ;
		}
		i++;
	}
	my_mlx_pixel_put(fractol, x, y, RED);
}

void	draw_mandelbrot(t_data *fractol)
{
	fractol->max_iterations = ITER;
	fractol->escape_value = 4;
	window_setup(fractol);
	render_mandelbrot(fractol);
}
