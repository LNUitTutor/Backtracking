#include "procedures.h"
#include "tools.h"

// ������� ���������� ���� ������ ����������� �������
const int dx[] = { 2, 1, -1, -2, -2, -1, 1, 2 };
const int dy[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
const int dsize = sizeof dx / sizeof *dx;

bool success;           // ������ ����, �� �������� ����'����

void TryNextMove(int** board, int n, int step_number, int pos_x, int pos_y)
{
	int length = n * n;             // ������� ���� �������
	int continuation_number = 0;    // �������� �������� ����������
	do
	{   // ���������� ��������� ��� ����
		int new_x = pos_x + dx[continuation_number];
		int new_y = pos_y + dy[continuation_number];
		++continuation_number;
		// � ����������, �� ���� ����� ��������
		if (0 <= new_x && new_x < n && 0 <= new_y && new_y < n &&
			board[new_x][new_y] == 0)
		{
			board[new_x][new_y] = step_number;   //���� ���, �� ������ ���
			if (step_number < length)
			{   // � ������ �����������, ���� ��������� �� �� ���������
				TryNextMove(board, n, step_number + 1, new_x, new_y);
				if (!success)          // ��������� ���������� �����������
					board[new_x][new_y] = 0;  // ���������� �� ���� �����
			}
			else success = true;
		}
	} while (!success && continuation_number < dsize);
}

void TourByRecursion()
{
	int n;                                  // ����� ���������
	cout << "������ ����� ���������: "; cin >> n;
	int** board = BuildBoard(n);            // �������� �������� ���������
	int pos_x, pos_y;                       // �������� ���������� ����
	cout << "������ ���������� x y ������� ���� (1<=x,y<=" << n << "): ";
	cin >> pos_y >> pos_x;
	board[--pos_x][--pos_y] = 1;            // ��������� ����
	success = false;                        // ����'���� �� �� �������
	TryNextMove(board, n, 2, pos_x, pos_y); // ������� ������ ��� ����
	// ��������� ���������� � ��������� ���'��
	if (success)
	{
		cout << "\n       �������� ��� ����\n---------------------------------\n\n";
		WriteBoard(board, n);
	}
	else cout << "\n       ����'���� �� �������\n";
	EraseBoard(board);
}

// ���� ��� � ��� ���� ������ ���������� ������� � �������
// ������������ ��������� �� �����������
struct State
{
	int x, y, k;
	State(int _x = 0, int _y = 0, int _k = 0) :x(_x), y(_y), k(_k) {}
};

bool KnightTour(int** board, int n, int pos_x, int pos_y)
{
	int length = n * n - 1;               // ������� ����
	State* moves = new State[length + 1]; // �������� ����
	int step_number = 0;                  // ���� �� �� ������
	board[--pos_x][--pos_y] = 1;          // ��������� ������������ ����
	State curr(pos_x, pos_y, 0);
	moves[step_number] = curr;            // � ���� �����
	do
	{
		bool success = false;  // �������� ��������� ����
		int new_x, new_y;      // ���������� ��������� ����
		while (curr.k < 8 && !success)
		{                      // ������ ������� �����������
			new_x = curr.x + dx[curr.k];
			new_y = curr.y + dy[curr.k];
			success = 0 <= new_x && new_x < n && 0 <= new_y && new_y < n
				&& board[new_x][new_y] == 0;
			++curr.k;
		}
		if (success)
		{            // ������� �����������
			moves[++step_number] = curr;       // �����'������� ���
			board[new_x][new_y] = step_number + 1;
			curr = State(new_x, new_y, 0);     // ����� ���� �����
		}
		else         // ����������� �� ��� �����
		{
			board[curr.x][curr.y] = 0;        // �������� �������
			curr = moves[step_number--];      // ��������� ����
		}
	} while (step_number < length && step_number >= 0);
	delete[] moves;
	return step_number == length;
}

void SolveTour()
{
	int n;                                  // ����� ���������
	cout << "������ ����� ���������: "; cin >> n;
	int** board = BuildBoard(n);            // �������� �������� ���������
	int pos_x, pos_y;                       // �������� ���������� ����
	cout << "������ ���������� x y ������� ���� (1<=x,y<=" << n << "): ";
	cin >> pos_y >> pos_x;
	bool success = KnightTour(board, n, pos_x, pos_y); // ������ ��� ����
	// ��������� ���������� � ��������� ���'��
	if (success)
	{
		cout << "\n       �������� ��� ����\n---------------------------------\n\n";
		WriteBoard(board, n);
	}
	else cout << "\n       ����'���� �� �������\n";
	EraseBoard(board);
}
