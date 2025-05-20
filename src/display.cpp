/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:07:28 by tchartie          #+#    #+#             */
/*   Updated: 2025/05/20 22:49:17 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

static void createBackgroundHills(char back[HEIGHT][WIDTH], double freq, double amp, int height, str type);
static void displayBackgroundHills(char back[HEIGHT][WIDTH], str type, int index, WINDOW *board);

static str intToStr(int value);
//static str doubleToStr(double value);


void	Game::displayBackground( void ) {
	static char backgroundBase[HEIGHT][WIDTH];
	static char backgroundDetail[HEIGHT][WIDTH];
	static char backgroundFine[HEIGHT][WIDTH];
	static char backgroundFirst[HEIGHT][WIDTH];

	static bool initialized = false;

	static int	indexAddBase = 0;
	static int	indexAddDetail = 0;
	static int	indexAddFine = 0;

	static int	indexBase = 0;
	static int	indexDetail = 0;
	static int	indexFine = 0;
    static int	index = 0;

	//Randomly Generate Background
	if (!initialized) {
        createBackgroundHills(backgroundBase, BASEF, BASEA, 25, "base");
        createBackgroundHills(backgroundDetail, DETAILF, DETAILA, 20, "detail");
        createBackgroundHills(backgroundFine, FINEF, FINEA, 15, "fine");
        createBackgroundHills(backgroundFirst, FIRSTF, FIRSTA, 7, "first");
		initialized = true;
	}

	//Scroll Background
    displayBackgroundHills(backgroundBase, "base", indexBase, this->_board);
    displayBackgroundHills(backgroundDetail, "detail", indexDetail, this->_board);
    displayBackgroundHills(backgroundFine, "fine", indexFine, this->_board);
    displayBackgroundHills(backgroundFirst, "first", index, this->_board);

    index++;
    if (++indexAddBase  % 15 == 0) ++indexBase;
    if (++indexAddDetail %  7 == 0) ++indexDetail;
    if (++indexAddFine   %  3 == 0) ++indexFine;

	//Create Upper & Lower Border
	this->addBorder();
	init_pair(3, COLOR_BLACK, COLOR_WHITE);
	wattron(this->_board, COLOR_PAIR(3));
	for (size_t i = 0; i < LENGTH; ++i) {
		this->addAt(0, i, ' ');
		this->addAt(HEIGHT - 1, i, ' ');
	}
	wattroff(this->_board, COLOR_PAIR(3));
}

void	Game::displayPlayer( void ) {
	mvwprintw(this->_board, this->_player.getPosY(), this->_player.getPosX(), "🛸");
	this->_player.updateTime();
}

void    Game::displayEnd( void ) {
    wattron(this->_board, A_BOLD);

	mvwprintw(this->_board, HEIGHT / 2 - 10, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 9, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁");
	mvwprintw(this->_board, HEIGHT / 2 - 8, LENGTH / 2 - 20, "⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁  ");
	mvwprintw(this->_board, HEIGHT / 2 - 7, LENGTH / 2 - 20, "⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 6, LENGTH / 2 - 20, "⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 5, LENGTH / 2 - 20, "⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀  ");
	mvwprintw(this->_board, HEIGHT / 2 - 4, LENGTH / 2 - 20, "⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   ");
	mvwprintw(this->_board, HEIGHT / 2 - 3, LENGTH / 2 - 20, "⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀");
	mvwprintw(this->_board, HEIGHT / 2 - 2, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆");
	mvwprintw(this->_board, HEIGHT / 2 - 1, LENGTH / 2 - 20, "⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 0, LENGTH / 2 - 20, "⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 1, LENGTH / 2 - 20, "⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 2, LENGTH / 2 - 20, "⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 3, LENGTH / 2 - 20, "⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + 4, LENGTH / 2 - 20, "⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");

	wattron(this->_board, A_BLINK);
	mvwprintw(this->_board, HEIGHT / 2 + 6, LENGTH / 2 - 10, "Press any Key to Quit!");
	wattroff(this->_board, A_BLINK);

	mvwprintw(this->_board, HEIGHT / 2 + 10, LENGTH / 2 - 20, "Score:");
	mvwprintw(this->_board, HEIGHT / 2 + 10, LENGTH / 2 + 14, "Time:");

	wattroff(this->_board, A_BOLD);

    const str	scoreDisplay = intToStr(this->_player.getScore());
	int			padding = scoreDisplay.size();
	if (padding % 2 != 0)
		padding++;
	mvwprintw(this->_board, HEIGHT / 2 + 11, LENGTH / 2 - 20 + 3 - (padding / 2), "%s", scoreDisplay.c_str());

    //double	endTime = static_cast<double>(this->_player.getTimeSurvived() - std::clock()) / CLOCKS_PER_SEC;
	//const str	timeDisplay = doubleToStr(endTime);
	//padding = timeDisplay.size();
	//if (padding % 2 != 0)
	//	padding++;
	//mvwprintw(this->_board, HEIGHT / 2 + 11, LENGTH / 2 + 14 + 3 - (padding / 2), "%s", scoreDisplay.c_str());
}

static void createBackgroundHills(char back[HEIGHT][WIDTH], double freq, double amp, int height, str type) {
    double offset = HEIGHT / 2.0;

    amp *= (0.8 + 0.4 * (std::rand() / (double)RAND_MAX));

    chtype ch;
    ch = (type == "base")   ? BASE   :
    (type == "detail")      ? DETAIL :
    (type == "fine")        ? FINE   :
    (type == "first")       ? FIRST  :
    SPACE;

    for (int x = 0; x < WIDTH; ++x) {
        double hill = static_cast<int>(ft_sin(x * freq) * amp + offset * 2.0) - height;
        for (int y = 0; y < HEIGHT; ++y) {
            back[y][x]   = (y < hill) ? SPACE : ch;
		}
    }
    
}

static void displayBackgroundHills(char back[HEIGHT][WIDTH], str type, int index, WINDOW *board) {
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);

    int color = (type == "base" || type == "detail") ? 4 : 5;

    for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
			int wrapped_col = (j + index) % WIDTH;
                wattron(board, COLOR_PAIR(color));
                wattron(board, A_BOLD);
                if (type == "base" || back[i][wrapped_col] != SPACE)
                    mvwaddch(board, i, j, back[i][wrapped_col]);
                wattroff(board, A_BOLD);
                wattroff(board, COLOR_PAIR(color));
		}
	}
}

static str intToStr(int value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

/*static str doubleToStr(double value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}*/