/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoukaddo <zoukaddo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 19:07:29 by zoukaddo          #+#    #+#             */
/*   Updated: 2021/11/19 16:53:59 by zoukaddo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;

	head = NULL;
	if (lst)
	{
		head = ft_lstnew(f(lst->content));
		if (!head)
			return (NULL);
		lst = lst->next;
		while (lst)
		{
			new = malloc(sizeof(t_list));
			if (!new)
			{
				ft_lstclear(&head, del);
				return (NULL);
			}
			new->next = NULL;
			ft_lstadd_back(&head, new);
			new->content = f(lst->content);
			lst = lst->next;
		}
	}
	return (head);
}
