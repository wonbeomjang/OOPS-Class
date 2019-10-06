#include "inf_int.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>

using namespace std;

int main()
{
	inf_int a("100");
	inf_int b("9913414");
	inf_int c = b * a;

	cout << c;
	return 0;
}


