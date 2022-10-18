#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_cube
{
	int		res_x;
	int		res_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*s;

	char	**map;
}	t_cube;

typedef struct s_vars
{
	t_cube			*cude;
	mlx_t			*mlx;
}	t_vars;

#endif
