/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naser <naser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:01:41 by naser          #+#    #+#             */
/*   Updated: 2024/07/20 18:26:43 by naser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	handle_pixel_julia(int x, int y, t_data *fractol)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (map(x, -2, 2, WIDTH) * fractol->zoom) + fractol->x_shift;
	z.y = (map(y, 2, -2, HEIGHT) * fractol->zoom) + fractol->y_shift;
	c.x = fractol->x_julia;
	c.y = fractol->y_julia;
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

void	render_julia(t_data *fractol)
{
	int	x;
	int	y;

	y = -1;
	while (y++ < HEIGHT - 1)
	{
		x = -1;
		while (x++ < WIDTH - 1)
		{
			handle_pixel_julia(x, y, fractol);
		}
	}
	mlx_put_image_to_window(fractol->mlx, fractol->mlx_win, fractol->img, 0, 0);
	mlx_key_hook(fractol->mlx_win, handle_key, fractol);
	mlx_hook(fractol->mlx_win, 17, 1L << 17, handle_close, fractol);
	mlx_hook(fractol->mlx_win, 4, 1L << 2, handle_button, fractol);
	mlx_loop(fractol->mlx);
}

static	void	draw_julia(t_data *fractol)
{
	fractol->max_iterations = ITER;
	fractol->escape_value = 4;
	window_setup(fractol);
	render_julia(fractol);
}

static	void	check_julia_param(double x, double y)
{
	if (x > 2 || x < -2)
	{
		ft_putstr_fd("Invalid X Value!\nValues: -2 >= or <= 2\n", 2);
		exit_usuage();
	}
	else if (y > 2 || y < -2)
	{
		ft_putstr_fd("Invalid Y Value!\nValues: -2 >= or <= 2\n", 2);
		exit_usuage();
	}
}

int	main(int argc, char **argv)
{
	t_data	fractol;

	if (argc < 2)
		exit_usuage();
	if (ft_strncmp("mandelbrot", argv[1], 10) == 0 && argc == 2)
	{
		fractol.title = argv[1];
		draw_mandelbrot(&fractol);
	}
	else if (ft_strncmp("julia", argv[1], 5) == 0 && argc == 4)
	{
		fractol.title = argv[1];
		fractol.x_julia = ft_atod(*(argv + 2));
		fractol.y_julia = ft_atod(*(argv + 3));
		check_julia_param(fractol.x_julia, fractol.y_julia);
		draw_julia(&fractol);
	}
	else
		exit_usuage();
	return (0);
}
