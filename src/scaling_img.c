//dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]
 //dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]

#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <math.h>

#include <stdio.h>


int	calc_middle_offset(int img_length, int screen_y)
{
	int offset;
	
	img_length /= 2;
	screen_y /= 2;
	offset = screen_y - img_length;

	return offset;
}
//get_pixel
// int	gp(int h, int w, int vert_line, int bpp)
// {
// 	return ((vert_line + (h * w)) * bpp);
// }

int	get_pixel(t_put_line *line, int pixel_y)
{
	double		temp;
	double		temp_s;
	u_int32_t	scaled_pixel_y;

	int sum;

	if (line->scale > 1)
		temp_s = 1 / line->scale;
	else
		temp_s = line->scale;
	temp = pixel_y * temp_s;
	scaled_pixel_y = round(temp);//i;// i / scale;//
	
	sum = scaled_pixel_y * line->texture->width;
	sum = sum + line->texture_line;
	sum = sum * line->texture->bytes_per_pixel;
	return (sum);
	
	
	//return ((vert_line + ((texture->height / 2 + scaled_y) * texture->width)) * texture->bytes_per_pixel);
}

int get_color_put_pixel(t_put_line *line, int pixel_y, int scaled_pixel_height)
{
	u_int32_t	color;
	u_int32_t	middle;
	int			pixel_in_tex;
	middle = calc_middle_offset(scaled_pixel_height, SCREEN_Y);//SCREEN_Y / 2;//texture->height / 2;
	pixel_in_tex = get_pixel(line, pixel_y);
	color = get_rgba(line->texture->pixels[pixel_in_tex], line->texture->pixels[pixel_in_tex + 1], line->texture->pixels[pixel_in_tex + 2], line->texture->pixels[pixel_in_tex + 3]);
	
	mlx_put_pixel(line->img, line->ver_line, middle  + pixel_y, color);
	//mlx_put_pixel(img, x, middle  + i, 0x00FF00FF);
	return (0);
}


mlx_texture_t *set_texture(t_cube *cube, t_ray *ray)
{

	if (ray->wall_ori == 'N')
		return (cube->texture_no_wall);
	if (ray->wall_ori == 'E')
		return (cube->texture_ea_wall);
	if (ray->wall_ori == 'S')
		return (cube->texture_so_wall);
	if (ray->wall_ori == 'W')
		return (cube->texture_we_wall);
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
	t_put_line line;
	u_int32_t	pixel_y;
	//u_int32_t	color;
	//mlx_image_t *img;
//	mlx_texture_t *texture;
	u_int32_t	scaled_pixel_height;

	pixel_y = 0;
	line.img = cube->g_img_DEMO;
	line.texture = set_texture(cube, ray);
	line.scale = scale; line.scale *= 4;//TEStING
	printf("DEBUG: scale = %f\n", line.scale);
	line.ver_line = vert_line;
	line.texture_line = calc_text_line(line.texture, ray);
	scaled_pixel_height = line.texture->height * line.scale;
	while (pixel_y < scaled_pixel_height)//(i < texture->height / 2)
	{
		
		//color = get_rgba(texture->pixels[gp(middle + scaled_i, w, x, bpp)], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 1], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 2], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 3]);
		get_color_put_pixel(&line, pixel_y, scaled_pixel_height);
		//get_color_put_pixel(&line, line.img, pixel_y, -1);
		pixel_y++;
	}
	return (0);
}

// int print_more_lines(mlx_texture_t *texture, mlx_image_t *img, double scale, int vert_lines)
// {
// 	int i = 0;

// 	while (i < vert_lines)
// 	{
// 		print_line(texture, img, scale, i);
// 		i++;
// 	}
// 	return (0);
// }

// int demo_scaling(mlx_t *mlx, t_cube *cube)
// {
// 	//int vert_line = 100;

// 	cube->texture_DEMO = mlx_load_png("pics/greystone.png");//(cube->no);//
// 	cube->g_img_DEMO = mlx_new_image(mlx, 500, 500);//(mlx, cube->texture_DEMO->width, cube->texture_DEMO->height);
// 	print_more_lines(cube->texture_DEMO, cube->g_img_DEMO, 0.9, 10);
// 	//cube->g_img_DEMO = mlx_texture_to_image(mlx, cube->texture_DEMO);
// 	//print_line(cube->texture_DEMO, cube->g_img_DEMO, 1.0, 10);
// 	mlx_image_to_window(mlx, cube->g_img_DEMO, SCREEN_X / 2, calc_middle_offset(cube->texture_DEMO->height, SCREEN_Y));
// 	return (0);
// }

	// printf("DEBUG\n");`
	  

