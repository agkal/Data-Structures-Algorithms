
//Assignment#3
#include<cmath>
#include<iostream>

using namespace std;


# define length_Stack 50        /* total stack size */
# define length_PostFix 50     /* total number of characters in postfix expression */

//stacking class where stack functions are created
class stacking{

public:

	/* declaring stack array*/
int stack[length_Stack];
int max = -1;             /* As array index in C begins at 0 */

//function PushData
void PushData(int value)
{

	if (max >= length_Stack - 1)
	{
		cout << "stack over flow";
		return;
	}
	else
	{
		++max;
		stack[max] = value;
	}
}

//PopData function
int PopData()
{
	int value;
	if (max <0)
	{
		cout << "stack under flow";
	}
	else
	{
		value = stack[max];
		--max;
		return value;
	}
}
};

int main()
{
	//object for class stacking
	stacking object;
	int counter;
	char any_char;
	int number;
	int num1, num2;


	// array of characters to store postfix expression
	char array[length_PostFix];
	cout << "~~Evaluation of Postfix expressions~~" << endl;
	cout << "Using stacks and arrays contains the operations (+,-,*,/,^)";
	cout << " \nEnter postfix expression,\npress 'z' for end expression : ";

	
	for (counter = 0; counter <= length_PostFix - 1; counter++)
	{	//input of postfix expression
		cin >> array[counter];

		if (array[counter] == 'z') /* elimination condition */
		{
			break;
		} /* execute from loop */
	}


	/* evaluate postfix expression */
	for (counter = 0; array[counter] != 'z'; counter++)
	{
		any_char = array[counter];
		if (isdigit(any_char))
		{
			object.PushData(any_char - '0');  //take digit value from character code
		}
		else if (any_char == '+' || any_char == '-' || any_char == '*' || any_char == '/' || any_char == '^')
		{
			
			//pop num1 and num2 from stack
			num1 = object.PopData();
			num2 = object.PopData();

			switch (any_char) // any_char is an operator
			{

			case '/':  number = num2 / num1;  break;

			case '*':  number = num2 * num1;   break;

			case '+':   number = num2 + num1;   break;

			case '-':   number = num2 - num1;   break;
			case '^':   number = pow(num2, num1);   break;
			}

			//Pushing the data from the stack
			object.PushData(number);
		}
	}
	cout << " \n Result of postfix evaluation is : " << object.PopData() << endl;


	getchar();
	getchar();
	return 0;
}

