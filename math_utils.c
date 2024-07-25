/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naser <naser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:20:22 by naser          #+#    #+#             */
/*   Updated: 2024/07/20 17:08:26 by naser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double value, double inputMin, double inputMax, double outputMax)
{
	double	input_range;
	double	output_range;
	double	mapped_value;
	double	output_min;

	output_min = 0.0;
	input_range = inputMax - inputMin;
	output_range = outputMax - output_min;
	mapped_value = ((value - inputMin) * input_range / output_range) + inputMin;
	return (mapped_value);
}

t_complex	sum_complex(t_complex z, t_complex z2)
{
	t_complex	res;

	res.x = z.x + z2.x;
	res.y = z.y + z2.y;
	return (res);
}

t_complex	square_complex(t_complex z)
{
	t_complex	res;

	res.x = (z.x * z.x) - (z.y * z.y);
	res.y = 2 * z.x * z.y;
	return (res);
}

static	void	atod_helper(char *s, double *res)
{
	double	after;

	after = 1;
	s++;
	if (!*s)
	{
		exit_usuage();
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		after *= 10;
		*res += (*s - '0') / after;
		s++;
	}
}

double	ft_atod(char	*s)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	if (*s < 0)
	{
		s = s + 3;
		sign *= -1;
	}
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while (*s && *s >= '0' && *s <= '9')
	{
		result *= 10;
		result += *s - '0';
		s++;
	}
	if (*s && *s == '.')
		atod_helper(s, &result);
	return (result * sign);
}
