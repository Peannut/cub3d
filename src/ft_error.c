/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 16:47:09 by zoukaddo          #+#    #+#             */
/*   Updated: 2023/03/28 16:49:07 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_error(char *msg)
{
	ft_putendl_fd("Error :", 2);
	ft_putendl_fd(msg, 2);
	exit(1);
}
