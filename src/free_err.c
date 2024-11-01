#include "cub3d.h"

void free_arri(int **arr, int size)
{
	int i;

	i = 0;
	while (i != size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
void	free_ev(t_data *data)
{
	free_arri(data->map, HMAP);
	free(data);
}