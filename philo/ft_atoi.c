/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperinch <jperinch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 08:26:28 by jperinch          #+#    #+#             */
/*   Updated: 2023/07/28 12:48:17 by jperinch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosphers.h"

int	spacexsign(const char *nptr, int i, int *sign)
{
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoi(const char *nptr, int *status, int sign)
{
	int			i;
	long long	result;

	result = 0;
	i = spacexsign(nptr, 0, &sign);
	while (nptr[i] != '\0')
	{
		
		if (nptr[i] >= '0' && nptr[i] <= '9')
			result = result * 10 + (nptr[i] - '0');
		else
			(*status) = 1;
		if (sign == -1 && result > 2147483648)
		{
			(*status) = 1;
			return (result);
		}
		if (sign == 1 && result > 2147483647)
		{
			(*status) = 1;
			return (result);
		}
		i++;
	}
	return (result * sign);
}
