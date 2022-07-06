#include "procedures.h"
#include "tools.h"

// правила переміщення коня задано глобальними змінними
const int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
const int dsize = sizeof dx / sizeof *dx;

bool success;           // ознака того, чи знайдено розв'язок

void TryNextMove(int** board, int n, int step_number, int pos_x, int pos_y)
{
	int length = n * n;             // кількість ходів незмінна
	int continuation_number = 0;    // лічильник можливих продовжень
	do
	{   // обчислюємо наступний хід коня
		int new_x = pos_x + dx[continuation_number];
		int new_y = pos_y + dy[continuation_number];
		++continuation_number;
		// і перевіряємо, чи його можна виконати
		if (0 <= new_x && new_x < n && 0 <= new_y && new_y < n &&
			board[new_x][new_y] == 0)
		{
			board[new_x][new_y] = step_number;   //якщо так, то робимо хід
			if (step_number < length)
			{   // і шукаємо продовження, якщо шахівниця ще не заповнена
				TryNextMove(board, n, step_number + 1, new_x, new_y);
				if (!success)          // неможливо побудувати продовження
					board[new_x][new_y] = 0;  // повернення на крок назад
			}
			else success = true;
		}
	} while (!success && continuation_number < dsize);
}

void TourByRecursion()
{
	int n;                                  // розмір шахівниці
	cout << "Введіть розмір шахівниці: "; cin >> n;
	int** board = BuildBoard(n);            // побудова порожньої шахівниці
	int pos_x, pos_y;                       // початкові координати коня
	cout << "Введіть координати x y першого поля (1<=x,y<=" << n << "): ";
	cin >> pos_y >> pos_x;
	board[--pos_x][--pos_y] = 1;            // поставили коня
	success = false;                        // розв'язку ще не знайшли
	TryNextMove(board, n, 2, pos_x, pos_y); // пробуємо знайти тур коня
	// виведення результатів і звільнення пам'яті
	if (success)
	{
		cout << "\n       Знайдено тур коня\n---------------------------------\n\n";
		WriteBoard(board, n);
	}
	else cout << "\n       Розв'язку не знайшли\n";
	EraseBoard(board);
}

// Один хід у турі коня містить координати клітинки і кількість
// випробуваних кандидатів на продовження
struct State
{
	int x, y, k;
	State(int _x = 0, int _y = 0, int _k = 0) :x(_x), y(_y), k(_k) {}
};

bool KnightTour(int** board, int n, int pos_x, int pos_y)
{
	int length = n * n - 1;               // кількість ходів
	State* moves = new State[length + 1]; // внутрішній стек
	int step_number = 0;                  // ходів ще не робили
	board[--pos_x][--pos_y] = 1;          // початкове розташування коня
	State curr(pos_x, pos_y, 0);
	moves[step_number] = curr;            // і стан дошки
	do
	{
		bool success = false;  // успішність чергового ходу
		int new_x, new_y;      // координати чергового ходу
		while (curr.k < 8 && !success)
		{                      // шукаємо можливе продовження
			new_x = curr.x + dx[curr.k];
			new_y = curr.y + dy[curr.k];
			success = 0 <= new_x && new_x < n && 0 <= new_y && new_y < n
				&& board[new_x][new_y] == 0;
			++curr.k;
		}
		if (success)
		{            // знайшли продовження
			moves[++step_number] = curr;       // запам'ятовуємо хід
			board[new_x][new_y] = step_number + 1;
			curr = State(new_x, new_y, 0);     // новий стан дошки
		}
		else         // повертаємося на хід назад
		{
			board[curr.x][curr.y] = 0;        // звільнили клітинку
			curr = moves[step_number--];      // повернули стан
		}
	} while (step_number < length && step_number >= 0);
	delete[] moves;
	return step_number == length;
}

void SolveTour()
{
	int n;                                  // розмір шахівниці
	cout << "Введіть розмір шахівниці: "; cin >> n;
	int** board = BuildBoard(n);            // побудова порожньої шахівниці
	int pos_x, pos_y;                       // початкові координати коня
	cout << "Введіть координати x y першого поля (1<=x,y<=" << n << "): ";
	cin >> pos_y >> pos_x;
	bool success = KnightTour(board, n, pos_x, pos_y); // шукаємо тур коня
	// виведення результатів і звільнення пам'яті
	if (success)
	{
		cout << "\n       Знайдено тур коня\n---------------------------------\n\n";
		WriteBoard(board, n);
	}
	else cout << "\n       Розв'язку не знайшли\n";
	EraseBoard(board);
}
