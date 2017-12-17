
enum class GameSpeed
{
	Slow = 0,
	SlowMedium = 1,
	Medium = 2,
	MediumFast = 3,
	Fast = 4,
	Full = 5
};

GameSpeed& operator++(GameSpeed& gs)
{
	int n = static_cast<int>(gs);
	n++;
	if (n > 5) n = 0;

	gs = static_cast<GameSpeed>(n);

	return gs;
}

GameSpeed& operator++(GameSpeed& gs, int)
{
	int n = static_cast<int>(gs);
	n++;
	if (n > 5) n = 0;
	gs = static_cast<GameSpeed>(n);

	return gs;
}

GameSpeed& operator--(GameSpeed& gs)
{
	int n = static_cast<int>(gs);
	n--;
	if (n < 0) n = 5;

	gs = static_cast<GameSpeed>(n);

	return gs;
}

GameSpeed& operator--(GameSpeed& gs, int)
{
	int n = static_cast<int>(gs);
	n--;
	if (n < 0) n = 5;
	gs = static_cast<GameSpeed>(n);

	return gs;
}