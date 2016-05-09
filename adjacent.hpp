#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
 
//Struct to define a node of the adjacency list. Each node represents a 
//connection between two elements of the graph.
struct Node
{
    int dest;
	double weight;
    struct Node* next;
};
 
//Struct to define how the graph is represented.
//This implementation uses an Adjacency List
//The only member of the AdjList is a Node pointer named head that points
//to the first element in each list
struct AdjList
{
    Node *head;
};

struct Iterator {
	Node* i = nullptr;

	Iterator (Node* x) : i(x) {}

	T& operator*() {
		return i->weight;
	}

	Iterator operator ++(){
		
 
//Struct to define the actual graph. The graph consists of an int for the number
//of Verticies and an array of AdjList pointers.
struct Graph
{
        int V;
        struct AdjList* array;

		//Constructor that takes a number of Verticies and creates an adjacency
		//list with that many elements 
        Graph(int input)
        {
            V = input;
            array = new AdjList [V];
            for (int i = 0; i < V; ++i)
                array[i].head = NULL;
        }

		//Function that defines an adjacency list connection Node with a
		//destination and a weight
        Node* newNode(int dest, int weight)
        {
            Node* newNode = new Node;
            newNode->dest = dest;
			newNode->weight = weight;
            newNode->next = NULL;
            return newNode;
        }

		//Add an edge (A node in the adjacency list) between two points in the
		//graph with a given weight
        void addEdge(int src, int dest, int weight)
        {
            Node* node = newNode(dest, weight);
            node->next = array[src].head;
            array[src].head = node;
        }

		//Function to combine to nodes in parallel
		//Takes two Node pointers by reference and modifies the actual 
		//weights of the nodes
		void parallel(Node* &temp, Node* temp2) {
			temp->weight = (temp->weight * temp2->weight)/(temp->weight + temp2->weight);
		}
		
		//Core funciton that finds the resistance between a source and a
		//destination. 
		double advanceResist(int src, int destination) {
			
			//First all of the parallel connections are combined into series
			//connections and the old nodes are removed from the list
			//integer check to keep track of destination to be combined
			int check = 0;
			Node* temp;
			Node* temp2;
			//First for loop to determine the element to check against
			for(int n = 0; n < V; n++) {
				for(temp = array[n].head; temp != NULL; temp = temp->next) {
					check = temp->dest;

					//second for loop to find and combine all of the elements
					//that match the destination of the check variable
					for(temp2 = temp->next; temp2!=NULL;temp2 = temp2->next) {
						if(check == temp2->dest) {
							parallel(temp, temp2);
							temp->next = temp2->next;
						}
					}
				}
			}

			//Next all of paths to the destination nodes need to be recorded
			//and then added together in parallel
			//counter to store which path you're on. Used to save the series
			//resistance of each path
			int counter = 0;
			//Node pointer named whereami, this node always points to the
			//source adjacency list and moves along node by node for the start
			//of each path
			Node* whereami;
			double store[V] = {0};

			whereami = array[src].head;

			//temp Node pointer that follows the path until the final value and
			//is used to find the total series resistance
			temp = whereami; 

			while (whereami != NULL) {
				store[counter] += temp->weight;

				if(temp->next == NULL && temp->dest == destination) {
					whereami = whereami->next;
					temp = whereami;
					counter++;
				}

				else if (temp->dest == destination) {
					whereami = whereami->next;
					temp = temp->next;
					counter++;
				}

				else {
					temp = array[temp->dest].head; 
				} 
			}

			int numPaths = 0;
			for(Node* p = array[src].head; p != NULL; p = p->next)
				numPaths++;
			

			//Add the final resistances together. 
				
			for(int i = 1; i < numPaths; i++) {
				store[i] = (store[i] * store[i-1]) / (store[i] + store[i-1]);
			}

			return store[0];
		}
		
		//Funciton to print the adjacency list representation of the graph
        void printGraph()
        {
            for (int i = 0; i < V; i++)
            {
                Node* temp = array[i].head;
                cout << endl << "Vertex: " << i << endl;
                while (temp)
                {
                    cout << "-> " << temp->dest << "|" << temp->weight;
                    temp = temp->next;
                }
                cout<<endl;
            }
        }
};
