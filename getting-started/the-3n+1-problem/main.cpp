#include <iostream>
using namespace std;

int main() {
	unsigned int x, y, z, max, trial, larger, smaller;

	while (cin >> x >> y) {
		max = 0;
		if (x > y)
			larger = x, smaller = y;
		else
			larger = y, smaller = x;

		unsigned int tries[larger + 1];
		for (unsigned int i = 1; i < larger +1; i++){
			tries[i] = 0;
		}

		for (unsigned int i = 1; i <= larger; i++) {
			z = i;
			trial = 1;
			while (z != 1) {
				if (z % 2 == 0) {
					if (z/2 <larger+1 && z<i) {
						trial += tries[z / 2];
						break;
					}
					else{
						z /=2;
					}
				} else {
					z = z * 3 + 1;
				}
				trial++;
			}
			tries[i] = trial;
		}
		for (unsigned int i = smaller; i<= larger; i++){
			if (tries[i] > max) max = tries[i];
		}

		cout << x << " " << y << " " << max << endl;
	}
	return 0;
}