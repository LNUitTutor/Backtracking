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

// ��������, �� ������� k-�� �������� ���������
bool Safe(Cell* queens, int k)
{
	for (int i = k - 1; i >= 0; --i)      // ���'�����, �� �������� ���, ����
		if (queens[i].y == queens[k].y || // ��������� ���������� ��
			queens[i].x - queens[i].y == queens[k].x - queens[k].y || // �������
			queens[i].x + queens[i].y == queens[k].x + queens[k].y) return false;
	return true;
}

// ���� �������� ������������ n �����
bool TryPutQueen(Cell* queens, int n, int k)
{
	// k-�� ������ ������ ��� � ���� ���������
	queens[k].x = 'a' + k;
	queens[k].y = 0;      // ����������� ������������ (� n �����)
	bool success = false;
	do
	{	++queens[k].y;    // ������� �����������
		if (Safe(queens, k))
		{   // ������������ k-� ������ - ��������
			if (k + 1 == n) success = true; // ������� ����'����
			else                            // ������ �����������
				success = TryPutQueen(queens, n, k + 1);
		}
	} while (!success && queens[k].y < n);
	return success;
}

void PutQueens()
{
	int n;                                // ����� ���������
	cout << "������ ����� ���������: "; cin >> n;
	Cell * queens = new Cell[n];          // ������� ���'����
	bool success = TryPutQueen(queens, n, 0);
	// ��������� ���������� � ��������� ���'��
	if (success)
	{
		int** board = BuildBoard(n);       // ������� �������� ��������� ���������
		cout << "\n       �������� ������������\n---------------------------------\n\n      ";
		for (int i = 0; i < n; ++i)
		{
			cout << "  " << queens[i];    // ������� �������� ������������
			// � "������������" ������ �� ���������:
			// ������� ������� ������ 0, ������� � ������ - 13
			board[queens[i].x - 'a'][queens[i].y - 1] = 13;
		}
		cout << "\n\n";
		WriteBoard(board, n);             // ���� ���������
		EraseBoard(board);
	}
	else cout << "\n       ����'���� �� �������\n";
	delete[] queens;
}