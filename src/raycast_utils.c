#include "../includes/cub3d.h"

float	round_rad(rad rad)
{
	while (rad < 0)
		rad += 2 * PI;
	while (rad > 2 * PI)
		rad -= 2 * PI;
	return (rad);
}

float	ft_fmod(float f, bool exclude_zero)
{
	while (f <= -1 || f >= 1)
	{
		if (f < 0)
			f += 1;
		else
			f -= 1;
	}
	if (exclude_zero == 1 && f == 0)
		f = 1;
	return (f);
}

double	ft_abs(double i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}