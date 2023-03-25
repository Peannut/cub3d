/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:10:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/25 15:15:11 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mouse_event(int x, int y, void *param)
{
	t_data	*data;
	int		mouse_x;
	int		screen_midpoint;

	mouse_x = x;
	screen_midpoint = WIN_WIDTH / 2;
	data = (t_data*)param;
	mlx_mouse_move(data->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	mlx_mouse_hide();
	if (x < screen_midpoint)
		data->player.rotationAngle -= 3 * (PI / 180);
	else if (x > screen_midpoint)
		data->player.rotationAngle += 3 * (PI / 180);
	update(data);
	render(data);
	return (0);
}
