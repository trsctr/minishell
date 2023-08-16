/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:59:09 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/13 15:46:54 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_lstadd_front
// adds the new node *new to the beginning of list *lst
// returns nothing
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
