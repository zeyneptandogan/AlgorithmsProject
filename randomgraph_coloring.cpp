// C++ program to illustrate Edge Coloring 
#include "stdc++.h"

using namespace std;

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
    srand((unsigned) time(NULL));
    
    // declaring vector of vector of pairs, to define Graph
    vector<vector<pair<int, int> > > gra;
    
    vector<int> edgeColors;
    
    bool isVisited[100000] = { 0 };
    
    int ver =0;
    
    cout << "Please enter the total vertex number: ";
    cin >> ver;
    
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
    
    
    
    colorEdges(0, gra, edgeColors, isVisited);
    
    int max_Edges=checkmaxedges(gra);//calculating max number of edges that one vertex has
    // printing all the edge colors
    int max_Colored=0;
    for (int i = 0; i < index_edge; i++) {
        cout << "Edge " << i << " is of color "<< edgeColors[i] + 1 << "\n";
        if (edgeColors[i] + 1>max_Colored)
            max_Colored=edgeColors[i] + 1;
    }
    cout<<"According to Vizing's theorem the color number for chromatic index should be "<<  max_Edges <<" or "<< max_Edges+1<<endl;
    
    if(max_Edges==max_Colored || max_Colored== max_Edges+1 )
        cout<<"It works optimally, chromatic index is "<< max_Colored <<endl;
    else
        cout<<"It colors more edges than it should be in the optimum,minimum colors, the resulting edge coloring is "<<max_Colored <<endl;
    

	return 0;
} 