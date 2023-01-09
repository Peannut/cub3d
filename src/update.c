/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:23:13 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/01/09 04:57:48 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void update(t_data *data) {
    t_player *player = &data->player;
    char **map = data->map;

    printf("before x: %f, y: %f\n", player->x, player->y);
    // update player's rotation
    player->rotationAngle += player->turnDirection * player->rotationSpeed;

    // update player's position
    double moveStep = player->walkDirection * player->moveSpeed;
    double newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
    double newPlayerY = player->y + sin(player->rotationAngle) * moveStep;

    player->x = newPlayerX;
    player->y = newPlayerY;
    printf("after x: %f, y: %f\n", player->x, player->y);
}

void render(t_data *data) {
    t_player *player = &data->player;

    draw_map(data);
    draw_line(data);
    draw_grid(data);
    draw_player(data, 0);
    castAllRays(data);
    mlx_do_sync(data->mlx);
}
