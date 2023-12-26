#include "DyArray.h"
#include <cstring>
using namespace Dynamic;
using namespace std;
int main()
{
	DyArray<char> stack;
	DyArray<char> queue;

	const char* name = "(5+5)/2";

	int size = strlen(name);
	
	stack.add('#');

	for (int i = 0; i < size; i++)
	{
		char token = name[i];
		if (isdigit(token))
		{
			queue.add(token);
		}
		else if (token == '(')
		{
			stack.add('(');
		}
		else if (token == ')')
		{
			char tmp = stack.remove_last();
			while (tmp != '(')
			{
				queue.add(tmp);
				tmp = stack.remove_last();
			}
		}
		else
		{
			while (precedence(token) <= precedence(stack.topofstack()))
			{
				char tmp = stack.remove_last();
				queue.add(tmp);
			}
			stack.add(token);
		}
	}

	while (stack.topofstack() != '#')
	{
		char tmp = stack.remove_last();
		queue.add(tmp);
	}
	cout << name << endl;
	cout << stack << endl;
	cout << queue << endl;

	DyArray<float> stack2;

	while (!(queue.isEmpty()))
	{
		char token = queue.remove_first();
		cout << "token: " << token << endl;
		if (isdigit(token))
		{
			stack2.add(token - '0');
			cout << "stack: " << stack2 << endl;
		}
		else
		{
			
			auto operand1 = stack2.remove_last();
			auto operand2 = stack2.remove_last();
			auto result = perform(operand1, operand2, token);
			cout << operand2 << " " << token << " " << operand1 << " = " << result << endl;
			stack2.add(result);
			cout << "stack: " << stack2 << endl;
		}
		cout << "next loop" << endl;
	}
	

}