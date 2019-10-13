#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;
typedef enum {add, sub, mul} operation;


int main()
{	
	srand(time(0));
	inf_int num1, num2, res1, res2;	
	int int_num1, int_num2;
	int operation_index;


	int num_correct = 0;
	int num_wrong = 0;

	for(int i = 0; i < 100000; i++) {
		// sample
		num1 = int_num1 = rand() % 10000 - 5000;
		num2 = int_num2 = rand() % 10000 - 5000;
		if (!(i%10000))
			cout << '[' << i << '/' << "100000] " << "[correct: " << num_correct << ']' << " [worng: "<< num_wrong << ']'<< endl;

		switch (rand()%3) {
		case add:
			res1 = num1 + num2;
			res2 = int_num1 + int_num2;
			if (res1 != res2)
				cout << num1 << "+" << num2 << "=" << res1 << "=" << res2 << endl;
				break;

		case sub:
			res1 = num1 - num2;
			res2 = int_num1 - int_num2;
			if (res1 != res2)
				cout << num1 << "-" << num2 << "=" << res1 << "=" << res2 << endl;
				break;

		case mul:
			res1 = num1 * num2;
			res2 = int_num1 * int_num2;
			if (res1 != res2)
				cout << num1 << "*" << num2 << "=" << res1 << "=" << res2 << endl;
				break;
		}

		if(res1 == res2)
			num_correct++;
		else
			num_wrong++;
	}

	cout << "correct: " << num_correct << " worng: " << num_wrong << endl;

	return 0;
}