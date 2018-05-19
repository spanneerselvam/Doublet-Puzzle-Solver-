#include <iostream>
#include <vector>
#include <fstream>
#include <list>
#include <assert.h>
#include <queue>

using namespace std;


class Graph {
public:
    //Constructor
    Graph() {};

    // Build adjacency list graph with integer vertices
    // Integers correspond to indices for words in dictionary vector
    int n();
    void add_vertex();
    void add_edge(int a, int b);
    bool is_edge(int a, int b);
    list<int> shortest_path(int start, int end);

private:
    // Adjacency list graph
    vector<list<int>> _v;

    // Helper function that does bfs traversal
    void bfs(int start, vector<int> &parent);
};

int Graph::n() {
    return _v.size();
}

void Graph::add_vertex() {
    _v.push_back(list<int>());
}

void Graph::add_edge(int a, int b) {
    assert(a < n() && b < n());
    if (!is_edge(a, b))
    {
        _v[a].push_front(b);
        _v[b].push_front(a);
    }
}

bool Graph::is_edge(int a, int b) {
    if (a >= n() || b >= n())
        return false;

    for (auto e: _v[a])
        if (e == b)
            return true;

    return false;
}

list<int> Graph::shortest_path(int start, int end) {
    vector<int> parent(n(),-1); // Holds parents
    bfs(start,parent);

    // No answer found
    if (parent[end] == -1) {
        cout << "None";
        return list<int>();
    }

    // Create answer list by tracing back parents from end word
    list<int> ans;
    list<int>::iterator it;
    for(int v = end; v!=start; v=parent[v]) {
        ans.push_front(v);
    }
    ans.push_front(start);

    return ans;
}

void Graph::bfs(int start, vector<int> &parent) {
    queue<int> vertex_num; // Holds unprocessed vertices

    vertex_num.push(start);
    parent[start] = start;

    while (!vertex_num.empty())
    {
        int current = vertex_num.front();
        vertex_num.pop();

        for (auto e:_v[current])
        {
            if(parent[e] == -1) {
                parent[e] = current;
                vertex_num.push(e);
            }
        }
    }
}


class doublet {
public:
    //Constructor
    doublet() {};

    // Member functions
    void build_graph(string dict);
    void solve(string first_word, string last_word);

private:
    // Adjacency list graph where vertices represent words
    Graph graph;

    // Dictionary vector
    vector<string> dictionary;

    // Helper function determines number of chars in common for 2 words
    int intersections(string string1, string string2);
};

int doublet::intersections(string string1, string string2) {
    int matches = 0;

    // Count matching characters in strings of length 5
    for(int i=0; i < 5; i++) {
        if (string1[i] == string2[i]) {
            matches++;
        }
    }
    return matches;
}

void doublet::build_graph(string dict) {

    ifstream inFile(dict);
    string line;

    // Create dictionary vector
    while(getline(inFile,line)) {
        if(line.length() != 0) {
            graph.add_vertex();
            dictionary.push_back(line);
        }
    }

    inFile.close();

    string word1, word2;

    // Add edges to graph for words that have 4 common characters
    for( int i = 0; i < dictionary.size(); i++) {
        word1 = dictionary[i];
        for( int j = i; j < dictionary.size(); j++) {
            word2 = dictionary[j];
            if (intersections(word1, word2) == 4) {
                graph.add_edge(i,j);
            }
        }
    }

}

void doublet::solve(string first_word, string last_word) {
    int index1, index2;

    // Find index of first word
    for (int i = 0; i < dictionary.size(); i++) {
        if (first_word == dictionary[i]) {
            index1 = i;
        }
    }

    // Find index of last word
    for (int i = 0; i < dictionary.size(); i++) {
        if (last_word == dictionary[i]) {
            index2 = i;
        }
    }

    // Execute breadth-first-search to find shortest path b/w first
    // and last word; print out answer
    cout << "Path from " << first_word << "to " << last_word << ": "<< endl;
    list <int> answer = graph.shortest_path(index1, index2);
    list <int>::iterator it;
    for(it = answer.begin(); it!= answer.end(); it++) {
        cout << dictionary[*it] << " ";
    }
    cout << "\n\n";
}

int main() {
    doublet puzzle;
    puzzle.build_graph("dictionary.txt");
    puzzle.solve("black", "white");
    puzzle.solve("tears", "smile");
    puzzle.solve("small", "giant");
    puzzle.solve("stone", "money");
    puzzle.solve("angel", "devil");
    puzzle.solve("amino", "right");
    puzzle.solve("amigo", "signs");

    return 0;
}
