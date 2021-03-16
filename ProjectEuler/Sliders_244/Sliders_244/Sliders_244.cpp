// Sliders_244.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//

#include "pch.h"
#include <iostream>
#include <algorithm>    // std::remove_copy_if
#include <vector> 
#include <string>
#define L 76
#define R 82
#define U 85
#define D 68
#define W 87
#define B 66
#include <queue> 
void GetBoard(int N, int &endX, int &endY, std::vector<std::vector<int>> &finishBoard);


struct Pos {
	int x = 0, y = 0;

	Pos(int x, int y) : x(x), y(y) {}

	friend bool operator==(Pos const& x, Pos const& p2);



};
bool operator==(Pos const& x, Pos const& p2) {
	return  x.x == p2.x && x.y == p2.y;
}

long long getChecksum(std::vector<unsigned char> commands) {
	long long check = 0;

	for (auto it = commands.begin(); it != commands.end(); ++it) {


		check = ((check * 243LL) + *it) % 100000007LL;
		//std::cout << *it << " and check: " << check << std::endl;
	}
	return check;
}

bool isValidMove(int x, int y, int N, int nextCommand) {
	if (nextCommand == R) return ((x - 1) >= 0);
	if (nextCommand == D) return ((y - 1) >= 0);
	if (nextCommand == L) return ((x + 1) < (N));
	if (nextCommand == U) return ((y + 1) < (N));
}
void GetBoard(int N, int &endX, int &endY, std::vector<std::vector<unsigned char>> &finishBoard)
{
	for (int x = 0; x < N; x++) {
		std::vector<unsigned char> row;
		finishBoard.push_back(row);
	}
	for (int x = 0; x < N; x++) {
		std::vector<int> row;
		for (int y = 0; y < N; y++) {
			char inh;
			std::cin >> inh;
			finishBoard[y].push_back((unsigned char)inh);
			if (inh == W) {
				endX = x;
				endY = y;
			}
		}
		//finishBoard.push_back(row);
	}
}
std::vector<std::vector<unsigned char>> CreateNewPath(std::vector<unsigned char> in, int lenght) {
	std::vector<std::vector<unsigned char>> v;
	if (lenght <= 0) {
		//v.push_back({0});
		return v;
	}
	else {
		auto b = CreateNewPath(in, lenght - 1);
		for (auto i = in.begin(); i != in.end(); ++i) {


			if (b.size() != 0) {
				for (auto c = b.begin(); c != b.end(); ++c) {
					std::vector<unsigned char> output;
					output.push_back(*i);
					output.insert(output.end(), c->begin(), c->end());
					v.push_back(output);
				}
			}
			else {
				std::vector<unsigned char> output;
				output.push_back(*i);
				v.push_back(output);
			}

		}
		return v;
	}

}
bool CheckPath(int startX, int startY, int endX, int endY, int N, std::vector<unsigned char> *pathToDo) {
	int x = startX; int y = startY;

	for (auto command = pathToDo->begin(); command != pathToDo->end(); ++command) {
		if (((*command) != -1) && isValidMove(x, y, N, (*command))) {
			switch ((*command)) {
			case L:
				x += 1;
				break;
			case R:
				x -= 1;
				break;
			case U:
				y += 1;
				break;
			case D:
				y -= 1;
				break;
			default:
				break;
			}

		}
		else {
			return false;
		}
	}
	if (x == endX && y == endY) {
		//std::cout << "Raggiunta la fine!\n" << std::endl;
		return true;
	}
	return false;
}
std::vector <std::vector<unsigned char>> CheckBoard(std::vector <std::vector<unsigned char>> board, std::vector <std::vector<unsigned char>> endBoard, std::vector<unsigned char> path, int stx, int sty, int enx, int eny) {
	int x = stx; int y = sty;
	int tmp = 0;

	for (auto c = path.begin(); c != path.end(); ++c) {
		switch ((*c)) {
		case L:
			tmp = board[x][y];
			board[x][y] = board[x + 1][y];
			board[x + 1][y] = tmp;
			x += 1;

			break;
		case R:
			tmp = board[x][y];
			board[x][y] = board[x - 1][y];
			board[x - 1][y] = tmp;

			x -= 1;
			break;
		case U:
			tmp = board[x][y];
			board[x][y] = board[x][y + 1];
			board[x][y + 1] = tmp;

			y += 1;
			break;
		case D:
			tmp = board[x][y];
			board[x][y] = board[x][y - 1];
			board[x][y - 1] = tmp;

			y -= 1;
			break;
		default:
			break;
		}
		tmp = 0;
	}
	return board;
}
template<typename T>
bool isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
{
	return (v1.size() == v2.size() &&
		std::equal(v1.begin(), v1.end(), v2.begin()));
}
bool equalsBoards(std::vector <std::vector<unsigned char>> board, std::vector <std::vector<unsigned char>> endBoard) {
	/*for (int x = 0; x < board.size(); ++x) {
		for (int y = 0; y < board[0].size(); ++y) {
			if (board[x][y] != endBoard[x][y]) {
				return false;
			}
		}
	}
	return true;*/
	return isEqual(board, endBoard);
}
void convert_to_base(long long number, char result[], int base, int number_of_digits) {
	for (int i = number_of_digits - 1; i >= 0; i--) {
		long long remainder = number % base;
		number = number / base;
		result[i] = '0' + remainder;
	}
}
std::vector<unsigned char> ConvertToCommandVector(std::vector<unsigned char> pos, int x, int y, int n) {
	std::vector<unsigned char> data;
	for (auto i = pos.begin(); i != pos.end(); ++i) {
		if ((n*y + (x + 1)) == *i) {
			data.push_back(L);
			x += 1;
		}
		else if ((n*y + (x - 1)) == *i) {
			data.push_back(R);
			x -= 1;
		}
		else if ((n*(y - 1) + x) == *i) {
			data.push_back(D);
			y -= 1;
		}
		else if ((n*(y + 1) + x) == *i) {
			data.push_back(U);
			y += 1;
		}
	}
	return data;
}
void ShowBoard(std::vector <std::vector<unsigned char>> board) {
	for (auto y = board.begin(); y != board.end(); ++y) {
		for (auto x = y->begin(); x != y->end(); ++x) {
			std::cout << (*x) << "|";
		}
		std::cout << std::endl;
	}
}
int isNotVisited(int x, std::vector<unsigned char>& path)
{
	int size = path.size();
	for (int i = 0; i < size; i++)
		if (path[i] == x)
			return 0;
	return 1;
}
std::vector<std::vector<unsigned char>> findpaths(std::vector <std::vector<unsigned char>> startB, std::vector <std::vector<unsigned char>> endB, std::vector<std::vector<unsigned char>> graph, int src, int dst, int v,int n,int startX, int startY,int ex,int ey) {

	std::vector<std::vector<unsigned char>> paths;
	std::queue<std::vector<unsigned char> > q;

	std::vector<unsigned char> path;
	path.push_back(src);

	q.push(path);
	bool lastIteration = false;
	unsigned int result = 0;
	while (!lastIteration) {
		path = q.front();
		q.pop();
		int last = path[path.size() - 1];
		if (last == dst) {
			paths.push_back(path);
			auto Cpath = ConvertToCommandVector(path, startX, startY, n);
			if (CheckPath(startX, startY, ex, ey, n, &Cpath)) {
				auto newBoard = CheckBoard(startB, endB, Cpath, startX, startY, ex, ey);
				if (isEqual(newBoard, endB)) {
					for (auto e = Cpath.begin(); e != Cpath.end(); ++e) {
						std::cout << (char)(*e) << "";
					}
					auto checksum = getChecksum(Cpath);
					result += checksum;
					std::cout << " Checksum: " << checksum;

					std::cout << std::endl;
					ShowBoard(newBoard);
					lastIteration = true;
				}
			}
		}

		for (int i = 0; i < graph[last].size(); i++) {
			if (isNotVisited(graph[last][i], path)) {
				std::vector<unsigned char> newpath(path);
				newpath.push_back(graph[last][i]);
				q.push(newpath);
			}
		}
	}
	return paths;
}
int main()
{
	int n = 3, m = 16;
	std::vector<std::vector<unsigned char>> graph;



	int N = 0;
	std::cin >> N;

	graph.resize(N*N);
	if (N == 2) {
		graph[0] = { 1,2 };
		graph[1] = { 0,3 };
		graph[2] = { 0,3 };
		graph[3] = { 2,1 };
	}
	if (N == 3) {
		graph[0] = { 1,3 };
		graph[1] = { 1,2,4 };
		graph[2] = { 1,5 };
		graph[3] = { 0,4,6 };
		graph[4] = { 1,5,3,7 };
		graph[5] = { 2,4,8 };
		graph[6] = { 3,7 };
		graph[7] = { 6,4,8 };
		graph[8] = { 5,7 };
	}


	std::vector <std::vector<unsigned char>> startBoard;
	std::vector <std::vector<unsigned char>> finishBoard;
	int startX = 0, startY = 0;
	//start board
	GetBoard(N, startX, startY, startBoard);
	int endX = 0, endY = 0;
	//finish board
	GetBoard(N, endX, endY, finishBoard);

	int src = (startY * N) + startX;
	int dst = (endY * N) + endX;
	auto path = findpaths(startBoard, finishBoard,graph, src, dst, N*N,N,startX,startY,endX,endY);

	unsigned int result = 0;

	bool found = false, end = false;
	for (auto i = path.begin(); i != path.end(); ++i) {
		/*auto Cpath = ConvertToCommandVector(*i, startX, startY, N);*/
		/*if (CheckPath(startX, startY, endX, endY, N, &Cpath)) {
			auto newBoard = CheckBoard(startBoard, finishBoard, Cpath, startX, startY, endX, endY);
			if (equalsBoards(newBoard, finishBoard)) {
				for (auto e = Cpath.begin(); e != Cpath.end(); ++e) {
					std::cout << (char)(*e) << "";
				}
				auto checksum = getChecksum(Cpath);
				result += checksum;
				std::cout << " Checksum: " << checksum;

				std::cout << std::endl;
				ShowBoard(newBoard);
			}
		}*/
	}

	auto check = result;
	std::cout << " Checksum: " << check;
	std::cout << " Checksum: " << check % 100000007LL;
}


