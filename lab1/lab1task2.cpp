#include<iostream>
using namespace std;

//main function

//declaring and initializing the function
void analyze_pointer(int *ptr){
	
	cout << "address = ";
	//printing the address of ptr
	cout << ptr << endl;
	cout << "value = ";
	//printing the value of ptr
	cout << *ptr;

}


int * heap(){
	int* pointer = new int;
	*pointer = 29;
	return pointer;
}


int * stack(){
	int* STACK;
	int value = 53;
	return STACK = &value;
}


int main(void)
{

	//part 1 of task 2
	cout << "part 1"<< endl;
	int*number;
	int value;
	value = 20;
	number = &value;
	
	//calling the function analyze_pointer
	analyze_pointer(number);

	//part2 of task 2

	int *x = new int;
	*x = 90;
	cout << "\npart 2" << endl;
	//calling the function analyze_pointer
	analyze_pointer(x);
	cout << "\n\n heap function:  ";
	cout << *heap();
	cout << "\n static function:  ";
	cout << *stack();

} //end main function
