/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 20:02:57 by zoukaddo          #+#    #+#             */
/*   Updated: 2021/11/10 19:16:41 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	result;
	int				sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = sign * -1;
		str++;
	}
	while ((*str != '\0') && (*str >= '0') && (*str <= '9'))
	{
		result = result * 10 + (*str - 48);
		str++;
		if (result > LONG_MAX)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
	}
	return ((int)(result * sign));
}
