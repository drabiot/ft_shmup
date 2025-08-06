/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchartie <tchartie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 23:03:10 by tchartie          #+#    #+#             */
/*   Updated: 2025/08/06 19:52:31 by tchartie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

static void	redirectPos(int *x, int *y, std::vector<Wall> obstacle);

Game::Game( void ) {
	size_t	xMax;
	size_t	yMax;

	//Init Game Screen
	initscr();

	//Init Colors
	if (!has_colors())
		throw std::runtime_error("Can't initialize Colors");
	start_color();
	init_pair(FOREGROUND, COLOR_BLACK, COLOR_WHITE);
	init_pair(BACK_NIGHT, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MID_NIGHT, COLOR_GREEN, COLOR_BLACK);
	init_pair(PLAYER_1, COLOR_CYAN, COLOR_BLACK);
	init_pair(HEALTH, COLOR_RED, COLOR_BLACK);

	//Create & Init Playing Board
	refresh();
	getmaxyx(stdscr, yMax, xMax);
	this->_board = newwin(HEIGHT, LENGTH, (yMax / 2) - (HEIGHT / 2), (xMax / 2) - (LENGTH / 2));
	if (!this->_board)
		throw std::runtime_error("Can't initialize Game window");

	this->_start = false;
	this->_gameOver = false;

	this->_up = 0;
	this->_down = 0;
	this->_left = 0;
	this->_right = 0;

	if (!createWall("map/test.mp"))
		throw std::runtime_error("Can't initialize Map");

}

Game::~Game( void ) {
	//End the Game Screen
	if (this->_board)
		delwin(this->_board);
	endwin();
}

void	Game::initializeBorder( void ) {
	
	this->clearBorder();
	this->refreshBorder();
}

void	Game::addBorder( void ) {
	box(this->_board, 0, 0);
}

void	Game::clearBorder( void ) {
	wnoutrefresh(this->_board);
	this->addBorder();
}

void	Game::refreshBorder( void ) {
	wrefresh(this->_board);
}

void	Game::addAt( int y, int x, chtype ch) {
	mvwaddch(this->_board, y, x, ch);
}

bool	Game::isStarted( void ) {
	return (this->_start);
}

bool	Game::isGameOver( void ) {
	return (this->_gameOver);
}

Player	*Game::getPlayer( void ) {
	return &(this->_player);
}

WINDOW	*Game::getWindow( void ) {
	return (this->_board);
}

bool	Game::getEmoji( void ) {
	return (this->_emoji);
}

void	Game::addDirection( int type ) {
	(void)type;
	/*chtype	input = wgetch(this->_board);
	while (input != this->_up && input != this->_down && input != this->_left && input != this->_right) {
		input = wgetch(this->_board);
	}
	switch (type) {
		case 0:
			this->_up = input;
			break;
		case 1:
			this->_down = input;
			break;
		case 2:
			this->_left = input;
			break;
		case 3:
			this->_right = input;
			break;
		default:
			break;
	}*/
}

bool	Game::createWall(str mapName) {
	(void)mapName;
	std::ifstream map("maps/test.mp");

	//Open Map
	if (!map.is_open()) return (false);
	map.seekg(0, std::ios::end);
	if (map.tellg() == 0) {
		map.close();
		return (false);
	}
	map.seekg(0, std::ios::beg);

	//Analyze Header
	str line;
	int origWidth = -1;
	int origHeight = -1;

	std::getline(map, line);
	if (line.substr(0, 6) == "size\t:") {
		origWidth = atoi(line.substr(6, line.size() - 7).c_str());
		if (line[line.size() - 1] != ';')
			return (false);
	} else
		return (false);

	std::getline(map, line);
	if (line.substr(0, 8) == "height\t:") {
		origHeight = atoi(line.substr(8, line.size() - 9).c_str());
		if (line[line.size() - 1] != ';')
			return (false);
	} else
		return (false);

	std::getline(map, line);
	if (line.substr(0, 9) == "element\t:") {
		this->_fillChar = line.substr(9, 1)[0];
		if (line[10] != ';')
			return (false);
	} else
		return (false);

	std::getline(map, line);
	if (line.substr(0, 7) == "empty\t:") {
		this->_emptyChar = line.substr(7, 1)[0];
		if (line[8] != ';')
			return (false);
	} else
		return (false);

	//Save Map
	std::vector<std::string> originalMap;
	for (int i = 0; i < origHeight; ++i) {
		if (!std::getline(map, line))
			return (false);
		if ((int)line.size() < origWidth)
			line += std::string(origWidth - line.size(), this->_emptyChar);
		originalMap.push_back(line);
	}

	//Scale Map
	float scaleX = static_cast<float>(origWidth) / WIDTH;
	float scaleY = static_cast<float>(origHeight) / HEIGHT;

	this->_finalMap.clear();
	this->_finalMap.resize(HEIGHT, std::string(WIDTH, this->_emptyChar));

	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			int origX = static_cast<int>(x * scaleX);
			int origY = static_cast<int>(y * scaleY);

			if (origX >= origWidth)
				origX = origWidth - 1;
			if (origY >= origHeight)
				origY = origHeight - 1;

			char c = originalMap[origY][origX];
			if (c == this->_fillChar || c == this->_emptyChar)
				this->_finalMap[y][x] = c;
			else
				this->_finalMap[y][x] = this->_emptyChar;
		}
	}

	//Init - Fill Map with obstacle
	for (int y = 0; y < HEIGHT; ++y) {
		for (int x = 0; x < WIDTH; ++x) {
			if (this->_finalMap[y][x] == this->_fillChar) {
				this->_obstacle.push_back(Wall(x, y));
				this->_obstacle.push_back(Wall(x + WIDTH, y));
			}
		}
	}

	return (true);
}


chtype	Game::getInput( void ) {
	noecho();
	curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(this->_board, TRUE);
	cbreak();
	
	return (wgetch(this->_board));
}

void	Game::processInput( void ) {
	chtype	input = this->getInput();
	static unsigned int	attackSpeed = 0;
	attackSpeed++;

	switch (input) {
		case 'w':
			if (this->_player.getPosY() - 1 > 0 && checkCollision(this->_player.getPosX(), this->_player.getPosY() - 1, VERTICAL))
				this->_player.setPosY(this->_player.getPosY() - 1);
			break;
		case 's':
			if (this->_player.getPosY() + 1 < HEIGHT - 1 && checkCollision(this->_player.getPosX(), this->_player.getPosY() + 1, VERTICAL))
				this->_player.setPosY(this->_player.getPosY() + 1);
			break;
		case 'd':
			if (this->_player.getPosX() + 2 < LENGTH - 1 && checkCollision(this->_player.getPosX() + 2, this->_player.getPosY(), HORIZONTAL))
				this->_player.setPosX(this->_player.getPosX() + 2);
			break;
		case 'a':
			if (this->_player.getPosX() - 1 >= 0 && checkCollision(this->_player.getPosX(), this->_player.getPosY(), HORIZONTAL))
				this->_player.setPosX(this->_player.getPosX() - 1);
			break;
		case ' ':
			if (attackSpeed > 5) {
				this->_player.attack();
				attackSpeed = 0;
			}
			break;
		case 'p':
			this->_gameOver = true;
			break;
		default:
			break;
	}
}

void	Game::updateGame( void ) {
	this->clearBorder();
	
	//Create & Display Background
	this->displayBackground();

	//Add Foreground
	static int	frame = 0;
	
	if (frame == 299) {
		for (int y = 0; y < HEIGHT; ++y) {
			for (int x = 0; x < WIDTH; ++x) {
				if (this->_finalMap[y][x] == this->_fillChar) {
					this->_obstacle.push_back(Wall(x + WIDTH, y));
				}
			}
		}
		frame = 0;
	}
	frame++;

	//Display Foreground
	this->displayObstacle();
	for (size_t i = 0; i < this->_obstacle.size(); ++i) {
		this->_obstacle[i].moveWall();

		//Delete Wall when inexistant
		if (this->_obstacle[i].getPosX() > -(WIDTH * 2) && this->_obstacle[i].getPosX() < -WIDTH)
			this->_obstacle.erase(this->_obstacle.begin() + i);
	}

	//Display Enemies

	//Display Player & Check collisions
	this->_player.updateInvincibility();
	this->checkCollision(this->_player.getPosX(), this->_player.getPosY(), HORIZONTAL);
	wattron(this->_board, A_BOLD);
	this->displayPlayer();
	wattroff(this->_board, A_BOLD);
	this->checkCollision(this->_player.getPosX(), this->_player.getPosY(), HORIZONTAL);

	//Display & Update Projectile
	this->updateRocket();
	wattron(this->_board, A_BOLD);
	this->displayRocket();
	wattroff(this->_board, A_BOLD);

	this->refreshBorder();
}

void	Game::endScreen( void ) {
	this->clearBorder();
	for (int i = 0; i < HEIGHT; ++i) {
		for (int j = 0; j < LENGTH; ++j) {
				this->addAt(i, j, ' ');
		}
	}
	this->addBorder();
	this->displayEnd();
	this->refreshBorder();
	doupdate();
}

void	Game::addRocket( Projectile newRocket ) {
	this->_rocket.push_back(newRocket);
}

void	Game::removeRocket( Projectile oldRocket ) {
	(void)oldRocket;
}

void	Game::updateRocket( void ) {
	this->_player.getPendingRocket(this->_rocket);
	for (size_t i = 0; i < this->_rocket.size(); ++i) {
		bool	hitWall = false;

		for (size_t j = 0; j < this->_obstacle.size(); ++j) {
			if (this->_rocket[i].getPosX() == this->_obstacle[j].getPosX() && this->_rocket[i].getPosY() == this->_obstacle[j].getPosY()) {
				hitWall = true;
				continue;
			}
		}
		if (hitWall)
			this->_rocket.erase(this->_rocket.begin() + i);
		else
    		this->_rocket[i].setPosX(this->_rocket[i].getPosX() + 1);
	}
}

bool	Game::checkCollision( int x, int y, int axis ) {
	//check if the player reach an obstacle
	for (size_t i = 0; i < this->_obstacle.size(); ++i) {
		if (x == this->_obstacle[i].getPosX() && y == this->_obstacle[i].getPosY()) {
			if (axis == HORIZONTAL)
				this->_player.setPosX(x - 1);
		return (false);
		}
	}

	//check if the player take a hit
	if (this->_player.getPosX() < 0) {
		this->_player.setLife(this->_player.getLife() - 1);
		
		int newX = BASE_X_1;
		int	newY = BASE_Y_1;

		redirectPos(&newX, &newY, this->_obstacle);	//Fix Redir in Y axis if not spawn point

		this->_player.setPosX(newX);
		this->_player.setPosY(newY);
		this->_player.setInvincibility(5);
	}

	//check death of the player
	if (this->_player.getLife() == 0) {
		this->_gameOver = true;
		return (false);
	}

	return (true);
}

static void redirectPos(int* x, int* y, std::vector<Wall> obstacle) {
	static bool obstacleBoard[HEIGHT][WIDTH];

	//Init Actual Board
	for (int i = 0; i < HEIGHT; ++i)
		for (int j = 0; j < WIDTH; ++j)
			obstacleBoard[i][j] = false;

	//Look for Walls in the Actual Board
	for (size_t i = 0; i < obstacle.size(); ++i) {
		int posX = obstacle[i].getPosX();
		int posY = obstacle[i].getPosY();

		if (posX >= 0 && posX < WIDTH && posY >= 0 && posY < HEIGHT)
			obstacleBoard[posY][posX] = true;
	}

	//Check if the Initial Respawn Point is available
	if (!obstacleBoard[*y][*x])
		return;

	//Check for the best Respawn Point
	bool visited[HEIGHT][WIDTH];
	for (int i = 0; i < HEIGHT; ++i)
		for (int j = 0; j < WIDTH; ++j)
			visited[i][j] = false;

	const int dx[8] = { 1, -1, 0, 0, 1, -1, 1, -1 };
	const int dy[8] = { 0, 0, 1, -1, 1, -1, -1, 1 };

	std::queue< std::pair<int, int> > q;
	q.push(std::make_pair(*x, *y));
	visited[*y][*x] = true;

	while (!q.empty()) {
		std::pair<int, int> current = q.front();
		q.pop();

		for (int dir = 0; dir < 8; ++dir) {
			int newX = current.first + dx[dir];
			int newY = current.second + dy[dir];

			if (newX >= 0 && newX < WIDTH && newY >= 0 && newY < HEIGHT && !visited[newY][newX]) {
				visited[newY][newX] = true;

				if (!obstacleBoard[newY][newX]) {
					*x = newX;
					*y = newY;
					return;
				}

				q.push(std::make_pair(newX, newY));
			}
		}
	}
}

