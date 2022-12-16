#include "NavigationGrid.h"
#include "Assets.h"

#include <fstream>

using namespace NCL;
using namespace CSC8503;

const int LEFT_NODE		= 0;
const int RIGHT_NODE	= 1;
const int TOP_NODE		= 2;
const int BOTTOM_NODE	= 3;

const char WALL_NODE	= 'x';
const char FLOOR_NODE	= '.';

NavigationGrid::NavigationGrid()	{
	nodeSize	= 0;
	gridWidth	= 0;
	gridHeight	= 0;
	allNodes	= nullptr;
}

NavigationGrid::NavigationGrid(const std::string&filename) : NavigationGrid() {

	std::ifstream infile(Assets::DATADIR + filename);

	infile >> nodeSize;
	infile >> gridWidth;
	infile >> gridHeight;

	allNodes = new GridNode[gridWidth * gridHeight];

	for (int y = 0; y < gridHeight; ++y) {
		for (int x = 0; x < gridWidth; ++x) {
			GridNode&n = allNodes[(gridWidth * y) + x];
			char type = 0;
			infile >> type;
			n.type = type;
			n.position = Vector3((float)(x * nodeSize), 0, (float)(y * nodeSize));
		}
	}
	
	//now to build the connectivity between the nodes
	for (int y = 0; y < gridHeight; ++y) {
		for (int x = 0; x < gridWidth; ++x) {
			GridNode&n = allNodes[(gridWidth * y) + x];		

			if (y > 0) { //get the above node
				n.connected[0] = &allNodes[(gridWidth * (y - 1)) + x];
			}
			if (y < gridHeight - 1) { //get the below node
				n.connected[1] = &allNodes[(gridWidth * (y + 1)) + x];
			}
			if (x > 0) { //get left node
				n.connected[2] = &allNodes[(gridWidth * (y)) + (x - 1)];
			}
			if (x < gridWidth - 1) { //get right node
				n.connected[3] = &allNodes[(gridWidth * (y)) + (x + 1)];
			}
			for (int i = 0; i < 4; ++i) {
				if (n.connected[i]) {
					if (n.connected[i]->type == '.') {
						n.costs[i]		= 1;
					}
					if (n.connected[i]->type == 'x') {
						n.connected[i] = nullptr; //actually a wall, disconnect!
					}
				}
			}
		}	
	}
}

NCL::CSC8503::NavigationGrid::NavigationGrid(int nodeSize)
{
	this->nodeSize = nodeSize;
	gridWidth = 50;
	gridHeight = 50;
	allNodes = new GridNode[50 * 50];
   for (int i = 0; i < 50; i++)
   {
	   for (int j = 0; j < 50; j++)
	   {
		   GridNode& n = allNodes[(50 * i) + j];
			if(i==0||i==49||j==0||j==49||(i==24&&j>=13&&j<=38)||(j==24&&i>=13&&i<=38))
			{
			   n.type = (int)'x';
			}
		   else
		   {
			   n.type = (int)'.';
		   }
			n.position = Vector3(((j - (gridWidth/2)  + 1)) * nodeSize  , 0, ((i - (gridHeight/2) + 1) * nodeSize  ));
	   }
   }


   for (int y = 0; y < 50; ++y) {
	   for (int x = 0; x < 50; ++x) {
		   GridNode& n = allNodes[(50 * y) + x];

		   if (y > 0) { //get the above node
			   n.connected[0] = &allNodes[(50 * (y - 1)) + x];
		   }
		   if (y < gridHeight - 1) { //get the below node
			   n.connected[1] = &allNodes[(50 * (y + 1)) + x];
		   }
		   if (x > 0) { //get left node
			   n.connected[2] = &allNodes[(50 * (y)) + (x - 1)];
		   }
		   if (x < 50 - 1) { //get right node
			   n.connected[3] = &allNodes[(50 * (y)) + (x + 1)];
		   }
		   for (int i = 0; i < 4; ++i) {
			   if (n.connected[i]) {
				   if (n.connected[i]->type == '.') {
					   n.costs[i] = 1;
				   }
				   if (n.connected[i]->type == 'x') {
					   n.connected[i] = nullptr; //actually a wall, disconnect!
				   }
			   }
		   }
	   }
   }
}

NavigationGrid::~NavigationGrid()	{
	delete[] allNodes;
}

void NavigationGrid::PrintAllNode()
{
	GridNode* node;
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			 node = &allNodes[(50 * i) + j];
			 std::cout << node->position<<" ";
		}
		std::cout << std::endl;
	}
}

bool NavigationGrid::FindPath(const Vector3& from, const Vector3& to, NavigationPath& outPath) 
{
	//need to work out which node 'from' sits in, and 'to' sits in
	//24 is a specfic value just for 50 * 50 grid
	int fromX = ((int)from.x / nodeSize) + 24;
	int fromZ = ((int)from.z / nodeSize) + 24;

	int toX = ((int)to.x / nodeSize) + 24;
	int toZ = ((int)to.z / nodeSize) + 24;

	if (fromX < 0 || fromX > gridWidth - 1 ||
		fromZ < 0 || fromZ > gridHeight - 1) {
		return false; //outside of map region!
	}

	if (toX < 0 || toX > gridWidth - 1 ||
		toZ < 0 || toZ > gridHeight - 1) {
		return false; //outside of map region!
	}


	GridNode* startNode = &allNodes[(fromZ * gridWidth) + fromX];
	GridNode* endNode	= &allNodes[(toZ * gridWidth) + toX];

	std::vector<GridNode*>  openList;
	std::vector<GridNode*>  closedList;

	openList.push_back(startNode);

	startNode->f = 0;
	startNode->g = 0;
	startNode->parent = nullptr;

	GridNode* currentBestNode = nullptr;

	while (!openList.empty()) {
		currentBestNode = RemoveBestNode(openList);

		if (currentBestNode == endNode) {			//we've found the path!
			GridNode* node = endNode;
			while (node != nullptr) {
				outPath.PushWaypoint(node->position);
				node = node->parent;
			}
			return true;
		}
		else {
			for (int i = 0; i < 4; ++i) {
				GridNode* neighbour = currentBestNode->connected[i];
				if (!neighbour) { //might not be connected...
					continue;
				}	
				bool inClosed	= NodeInList(neighbour, closedList);
				if (inClosed) {
					continue; //already discarded this neighbour...
				}

				float h = Heuristic(neighbour, endNode);				
				float g = currentBestNode->g + currentBestNode->costs[i];
				float f = h + g;

				bool inOpen		= NodeInList(neighbour, openList);

				if (!inOpen) { //first time we've seen this neighbour
					openList.emplace_back(neighbour);
				}
				if (!inOpen || f < neighbour->f) {//might be a better route to this neighbour
					neighbour->parent = currentBestNode;
					neighbour->f = f;
					neighbour->g = g;
				}
			}
			closedList.emplace_back(currentBestNode);
		}
	}
	return false; //open list emptied out with no path!
}

bool NavigationGrid::ReturnSamplePoint(Vector3& pos)
{
	int i = rand() % gridWidth;
	int j = rand() % gridHeight;

	GridNode n = allNodes[(50 * j) + i];

	if (n.type != (int)'x')
	{
		pos = n.position;
		return true;
	}
	return false;
}



bool NavigationGrid::NodeInList(GridNode* n, std::vector<GridNode*>& list) const 
{
	std::vector<GridNode*>::iterator i = std::find(list.begin(), list.end(), n);

	return i == list.end() ? false : true;
}

GridNode*  NavigationGrid::RemoveBestNode(std::vector<GridNode*>& list) const {
	std::vector<GridNode*>::iterator bestI = list.begin();

	GridNode* bestNode = *list.begin();

	for (auto i = list.begin(); i != list.end(); ++i) {
		if ((*i)->f < bestNode->f) {
			bestNode	= (*i);
			bestI		= i;
		}
	}
	list.erase(bestI);

	return bestNode;
}

float NavigationGrid::Heuristic(GridNode* hNode, GridNode* endNode) const {
	return (hNode->position - endNode->position).Length();
}