#include "tools.h"
#include "procedures.h"

struct Cell
{
	char x; int y;
	Cell(char a = 'a', int b = 1) :x(a), y(b) {}
};
std::ostream& operator<<(std::ostream& os, const Cell& c)
{
	os << c.x << c.y; return os;
}

// перевіряє, чи загрожує k-ва королева попереднім
bool Safe(Cell* queens, int k)
{
	for (int i = k - 1; i >= 0; --i)      // пам'ятаємо, що вертикалі різні, тому
		if (queens[i].y == queens[k].y || // порівнюємо горизонталі та
			queens[i].x - queens[i].y == queens[k].x - queens[k].y || // діагоналі
			queens[i].x + queens[i].y == queens[k].x + queens[k].y) return false;
	return true;
}

// шукає безпечне розташування n ферзів
bool TryPutQueen(Cell* queens, int n, int k)
{
	// k-ва фігура відразу стає у свою вертикаль
	queens[k].x = 'a' + k;
	queens[k].y = 0;      // горизонталь підбиратимемо (є n спроб)
	bool success = false;
	do
	{	++queens[k].y;    // чергова горизонталь
		if (Safe(queens, k))
		{   // розташування k-ї фігури - безпечне
			if (k + 1 == n) success = true; // знайшли розв'язок
			else                            // шукаємо продовження
				success = TryPutQueen(queens, n, k + 1);
		}
	} while (!success && queens[k].y < n);
	return success;
}

void PutQueens()
{
	int n;                                // розмір шахівниці
	cout << "Введіть розмір шахівниці: "; cin >> n;
	Cell * queens = new Cell[n];          // шуканий роз'язок
	bool success = TryPutQueen(queens, n, 0);
	// виведення результатів і звільнення пам'яті
	if (success)
	{
		int** board = BuildBoard(n);       // матриця допоможе зобразити шахівницю
		cout << "\n       Знайдено розташування\n---------------------------------\n\n      ";
		for (int i = 0; i < n; ++i)
		{
			cout << "  " << queens[i];    // друкуємо знайдене розташування
			// і "розставляємо" фігури на шахівниці:
			// порожня клітинка містить 0, клітинка з ферзем - 13
			board[queens[i].x - 'a'][queens[i].y - 1] = 13;
		}
		cout << "\n\n";
		WriteBoard(board, n);             // друк шахівниці
		EraseBoard(board);
	}
	else cout << "\n       Розв'язку не знайшли\n";
	delete[] queens;
}