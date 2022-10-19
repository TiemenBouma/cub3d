#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_cube
{
	int		window_x;
	int		window_y;
	int		res_x;
	int		res_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;
	int		floor_rgb[3];
	int		ceilling_rgb[3];

	mlx_image_t	*g_img_floor;
	mlx_image_t	*g_img_ceilling;
	mlx_image_t	*g_img_demo;

	char	**map;
}	t_cube;

typedef struct s_vars
{
	t_cube			*cube;
	mlx_t			*mlx;
}	t_vars;

#endif
