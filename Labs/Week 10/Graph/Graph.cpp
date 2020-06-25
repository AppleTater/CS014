//Viewed documentation about the make_pair function, referenced here:
//http://www.cplusplus.com/reference/utility/make_pair/

#include "Vertex.h"
#include "Graph.h"
#include <iostream>

Graph::Graph() {}


//Reads the graph input file and instantiates a graph object.
Graph::Graph(ifstream &ifs) {
  int numNodes = 0;
  int numVertices = 0;
  int weights = 0;
  string title;
  string neighborTitle;

  ifs >> numNodes >> numVertices;

  //i -= -i because i wanna be qUiRkY
  ifs.ignore();
  for(int i = 0; i < numNodes; i -= -1) {
    Vertex newNode;
    string labelName = "";
    getline(ifs, labelName);
    newNode.label = labelName;
    vertices.push_back(newNode);
  }

  while(ifs >> title) {
    int index = 0;
    int neighborIndex = 0;

    ifs >> neighborTitle >> weights;

    for(unsigned int i = 0; i < vertices.size(); i++) {
      if(title == vertices.at(i).label) {
        index = i;
      }
      if(neighborTitle == vertices.at(i).label) {
        neighborIndex = i;
      }
    }
    //im ngl, looking back now im not really sure how this monstrosity came into existence
    vertices.at(index).neighbors.push_back(make_pair(neighborIndex, weights));
  }
}

Graph::~Graph() {
  vertices.clear();
}

//copied and pasted that blurb from lab 7, i assume that the rest is more or less similar
void Graph::output_graph(const string &file) {
  ofstream outFS(file.c_str());
    if(!outFS.is_open()) {
        cout<< "Error" << endl;
        return;
    }

    outFS << "digraph G {" << endl;
    //outFS << vertices.size() << endl;
    for(unsigned int i = 0; i < vertices.size(); i++) {
      if(vertices.at(i).distance <= INT_MAX) {
        outFS << "   " << vertices.at(i).label << "[label= \"" << vertices.at(i).label << " " << vertices.at(i).distance 
        << "\"];" << endl;
        /*
        for(auto j = vertices.at(i).neighbors.begin(); j != vertices.at(i).neighbors.end(); j++) {
            outFS << "1" << endl;
          outFS << "   " << vertices.at(i).label << " -> " << vertices.at(j->first).label << ";" << endl;
        }*/
      }
    }

    for(unsigned int i = 0; i < vertices.size(); i++) {
        for(auto j = vertices.at(i).neighbors.begin(); j != vertices.at(i).neighbors.end(); j++) {
          outFS << "   " << vertices.at(i).label << " -> " << vertices.at(j->first).label << ";" << endl;
        }
    }
    outFS << "}";
    outFS.close();

    string systemCommand = "dot -T jpg " + file + "-o pic.jpg";
    system(systemCommand.c_str());
}

void Graph::bfs() {
  vertices.at(0).distance = 0;
	
	queue<Vertex*> vertexQueue;
	vertexQueue.push(&vertices.at(0));
	
	while(!vertexQueue.empty()) {
		Vertex* frontVertex = vertexQueue.front();
		vertexQueue.pop();
		frontVertex->color = "GRAY";
		
		for(auto i = frontVertex->neighbors.begin(); i != frontVertex->neighbors.end(); i++) {
			if(vertices.at(i->first).color == "WHITE") {
				vertices.at(i->first).prev = frontVertex;
				vertices.at(i->first).distance = 0;
				vertices.at(i->first).color = "GRAY";
				vertices.at(i->first).distance += vertices.at(i->first).prev->distance + 1;
				vertexQueue.push(&vertices.at(i->first));
			}
		}
		
		frontVertex->color = "BLACK";
	}
}
