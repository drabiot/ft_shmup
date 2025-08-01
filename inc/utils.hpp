/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:08:31 by tchartie          #+#    #+#             */
/*   Updated: 2025/08/01 16:01:30 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <string>
# include <ncursesw/ncurses.h>
# include <unistd.h>
# include <cstdlib>
# include <ctime>
# include <sstream>
# include <vector>
# include <iomanip>
# include <fstream>

# include "color.hpp"

# define AND	<<
# define PRINT	std::cout AND
# define ERROR	std::cerr AND
# define NLINE	PRINT std::endl
# define ENDL	AND std::endl
# define CENDL	AND BASE_COLOR ENDL
# define TAB	"\t"

typedef std::string str;

# define cref(type) const type &
# define ref(type) type &

/* Window */
# define HEIGHT			40
# define LENGTH 		(40 + 20) * 2.5
# define WIDTH			300
# define FRAME_DELAY	16000
# define M_PI			3.14159265

/* Background */
# define SPACE          ' '
# define BASE           '.'
# define DETAIL         '%'
# define FINE           '*'
# define FIRST          '@'

# define BASEF          (2.0 * M_PI) / 300
# define DETAILF        (2.0 * M_PI) / 150
# define FINEF          (2.0 * M_PI) / 100
# define FIRSTF         (2.0 * M_PI) / 50

# define BASEA          (HEIGHT / 5)
# define DETAILA        (HEIGHT / 10)
# define FINEA          (HEIGHT / 20)
# define FIRSTA         (HEIGHT / 30)

/* Color */
# define FOREGROUND		1
# define BACK_NIGHT		2
# define MID_NIGHT		3
# define BACK_DAY		4
# define MID_DAY		5
# define PLAYER_1		6
# define PLAYER_2		7
# define HEALTH			8

/* Movement */
# define HORIZONTAL		0
# define VERTICAL		1

/* Players */
# define BASE_X_1		30
# define BASE_Y_1		20

double  ft_sin( double x );

#endif //UTILS_HPP
