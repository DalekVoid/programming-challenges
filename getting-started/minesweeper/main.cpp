#include <iostream>
using namespace std;
int main() {
	int width, height, testcaseNo = 1;
	char c;
	while (cin >> height >> width) {
		//dont process cases which height and width both equal zero
		if (!(height == 0 && width == 0)) {

			//create and initialization of minefield
			bool minefield[height + 2][width + 2];
			int count[height + 2][width + 2];

			for (int y = 0; y < height + 2; y++)
				for (int x = 0; x < width + 2; x++) {
					minefield[y][x] = 0;
					count[y][x] = 0;
				}

			cin.get(c);
			for (int y = 1; y <= height; y++) {
				for (int x = 1; x <= width; x++) {
					cin.get(c);
					minefield[y][x] = (c == '*') ? true : false;
				}
				cin.get(c);
			}

			//calculation
			for (int y = 1; y <= height; y++)
				for (int x = 1; x <= width; x++)
					if (minefield[y][x]) {
						count[y + 1][x + 1]++;
						count[y + 1][x]++;
						count[y + 1][x - 1]++;

						count[y][x + 1]++;
						count[y][x]++;
						count[y][x - 1]++;

						count[y - 1][x + 1]++;
						count[y - 1][x]++;
						count[y - 1][x - 1]++;
					}

			//output
			if(testcaseNo != 1) cout<< endl;
			cout << "Field #" << testcaseNo << ":\n";
			for (int y = 1; y <= height; y++) {
				for (int x = 1; x <= width; x++)
					if (minefield[y][x])
						cout << '*';
					else
						cout << count[y][x];
				cout << endl;
			}

			//increment testcaseNo
			testcaseNo++;
		}
	}
	return 0;
}