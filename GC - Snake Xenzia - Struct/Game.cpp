#include "Game.hpp"

bool operator==(Position positionLeft, Position positionRight)
{
	if ((positionLeft.x == positionRight.x) && (positionLeft.y == positionRight.y))
	{
		return true;
	}
	return false;
}
Snake initialSnake(int size, Direction direction)
{
	Snake snake;
	snake.size = size;
	snake.position = new Position[snake.size];

	if (direction == Direction::UP)
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5;
			snake.position[i].y = TOP_WALL + 2 + i;
		}
	}
	else if (direction == Direction::DOWN)
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5;
			snake.position[i].y = TOP_WALL + 2 + (snake.size - i);
		}
	}
	else if (direction == Direction::LEFT)
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5 + i;
			snake.position[i].y = TOP_WALL + 2;
		}
	}
	else if (direction == Direction::RIGHT)
	{
		for (int i = 0; i < snake.size; i++)
		{
			snake.position[i].x = LEFT_WALL + 5 + (snake.size - i);
			snake.position[i].y = TOP_WALL + 2;
		}
	}
	return snake;
}
Food initialFood()
{
	srand(time(NULL));
	int x, y;
	x = (LEFT_WALL + 1) + (rand()% (RIGHT_WALL - LEFT_WALL - 1));
	y = (TOP_WALL + 1) + (rand() % (BOT_WALL - TOP_WALL - 1));
	return{ x, y };
}
Position nodeEnd(Snake snake)
{
	return{ snake.position[snake.size - 1].x, snake.position[snake.size - 1].y };
}
//
bool isEatFood(Snake snake, Food food)
{
	if (snake.position[0] == food)
	{
		return true;
	}
	return false;
}
bool isErrorFood(Snake snake, Food food)
{
	for (int i = 0; i < snake.size; i++)
	{
		if (snake.position[i] == food)
		{
			return true;
		}
	}
	return false;
}
bool isLose(Snake snake)
{
	bool flag = false;
	if (snake.position[0].x == LEFT_WALL || snake.position[0].x == RIGHT_WALL)
	{
		flag = true;
	}
	if (snake.position[0].y == TOP_WALL || snake.position[0].y == BOT_WALL)
	{
		flag = true;
	}

	for (int i = 1; i < snake.size; i++)
	{
		if (snake.position[0] == snake.position[i])
		{
			flag = true;
			break;
		}
	}
	return flag;
}
//
void drawWall()
{
	for (int i = LEFT_WALL; i <= RIGHT_WALL; i++)
	{
		gotoXY(i, TOP_WALL);
		cout << (char)223;
		gotoXY(i, BOT_WALL);
		cout << (char)220;
	}
	for (int i = TOP_WALL; i <= BOT_WALL; i++)
	{
		gotoXY(LEFT_WALL, i);
		cout << (char)222;
		gotoXY(RIGHT_WALL, i);
		cout << (char)221;
	}
}
void drawFood(Food food)
{
	gotoXY(food.x, food.y);
	cout << (char)FOOD;
}
void drawSnake(Snake snake)
{
	gotoXY(snake.position[0].x, snake.position[0].y);
	cout << (char)HEAD_SNAKE;
	for (int i = 1; i < snake.size; i++)
	{
		gotoXY(snake.position[i].x, snake.position[i].y);
		cout << (char)BODY_SNAKE;
	}
}
void displayScore(int score)
{
	gotoXY(0, TOP_WALL);
	cout << "Score: " << score;
}
void deleteNode(Position node)
{
	gotoXY(node.x, node.y);
	cout << " ";
}
void pollEvent(Direction &direction)
{
	int key = inputKey();
	if ((key == 'W' || key == 'w' || key == DirectionKey::KEY_UP) && (direction != Direction::DOWN))
	{
		direction = Direction::UP;
	}
	else if ((key == 'S' || key == 's' || key == DirectionKey::KEY_DOWN) && (direction != Direction::UP))
	{
		direction = Direction::DOWN;
	}
	else if ((key == 'A' || key == 'a' || key == DirectionKey::KEY_LEFT) && (direction != Direction::RIGHT))
	{
		direction = Direction::LEFT;
	}
	else if ((key == 'D' || key == 'd' || key == DirectionKey::KEY_RIGHT) && (direction != Direction::LEFT))
	{
		direction = Direction::RIGHT;
	}
}
void pushBack(Snake &snake)
{
	Position* temp = new Position[snake.size];
	for (int i = 0; i < snake.size; i++)
	{
		temp[i] = snake.position[i];
	}
	snake.position = nullptr;
	delete[] snake.position;
	snake.position = new Position[snake.size + 1];
	for (int i = 0; i < snake.size; i++)
	{
		snake.position[i] = temp[i];
	}
	snake.position[snake.size] = snake.position[snake.size - 1];
	snake.size++;
	temp = nullptr;
	delete[] temp;
}
void actionLose()
{
	gotoXY(0, TOP_WALL + 1);
	cout << "Game over!";
}
void move(Snake snake, Direction direction)
{
	for (int i = (snake.size - 1); i >= 1; i--)
	{
		snake.position[i] = snake.position[i - 1];
	}
	if (direction == Direction::UP)
	{
		snake.position[0].y--;
	}
	else if (direction == Direction::DOWN)
	{
		snake.position[0].y++;
	}
	else if (direction == Direction::LEFT)
	{
		snake.position[0].x--;
	}
	else if (direction == Direction::RIGHT)
	{
		snake.position[0].x++;
	}
}
void run()
{
	int score = 0, speed = 100, count = 1;
	Direction direction = Direction::RIGHT;
	Snake snake = initialSnake(3, direction);
	Food food = initialFood();
	Position oldNodeEnd;

	drawWall();
	drawSnake(snake);
	drawFood(food);
	displayScore(score);

	while (true)
	{
		oldNodeEnd = nodeEnd(snake);
		move(snake, direction);
		drawSnake(snake);
		deleteNode(oldNodeEnd);
		if (isErrorFood(snake, food) && count == 1)
		{
			food = initialFood();
			drawFood(food);
			count = 0;
		}
		else if (isEatFood(snake, food))
		{
			pushBack(snake);
			food = initialFood();
			drawFood(food);
			count = 0;
			score++;
			displayScore(score);
		}
		if (isLose(snake))
		{
			actionLose();
			break;
		}
		pollEvent(direction);
		count++;
		Sleep(speed);
		noCursorType();
	}
	_getch();
}