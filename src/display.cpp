/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 20:07:28 by tchartie          #+#    #+#             */
/*   Updated: 2025/08/04 21:41:15 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

static void createBackgroundHills(char back[HEIGHT][WIDTH], double freq, double amp, int height, str type);
static void displayBackgroundHills(char back[HEIGHT][WIDTH], str type, int index, WINDOW *board);

static str intToStr(int value);
static str	createTimerFormat(int value);


void	Game::displayBackground( void ) {
	static char backgroundBase[HEIGHT][WIDTH];
	static char backgroundDetail[HEIGHT][WIDTH];
	static char backgroundFine[HEIGHT][WIDTH];
	static char backgroundFirst[HEIGHT][WIDTH];

	static bool initialized = false;
	static std::vector<int> index(4, 0);

	//Randomly Generate Background
	if (!initialized) {
        createBackgroundHills(backgroundBase, FREQ_BASE, AMP_BASE, HEIGHT_BASE, "base");
        createBackgroundHills(backgroundDetail, FREQ_DETAIL, AMP_DETAIL, HEIGHT_DETAIL, "detail");
        createBackgroundHills(backgroundFine, FREQ_FINE, AMP_FINE, HEIGHT_FINE, "fine");
        createBackgroundHills(backgroundFirst, FREQ_FIRST, AMP_FIRST, HEIGHT_FIRST, "first");
		initialized = true;
	}

	//Scroll Background
    displayBackgroundHills(backgroundBase, "base", index[IDX_BASE], this->_board);
    displayBackgroundHills(backgroundDetail, "detail", index[IDX_DETAIL], this->_board);
    displayBackgroundHills(backgroundFine, "fine", index[IDX_FINE], this->_board);
    displayBackgroundHills(backgroundFirst, "first", index[IDX_FIRST], this->_board);

	int	frameRateBase = 15;
	int	frameRateDetail = 7;
	int	frameRateFine = 3;

    index[0]++;
    if (!(index[IDX_FIRST] % frameRateBase))
		++index[IDX_BASE];
    if (!(index[IDX_FIRST] %  frameRateDetail))
		++index[IDX_DETAIL];
    if (!(index[IDX_FIRST] %  frameRateFine))
		++index[IDX_FINE];

	//Create Upper & Lower Border
	this->addBorder();
	wattron(this->_board, COLOR_PAIR(FOREGROUND));
	for (size_t i = 0; i < LENGTH; ++i) {
		this->addAt(0, i, ' ');
		this->addAt(HEIGHT - 1, i, ' ');
	}
	wattroff(this->_board, COLOR_PAIR(FOREGROUND));
}

void	Game::displayPlayer( void ) {
	wattron(this->_board, COLOR_PAIR(PLAYER_1));
	if (this->_emoji)
		mvwprintw(this->_board, this->_player.getPosY(), this->_player.getPosX(), "🛩️");
	else
		mvwprintw(this->_board, this->_player.getPosY(), this->_player.getPosX(), ">");
	wattroff(this->_board, COLOR_PAIR(PLAYER_1));
	this->_player.updateTime();
}

void	Game::displayObstacle( void ) {
	for (size_t i = 0; i < this->_obstacle.size(); ++i) {
		wattron(this->_board, COLOR_PAIR(FOREGROUND));
		if (this->_obstacle[i].getPosX() >= 0)
			mvwprintw(this->_board, this->_obstacle[i].getPosY(), this->_obstacle[i].getPosX(), " ");
		wattroff(this->_board, COLOR_PAIR(FOREGROUND));
	}
}

void	Game::displayRocket( void ) {
	for (size_t i = 0; i < this->_rocket.size(); ++i) {
		if (this->_rocket[i].getDamage() == 5)
			mvwprintw(this->_board, this->_rocket[i].getPosY(), this->_rocket[i].getPosX(), "=");
		else
    		mvwprintw(this->_board, this->_rocket[i].getPosY(), this->_rocket[i].getPosX(), "-");
	}
}

void	Game::introGame( void ) {
	this->clearBorder();

	int	paddingHeight = -10;
	int	paddingLength = 24;

	wattron(this->_board, COLOR_PAIR(PLAYER_1));
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "   _    _      _                               ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "  | |  | |    | |                              ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "  | |  | | ___| | ___ ___  _ __ ___   ___      ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "  | |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\     ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "  \\  /\\  /  __/ | (_| (_) | | | | | |  __/     ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "   \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|     ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "  __ _         _     _                        ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , " / _| |       | |   | |                        ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "| |_| |_   ___| |__ | |_ _ __ ___  _   _ _ __  ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "|  _| __| / __| '_ \\| __| '_ ` _ \\| | | | '_ \\ ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "| | | |_  \\__ \\ | | | |_| | | | | | |_| | |_) |");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "|_|  \\__| |___/_| |_|\\__|_| |_| |_|\\__,_| .__/ ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "      ______                            | |    ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength , "     |______|                           |_|    ");
	wattroff(this->_board, COLOR_PAIR(PLAYER_1));

	mvwprintw(this->_board, HEIGHT / 2 + 7, LENGTH / 2 - 40, "Press 1: for Emojies");
	mvwprintw(this->_board, HEIGHT / 2 + 7, LENGTH / 2 + 20, "Press 2: for ASCII");

	wattron(this->_board, A_BLINK);
	mvwprintw(this->_board, HEIGHT / 2 + 12, LENGTH / 2 - 22, "*If this text don't blink select ASCII mode*");
	wattroff(this->_board, A_BLINK);

	chtype	input = this->getInput();
	switch (input) {
		case '1':
			this->_emoji = true;
			this->_start = true;
			break;
		case '2':
			this->_emoji = false;
			this->_start = true;
			break;
		default:
			break;
	}

	this->refreshBorder();
}

void    Game::displayEnd( void ) {
    wattron(this->_board, A_BOLD);

	int	paddingHeight = -10;
	int	paddingLength = 20;

	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁  ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀  ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀   ");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀");
	mvwprintw(this->_board, HEIGHT / 2 + ++paddingHeight, LENGTH / 2 - paddingLength, "⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀");

	wattron(this->_board, A_BLINK);
	mvwprintw(this->_board, HEIGHT / 2 + 6, LENGTH / 2 - 10, "Press any Key to Quit!");
	wattroff(this->_board, A_BLINK);

	mvwprintw(this->_board, HEIGHT / 2 + 10, LENGTH / 2 - 20, "Score:");
	mvwprintw(this->_board, HEIGHT / 2 + 10, LENGTH / 2 + 14, "Time:");

	wattroff(this->_board, A_BOLD);

	//Create Score
    const str	scoreDisplay = intToStr(this->_player.getScore());
	int			padding = scoreDisplay.size();
	if (padding % 2 != 0)
		padding++;
	mvwprintw(this->_board, HEIGHT / 2 + 11, LENGTH / 2 - 20 + 3 - (padding / 2), "%s", scoreDisplay.c_str());

	//Create Timer
	const str	timeDisplay = createTimerFormat(this->_player.getTimer());
	padding = timeDisplay.size();
	if (padding % 2 != 0)
		padding++;
	mvwprintw(this->_board, HEIGHT / 2 + 11, LENGTH / 2 + 14 + 3 - (padding / 2), "%s", timeDisplay.c_str());
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

    int color = (type == "base" || type == "detail") ? 2 : 3;

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

static str	createTimerFormat(int value) {
	int	sec = value % 60;
	int	min = (value / 60) % 60;
	int hour = value / 3600;

    std::ostringstream oss;

    if (hour > 0)
        oss << std::setw(2) << std::setfill('0') << hour << ":";
    
    oss << std::setw(2) << std::setfill('0') << min << ":"
        << std::setw(2) << std::setfill('0') << sec;

    return oss.str();
}
