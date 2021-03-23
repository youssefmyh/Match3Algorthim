//  Created by Youssef Hanna.
//  Copyright © 2021. All rights reserved.
//
#pragma once
#include <set>
#include <map>
#include "Match3Settings.h"
#include <vector>
#include <string>

class Item;

/*struct Match3Node {

	Match3Node(int id, std::set<int> &connectedNodes) : nodeId(id),adjacents(connectedNodes){}
	int nodeId;
	int color;
	std::set<int> adjacents;

};*/
class Match3Graph
{

/*---------------------------------Public Function Section----------------------------------------------------------------*/
public:
		
	Match3Graph(std::vector<int>& nodesColors):nodesColors(nodesColors){
		nodes = new std::map<int, std::set<int>>();
		
	}

	~Match3Graph() {
		
		auto it = nodes->begin();
		nodes->clear();
		delete nodes;
	}
	/*
	* Add Node to the Graph
	* @param int color
	* @param int row
	* @param int col
	*/
	void addNode(int color, int row,int col);


	/*
	* Add Node By Color and ID
	* @param int color
	* @param int nodeId
	*/
	void addNode(int color, int nodeId);
	/*
	* find Node Location By Id 
	* @param Node Id from 0 --> MAX_COL
	*/
	static std::tuple<int, int> findNodeLocationById(int nodeId);
	
	/*
	* GgetNodeset 
	* Get the Graph Adjacency list 
	*/
	std::map<int, std::set<int>>* getNodes() const;


	/*
	* Calculate Max NodeId Per Row
	* Used to know how much you have to continue checking in specific row
	*/
	int calculateMaxNodeIdPerRow(int nodeId);

	/*
	* Calculate Max Node Id Per Col
	* Used to know how much you have to continue checking in specific Col
	*/
	int calculateMaxNodeIdPerCol(int nodeId);

	/*
	/* Check if the node has more Right Nodes
	*/
	bool nodeHasMoreRightNodes(int nodeId);

	/*
	/* Check if the node has more Right Nodes
	*/
	bool nodeHasMoreTopNodes(int nodeId);

	/*
	* findMatchedNodes
	* @param int nodeId 
	* return a vector of vector<vector> cotain all nodes to be delted
	* each vector will be used by specific command
	*/
	std::vector<std::vector<int>> findMatchedNodes(int nodeId);


	/*
	/*setNodesColors
	* @param std::vector<int> &levelNodes
	*/
	void setNodesColors(std::vector<int> &levelNodes);


	/*
	/*setNodesColors
	* @param std::vector<int> &levelNodes
	*/
	void setNodesColors(std::vector<Item*>& levelNodes);

	/*
	/*getNodesColors
	*/
	std::vector<int>& getNodesColors();

	/*
	* swapNodes
	* Check if node are swabale
	*/
	std::vector<std::vector<int>> swapNodes(int first, int second);


	/*
	* removeMatchedNodes
	* Marked the removed nodes to be -1 
	* then we will link it with next noded in the col
	*/
	void removeMatchedNodes(std::vector<int> nodes);


	/*
	* nodesGravityCheck 
	* if color vector has -1 
	* move the top point down and make sure to init the level with sufficient items
	*/
	void nodesGravityCheck(std::vector<int> &markedNodes);

	

/*---------------------------------Private Function Section----------------------------------------------------------------*/
private:
	/*
	* connectNodeById Every node should connect to 4 nodes 
	/*In case it's Located Row > 0 & Col <  MAX_COL(8) 
	* ----|---|-----
	* ----| Z |-----
	* ----|---|-----
	* @param int NodeId
	*/
	void connectNodeById(int nodeId);

	
	

/*---------------------------------Private Variable Section----------------------------------------------------------------*/

private:
	std::map<int, std::set<int>> *nodes; //Adjacency list of Nodes to describe the relation between nodes 

	std::vector<int> &nodesColors; // nodes Colors
	
	/*
	* dfsFindAllMatches 
	/* depth First Search:move through all nodes and find all matches 
	* @param int nodeId
	/*@param std::vector<bool>& hVisited horizontal visited points 
	* @param std::vector<bool>& vVisited 
	* @param std::vector<std::vector<int>> &matched vector of matached 
	*/
	void dfsFindAllMatches(int nodeId, std::vector<bool>& hVisited, std::vector<bool>& vVisited, std::vector<std::vector<int>> &matched);
};

