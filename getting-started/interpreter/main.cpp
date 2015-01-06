#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <vector>
#include <functional>
using namespace std;

#define DEBUG false
#define _DEBUG if(DEBUG)

class MemSpace {
private:
	unsigned int data;
public:
	MemSpace() :
		data(0) {
	}

	MemSpace(unsigned int i) {
		data = i % 1000;
	}

	MemSpace(const MemSpace& ms) {
		data = ms.data % 1000;
	}

	~MemSpace() {
	}

	operator int() {
		return data;
	}

	MemSpace& operator+=(unsigned int i) {
		this->data = (this->data + i) % 1000;
		return *this;
	}

	MemSpace& operator*=(unsigned int i) {
		this->data = (this->data * i) % 1000;
		return *this;
	}

	bool operator==(const MemSpace& ms) const {
		if (this->data == ms.data)
			return true;
		else
			return false;
	}

	MemSpace& operator=(unsigned int i) {
		this->data = i % 1000;
		return *this;
	}

	void reset(){
		this->data = 0;
	}

	unsigned int read1() const{
		return data/100;
	}

	unsigned int read2() const{
		return data%100/10;
	}

	unsigned int read3() const{
		return data%10;
	}

	friend ostream& operator>>(ostream& os, const MemSpace&);
};

ostream& operator>>(ostream& os, const MemSpace& ms){
	return os>>ms.data;
}


int main(){
	unsigned int inputNo;
	vector<MemSpace> registers(10);
	vector<MemSpace> RAM(1000);

	//fetch no of test cases
	cin >> inputNo;

	//execute each test case
	for(int caseNo = 0; caseNo < inputNo; caseNo++){
		unsigned int executionNo = 0;
		unsigned int RAMused = 0;
		unsigned int sp;//stack pointer showing the current executing line

		//initialize memory
		unsigned int input;
		while(cin >> input){
			RAM[RAMused++] = input;
			cin.ignore();
			if (cin.peek() == '\n') break;
		}

		/*
		cout << "RAMused: " << RAMused << endl;
		for(unsigned int i = 0; i<10;i++)
			cout << "reg" << i << ": "<< registers[i] << endl;
		cout << endl;
		for(unsigned int i = 0;i < RAMused; i++)
			cout << "RAM" << i << ": "<< RAM[i] << endl;
		*/

		//display result
		unsigned char command;
		unsigned char destination;
		unsigned char source;
		unsigned char number;
		unsigned char address;
		for(sp = 0; sp<1000; sp++){
			executionNo++;
			command = RAM[sp].read1();
			destination = RAM[sp].read2();
			source = number = address = RAM[sp].read3();
			_DEBUG cout << "executing line "<< sp << " command ";
			switch(command){
				case 1:
					//halt
					sp = 999;
					_DEBUG cout << "1: halt\n";
					break;
				case 2:
					//set register d to n
					_DEBUG cout << "2: register "<< (int)destination << " " <<registers[destination] << "->" << (int)number << endl;
					registers[destination] = number;
					break;
				case 3:
					//add n to register d
					_DEBUG cout << "3: register "<< (int)destination << " " <<registers[destination] << "->";
					registers[destination] += number;
					_DEBUG cout << registers[destination] << endl;
					break;
				case 4:
					//multiply register d by n
					_DEBUG cout << "4: register "<< (int)destination << " " <<registers[destination] << "->";
					registers[destination] *= number;
					_DEBUG cout << registers[destination] << endl;
					break;
				case 5:
					//set register d to value of register s
					_DEBUG cout << "5: register "<< (int)destination << " " <<registers[destination] << "->";
					registers[destination] = registers[source];
					_DEBUG cout << registers[destination] << endl;
					break;
				case 6:
					//add the value of register s to register d
					_DEBUG cout << "6: register "<< (int)destination << " " <<registers[destination] << "->";
					registers[destination] += registers[source];
					_DEBUG cout << registers[destination] << endl;
					break;
				case 7:
					//multiply register d by the value of register s
					_DEBUG cout << "7: register "<< (int)destination << " " <<registers[destination] << "->";
					registers[destination] *= registers[source];
					_DEBUG cout << registers[destination] << endl;
					break;
				case 8:
					//set register d to the value in RAM whose address is in register a
					_DEBUG cout << "8: register "<< (int)destination << " " <<registers[destination] << "->";
					registers[destination] = RAM[registers[address]];
					_DEBUG cout << registers[destination] << endl;
					break;
				case 9:
					//set the value in RAM whose address is in register a to the value of register d
					_DEBUG cout << "9: RAM "<< registers[address] << " " <<RAM[registers[address]] << "->";
					RAM[registers[address]] = registers[destination];
					_DEBUG cout << RAM[registers[address]] << endl;
					break;
				case 0:
					//means goto the location in register d unless register s contains 0
					_DEBUG{
						cout << "0: register " << (int)source << " contains " << registers[source];
						if(registers[source]!=0) cout << " branch to " << registers[destination] << "."<<endl;
						else cout << " no branch." << endl;
					}
					if(registers[source]!=0) sp = registers[destination]-1;
					break;
				default:
					//halt
					break;
			}
			_DEBUG sleep(1);
		}
		if(caseNo>0) cout << endl;
		cout << executionNo << endl;

		//clean up
		for_each(registers.begin(), registers.end(), mem_fun_ref(&MemSpace::reset));
		for_each(RAM.begin(), RAM.end(), mem_fun_ref(&MemSpace::reset));
	}

	return 0;
}