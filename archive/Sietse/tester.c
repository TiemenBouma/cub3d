#include "includes/cub3d.h"

void	test_check_if_hit()
{
	char*	map[] = {	"111111111111",
						"100000000001",
						"100000P00001",
						"100000000001",
						"111111111111"};
	t_axis	ray;
	float	angle;

	printf("\ntest 1:\n");
	ray.x = 3;
	ray.y = 4;
	angle = 0;
	if (check_if_hit(ray, angle, map) == 1)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 2:\n");
	ray.x = 11;
	ray.y = 2;
	angle = 0;
	if (check_if_hit(ray, angle, map) == 1)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 3:\n");
	ray.x = 11;
	ray.y = 2;
	angle = 0.3 * PI;
	if (check_if_hit(ray, angle, map) == 1)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 4:\n");
	ray.x = 11;
	ray.y = 2.1;
	angle = PI;
	if (check_if_hit(ray, angle, map) == 0)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 5:\n");
	ray.x = 1;
	ray.y = 1;
	angle = 0.1 * PI;
	if (check_if_hit(ray, angle, map) == 0)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 6:\n");
	ray.x = 1;
	ray.y = 1;
	angle = PI * 0.75;
	if (check_if_hit(ray, angle, map) == 1)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 7:\n");
	ray.x = 4;
	ray.y = 1;
	angle = 0.5 * PI;
	if (check_if_hit(ray, angle, map) == 0)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 8:\n");
	ray.x = 4;
	ray.y = 1;
	angle = 1.5 * PI;
	if (check_if_hit(ray, angle, map) == 1)
		printf("Success!\n");
	else
		printf("Failure.\n");

	printf("\ntest 8:\n");
	ray.x = 4.623607;
	ray.y = 5.082654;
	angle = 0.6999999 * PI;
	printf("data on map: %c\n", map[(int)ray.y][(int)ray.x]);
	if (check_if_hit(ray, angle, map) == 0)
		printf("Success!\n");
	else
		printf("Failure.\n");
}

int	main()
{
	test_check_if_hit();
}