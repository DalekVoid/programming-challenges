#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string>

using namespace std;

static string msg_begin = "Game #";
static string msg_black = ": black king is in check.\n";
static string msg_white = ": white king is in check.\n";
static string msg_no = ": no king is in check.\n";

enum Type {
	KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN, EMPTY
};

enum Color {
	BLACK, WHITE, BLANK
};

inline int abs(int i){
	if(i<0) return -i;
	else return i;
}

inline int min(int x, int y){
	return (x>y)?y:x;
}

inline int max(int x, int y){
	return (x>y)?x:y;
}

class Point {
public:
	int x;
	int y;
	Point(int xx, int yy) :
		x(xx), y(yy) {
	}
	;
	~Point() {
	}
	;
	bool invalid() {
		if (x < 0 || x > 7 || y < 0 || y > 7)
			return true;
		else
			return false;
	}
	Point& operator=(const Point& p){
		this->x = p.x;
		this->y = p.y;
		return *this;
	}
	void print() {
		cout << "(" << x << ", " << y << ")\n";
	}
};

static string chessboard;
static int gameCount = 0;
static Point bKingPos(-1, -1);
static Point wKingPos(-1, -1);

//identify piece types
Type getType(Point p) {
	switch (chessboard[p.y * 8 + p.x]) {
	case 'k':
		return KING;
	case 'K':
		return KING;
	case 'q':
		return QUEEN;
	case 'Q':
		return QUEEN;
	case 'r':
		return ROOK;
	case 'R':
		return ROOK;
	case 'b':
		return BISHOP;
	case 'B':
		return BISHOP;
	case 'n':
		return KNIGHT;
	case 'N':
		return KNIGHT;
	case 'p':
		return PAWN;
	case 'P':
		return PAWN;
	case '.':
		return EMPTY;
	default:
		exit(-1);
	}
}

//identify piece color
Color getColor(Point p) {
	if (isupper(chessboard[p.y * 8 + p.x]))
		return WHITE;
	else if (islower(chessboard[p.y * 8 + p.x]))
		return BLACK;
	else
		return BLANK;
}

//check if a piece checks
bool horzFree(const Point& init, const Point& target){
	for(int inc = min(init.x, target.x)+1; inc < max(init.x, target.x); inc++){
		//cout << chessboard[init.y*8+inc] << endl;
		if(chessboard[init.y*8+inc]!='.') return false;
	}
	return true;
}
bool vertFree(const Point& init, const Point& target){
	for(int inc = min(init.y, target.y)+1; inc < max(init.y, target.y); inc++){
		//cout << chessboard[inc*8+init.y] << endl;
		if(chessboard[inc*8+init.x]!='.') return false;
	}
	return true;
}
bool diagFree(const Point& init, const Point& target){
	if(init.x > target.x && init.y > target.y || init.x < target.x && init.y < target.y){
		for(int x = min(init.x, target.x)+1, y = min(init.y, target.y)+1; x < max(init.x, target.x) && y < max(init.y, target.y);){
			if (chessboard[y*8 + x] != '.') return false;
			x++; y++;
		}
	}
	else if(init.x > target.x && init.y < target.y){
		for(int x = target.x +1, y = target.y-1; x < init.x && y > init.y;){
			if (chessboard[y*8 + x] != '.') return false;
			x++; y--;
		}
	}
	else{
		for(int x = init.x+1, y = init.y-1; x < target.x && y > target.y;){
			if (chessboard[y*8 + x] != '.') return false;
			x++; y--;
		}
	}
	return true;
}

bool checkKing(const Point& p) {
	Point enemyKingPos = (getColor(p)==BLACK)?wKingPos:bKingPos;
	if(abs(p.x - enemyKingPos.x)<=1 && abs(p.y - enemyKingPos.y)<=1)
		return true;
	else return false;
}
bool checkQueen(const Point& p) {
	Point enemyKingPos = (getColor(p)==BLACK)?wKingPos:bKingPos;
	if(abs(p.x-enemyKingPos.x)==abs(p.y-enemyKingPos.y)){
		return diagFree(p, enemyKingPos);
	}
	else if(p.x!=enemyKingPos.x && p.y!= enemyKingPos.y)
		return false;
	else{
		if (p.y == enemyKingPos.y)
			return horzFree(p, enemyKingPos);
		else return vertFree(p, enemyKingPos);
	}
}
bool checkRook(const Point& p) {
	Point enemyKingPos = (getColor(p)==BLACK)?wKingPos:bKingPos;
	if(p.x!=enemyKingPos.x && p.y!= enemyKingPos.y)
		return false;
	else{
		if (p.y == enemyKingPos.y)
			return horzFree(p, enemyKingPos);
		else return vertFree(p, enemyKingPos);
	}
}
bool checkKnight(const Point& p) {
	Point enemyKingPos = (getColor(p)==BLACK)?wKingPos:bKingPos;
	if(abs(p.x - enemyKingPos.x)==2 && abs(p.y - enemyKingPos.y)==1 ||
			abs(p.x - enemyKingPos.x)==1 && abs(p.y - enemyKingPos.y)==2)
		return true;
	else return false;
}
bool checkBishop(const Point& p) {
	Point enemyKingPos = (getColor(p)==BLACK)?wKingPos:bKingPos;
	if(abs(p.x-enemyKingPos.x)==abs(p.y-enemyKingPos.y)){
		return diagFree(p, enemyKingPos);
	}
	else return false;
}

bool checkPawn(Point p) {
	Point enemyKingPos = (getColor(p)==BLACK)?wKingPos:bKingPos;
	if(getColor(p)==BLACK){
		if(abs(p.x-enemyKingPos.x)==1 && (p.y-enemyKingPos.y)==-1) return true;
		else return false;
	}
	else{
		if(abs(p.x-enemyKingPos.x)==1 && (p.y-enemyKingPos.y)==1) return true;
		else return false;
	}
}

//find out any piece checks
bool determineChecked(Point p) {
	switch(getType(p)){
	case KING:
		return checkKing(p);
	case QUEEN:
		return checkQueen(p);
	case ROOK:
		return checkRook(p);
	case BISHOP:
		return checkBishop(p);
	case KNIGHT:
		return checkKnight(p);
	case PAWN:
		return checkPawn(p);
	default:
		return false;
	}
}
//print chessboard
void printChessboard() {
	for (int i = 0; i < 64; i++) {
		cout << chessboard[i];
		if ((i + 1) % 8 == 0)
			cout << '\n';
	}
}

int main() {
	while (true) {
		//get input
		char cstr[8];
		for (int i = 0; i < 8; i++) {
			cin.getline(cstr, 9, '\n');
			chessboard += cstr;
		}

		//find the position of the kings
		size_t pos;

		pos = chessboard.find_first_of('k');
		if (pos != string::npos)
			bKingPos.x = pos % 8;
		bKingPos.y = pos / 8;

		pos = chessboard.find_first_of('K');
		if (pos != string::npos)
			wKingPos.x = pos % 8;
		wKingPos.y = pos / 8;
		//bKingPos.print();
		//wKingPos.print();
		if (bKingPos.invalid() || wKingPos.invalid())
			break;
		cin.ignore(1);

		gameCount++;

		//printChessboard();
		Point p(0, 0);
		bool incheck = false;
		//a loop to find out if checked
		for(int i =0; i < 64;i++){
			p.x = i%8; p.y = i/8;
			if(determineChecked(p)){
				if(getColor(p) == BLACK){
					cout << msg_begin << gameCount << msg_white;
					//cout << "by" << p.x << ", " << p.y << endl;
					incheck = true;
				}
				else{
					cout << msg_begin << gameCount << msg_black;
					//cout << "by" << p.x << ", " << p.y << endl;
					incheck = true;
				}
				break;
			}
		}
		if (!incheck)  cout << msg_begin << gameCount << msg_no;

		//clear
		chessboard.clear();
		bKingPos.x = -1;
		bKingPos.y = -1;
		wKingPos.x = -1;
		wKingPos.y = -1;
	}
	return 0;
}