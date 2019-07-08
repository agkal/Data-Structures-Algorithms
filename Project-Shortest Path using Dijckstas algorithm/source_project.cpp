//our project finds the shortest distance and path for given any two vertices

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include<string>
#include<cstring>
#include<fstream>
#include<map>				
#include <vector>
#include <sstream>			//used to convert integer into string
#include "DrawGraph.h"
using namespace std;
int V = 0;  //total vertices present in glass

string* Store_city = new string[100];//stores all the available cities
int* city_distance = new int[100];//store distance between all the vertices
string* city_path = new string[100];//stores all the cities that comes in the path of source to destination
int city_count = 0;//counts all the path cities
string* g = new string[100];//stores graph vertices

using namespace std;

DrawGraph graph;//main object to control the draGraph functions

class Shortest_path{
public:
    //constructor
    map<string, int> index;
    map<int, string> reverse_index;
    //functions
    Shortest_path(){}
    string* token(std::string str, char delimiter);
    void readingIndex();
    void reading(int** graph);
    void printShortestDistance(int* weight, int n, int target_index);
    void printShortestpath(int* prev, int n, int target_index);
    void dijkstra(int** graph, int source_index, int target_index);
    ~Shortest_path(){}//destructor
};
//token function
string* Shortest_path::token(std::string str, char delimiter)
{
    if (str.find(delimiter) != std::string::npos) {
	   int countDel = 0;
	   std::string *strArr;
	   for (int i = 0; i < str.length(); i++) {
		  if (str[i] == delimiter) {
			 countDel++;
		  }
	   }
	   strArr = new std::string[countDel + 1];
	   std::string temp;
	   for (int i = 0; i < (countDel + 1); i++) {
		  strArr[i] = str.substr(0, str.find(delimiter));

		  temp = str.substr(str.find(delimiter) + 1, str.length());
		  str = temp;
	   }
	   return strArr;
    }
    else {
	   return NULL;
    }
}
void Shortest_path::readingIndex(){

    string line;

    string* tokens;
    //reading from indices
    ifstream file;
    //initialize diagonal elements of the matrix by infinity;
    file.open("new.txt");
    if (file.good())
    {
	   while (getline(file, line))
	   {
		  tokens = token(line, '-');
		  int index_number = atoi(tokens[1].c_str());
		  index[tokens[0]] = index_number;
		  reverse_index[index_number] = tokens[0];
		  V++;
	   }
    }
    else

	   file.close();
  //v = 24
}
//reading from the file and storing into graph adjacency matrix
void Shortest_path::reading(int** graph){

    string line;

    string* tokens;
    //reading from indices
    ifstream file;
    //initialize diagonal elements of the matrix by infinity;
    for (int i = 0; i < V; i++){

	   for (int j = 0; j < V; j++){
		  graph[i][j] = 9999;
	   }
    }

    int counter = 0;
    file.open("new.txt");
    if (file.good())
    {
	   while (getline(file, line))
	   {
		  tokens = token(line, '-');
		  int index_number = atoi(tokens[1].c_str());
		  index[tokens[0]] = index_number;
		  reverse_index[index_number] = tokens[0];
		  Store_city[counter] = tokens[0];
		  counter++;
	   }
    }
    else

	   file.close();
    //reading from graph.txt and storing in 2 dimensional graph

    ifstream f;
    f.open("testing.txt");
    if (f.good())
    {
	   f.seekg(0);
	   while (getline(f, line))
	   {
		  tokens = token(line, '-');
		  int src_index = index[tokens[0]];
		  int destination_index = index[tokens[1]];
		  int distance = atoi(tokens[2].c_str());
		  graph[src_index][destination_index] = distance;
		  graph[destination_index][src_index] = distance;
	   }
    }
    else
	   cout << "file distances not open\n";
    f.close();

}
//prints the shortest path
void Shortest_path::printShortestDistance(int* weight, int n, int target_index)
{
    printf("Shortest distance from Source\n");
    cout << weight[target_index] << "KM";

}
//Function that gives the shortest path between two vertices when adjacency matrix is given
void Shortest_path::printShortestpath(int* prev, int n, int target_index){
    cout << "\n";
    //printing the path
    int i = target_index;
    {
	   int counter = 0;
	   int j;
	   cout << "Path = " << reverse_index[i];
	   city_path[counter] = reverse_index[i];
	   counter++;
	   city_count++;
	   j = i;
	   do{

		  j = prev[j];
		  cout << " <- " << reverse_index[j];
		  city_path[counter] = reverse_index[j];;
		  counter++;
		  city_count++;
	      
	   } while (j != n);

	   cout << "\n";
    }

}
//gives shortset distance and path between two vertices
void Shortest_path::dijkstra(int** graph, int source_index, int target_index)
{
    int* distance = new int[V];
    int* visited = new int[V];
    int* preD = new int[V];
    int min;
    int nextNode = 0;

    for (int i = 0; i < V; i++){
	   visited[i] = 0;
	   preD[i] = source_index;
	   distance[i] = graph[source_index][i];
    }

    distance[source_index] = 0;
    visited[source_index] = 1;



    for (int i = 0; i < V; i++){

	   min = 9999;
	   for (int j = 0; j < V; j++){

		  if (min > distance[j] && visited[j] != 1){
			 min = distance[j];
			 nextNode = j;

		  }


	   }

	   visited[nextNode] = 1;

	   for (int c = 0; c < V; c++){

		  if (visited[c] != 1){
			 if (min + graph[nextNode][c] < distance[c]){

				distance[c] = min + graph[nextNode][c];
				preD[c] = nextNode;
			 }

		  }

	   }
	   if (visited[nextNode] == target_index)
		  break;
    }

    printShortestDistance(distance, source_index, target_index);
    printShortestpath(preD, source_index, target_index);
}
// driver program to test above function
void displayCities(Shortest_path* access){

    for (int i = 0; i < V; i++){

	   cout << access->reverse_index[i] << endl;

    }
}
//constructor that sets radius of the circle
DrawGraph::DrawGraph() {
    radius = .83;
    sides;
}
//saves the co ordinates of the graph into .gph file
void DrawGraph::save(string fileName, vector <string> input) {
    ofstream myfile;

    //append the fileName to add the extention and open the file
    fileName += ".gph";
    myfile.open(fileName);

    //write all of the accepted input into a file
    for (int i = 0; i < input.size(); i++)
	   myfile << input[i] << endl;

    //complete!
    myfile.close();
}
//sets the vertices for the given points and stores into vertices object
void DrawGraph::setVerticesComplete() {
    //This method draws all vertices for a complete graph
    Vertices testVert;

    for (int i = 0; i < pts.size() - 1; i++)
    for (int j = 0; j < pts.size(); j++) {
	   if (i != j) {
		  testVert.x1 = pts[i].x;
		  testVert.y1 = pts[i].y;
		  testVert.x2 = pts[j].x;
		  testVert.y2 = pts[j].y;
		  vertices.push_back(testVert);
	   }
    }
}
//stores the points that needs to be drawn
void DrawGraph::setPoints() {
    //run through all the points and set them
    Point newPoint;

    for (double i = 0; i < 2 * PI; i += PI / (sides / 2.0)) {
	   newPoint.x = cos(i) * radius;
	   newPoint.y = sin(i) * radius;
	   pts.push_back(newPoint);
    }
}
//This method draws all of the points inside the DrawGraph object
void drawPoints() {
    
    glPointSize(3);

    //draw all of the points
    glBegin(GL_POINTS);
    for (int i = 0; i < graph.pts.size(); i++)
	   glVertex2d(graph.pts[i].x, graph.pts[i].y);
    glEnd();
}
//converts integer into string for the distances
string convertInt(int number) {
    //converts an int into a string and returns it
    stringstream ss;
    ss << number;

    //this fixes a bug where an extra number is sometimes printed
    if (number > graph.sides)
	   return "";

    return ss.str();
}
//turns integers into string for city indices
string convertInt2(int number) {
    //converts an int into a string and returns it
    stringstream ss;
    ss << number;

    return ss.str();
}
//draw string distances in opengl form
void drawString(float x, float y, string str) {

    //Color and set position
    glColor3f(0.0, 0.0, 1.0);
    glRasterPos2f(x, y);
    char scoreArr[300];

    //converts the string to a char *
    sprintf_s(scoreArr, str.c_str());

    //draw out each character
    for (const char* c = scoreArr; *c != '\0'; c++) {
	   glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
//draw string indices in opengl form
void drawString2(float x, float y, string str) {

    //Color and set position
    glColor3f(2.0, 0.0, 1.0);
    glRasterPos2f(x, y);
    char scoreArr[300];

    //converts the string to a char *
    sprintf_s(scoreArr, str.c_str());

    //draw out each character
    for (const char* c = scoreArr; *c != '\0'; c++) {
	   glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}
//checks the cities if they are in the shortest path return true else return false
bool checkPath(string checkCityName){

    for (int i = 0; i < city_count;i++){
	   if (city_path[i] == checkCityName)
		  return true;
    }
    return false;
}
//set color and paints all the points
void drawNames(){
    //because it's drawn onto the screen an offset is needed
    //enlarge makes the radius bigger so it doesn't overlap with the points
    Shortest_path object;
    float offset = .03;
    float enlarge = 1.08;

    //convertInt(i + 1)
    //loop through all the points and draw the point #'s
    cout << graph.pts.size();
    for (int i = 0; i < graph.pts.size(); i++){
	   //convertInt(i+1) converts the current point to a string and adds one (so we go from 1-22 etc.)
	   //drawString (x, y, string) x and y are based upon the point in which we want the string to be displayed
	   if (checkPath(Store_city[i])==false)
	   drawString((graph.pts[i].x * enlarge - offset), (graph.pts[i].y * enlarge - offset), Store_city[i]);
	   else
		  drawString2((graph.pts[i].x * enlarge - offset), (graph.pts[i].y * enlarge - offset), Store_city[i]);
    
    }
    int temp = 0;

    offset = .01;
    enlarge = 1.01;

    for (int i = 0; i < graph.vertices.size(); i++){
    double xtemp = (graph.vertices[i].x1 + graph.vertices[i].x2) / 2;
    double ytemp = (graph.vertices[i].y1 + graph.vertices[i].y2) / 2;
    drawString((xtemp * enlarge - offset), (ytemp * enlarge - offset), convertInt2(city_distance[temp])+"km");
    ++temp;
    }
}
//set color and paints all the vertices
void drawVertices() {
    //Shockingly this method draws all the vertices of a DrawGraph object
    glLineWidth(1.0);
    glColor3f(1, 0, 0);

    glBegin(GL_LINES);
    for (int i = 0; i < graph.vertices.size(); i++) {
	   glVertex2f(graph.vertices[i].x1, graph.vertices[i].y1);
	   glVertex2f(graph.vertices[i].x2, graph.vertices[i].y2);
    }
    glEnd();
}
//main function to control all the display functions
void graphicsDisplay() {
    //clear window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Draw the points, vertices, and point names
    drawPoints();		drawVertices();		drawNames();

    //finish drawing
    glutSwapBuffers();
}
//sets all the input and calls main graphic function to paint whole graph
void displayGraph(int** gr) {
    //Get input from the user to make a graph
    Vertices testVert;

    string testInput;
    vector<string> input;

    int counter = 0;
    for (int i = 0; i < V; i++){
	   g[i] = "";
	   for (int j = 0; j < V; j++){
		  if (gr[i][j] == 9999)
			 g[i] = g[i] + "0";
		  else{
			 g[i] = g[i] + "1";
			 city_distance[counter] = gr[i][j];
			 counter++;
		  }
		  }

    }

    //graph via keyboard
    cout << "\n";
    cout << "do you want to see the graph\n: ";
    graph.sides = V;
    graph.setPoints();
    cout << "You chose " << graph.sides << " sides" << endl;
    cout << "Please ensure each matrix row has a length of " << graph.sides << endl;

    //this giant loop gets the matrix from the user
    for (int i = 0; i < graph.sides; i++) {
	   //puts the current point for the entire line into the vertices
	   testVert.x1 = graph.pts[i].x;
	   testVert.y1 = graph.pts[i].y;

	   //clear input
	   testInput = "";

	   //ensure the input has enough characters
	   while (testInput.length() < graph.sides) {
		  //cout << "Please enter the " << i + 1 << " line of the matrix : ";
		  testInput = g[i];
	   }

	   //now that we've gotten a valid input, put it in the vector
	   input.push_back(testInput);

	   //loop through all inputs, if a 1 is found then it needs to be connected
	   for (int j = 0; j < graph.sides; j++) {
		  if (testInput[j] == '1') {
			 //places the vertices requested, attached to the current point (eg 3)
			 testVert.x2 = graph.pts[j].x;
			 testVert.y2 = graph.pts[j].y;

			 //put into the graph
			 graph.vertices.push_back(testVert);
		  }
	   }
    } //end matrix input

    //ask user to save graph
    cout << "Would you like to save this graph? Y or N : ";
    cin >> testInput;

    if (testInput == "Y" || testInput == "y") {
	   cout << "Please enter a file name: (ex: myGraph)";
	   cin >> testInput;
	   graph.save(testInput, input);
    }
}
//menu to call displayGraph
void menu(int** gr) {
    //MENU
    string option;
    cout << "Welcome to DrawGraph" << endl;
    cout << "Press 1 to draw a Graph " << endl;

    do{
	   cin >> option;
	   if (option == "1")
		  displayGraph(gr);
    } while (option!="1");
    }
//control function
int main(int argc, char *argv[])
{
    //adjacency matrix //9999 shows 0 input meaning no edge
    Shortest_path* obj = new Shortest_path;
    string choice;

    obj->readingIndex();
    int** grap = new int*[V];

    for (int i = 0; i < V; i++){
	   grap[i] = new int[V];
    }

    string source, destination;
    int source_index, destination_index;

    obj->reading(grap);
    cout << endl;

    while (1){
	   cout << "*********** Shortest Path **********\n" << endl;

	   do{
		  cout << "Do you want to see the list of available Cities\n" 
<< "Pree 1 for yes or 0 for No\n" << endl;
		  cin >> choice;
		  if (choice == "1")
			 displayCities(obj);
	   } while (choice != "0");

	   do{
		  cout << "Enter the Source city" << endl;
		  cin >> source;
		  source_index = obj->index[source];
	   } while (source != obj->reverse_index[source_index]);

	   do{
		  cout << "Enter the Destination city" << endl;
		  cin >> destination;
		  destination_index = obj->index[destination];
	   } while (destination != obj->reverse_index[destination_index]);

	   cout << endl;
	   obj->dijkstra(grap, source_index, destination_index);
	   cout << endl;

	   do{
		  cout << "Press 1 to continue , 0 to exit" << endl;
		  cin >> choice;
		  if (choice == "0")
			 break;
	   } while (choice != "1");
	   if (choice == "0")
		  break;
	    menu(grap);

	   //initialize OpenGL
	   glutInit(&argc, argv);
	   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	   //window attributes
	   glutInitWindowSize(500, 500);
	   glutInitWindowPosition(0, 0);
	   glutCreateWindow("DrawGraph");

	   //register display callback
	   glClearColor(1, 1, 1, 1);
	   glutDisplayFunc(graphicsDisplay);

	   //turn control over to event loop
	   glutMainLoop();

    }
    system("pause");
    return 0;
}
