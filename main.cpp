#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;
typedef enum {add, sub, mul} operation;

int main()
{
	inf_int num1, num2, res1, res2;
	int int_num1, int_num2;
	int operation_index;

	int num_correct = 0;
	int num_wrong = 0;

	// num1 = 37; num2 = -47;
	// res1 = num1 * num2;
	// cout << res1 << endl;

	for(int i = 0; i < 1000000; i++) {
		num1 = int_num1 = rand() % 10000 - 5000;
		num2 = int_num2 = rand() % 10000 - 5000;
		cout << '[' << i << '/' << "1000000]" << endl;

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

		default:
			break;
		}
		if(res1 == res2)
			num_correct++;
		else
			num_wrong++;
	}

	cout << "correct: " << num_correct << "worng: " << num_wrong << endl;

	return 0;
}
