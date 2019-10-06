#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

int main()
{
	inf_int a("-10");
	inf_int b("9");

	cout << (a - b);
	return 0;
}


