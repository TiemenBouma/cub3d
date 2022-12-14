/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_texture_line2.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tiemen <tiemen@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/17 10:41:47 by tiemen        #+#    #+#                 */
/*   Updated: 2022/11/17 10:41:48 by tiemen        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	calc_middle_offset(int img_length, int screen_y)
{
	int	offset;

	img_length /= 2;
	screen_y /= 2;
	offset = screen_y - img_length;
	return (offset);
}

int	get_pixel(t_put_line *line, double ratio)
{
	int		pixel_y;
	int		sum;

	pixel_y = ratio * line->texture->height;
	sum = pixel_y * line->texture->width;
	sum += line->texture_line;
	sum *= line->texture->bytes_per_pixel;
	return (sum);
}
