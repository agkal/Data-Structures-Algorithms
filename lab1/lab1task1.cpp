#include<iostream>
using namespace std;

//main function
int main(void)
{
	//declaring pointer
	int* salary;
	salary = new int[20];
	int i;
	for (i = 0; i<20; ++i)
	{
		cout << "Enter Salary: ";
		cin >> salary[i];
	}
	for (i = 0; i<20; ++i)
		salary[i] = salary[i] + salary[i] / (i + 1);
	return 0;
}  //end main function.
