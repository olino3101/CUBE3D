#include "cub3d.h"
#include <stdio.h>

// segfault si je vais dans un coin en reculant

int main()
{
    t_data *data;
    data = init();

    
    mlx_loop_hook(data->mlx, input, data);
    mlx_loop(data->mlx);
    free_ev(data);
    return 0;
}
