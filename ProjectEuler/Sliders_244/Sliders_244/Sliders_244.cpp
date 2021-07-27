#include "pch.h"
#include <iostream>
#include <algorithm> 
#include <vector> 
#include <string>
#include <tuple>
#include <queue> 
#define L 76
#define R 82
#define U 85
#define D 68
#define W 87
#define B 66

long long getChecksum(int src, int n, std::vector<unsigned char> commands) {
	long long check = 0;

	for (auto i = commands.begin(); i != commands.end(); ++i) {
		long long c = 0;
		if (src + 1 == *i) {
			c = L;
			src += 1;
		}
		else if (src - 1 == *i) {
			c = R;
			src -= 1;
		}
		else if (src - n == *i) {
			c = D;
			src -= n;
		}
		else if (src + n == *i) {
			c = U;
			src += n;
		}
		if (c != 0)
			check = ((check * 243LL) + c) % 100000007LL;
	}
	return check;
}

std::tuple<int, std::vector<unsigned char>> GetBoard(int N)
{
	int end = 0, dim = N * N;
	std::vector<unsigned char> board;

	for (int x = 0; x < dim; x++) {
		char inh;
		std::cin >> inh;
		board.push_back((unsigned char)inh);
		if (inh == W)
			end = x;
	}
	return { end,board };
}

template<typename T>
bool isEqual(std::vector<T> const &v1, std::vector<T> const &v2)
{
	return (v1.size() == v2.size() &&
		std::equal(v1.begin(), v1.end(), v2.begin()));
}
bool CheckBoard(
	std::vector<unsigned char> board,
	std::vector<unsigned char> endBoard,
	std::vector<unsigned char> path,
	int src, int dst, int n) {

	unsigned char tmp = 0;

	for (auto i = path.begin(); i != path.end(); ++i) {
		tmp = board[src];
		if (src + 1 == *i) {
			board[src] = board[src + 1];
			board[src + 1] = tmp;
			src += 1;
		}
		else if (src - 1 == *i) {
			board[src] = board[src - 1];
			board[src - 1] = tmp;
			src -= 1;
		}
		else if (src - n == *i) {
			board[src] = board[src - n];
			board[src - n] = tmp;
			src -= n;
		}
		else if (src + n == *i) {
			board[src] = board[src + n];
			board[src + n] = tmp;
			src += n;
		}
	}
	return (src == dst) && isEqual(board, endBoard);					//Check if the board is equal to the end one
}

int isNotVisited(std::vector<std::vector<unsigned char>>& history, int nextMove, std::vector<unsigned char>& path)
{
	if (path.size() >= 2 && nextMove == path[path.size() - 2]) return 0;
	for (auto i = history.begin(); i != history.end(); ++i) {
		if (i->size() == path.size() + 1) {
			if ((*i)[i->size() - 1] == nextMove) {
				for (auto p = 0; p < i->size() - 1; ++p) {	//qui verifico se tutto il path è lo stesso
					if ((*i)[p] != path[p]) return 1;
				}
				return 0;
			}
		}
	}
	return 1;
}

long findpaths(std::vector<unsigned char> start, std::vector<unsigned char> end, std::vector<std::vector<unsigned char>> graph, int n, int src, int dst) {

	std::vector<std::vector<unsigned char>> paths, pathsHistory;
	std::queue<std::vector<unsigned char>> q;						//save the paths being done
	std::vector<unsigned char> path;								//current path

	path.push_back(src);											//Create the initalized path position 0
	q.push(path);

	long long result = 0;
	int limit = INT32_MAX;
	while (q.size() != 0) {

		path = q.front();
		q.pop();
		int last = path[path.size() - 1];

		if (last == dst && path.size() > 1 && path.size() < limit) {
			paths.push_back(path);
			if (CheckBoard(start, end, path, src, dst, n)) {


				result += getChecksum(src, n, path);
				std::cout << " Checksum: " << result << "  Result " << result << std::endl;
				if (path.size() < limit)
					limit = path.size();
			}
		}
		if (path.size() < limit) {
			bool foundNewPath = false;
			for (int i = 0; i < graph[last].size(); i++) {
				if (isNotVisited(pathsHistory, graph[last][i], path)) {
					std::vector<unsigned char> newpath(path);
					newpath.push_back(graph[last][i]);
					pathsHistory.push_back(newpath);
					q.push(newpath);
					foundNewPath = true;
				}
			}
			if (foundNewPath) {
				auto i_index = std::find(pathsHistory.begin(), pathsHistory.end(), path);
				if (i_index != pathsHistory.end()) {
					pathsHistory.erase(i_index);
				}
			}
		}
	}
	return result;
}
int main()
{
	std::vector<std::vector<unsigned char>> graph;

	int N = 0;
	std::cin >> N;

	graph.resize(N*N);
	if (N == 2) {
		graph = { { 1,2 } ,{ 0,3 } ,{ 0,3 },{ 2,1 } };
	}
	if (N == 3) {
		graph = { {1,3},{0,4,2},{1,5},{0,4,6},{1,5,7,3},{2,4,8},{3,7},{6,4,8},{7,5} };
	}

	auto[start, startBoard] = GetBoard(N);				//Start Board
	auto[end, finishBoard] = GetBoard(N);				//Finish Board

	auto result = findpaths(startBoard, finishBoard, graph, N, start, end);

	std::cout << " Checksum: " << result;
	std::cout << " Checksum: " << result % 100000007LL;
}