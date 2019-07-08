/*
	Assignment 5 -- Trie Implementation
	Prepared by:	Abdul Ghaffar Kalhoro & Hamad Nasir

*/


#include<stdio.h>
#include<iostream>
#include<string>

//libraries for file inssertion
#include<fstream>
using namespace std;
const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];
	bool isEndOfWord;
	// isEndOfWord is true if the node represents
};

// function used to initialize all data to NULL and return new TrieNode
struct TrieNode *getNode(void)
{
	struct TrieNode *tempNode = new TrieNode;

	tempNode->isEndOfWord = false;

	for (int counter = 0; counter < ALPHABET_SIZE; counter++)
		tempNode->children[counter] = NULL;

	//returning tempNode
	return tempNode;
}

//function to get the position of abd alphabets
int char_to_posi(char c){

	return c - 'a';
}

//insert function to insert any word in try 
/*
	---returns nothing
	---take TrieNode pointer type object 
	& string type word
*/
void Insert(TrieNode *root, string combinations) {
	if (root == NULL) 
		root = getNode(); //for base case initialize every data to null.
	//create temperary node and initialize it with rood node
	TrieNode *nodeTemp = root;
	//for loop to insert the correct data in TRIE
	for (int counter = 0; counter < combinations.length(); counter++) {
		//string of characters
		char char_value = combinations[counter];
		//check for the root descendent to be null
		if (nodeTemp->children[char_to_posi(char_value)] == NULL)
			nodeTemp->children[char_to_posi(char_value)] = getNode(); //create node for children nodes
     		nodeTemp = nodeTemp->children[char_to_posi(char_value)];  //make root node as child node
	}
	//if the word is inserted make isEndOfWord true
	nodeTemp->isEndOfWord = true;
}
//var for line allignment
int var = 1;
//display function used to print all the words that a Trie is made of
/*
	--returns nothing
	-- takes 3 parameters
	a)TrieNode type object pointer
	b) integer type index
	c) array of characters to store words

*/
void display(TrieNode* temp, int index, char tempArray[] ) {
	//check for the word formed
	if (temp->isEndOfWord) {
		tempArray[index] = NULL; //make node indicating the word as null
		if (var % 3 == 0) // line indentation condition
			cout << endl;
		var++; //increment var
		printf("  %s %16s ",tempArray," ");//printing the words
	}
	int t_num = 0;// counter variable t_num
	while (t_num < 26)  //condition of abc alphabets position
	{
		if (temp->children[t_num] != NULL) //check if the child node is null
		{
			tempArray[index] = t_num + 'a';  //store the char at correct position
			display(temp->children[t_num], index + 1, tempArray);//call display function recursively
		}
		t_num++;//increment t_num
	}
}

// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
	//creating temp TrieNode
	struct TrieNode *tempNode = root;
	//loop to search full word formation
	for (int counter = 0; counter < key.length(); counter++)
	{
		int index = char_to_posi(key[counter]); //giving index node position
		if (!tempNode->children[index]) //check if the children node is false
			return false;

		tempNode = tempNode->children[index]; //making root node as the child node
	}
	//returning boolean value that if the word found or not
	return (tempNode != NULL && tempNode->isEndOfWord); 
}//end search



int main(){
	int choice;
	string word;
	cout << "\t~~~~~This is the trie implementation~~~~~~" << endl;
	cout << "\tContains the functions of:"<<endl;
	cout << "\t1) Searching" << endl;
	cout << "\t2) Display" << endl;
	cout << "    Enter your choice:  " << endl;
	cin >> choice;



	struct TrieNode *root = getNode();

	int counter = 1;
	string my;
	cout << "\t\tReading From file\n";
	ifstream read;
	//opening file to read words from it
	read.open("arraywords.txt");

	while (read >> my) {
		Insert(root, my);
	}


	read.close();
	///*************************///
	//check conditions for differnt user choices.
	switch (choice){
	case 1:
		cout << "Enter word of string to search:  ";
		cin >> word;
		if (search(root, word)) {
			cout << "The give word: " << word << " is part of Trie" << endl;
		}
		else
			cout << "Word not found";
		break;
	case 2:
		char abc[26];
		display(root,0,abc);
		break;
	default:
		cout << "Enter valid choice" << endl;
		break;
	}
	cout << endl << endl;
	system("pause");
	return 0;
}//end main