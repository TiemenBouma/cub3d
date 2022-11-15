#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

int	get_color_put_pixel(t_put_line *line, int pixel_y, int scaled_pixel_height)
{
	u_int32_t	color;
	int			pixel_in_tex;
	double		ratio;

	ratio = (double)pixel_y / (double)scaled_pixel_height;
	pixel_in_tex = get_pixel(line, ratio);
	color = get_rgba(line->texture->pixels[pixel_in_tex],
			line->texture->pixels[pixel_in_tex + 1],
			line->texture->pixels[pixel_in_tex + 2],
			line->texture->pixels[pixel_in_tex + 3]);
	if ((line->texture_line >= 0 && line->texture_line < 5))
		mlx_put_pixel(line->img, line->vert_line, line->middle
			+ pixel_y, 0xFF0000FF);
	else
		mlx_put_pixel(line->img, line->vert_line, line->middle
			+ pixel_y, color);
	return (0);
}

mlx_texture_t	*set_texture(t_cube *cube, char wall_ori)
{
	if (wall_ori == 'N')
		return (cube->texture_no_wall);
	else if (wall_ori == 'E')
		return (cube->texture_ea_wall);
	else if (wall_ori == 'S')
		return (cube->texture_so_wall);
	else if (wall_ori == 'W')
		return (cube->texture_we_wall);
	error_msg_exit("Error: set_texture: no texture set\n", 1);
	return (NULL);
}

int	calc_texture_line(mlx_texture_t *texture, t_ray *ray)
{
	double	temp;

	if (ray->wall_ori == 'N' || ray->wall_ori == 'S')
		temp = ft_fmod(ray->end_pos.x, 0);
	if (ray->wall_ori == 'E' || ray->wall_ori == 'W')
		temp = ft_fmod(ray->end_pos.y, 0);
	return ((int)(texture->width * temp));
}

int	set_texture_line(t_ray *ray, int width)
{
	int	texture_line;

	if (ray->wall_ori == 'S' || ray->wall_ori == 'E')
		texture_line = width * ft_abs(1 - ft_fmod(ray->wall_x, 0));
	else
		texture_line = width * ft_abs(ft_fmod(ray->wall_x, 0));
	return (texture_line);
}

int	print_line(t_cube *cube, int col, t_ray *ray)
{
	t_put_line	line;
	u_int32_t	pixel_y;
	u_int32_t	scaled_pixel_height;

	pixel_y = 0;
	line.img = cube->g_img_DEMO;
	line.texture = set_texture(cube, ray->wall_ori);
	line.scale = ray->scale;
	line.vert_line = col;
	line.texture_line = set_texture_line(ray, line.texture->width);
	scaled_pixel_height = (int)(line.texture->height * line.scale);
	line.middle = calc_middle_offset(scaled_pixel_height, SCREEN_Y);
	while (pixel_y < scaled_pixel_height)
	{
		if (line.middle + pixel_y > 0 && line.middle + pixel_y < SCREEN_Y)
			get_color_put_pixel(&line, pixel_y, scaled_pixel_height);
		pixel_y++;
	}
	return (0);
}
