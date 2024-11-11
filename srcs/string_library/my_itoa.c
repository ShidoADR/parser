/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariandr <hariandr@student.42antananariv>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 13:09:28 by hariandr          #+#    #+#             */
/*   Updated: 2024/11/11 13:11:10 by hariandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	*my_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*desti;
	char	*srci;

	desti = (char *)dest;
	srci = (char *)src;
	i = 0;
	if (dest == ((void *)0) && src == ((void *)0))
		return (dest);
	while (n--)
	{
		desti[i] = srci[i];
		i++;
	}
	return (dest);
}

static int	get_lenght(int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while ((n / 10) != 0)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

static char	*get_string(int n, int len, char *result)
{
	int	mod;

	mod = 10;
	if (n < 0)
	{
		n *= -1;
		len += 1;
		result[0] = '-';
		result[len] = '\0';
		while (len-- > 1)
		{
			result[len] = (n % mod) + '0';
			n /= 10;
		}
	}
	else
	{
		result[len] = '\0';
		while (len--)
		{
			result[len] = (n % mod) + '0';
			n /= 10;
		}
	}
	return (result);
}

char	*my_itoa(int n)
{
	char	*result;
	int		len;

	len = get_lenght (n);
	if (n == -2147483648)
	{
		result = malloc(12);
		if (!result)
			return (0);
		my_memcpy (result, "-2147483648", 11);
		result[11] = '\0';
		return (result);
	}
	else if (n < 0)
		result = malloc ((sizeof(char) * len) + 2);
	else
		result = malloc ((sizeof(char) * len) + 1);
	if (!result)
		return (0);
	result = get_string (n, len, result);
	return (result);
}
