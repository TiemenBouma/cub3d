//dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]
 //dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]

#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"

int	calc_middle_offset(int img_length, int screen_y)
{
	int offset;
	
	img_length /= 2;
	screen_y /= 2;
	offset = screen_y - img_length;

	return offset;
}

int	print_line(mlx_texture_t *texture, mlx_image_t *img, double scale, int vert_line)
{
	u_int8_t	i;
	u_int32_t color;

	(void)scale;
	i = 0;
	while (i < texture->height * 4)
	{
		color = get_rgba(texture->pixels[vert_line * i + 3], texture->pixels[vert_line * i + 2], texture->pixels[vert_line * i + 1], texture->pixels[vert_line * i]);
		mlx_put_pixel(img, i, vert_line, color);
		i += 4;
	}
	return (0);
}

int print_more_lines(mlx_texture_t *texture, mlx_image_t *img, double scale, int vert_lines)
{
	int i = 0;

	while (i < vert_lines)
	{
		print_line(texture, img, scale, i);
		i++;
	}
	return (0);
}

int demo_scaling(mlx_t *mlx, t_cube *cube)
{
	int vert_line = 500;

	cube->texture_DEMO = mlx_load_png("pics/greystone.png");//(cube->no);//
	cube->g_img_DEMO = mlx_new_image(mlx, cube->texture_DEMO->width, cube->texture_DEMO->height);
	print_more_lines(cube->texture_DEMO, cube->g_img_DEMO, 1.0, 100);
	//cube->g_img_DEMO = mlx_texture_to_image(mlx, cube->texture_DEMO);
	
	mlx_image_to_window(mlx, cube->g_img_DEMO, vert_line, calc_middle_offset(cube->texture_DEMO->height, SCREEN_Y));
	return (0);
}


