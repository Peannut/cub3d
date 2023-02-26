/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouhaga <abouhaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 15:23:13 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/02/26 22:51:21 by abouhaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void update(t_data *data) {
//     t_player *player = &data->player;
//     char **map = data->map;

//     // printf("before x: %f, y: %f\n", player->x, player->y);
//     // update player's rotation
//     player->rotationAngle += player->turnDirection * player->rotationSpeed;

//     // update player's position
//     double moveStep = player->walkDirection * player->moveSpeed;
//     double newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
//     double newPlayerY = player->y + sin(player->rotationAngle) * moveStep;

//     player->x = newPlayerX;
//     player->y = newPlayerY;
//     // printf("after x: %f, y: %f\n", player->x, player->y);
//     // printf("rotation angel val:%f\n",player->rotationAngle);
// }

void update(t_data *data) {
    t_player *player = &data->player;
    char **map = data->info.map;

    // update player's rotation
    player->rotationAngle += player->turnDirection * player->rotationSpeed;

    // update player's position
    double moveStep = player->walkDirection * player->moveSpeed;
    double sidewaysStep = player->sidewaysDirection * player->moveSpeed;

    double newPlayerX = player->x + cos(player->rotationAngle) * moveStep;
    double newPlayerY = player->y + sin(player->rotationAngle) * moveStep;
    newPlayerX += -sin(player->rotationAngle) * sidewaysStep;
    newPlayerY += cos(player->rotationAngle) * sidewaysStep;

    player->x = newPlayerX;
    player->y = newPlayerY;
}
void render(t_data *data) {
    t_player *player = &data->player;

    draw_map(data);
    draw_line(data);
    draw_grid(data);
    draw_player(data, 0);
    castAllRays(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->frame, 0, 0);
    mlx_do_sync(data->mlx);
}
