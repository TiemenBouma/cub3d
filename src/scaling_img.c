//dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]
 //dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]

#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <math.h>
#include <stdint.h>

#include <stdio.h>


int	calc_middle_offset(int img_length, int screen_y)
{
	int offset;
	
	img_length /= 2;
	screen_y /= 2;
	offset = screen_y - img_length;

	return offset;
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

int get_color_put_pixel(t_put_line *line, int pixel_y, int scaled_pixel_height)
{
	u_int32_t	color;
	int			middle;
	int			pixel_in_tex;
	double		ratio;

	ratio = (double)pixel_y / (double)scaled_pixel_height;
	middle = calc_middle_offset(scaled_pixel_height, SCREEN_Y);
	pixel_in_tex = get_pixel(line, ratio);
	color = get_rgba(line->texture->pixels[pixel_in_tex], line->texture->pixels[pixel_in_tex + 1], line->texture->pixels[pixel_in_tex + 2], line->texture->pixels[pixel_in_tex + 3]);
	
	if (middle + pixel_y > 0 && middle + pixel_y < SCREEN_Y)
		mlx_put_pixel(line->img, line->vert_line, middle  + pixel_y, color);
	return (0);
}


mlx_texture_t *set_texture(t_cube *cube, t_ray *ray)
{

	if (ray->wall_ori == 'N')
		return (cube->texture_no_wall);
	else if (ray->wall_ori == 'E')
		return (cube->texture_ea_wall);
	else if (ray->wall_ori == 'S')
		return (cube->texture_so_wall);
	else if (ray->wall_ori == 'W')
		return (cube->texture_we_wall);
	printf("\n\nDEBUG: set_texture: no texture set\n\n");
	return (NULL);
}

int calc_text_line(mlx_texture_t *texture, t_ray *ray)
{
	double temp;

	if (ray->wall_ori == 'N' || ray->wall_ori == 'S')
		temp = ft_fmod(ray->end_pos.x, 0);
	if (ray->wall_ori == 'E' || ray->wall_ori == 'W')
		temp = ft_fmod(ray->end_pos.y, 0);
	return (texture->width * temp);
}

int	print_line(t_cube *cube, t_ray *ray, double scale, int vert_line)
{
	t_put_line	line;
	u_int32_t	pixel_y;
	u_int32_t	scaled_pixel_height;

	pixel_y = 0;
	line.img = cube->g_img_DEMO;
	line.texture = set_texture(cube, ray);
	line.scale = scale;
	//printf("DEBUG: scale = %f\n", line.scale);
	line.vert_line = vert_line;
	line.texture_line = calc_text_line(line.texture, ray);
	scaled_pixel_height = line.texture->height * line.scale;
	while (pixel_y < scaled_pixel_height)
	{
		get_color_put_pixel(&line, pixel_y, scaled_pixel_height);
		pixel_y++;
	}
	return (0);
}
