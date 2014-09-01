#include <iostream>
#include <iomanip>
#include <fstream>

#include "stack.h"


using namespace std;
const int MAXFILE = 100;
const int MAXLINE = 100;

struct node {
public:
	char name;
	char aTrans;
	char bTrans;
	char zTrans;
	int type;//1 for read, 2 for push, 3 for pop
	node();
};
node::node(){
	name = 0;
	aTrans = 0;
	bTrans = 0;
	zTrans = 0;
}
int findNode(node* nodePtr, char nodeName, int numStates) {//returns index of nodeName if it exists, -1 for not found, -2 for final

	if(nodeName == 'F')
		return -2;
	for(int i=0;i<numStates+1;i++) {
		if(nodePtr[i].name == nodeName)
			return i;
	}
	return -1;
}
void printCharArray(char input[ ]) {//prints a null terminated character array
	for(int i = 0;input[i]!=0;i++)
		cout << input[i];
}
char findPush(node* &nodePtr,int currState)//finds value to push onto stack for given state
{
	if(nodePtr[currState].aTrans != 0)
	{
		return 'a';
	}
	 if(nodePtr[currState].bTrans != 0)
	 {
		return 'b';
	 }

	if(nodePtr[currState].zTrans != 0){
		return 'z';
	}
	return 0;

}
void runSim(ifstream &inputStream, node* &nodePtr, int numStates) {//runs simulation, prints results
	char tempArray[MAXLINE];
	char temp;
	int currState = 0;//holds index of current node
	int i =0; //holds index of current word
	stack myStack;

	inputStream.getline(tempArray, MAXLINE);//gets newline character

	while(!inputStream.eof())
	{
		inputStream.getline(tempArray, MAXLINE);
		while(currState > -1)
		{
			if(nodePtr[currState].type == 1)//if read
			{
				temp = tempArray[i];//get next char
				if(temp == 0)//if out of input
					temp = 'z';
				i++;
			}
			else if(nodePtr[currState].type == 2)//if push
			{
				myStack.push(findPush(nodePtr, currState));//push data
				temp = findPush(nodePtr, currState);//next state
			}
			else if(nodePtr[currState].type == 3)//if pop
			{
				temp = myStack.pop();
			}
			//now move to next node
			if(temp == 'a')
				currState = findNode(nodePtr, nodePtr[currState].aTrans, numStates);
			else if(temp == 'b')
				currState = findNode(nodePtr, nodePtr[currState].bTrans, numStates);
			else if(temp == 'z')
				currState = findNode(nodePtr, nodePtr[currState].zTrans, numStates);
		}
		if (currState == -2)//if word
		{
			cout << left << setw(10) << "good ";
			printCharArray(tempArray);
			cout << endl;
		}
		else//if not a word
		{
			cout << left << setw(10) << "bad ";
			printCharArray(tempArray);
			cout << endl;
		}
		currState = 0;
		i = 0;
		myStack.clear();
	}
}
void parseFile(ifstream &inputStream) {//generates nodes, calls simulator function
	char tempArray[MAXLINE];
	char temp;
	char currNode;//used to hold node that we are currently processing
	char readString[6] = "read,";
	char pushString[6] = "push,";
	char popString[5] = "pop,";
	node* nodePtr;
	int numStates;
	int i = 0; //used to hold index of last created node

	inputStream >> temp; //gets '
	inputStream.getline(tempArray, MAXLINE,'\n'); // first line is always a comment
	printCharArray(tempArray); //prints out language rule
	cout << endl;

	inputStream >> numStates;
	nodePtr = new node[numStates];

	//create nodes
	inputStream >> temp;
	while(1)
	{
		if(findNode(nodePtr, temp, numStates) == -1)//only execute for new nodes
		{
			nodePtr[i].name = temp;
			currNode = temp;
			inputStream >> temp;
			inputStream >> tempArray;
			//determine what type node is
			if(strncmp(tempArray,readString,5) == 0)
				nodePtr[i].type = 1;
			else if(strncmp(tempArray,pushString,5) == 0)
				nodePtr[i].type = 2;
			else if(strncmp(tempArray,popString,4) == 0)
				nodePtr[i].type = 3;
			i++;
		}
		else//else throw away duplicate information
		{
			currNode = temp;
			inputStream >> temp;
			inputStream >> tempArray;
		}
		inputStream >> temp;
		if(temp == 'a')//assign a transition
		{
			inputStream >> temp;
			inputStream >> temp;
			nodePtr[findNode(nodePtr, currNode, numStates)].aTrans = temp;
			if (temp == 'F')
				break;
		}
		else if(temp == 'b')//assign b transition
		{
			inputStream >> temp;
			inputStream >> temp;
			nodePtr[findNode(nodePtr, currNode, numStates)].bTrans = temp;
			if (temp == 'F')
				break;
		}
		else if(temp == 'z')//assign z transition
		{
			inputStream >> temp;
			inputStream >> temp;
			nodePtr[findNode(nodePtr, currNode, numStates)].zTrans = temp;
			if (temp == 'F')
				break;
		}
		inputStream >> temp;
		
	}

	runSim(inputStream,nodePtr, numStates);//runs simulation


	delete[ ] nodePtr;
}
void getFileName(ifstream &inputStream) {//asks for input file until it is valid
	char filename[MAXFILE];
	while (inputStream.is_open() == false)
	{
		inputStream.clear();
		cout << "Input filename: ";
		cin >> filename;
		inputStream.open(filename);
	}
}
int main() {
	ifstream inputStream;

	getFileName(inputStream);//asks for input file until it is valid
	parseFile(inputStream);//generates nodes, calls simulator function

	cout << "Press enter to close";
	
	stack myStack;
	myStack.push('s');
	for(int i=0;i<198;i++)
	{
		myStack.push('t');
	}
	myStack.push('t');
	myStack.push('t');
	myStack.push('t');
	myStack.push('t');
	myStack.push('t');
	myStack.push('x');
	for(int i=0;i<200;i++)
	{
		myStack.push('q');
	}
	for(int i=0;i<250;i++)
	{
		cout << myStack.pop();
	}


	cin.get();//keep from closing
	cin.get();
	return 0;
}
