/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 13:01:48 by oandelin          #+#    #+#             */
/*   Updated: 2023/03/07 13:42:42 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	ft_atoi
//	converts ascii input *str to an int and returns the int value
int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	long	dig;
	long	sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		dig = str[i] - 48;
		res = res * 10 + dig;
		i++;
	}
	return (res * sign);
}
