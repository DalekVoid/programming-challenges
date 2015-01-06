#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

#define DEBUG false
#define _DEBUG if(DEBUG)
#define _TODO if(false)

const string msg_bk = "Black wins.\n";
const string msg_wh = "White wins.\n";
const string msg_tie = "Tie.\n";

enum SUITS {
	CLUB = 0, DIAMOND = 13, HEART = 26, SPADE = 39
};

enum VALUES {
	TWO = 0,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	ERR
};

enum HAND {
	HIGH_CARD,
	PAIR,
	TWO_PAIRS,
	THREE_OF_A_KIND,
	STRAIGHT,
	FLUSH,
	FULL_HOUSE,
	FOUR_OF_A_KIND,
	STRAIGHT_FLUSH
};

enum RESULT {
	BLACK, WHITE, TIE
};

bool sortByValue(char c1, char c2) {
	return (c1 % 13 < c2 % 13);
}

int convertSuit(char c) {
	switch (c) {
	case 'C':
		return CLUB;
	case 'D':
		return DIAMOND;
	case 'H':
		return HEART;
	case 'S':
		return SPADE;
	}
}

int convertValue(char c) {
	switch (c) {
	case 'A':
		return ACE;
	case '2':
		return TWO;
	case '3':
		return THREE;
	case '4':
		return FOUR;
	case '5':
		return FIVE;
	case '6':
		return SIX;
	case '7':
		return SEVEN;
	case '8':
		return EIGHT;
	case '9':
		return NINE;
	case 'T':
		return TEN;
	case 'J':
		return JACK;
	case 'Q':
		return QUEEN;
	case 'K':
		return KING;
	}
}

inline SUITS getSuit(char c) {
	int i = c / 13;
	switch (i) {
	case 0:
		return CLUB;
	case 1:
		return DIAMOND;
	case 2:
		return HEART;
	case 3:
		return SPADE;
	}
}

inline VALUES getValue(char c) {
	int i = c % 13;
	switch (i) {
	case 0:
		return TWO;
	case 1:
		return THREE;
	case 2:
		return FOUR;
	case 3:
		return FIVE;
	case 4:
		return SIX;
	case 5:
		return SEVEN;
	case 6:
		return EIGHT;
	case 7:
		return NINE;
	case 8:
		return TEN;
	case 9:
		return JACK;
	case 10:
		return QUEEN;
	case 11:
		return KING;
	case 12:
		return ACE;
	}
}

bool checkFlush(vector<char> v) {
	SUITS s = getSuit(*v.begin());
	for (vector<char>::iterator it = v.begin() + 1; it != v.end(); it++) {
		if (getSuit(*it) != s)
			return false;
	}
	return true;
}

VALUES getHighCard(vector<char> v) {
	return getValue(*(v.end() - 1));
}

RESULT compareHighCards(vector<char> v1, vector<char> v2) {
	vector<char>::reverse_iterator vit1 = v1.rbegin();
	vector<char>::reverse_iterator vit2 = v2.rbegin();

	for (; vit1 != v1.rend() && vit2 != v2.rend(); vit1++, vit2++) {
		if (getValue(*vit1) != getValue(*vit2))
			return (getValue(*vit1) < getValue(*vit2)) ? WHITE : BLACK;
	}
	return TIE;
}

bool checkStraight(vector<char> v) {
	VALUES val = getValue(*v.begin());
	vector<char>::iterator it;
	for (it = v.begin() + 1; it != v.end() - 1; it++) {
		if (getValue(*it) - val != 1)
			return false;
		else
			val = getValue(*it);
	}

	/*if (getValue(*it) == ACE)
		return (ACE - val == 1 || ACE - val == 12);
	else*/
		return (getValue(*it) - val == 1);
}

bool checkDistinct(vector<char> v) {
	VALUES val = getValue(*v.begin());
	for (vector<char>::iterator it = v.begin() + 1; it != v.end(); it++) {
		if (getValue(*it) == val)
			return false;
		else
			val = getValue(*it);
	}
	return true;
}

HAND determineHandType(vector<char> v, VALUES& pair1Value, VALUES& pair2Value) {
	pair1Value = ERR, pair2Value = ERR;
	if (checkDistinct(v)) {
		if (checkStraight(v))
			return (checkFlush(v)) ? STRAIGHT_FLUSH : STRAIGHT;
		else
			return (checkFlush(v)) ? FLUSH : HIGH_CARD;
	} else {
		int pairlen1 = 1, pairlen2 = 1;
		VALUES val = getValue(*v.begin());
		vector<char>::iterator it;

		for (it = v.begin() + 1; it != v.end(); it++) {
			if (getValue(*it) == val) {
				pair1Value = val;
				pairlen1++;
			} else {
				if (pairlen1 == 1)
					val = getValue(*it);
				else {
					val = getValue(*it++);
					break;
				}
			}
		}

		for (; it != v.end(); it++) {
			if (getValue(*it) == val) {
				pairlen2++;
				pair2Value = val;
			} else {
				if (pairlen2 == 1)
					val = getValue(*it);
				else {
					val = getValue(*it++);
					break;
				}
			}
		}

		int maxPairLen = (pairlen1 < pairlen2) ? pairlen2 : pairlen1;
		int minPairLen = (pairlen1 < pairlen2) ? pairlen1 : pairlen2;

		if(pairlen2>pairlen1){
			VALUES temp = pair2Value;
			pair2Value = pair1Value;
			pair1Value = temp;
		}
		if(pairlen1 == pairlen2 == 2 && pair2Value>pair1Value){
			VALUES temp = pair2Value;
			pair2Value = pair1Value;
			pair1Value = temp;
		}

		//cout << pair1Value << endl;

		if (maxPairLen == 4)
			return FOUR_OF_A_KIND;
		else if (maxPairLen == 3 && minPairLen == 2)
			return FULL_HOUSE;
		else if (maxPairLen == 3 && minPairLen == 1)
			return THREE_OF_A_KIND;
		else if (maxPairLen == 2 && minPairLen == 2)
			return TWO_PAIRS;
		else
			return PAIR;
	}
}

int main() {
	string str;
	vector<char> blackCards, whiteCards;
	VALUES blackPair1Value, blackPair2Value, whitePair1Value, whitePair2Value;
	HAND blackHand, whiteHand;

	RESULT result;
	while (getline(cin, str) && str != "") {
		//cout << str << endl;
		string::iterator it = str.begin();

		//push black cards into container
		for (int i = 0; i < 5; i++, it++)
			blackCards.push_back(convertValue(*it++) + convertSuit((*it++)));

		//push white cards into container
		for (int i = 0; i < 5; i++, it++)
			whiteCards.push_back(convertValue(*it++) + convertSuit((*it++)));

		//sorting according to the value
		sort(blackCards.begin(), blackCards.end(), sortByValue);
		sort(whiteCards.begin(), whiteCards.end(), sortByValue);

		_TODO {
			for (vector<char>::iterator it = blackCards.begin(); it
					!= blackCards.end(); it++)
				cout << (int) (*it) << " ";
			cout << endl;
			for (vector<char>::iterator it = whiteCards.begin(); it
					!= whiteCards.end(); it++)
				cout << (int) (*it) << " ";
			cout << endl;
		}

		//determine the hand type of players
		blackHand = determineHandType(blackCards, blackPair1Value,
				blackPair2Value);
		whiteHand = determineHandType(whiteCards, whitePair1Value,
				whitePair2Value);

		_DEBUG{
			switch (blackHand) {
			case HIGH_CARD:
				cout << "bk hand = high card\n"; break;
			case STRAIGHT:
				cout << "bk hand = st\n";break;
			case STRAIGHT_FLUSH:
				cout << "bk hand = stfl\n";break;
			case FLUSH:
				cout << "bk hand = fl\n";break;
			case FOUR_OF_A_KIND:
				cout << "bk hand = fourkind\n";break;

			case FULL_HOUSE:
				cout << "bk hand = full house\n";break;

			case THREE_OF_A_KIND:
				cout << "bk hand = three kind\n";break;
			case TWO_PAIRS:
				cout << "bk hand = two pairs\n";break;
			case PAIR:
				cout << "bk hand = one pair\n";break;
			}
			switch (whiteHand) {
			case HIGH_CARD:
				cout << "wh hand = high card\n"; break;
			case STRAIGHT:
				cout << "wh hand = st\n";break;
			case STRAIGHT_FLUSH:
				cout << "wh hand = stfl\n";break;
			case FLUSH:
				cout << "wh hand = fl\n";break;
			case FOUR_OF_A_KIND:
				cout << "wh hand = fourkind\n";break;

			case FULL_HOUSE:
				cout << "wh hand = full house\n";break;

			case THREE_OF_A_KIND:
				cout << "wh hand = three kind\n";break;
			case TWO_PAIRS:
				cout << "wh hand = two pairs\n";break;
			case PAIR:
				cout << "wh hand = one pair\n";break;
			}
		}

		//determine which player has higher hands
		if (blackHand == whiteHand) {
			//TODO
			switch (blackHand) {
			case HIGH_CARD:
			case STRAIGHT:
			case STRAIGHT_FLUSH:
			case FLUSH:
				result = compareHighCards(blackCards, whiteCards);
				break;
			case FOUR_OF_A_KIND:
			case FULL_HOUSE:
			case THREE_OF_A_KIND:
				_DEBUG cout << blackPair1Value << " "<<whitePair1Value << endl;
				result = (blackPair1Value > whitePair1Value) ? BLACK : WHITE;
				break;
			case TWO_PAIRS:
				if (blackPair1Value == whitePair1Value) {
					if (blackPair2Value == whitePair2Value)
						result = compareHighCards(blackCards, whiteCards);
					else
						result = (blackPair2Value > whitePair2Value) ? BLACK
								: WHITE;
				} else
					result = (blackPair1Value > whitePair1Value) ? BLACK
							: WHITE;
				break;
			case PAIR:
				if (blackPair1Value == whitePair1Value) {
					result = compareHighCards(blackCards, whiteCards);
					//_DEBUG cout << "cmp high cards\n";
				} else {
					//_DEBUG cout << "cmp values\n";
					result = (blackPair1Value > whitePair1Value) ? BLACK
							: WHITE;
				}
				break;
			}
		} else
			result = (blackHand > whiteHand) ? BLACK : WHITE;

		//output result
		switch (result) {
		case BLACK:
			cout << msg_bk;
			break;
		case WHITE:
			cout << msg_wh;
			break;
		case TIE:
			cout << msg_tie;
			break;
		}

		//clear
		blackCards.clear();
		whiteCards.clear();
	}

	return 0;
}