#include <iostream>
using namespace std;

int abs(int value){
	if (value <0)
		return -value;
	else return value;
}

int main() {
	int noOfDigits;
	bool isJolly;
	int x, y;
	int n;

	while (cin >> noOfDigits) {
		isJolly = true;

		bool diff[noOfDigits];
		for (unsigned int i = 0;  i < sizeof(diff) / sizeof(diff[0]); i++)
			diff[i] = false;

		n = 1;
		cin >> x;

		while (++n <= noOfDigits) {
			cin >> y;
			if (abs(x-y) == 0 || abs(x - y) > noOfDigits - 1 || diff[abs(x - y)]) {
				isJolly = false;
			} else {
				diff[abs(x - y)] = true;
			}
			x = y;
		}

		(isJolly)? cout << "Jolly\n" : cout << "Not jolly\n";
	}

	return 0;
}