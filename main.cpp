#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{

    ifstream is("complete1.txt");
    if (is.fail())
    {
        cout << "Can't open file!" << endl;
        return 1;
    }
    graph G;

    cout << "Graph 1: " << endl;
    is >> G;

    cout << "Read graph: " << endl;
    cout << G;
    cout<< "Is Graph 1 complete? " << G.is_complete() << endl;
    is.close();
    ifstream in("complete2.txt");
    if (in.fail())
    {
        cout << "Can't open file!" << endl;
        return 1;
    }
    graph G1;

    cout << "Enter a graph 2: " << endl;
    in >> G1;

    cout << "Read graph: " << endl;
    cout << G1;
    cout<< "Is graph 2 complete? " << G1.is_complete() << endl;
    in.close();
	
		
	//puzzle.build_dictionary();
    return 0;
}

