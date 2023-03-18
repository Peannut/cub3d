/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 19:10:45 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/17 11:08:06 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	mouse_event(int x, int y, void *param)
{
	t_data *data = (t_data*)param;
	int mouse_x = x;
	int screen_midpoint = WIN_WIDTH / 2;
	mlx_mouse_move(data->mlx_win, WIN_WIDTH/2, WIN_HEIGHT/2);
	mlx_mouse_hide();

	if (x < screen_midpoint)
		data->player.rotationAngle -= 3 * (PI / 180);
	else if (x > screen_midpoint)
		data->player.rotationAngle += 3 * (PI / 180);
	update(data);
	render(data);
	return (0);
}