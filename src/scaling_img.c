//dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]
 //dest_pixel [x,y] = src_pixel [x * x_scale_factor, y * y_scale_factor]

#include "../includes/MLX42/include/MLX42/MLX42.h"
#include "../includes/cub3d.h"
#include <math.h>

#include <stdio.h>

typedef struct s_put_pixel
{
	mlx_texture_t	*texture;
	double			scale;
	u_int32_t		color;
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
	u_int32_t	scaled_i;

	temp = i / scale;
	scaled_i = round(temp);//i;// i / scale;//
	return ((vert_line + ((texture->height / 2 + scaled_i) * texture->width)) * texture->bytes_per_pixel);
}

int get_color_put_pixel(t_pov *pov, mlx_texture_t *texture, mlx_image_t *img, int x_screen, int x_wall, int i, double scale)
{
	u_int32_t	color;
	u_int32_t	middle;
	middle = texture->height / 2;
	int			pixel;
	(void)pov;
	
	pixel = gp(texture, x_wall, i, scale);
	color = get_rgba(texture->pixels[pixel], texture->pixels[pixel + 1], texture->pixels[pixel + 2], texture->pixels[pixel + 3]);
	mlx_put_pixel(img, x_screen, middle  + i, color);
	//mlx_put_pixel(img, x, middle  + i, 0x00FF00FF);
	return (0);
}

// int	print_line(t_pov *pov, mlx_texture_t *texture, mlx_image_t *img, double scale, int vert_line)
// {
// 	u_int32_t	i;
// 	//u_int32_t	color;

// 	(void)scale;

// 	i = 0;

// 	u_int32_t	scaled_pixel_height;

// 	scaled_pixel_height = texture->height * scale;

// 	while (i < scaled_pixel_height / 2)//(i < texture->height / 2)
// 	{
		
// 		//color = get_rgba(texture->pixels[gp(middle + scaled_i, w, x, bpp)], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 1], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 2], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 3]);
// 		get_color_put_pixel(texture, img, vert_line, i, scale);
// 		get_color_put_pixel(texture, img, vert_line, i * (-1), scale);
// 		i++;
// 	}
// 	return (0);
// }

int	calc_x_wall(t_ray *ray, int texture_width)
{
	double	temp_d;

	if (ray->wall_ori == 0 || ray->wall_ori == 2)
		temp_d = ft_fmod(ray->end_pos.x, 0);
	else if (ray->wall_ori == 1 || ray->wall_ori == 3)
		temp_d = ft_fmod(ray->end_pos.y, 0);
	else
		return (-1);
	
	return (temp_d * texture_width);
}

int	print_line(t_pov *pov, mlx_texture_t *texture[4], mlx_image_t *img , int x_screen)
{
	u_int32_t	i;
	double		scale;
	u_int32_t	scaled_pixel_height;
	int			ori;
	int			x_wall;

	ori = pov->rays[x_screen].wall_ori;
	x_wall = calc_x_wall(&pov->rays[x_screen], texture[ori]->width);
	i = 0;
	scale = 1 / pov->rays[x_screen].dist;

	scaled_pixel_height = texture[ori]->height * scale;

	while (i < scaled_pixel_height / 2)//(i < texture->height / 2)
	{
		
		//color = get_rgba(texture->pixels[gp(middle + scaled_i, w, x, bpp)], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 1], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 2], texture->pixels[gp(middle + scaled_i, w, x, bpp) + 3]);
		get_color_put_pixel(pov, texture[ori], img, x_screen, x_wall, i, scale);
		get_color_put_pixel(pov, texture[ori], img, x_screen, x_wall, i * (-1), scale);
		i++;
	}
	return (0);
}


int demo_scaling(mlx_t *mlx, t_cube *cube)
{
	//int vert_line = 100;

	cube->texture_DEMO = mlx_load_png("pics/greystone.png");//(cube->no);//
	cube->g_img_DEMO = mlx_new_image(mlx, 500, 500);//(mlx, cube->texture_DEMO->width, cube->texture_DEMO->height);
	//print_more_lines(cube->texture_DEMO, cube->g_img_DEMO, 0.9, 10);
	//cube->g_img_DEMO = mlx_texture_to_image(mlx, cube->texture_DEMO);
	//print_line(cube->texture_DEMO, cube->g_img_DEMO, 1.0, 10);
	mlx_image_to_window(mlx, cube->g_img_DEMO, SCREEN_X / 2, calc_middle_offset(cube->texture_DEMO->height, SCREEN_Y));
	return (0);
}

	// printf("DEBUG\n");`
	  

