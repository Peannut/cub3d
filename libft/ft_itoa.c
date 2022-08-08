/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 19:36:36 by zoukaddo          #+#    #+#             */
/*   Updated: 2021/11/17 22:00:53 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static	int	ft_len(int j)
{
	int				counter;
	long			i;

	i = j;
	counter = 0;
	if (j < 0)
	{
		i = i * -1;
	}
	while (i >= 10)
	{
		i = i / 10;
		counter++;
	}
	return (counter + 1);
}

static char	*ft_fill(char *ptr, int lenght, long n)
{
	char	b;

	if (n < 0)
	{	
		n = n * -1;
		while (--lenght)
		{
			b = (n % 10) + '0';
			ptr[lenght] = b;
			n = n / 10;
		}
	}
	else
	{	
		while (--lenght >= 0)
		{
			b = (n % 10) + '0';
			ptr[lenght] = b;
			n = n / 10;
		}
	}
	return (ptr);
}

static char	*ft_alloc(int n, size_t lenght)
{
	char	*ptr;
	long	i;

	i = n;
	if (i < 0)
	{
		lenght = lenght + 2;
		ptr = malloc(lenght * sizeof(char));
		if (!ptr)
			return (NULL);
		ptr[0] = '-';
	}
	else
	{	
		lenght = lenght + 1;
		ptr = malloc(lenght * sizeof(char));
		if (!ptr)
			return (NULL);
	}
	ptr[--lenght] = '\0';
	return (ft_fill(ptr, lenght, i));
}

char	*ft_itoa(int n)
{
	int	i;

	i = ft_len(n);
	return (ft_alloc(n, i));
}
