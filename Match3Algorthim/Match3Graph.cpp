#include "Match3Graph.h"

void Match3Graph::addNode(int color, int row,int col)
{
	
}

void Match3Graph::addNode(int color, int nodeId)
{
	if (nodeId < 0 || nodeId > (GAME_MAX_CELLS-1) ) return;

	auto it = nodes->find(nodeId);

	if (it != nodes->end()) {
		return;
	}
	connectNodeById(nodeId);
	

}

std::tuple<int, int> Match3Graph::findNodeLocationById(int nodeId)
{
	// Find Node Col by dividing (NodeId / Max_Col )
	int col = nodeId % GAME_COL_MAX;
	int row = (int) floor( nodeId/ GAME_COL_MAX);

	return std::move(std::tuple<int, int>(row,col));
}

std::map<int, std::set<int>>* Match3Graph::getNodes() const
{
	return nodes;
}

int Match3Graph::calculateMaxNodeIdPerRow(int nodeId)
{
	std::tuple<int, int> nodeLocation = findNodeLocationById(nodeId);
	int row = std::get<0>(nodeLocation);

	return ((row+1) * GAME_ROW_MAX) -1; 
}


int Match3Graph::calculateMaxNodeIdPerCol(int nodeId)
{
	std::tuple<int, int> nodeLocation = findNodeLocationById(nodeId);
	int col = std::get<1>(nodeLocation);

	return GAME_MAX_CELLS - (GAME_COL_MAX - col);
}


void Match3Graph::dfsFindAllMatches(int nodeId, std::vector<bool>& hVisited, std::vector<bool>& vVisited, std::vector<std::vector<int>>& matched) {

	if (nodesColors[nodeId] == -1)
		return;
	std::vector<int> possibleHorizonatlMatches; // Horizonatl matched vector
	std::vector<int> possibleVerticalMatches; // vertical matched vector
	
	/*---------------------------------- find all Horizonatl Points  ---------------------------------------------------------*/
	/*
	* ----|---|-----
	* ----| Z |-----
	* ----|---|-----
	*/
	if (!hVisited[nodeId] ){

		int maxNodeIdInRow = calculateMaxNodeIdPerRow(nodeId);

		possibleHorizonatlMatches.push_back(nodeId);

		for (int i = nodeId + 1; i <= maxNodeIdInRow; i++){ 

			int lastAddNode = possibleHorizonatlMatches.at(possibleHorizonatlMatches.size() - 1);
			if (nodesColors[lastAddNode] == nodesColors[i]){

				possibleHorizonatlMatches.push_back(i);

			}else {
				break;
			}

		}
		if (possibleHorizonatlMatches.size() >= GAME_MINMUM_MATCHED){

			for (int visitedNode : possibleHorizonatlMatches)
			{
				hVisited[visitedNode] = true;
			}
			matched.push_back(std::move(possibleHorizonatlMatches));
		}
	
		hVisited[nodeId] = true;
	}



	/*---------------------------------- find all Vertical Matched ---------------------------------------------------------*/

	
	if (!vVisited[nodeId]) {

		int maxNodeIdInCol = calculateMaxNodeIdPerCol(nodeId);
		possibleVerticalMatches.push_back(nodeId);

		for (int j = nodeId + GAME_COL_MAX ; j <= maxNodeIdInCol; j = j + GAME_COL_MAX){

			int lastAddNode = possibleVerticalMatches.at(possibleVerticalMatches.size() - 1);
			if (nodesColors[lastAddNode] == nodesColors[j]) {

				possibleVerticalMatches.push_back(j);

			}
			else {
				break;
			}

		}


		if (possibleVerticalMatches.size() >= GAME_MINMUM_MATCHED) {

			for (int visitedNode : possibleVerticalMatches)
			{
				vVisited[visitedNode] = true;
			}

			matched.push_back(std::move(possibleVerticalMatches));
		}
		vVisited[nodeId] = true;
	}


	/*---------------------------------- Depth first Search -------------------------------------*/

	auto it = nodes->find(nodeId);
	if (it != nodes->end()) {
		std::set<int> neighbours = it->second;
		
		for (int neighbour : neighbours)
		{
			/* Point need to be checked*/
			if (!hVisited[neighbour] || !vVisited[neighbour]) {
				dfsFindAllMatches(neighbour, hVisited,vVisited, matched);
			}

		}
	}
}

std::vector<std::vector<int>> Match3Graph::findMatchedNodes(int nodeId)
{
	std::vector<bool> vVisited(GAME_MAX_CELLS, false);
	std::vector<bool> HVisited(GAME_MAX_CELLS, false);

	std::vector<std::vector<int>> options;

	dfsFindAllMatches(nodeId, vVisited, HVisited, options);


	return std::move(options);
}



bool Match3Graph::nodeHasMoreRightNodes(int nodeId)
{
	std::tuple<int, int> nodeLocation = findNodeLocationById(nodeId);
	int col = std::get<1>(nodeLocation);

	return col < GAME_ROW_MAX - 1;
}

bool Match3Graph::nodeHasMoreTopNodes(int nodeId)
{
	std::tuple<int, int> nodeLocation = findNodeLocationById(nodeId);
	int row = std::get<0>(nodeLocation);

	return row < GAME_ROW_MAX - 1;
}

void Match3Graph::connectNodeById(int nodeId)
{

	std::tuple<int, int> nodeLocation = findNodeLocationById(nodeId);

	int row = std::get<0>(nodeLocation);
	int col = std::get<1>(nodeLocation);

	
	int leftNodeId  = nodeId - 1;    // Get Left Node
	int rightNodeId = nodeId + 1;   // Get Right Node Location
	int topNodeId = nodeId + GAME_COL_MAX; // 8 in this case
	int bottomNodeId = nodeId - GAME_COL_MAX;  // 8

	std::set<int> connectedEdges;

	// connect right node
	if (col < GAME_ROW_MAX -1 ) {
		connectedEdges.insert(rightNodeId);
	}

	// connect top Node

	if (row < GAME_ROW_MAX - 1 && topNodeId < GAME_MAX_CELLS)
	{
		connectedEdges.insert(topNodeId);
	}

	// connect bottom Node
	if (row > 0 && bottomNodeId >= 0)
	{
		connectedEdges.insert(bottomNodeId);
	}


	// Connect with the leftNode
	if (col > 0 && leftNodeId >= 0) {
		connectedEdges.insert(leftNodeId);
	}

	nodes->insert(std::pair<int,std::set<int>>(nodeId, std::move(connectedEdges)));

}

std::vector<int>& Match3Graph::getNodesColors() {
	return this->nodesColors;
}

void Match3Graph::setNodesColors(std::vector<int>& levelNodes) {
	this->nodesColors = levelNodes;
}


std::vector<std::vector<int>> Match3Graph::swapNodes(int first, int second) {

	int firstNode = nodesColors[first];
	int secondNode = nodesColors[second];

	nodesColors[first] = secondNode;
	nodesColors[second] = firstNode;



	std::vector<std::vector<int>> allOptions = findMatchedNodes(0);

	if (allOptions.size() <= 0)
	{
		nodesColors[first] = firstNode;
		nodesColors[second] = secondNode;
	

	}

	return std::move(allOptions);

}

void Match3Graph::removeMatchedNodes(std::vector<int> markedNodes){

	for (unsigned int i = 0; i < markedNodes.size(); i++) {
		
		nodesColors[markedNodes[i]] = -1; // Marked removed nodes to be -1 

	}


}

void Match3Graph::nodesGravityCheck(std::vector<int> &markedNodes)
{

	
	bool isVertical = false;
	bool isHorizontal = false;

	if (markedNodes.size()  < GAME_MINMUM_MATCHED ) // minum matched number 3 in our case
		return;
	
	uint32_t lastNodeIndex = markedNodes.size() - 1;
	uint32_t maxNodePerCol = markedNodes[lastNodeIndex] + GAME_COL_MAX;
	if (maxNodePerCol > nodesColors.size() - 1) // back point to move all points to up
		return;
	


	if (markedNodes[0] == markedNodes[1] - 1)
	{
		isHorizontal = true;
	}
	else {
		// return point needed only in vertical matches
		isVertical = true;

		uint32_t maxNodeForCol = markedNodes[lastNodeIndex] + markedNodes.size() * GAME_COL_MAX;
		if (maxNodeForCol > nodesColors.size() - 1) // back point to move all points to up
			return;

	}


	if (isVertical){
		
		int j = 0;

		for (int col = markedNodes.size() -1; col >= 0; col--)
		{
			
			int removedNodeId = markedNodes[col];
			int nodeColor = nodesColors[removedNodeId];
			if (nodeColor == -1) {
				
				uint32_t nodeTobeMoved = removedNodeId + markedNodes.size() * GAME_COL_MAX;

				if (nodeTobeMoved < nodesColors.size()) {

					nodesColors[removedNodeId] = nodesColors[nodeTobeMoved];

					markedNodes[col] = nodeTobeMoved;


				}
				else {

					nodesColors[removedNodeId] = rand() % 5;
				}
				
				nodesColors[nodeTobeMoved] = -1;
			}

		}
	}
	else {
	
		for (int row = markedNodes.size() - 1; row >= 0; row--){
			int removedNodeId = markedNodes[row];
			int nodeColor = nodesColors[removedNodeId];
			if (nodeColor == -1) {

				uint32_t nodeTobeMoved = removedNodeId + GAME_COL_MAX;

				if (nodeTobeMoved < nodesColors.size()) {
					nodesColors[removedNodeId] = nodesColors[nodeTobeMoved];


					markedNodes[row] = nodeTobeMoved;
				}
				else {
					nodesColors[removedNodeId] = rand() % 5;
				}
				nodesColors[nodeTobeMoved] = -1;
			}

		}

	}

	
	nodesGravityCheck(markedNodes); // make sure all nodes to move up

}
