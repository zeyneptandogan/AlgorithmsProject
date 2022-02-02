// C++ program to illustrate Edge Coloring 
#include "stdc++.h"
#include <chrono>
#include <fstream>
#include <iostream>
using namespace std;

bool isEdgeColor(vector<vector<pair<int, int> > > &gra,vector<int>& edgeColors){
    
    for (int i=0; i<gra.size(); i++) { //for each vertex
        set<int> setOfColors;
        for (int j=0; j<gra[i].size(); j++) { //for each vertex connected to a edge
            int color_index= gra[i][j].second;
            int color = edgeColors[color_index];
            if (color==-1) { //a not colored edge
                return false;
            }
            else{
                setOfColors.insert(color);
            }
        }
        if (gra[i].size()!=setOfColors.size()) { //number of edges is not equal to number of colors means there exist edges with same color
            return false;
        }
    }
    return true;
}

set<int> used_vertex (vector<pair<int, int> > gra) {
    
    set<int>used_vertex;
    
    if (gra.size()!=0) {
        
        for (int i =0; i< gra.size(); i++) {
            
            used_vertex.insert(gra[i].first);
            
        }
    }
    
    return used_vertex;
    
}



void random_graph_gen (vector<vector<pair<int, int> > > &gra, int vertex_num,int &index) {
    
    int vertex_1=vertex_num;
    bool check_bigger= false;
    bool check_four = false;
    
    if (vertex_num>4) {
        check_bigger=true;
        
    }
    
    else if (vertex_num==4) {
        check_four=true;
        
    }
   
    
    
    for (int i=0; i<vertex_num; i++) {
        
        set<int>used_vertices = used_vertex(gra[i]);
        int  rand_edge_num=0;
        
        if (check_bigger) {
                vertex_1 = vertex_num-4;
                rand_edge_num = rand() % vertex_1 + 3; //Random number generator for edge.
           }
        else if (check_four) {
            
            rand_edge_num = 3; // if number of vertex is 4 then max and min edge number is 3;
        }
        
        
        int cur_edge_num = gra[i].size();
        
        rand_edge_num = rand_edge_num - cur_edge_num; // Discard the current edge number of vertex from random edge number assigned.
        
        for (int j=0; j< rand_edge_num;) {
            
            int  rand_vertex = (rand() % vertex_num ); //Random number generator to decide which vertex will be connected.
            
            
            if ((used_vertices.find(rand_vertex) == used_vertices.end()) && rand_vertex!=i) {
                
                gra[i].push_back(make_pair(rand_vertex, index));
                
                
                gra[rand_vertex].push_back(make_pair(i, index));
            
                cout << i << " " << rand_vertex << " index: "<< index << endl;
                
                index++;
                j++;
                used_vertices.insert(rand_vertex);
                
            }
            
        }
        cout << endl;
    }
}


set<int> outgoing_colors (int outgoing_index,vector<vector<pair<int, int> > >& gra,vector<int>& edgeColors) {
    
    set<int> colors;
    
    for (int i=0; i<gra[outgoing_index].size(); i++) {
        
        int edge_color = edgeColors[gra[outgoing_index][i].second];
        
        if (edge_color !=-1 ) {
            colors.insert(edge_color);
        }
    }
    
    return colors;
    
}

int checkmaxedges(vector<vector<pair<int, int> > >& gra){
    vector<int> counts;
    int temp;
    for(int i=0;i<gra.size();i++){//every vertex
        temp =gra[i].size();
        counts.push_back(temp);
    }
    int max_edges=0;
    for(int j=0;j<counts.size();j++){
        if(counts[j]>max_edges)
            max_edges=counts[j];
    }
    return max_edges;
}

// function to determine the edge colors 
void colorEdges(int ptr, vector<vector<pair<int, int> > >& gra, 
                vector<int>& edgeColors, bool isVisited[])
{ 
    
    //cout<<prev<<" "<<ptr<<endl;
    queue<int> q;
    int c = 0;
    
    set<int> colored;
    
    // return if isVisited[ptr] is true
    if (isVisited[ptr])
        return;
    
    // Mark the current node visited
    isVisited[ptr] = 1;
    
    // Traverse all edges of current vertex
    for (int i = 0; i < gra[ptr].size(); i++) {
        // if already colored, insert it into the set
        if (edgeColors[gra[ptr][i].second] != -1)
            colored.insert(edgeColors[gra[ptr][i].second]);
    }
    
    for (int i = 0; i < gra[ptr].size(); i++) {
        // if not visited, inset into the queue
        if (!isVisited[gra[ptr][i].first])
            q.push(gra[ptr][i].first);
        
        if (edgeColors[gra[ptr][i].second] == -1) {
            // if col vector -> negative
            
            // find the outgoing part for the edge
            
            int outgoing_edge =gra[ptr][i].first;
            
            // color set of going vertex
            set<int>color_prev = outgoing_colors(outgoing_edge,gra,edgeColors);
            
            while ((colored.find(c) != colored.end() ) || (color_prev.find(c) != color_prev.end()))
                
                // increment the color
                c++;
            // copy it in the vector
            edgeColors[gra[ptr][i].second] = c;
            
            // then add it to the set
            colored.insert(c);
            c++;
        }
    }
    
    // while queue's not empty
    while (!q.empty()) {
        int temp = q.front();
        q.pop();
        
        colorEdges(temp, gra, edgeColors, isVisited);
    }
    
    return;
} 


int main()
{
	int ver =0;
    int repeat_num=0;

	cout << "Please enter the total vertex number: ";
	cin >> ver;

	cout << "Please enter the repeat number: ";
	cin >> repeat_num;
    
	int total_edge=0;;
	double total_time=0;

	for(int i=0; i<repeat_num; i++)
	{
		srand((unsigned) time(NULL));
    
		// declaring vector of vector of pairs, to define Graph
		vector<vector<pair<int, int> > > gra;
    
		vector<int> edgeColors;
    
		bool isVisited[100000] = { 0 };

		gra.resize(ver);
		
		// Enter edge & vertices of edge
		// x--; y--;
		// Since graph is undirected, push both pairs
		// (x, y) and (y, x)
		// graph[x].push_back(make_pair(y, i));
 		// graph[y].push_back(make_pair(x, i));
    
    
    
		int index_edge =0; // index edge is the total number of edges that created.
		random_graph_gen(gra,ver,index_edge);
    
		edgeColors.resize(index_edge, -1);
    
    
		// time
		auto start = chrono::steady_clock::now();
		colorEdges(0, gra, edgeColors, isVisited);
		auto end = chrono::steady_clock::now();
		double time = chrono::duration_cast<chrono::microseconds>(end - start).count();
		cout << "Time of the  "<<i<< "th graph generation and color is: "<< time << endl;

		string file1="ver" + to_string(ver) + "rep" + to_string(repeat_num) + ".txt";
		fstream myfile1(file1, ios::app);

		if (myfile1.is_open())
		  {
			myfile1 << time << endl;
			myfile1.close();
		  }
		else cout << "Unable to open file";
    
		int max_Edges=checkmaxedges(gra);//calculating max number of edges that one vertex has
		// printing all the edge colors
		int max_Colored=0;
		for (int i = 0; i < index_edge; i++) {
			//cout << "Edge " << i << " is of color "<< edgeColors[i] + 1 << "\n";
			if (edgeColors[i] + 1>max_Colored)
				max_Colored=edgeColors[i] + 1;
		}
		total_edge=total_edge + index_edge;
		total_time= total_time + time;

		string file2="edgever" + to_string(ver) + "rep" + to_string(repeat_num) + ".txt";
		fstream myfile2(file2, ios::app);

		if (myfile2.is_open())
		  {
			myfile2 << index_edge << endl;
			myfile2.close();
		  }
		else cout << "Unable to open file";
		//cout<<"According to Vizing's theorem the color number for chronomatic index should be "<<  max_Edges <<" or "<< max_Edges+1<<endl;
    
		/*
		if(max_Edges==max_Colored || max_Colored== max_Edges+1 )
			cout<<"It works optimally, chromatic index is "<< max_Colored <<endl;
		else
			cout<<"It colors more edges than it should be in the optimum,minimum colors, the resulting edge coloring is "<<max_Colored <<endl;
		*/
	}//end of for loop

	double average_time= total_time / repeat_num;
	int average_edge= total_edge / repeat_num;

	cout << "Repeat number is: " << repeat_num << endl;
	cout << "Vertex num is: " << ver << endl;
	cout << "Average time is : " << average_time << endl;
	cout << "Average edge is: " << average_edge << endl;


	string file3="rep" + to_string(repeat_num) + ".txt";
	fstream myfile3(file3, ios::app);

	if (myfile3.is_open())
	  {
		myfile3 << ver << " " << average_edge << " " << average_time << endl;
		myfile3.close();
	  }
    else cout << "Unable to open file";
    return 0;
} 
