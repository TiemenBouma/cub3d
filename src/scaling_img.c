//dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]
 //dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]

#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <math.h>
#include <stdint.h>

#include <stdio.h>

typedef struct s_put_pixel
{
	mlx_texture_t	*texture;
	double			scale;
	unsigned int		color;
	int				x;
	int				y;
	int				bpp;
	int				orginal_y;
	int				middle;

} t_put_pixel;

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

int	gp(mlx_texture_t *texture, int vert_line, int i, double scale)
{
	double		temp;
	unsigned int	scaled_i;

	temp = i / scale;
	scaled_i = round(temp);//i;// i / scale;//
	return ((vert_line + ((texture->height / 2 + scaled_i) * texture->width)) * texture->bytes_per_pixel);
}

int get_color_put_pixel(mlx_texture_t *texture, mlx_image_t *img, int x, int i, double scale)
{
	//int			bpp;
	//int			w;
	unsigned int	color;
	//unsigned int	scaled_i;
	//double		temp;
	unsigned int	middle;
	middle = texture->height / 2;

	//temp = i / scale;
	//scaled_i = round(temp);//i;// i / scale;//
	//w = texture->width;
	//bpp = texture->bytes_per_pixel;
	//color = get_rgba(texture->pixels[gp(middle + scaled_i, w, x, bpp)], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 1], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 2], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 3]);
	color = get_rgba(texture->pixels[gp(texture, x, i, scale)], texture->pixels[gp(texture, x, i, scale) + 1], texture->pixels[gp(texture, x, i, scale) + 2], texture->pixels[gp(texture, x, i, scale) + 3]);
	mlx_put_pixel(img, x, middle  + i, color);
	return (0);
}

int	print_line(mlx_texture_t *texture, mlx_image_t *img, double scale, int vert_line)
{
	unsigned int	i;
	//unsigned int	color;

	(void)scale;

	i = 0;

	unsigned int	scaled_pixel_height;

	scaled_pixel_height = texture->height * scale;

	while (i < scaled_pixel_height / 2)//(i < texture->height / 2)
	{
		
		//color = get_rgba(texture->pixels[gp(middle + scaled_i, w, x, bpp)], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 1], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 2], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 3]);
		get_color_put_pixel(texture, img, vert_line, i, scale);
		get_color_put_pixel(texture, img, vert_line, i * (-1), scale);
		i++;
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
	//int vert_line = 100;

	cube->texture_DEMO = mlx_load_png("pics/greystone.png");//(cube->no);//
	cube->g_img_DEMO = mlx_new_image(mlx, 500, 500);//(mlx, cube->texture_DEMO->width, cube->texture_DEMO->height);
	print_more_lines(cube->texture_DEMO, cube->g_img_DEMO, 0.9, 64);
	//cube->g_img_DEMO = mlx_texture_to_image(mlx, cube->texture_DEMO);
	//print_line(cube->texture_DEMO, cube->g_img_DEMO, 1.0, 10);
	mlx_image_to_window(mlx, cube->g_img_DEMO, SCREEN_X / 2, calc_middle_offset(cube->texture_DEMO->height, SCREEN_Y));
	return (0);
}

	// printf("DEBUG\n");`
	  

