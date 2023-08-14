/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oandelin <oandelin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:37:51 by oandelin          #+#    #+#             */
/*   Updated: 2022/12/09 17:05:25 by oandelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// ft_countdigits
// counts how many digits there are in the int n
// need to know this allocate correct amount of memory for the string
// returns the amount of digits
static	int	ft_countdigits(int n)
{
	int	digits;

	digits = 0;
	while (n)
	{	
		n /= 10;
		digits++;
	}
	return (digits);
}

// ft_getstring
// a helper function used to write the correct ASCII
// characters to the string *dest once the memory has been allocated
// in the main function
static	char	*ft_getstring(char *dest, int n, int digits)
{
	dest[digits] = '\0';
	if (n < 0)
	{
		dest[0] = '-';
		n = n * -1;
	}
	while (n)
	{	
		digits--;
		dest[digits] = (n % 10) + '0';
		n /= 10;
	}
	return (dest);
}

// ft_itoa
// allocates memory for *str and then writes ASCII conversion of int n
// returns *str
char	*ft_itoa(int n)
{
	char	*str;
	int		digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	digits = ft_countdigits(n);
	if (n < 0)
		digits++;
	str = (char *) ft_calloc(digits + 1, sizeof(char));
	if (!str)
		return (NULL);
	return (ft_getstring(str, n, digits));
}
