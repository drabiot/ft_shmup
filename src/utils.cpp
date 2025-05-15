/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 13:22:26 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/15 14:11:09 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

double  ft_sin( double x ) {
    while (x > M_PI)
        x -= 2 * M_PI;
    while (x < -M_PI)
        x += 2 * M_PI;

    double x2 = x * x;
    double result = x;

    double term = x;
    term *= -x2 / (2 * 3);       result += term;
    term *= -x2 / (4 * 5);       result += term;
    term *= -x2 / (6 * 7);       result += term;
    term *= -x2 / (8 * 9);       result += term;
    term *= -x2 / (10 * 11);     result += term;

    return result;
}
