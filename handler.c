/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naser <naser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 11:54:26 by naser          #+#    #+#             */
/*   Updated: 2024/07/20 17:39:54 by naser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	handle_button(int button, int x, int y, t_data *fractol)
{
	(void)x;
	(void)y;
	if (button == SCROLL_UP)
		fractol->zoom *= 0.95;
	else if (button == SCROLL_DOWN)
		fractol->zoom *= 1.05;
	render_mandelbrot(fractol);
	return (0);
}

int	handle_key(int key, t_data *fractol)
{
	if (key == ESC_KEY)
	{
		mlx_destroy_image(fractol->mlx, fractol->img);
		mlx_destroy_window(fractol->mlx, fractol->mlx_win);
		if (fractol->mlx)
			free(fractol->mlx);
		exit(0);
	}
	else if (key == RIGHT_ARROW)
		fractol->x_shift -= (0.5 * fractol->zoom);
	else if (key == LEFT_ARROW)
		fractol->x_shift += (0.5 * fractol->zoom);
	else if (key == UP_ARROW)
		fractol->y_shift -= (0.5 * fractol->zoom);
	else if (key == DOWN_ARROW)
		fractol->y_shift += (0.5 * fractol->zoom);
	render_mandelbrot(fractol);
	return (0);
}

int	handle_close(t_data *fractol)
{
	mlx_destroy_image(fractol->mlx, fractol->img);
	mlx_destroy_window(fractol->mlx, fractol->mlx_win);
	if (fractol->mlx)
		free(fractol->mlx);
	exit(0);
	return (0);
}
//linux
//mlx_destroy_display(fractol->mlx);