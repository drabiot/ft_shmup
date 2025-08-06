/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:08:31 by tchartie          #+#    #+#             */
/*   Updated: 2025/08/06 20:13:36 by tchartie         ###   ########.fr       */
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
# include <queue>
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

# define IDX_BASE		3
# define IDX_DETAIL		2
# define IDX_FINE		1
# define IDX_FIRST		0

# define FREQ_BASE		(2.0 * M_PI) / 300
# define FREQ_DETAIL	(2.0 * M_PI) / 150
# define FREQ_FINE		(2.0 * M_PI) / 100
# define FREQ_FIRST		(2.0 * M_PI) / 50

# define AMP_BASE		(HEIGHT / 5)
# define AMP_DETAIL		(HEIGHT / 10)
# define AMP_FINE		(HEIGHT / 20)
# define AMP_FIRST		(HEIGHT / 30)

# define HEIGHT_BASE	25
# define HEIGHT_DETAIL	20
# define HEIGHT_FINE	15
# define HEIGHT_FIRST	7

/* Obstacle */
# define CORN_BAT		"#"	
# define HORI_BAT		"="
# define VERT_BAT		"|"
# define BASE_BAT		"o"

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

# define EMOJI_PLAYER	"🛩️"
# define BASE_PLAYER	">"

/* Projectile */
# define P_ROCKET		"-"
# define P_MAX_ROCKET	"="

double  ft_sin( double x );

#endif //UTILS_HPP
