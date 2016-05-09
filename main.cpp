#include <iostream>
#include <cstdlib>
#include "adjacent.hpp"
#include "Complexity_Timer.hpp"

#include "Complexity_Recorder.hpp"



using namespace std;

timer timer1;
int main()
{

	vector<recorder<timer> > stats(2);

	for(int i = 0; i < 2; i++)
		stats[i].reset();

	int size = 1000000;
	Resistive gh(6);
	//for(int i =0; i < size; i++)
	//	gh.addEdge(i, i+1, i+1);

	//for(int i = 0; i < size; i++)
	//	gh.addEdge(0, 1, i+1);

//	for(int i = 0; i < size; i++) {
//		for(int jazz = 0; jazz < 1000; jazz++)
//			gh.addEdge(i, i+1, 100);
//	}

	gh.addEdge(0, 1, 2);	
   	gh.addEdge(0, 1, 8);	
   	gh.addEdge(0, 5, 10);	
   	gh.addEdge(0, 2, 20);	
   	gh.addEdge(0, 2, 30);	
   	gh.addEdge(0, 2, 60);	
   	gh.addEdge(1, 3, 9);	
   	gh.addEdge(1, 3, 6);	
   	gh.addEdge(2, 4, 90);	
   	gh.addEdge(3, 5, 3);	
   	gh.addEdge(4, 5, 3);	
   	gh.addEdge(4, 5, 100);	
   	gh.addEdge(4, 5, 15);	
	
    gh.printGraph();

	timer1.restart();
	double ans = gh.traverse(0, 5);
   	timer1.stop();	
	stats[0].record(timer1);
   	cout << "-----------------" << endl; 
    
	gh.printGraph();
 
    // print the adjacency list representation of the above graph
	cout << endl << "TIME: ";
	stats[0].report(cout);

	cout << endl << ans << endl;
	double test = 0;
	for(int n = 1; n <= size; n++)
		test += n;
 
    return 0;
}

