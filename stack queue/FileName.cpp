#include "DyArray.h"
#include <cstring>
using namespace Dynamic;
using namespace std;
int main()
{
	while (true)
	{
		std::string operation;
		cout << "enter operation: ";
		std::getline(std::cin, operation);
		cout << calculate(operation);
		cout << endl;
	}
}