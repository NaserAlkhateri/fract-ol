/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naser <naser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:29:19 by naser          #+#    #+#             */
/*   Updated: 2024/07/20 18:04:22 by naser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# ifdef __APPLE__
#  include "mlx/mlx.h"
#  define ESC_KEY 53
#  define RIGHT_ARROW 124
#  define LEFT_ARROW 123
#  define UP_ARROW 126
#  define DOWN_ARROW 125
# else
#  include "mlx_linux/mlx.h"
#  include <X11/keysym.h>
#  define ESC_KEY 65307
#  define RIGHT_ARROW XK_Right
#  define LEFT_ARROW XK_Left
#  define UP_ARROW XK_Up
#  define DOWN_ARROW XK_Down
# endif
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define HEIGHT 1000
# define WIDTH	1000
# define BLACK 0x000000
# define NAVY 0x000080
# define BLUE 0x0000FF
# define GREEN 0x008000
# define LIME 0x00FF00
# define AQUA 0x00FFFF
# define RED 0xFF0000
# define PURPLE 0x800080
# define FUCHSIA 0xFF00FF
# define YELLOW 0xFFFF00
# define WHITE 0xFFFFFF
# define ITER 286

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	char	*title;
	int		max_iterations;
	int		escape_value;
	double	x_shift;
	double	y_shift;
	double	zoom;
	double	x_julia;
	double	y_julia;

}				t_data;
typedef struct s_complex
{
	double	x;
	double	y;
}				t_complex;
void		exit_usuage(void);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_putstr_fd(char *s, int fd);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
void		window_setup(t_data *fractol);
double		map(double value, double inputMin, double inputMax,
				double outputMax);
t_complex	square_complex(t_complex z);
t_complex	sum_complex(t_complex z, t_complex z2);
void		draw_mandelbrot(t_data *fractol);
void		handle_pixel(int x, int y, t_data *fractol);
int			handle_key(int key, t_data *fractol);
int			handle_close(t_data *fractol);
int			handle_button(int button, int x, int y, t_data *fractol);
void		render_mandelbrot(t_data *fractol);
double		ft_atod(char	*s);
void		render_julia(t_data *fractol);
#endif