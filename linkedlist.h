#include <iostream>
#include <string>
using namespace std;

struct neighborNode
{
	string neighborName;
	neighborNode * next;
	
	neighborNode()
		: neighborName(""), next(NULL)
	{}

	neighborNode(const string &n_name, neighborNode * n_nextNode)
		: neighborName(n_name), next(n_nextNode)
	{}

};

struct houseNode
{
	string houseName;
	neighborNode * neighborListHead;
	houseNode * next;
	
	houseNode()
		: houseName(""), next(NULL), neighborListHead(NULL)
	{}

	houseNode(const string &h_name, houseNode * h_nextNode, neighborNode * n_head = NULL)
		: houseName(h_name), next(h_nextNode), neighborListHead(n_head)
	{}

};


class linkedlist
{
public:
	linkedlist();
	void addHouseNode(string hname);	//adding a new house node
	void addNeighborNode (string hname, string nname); //adding a new neighbor node
	void printAll();
	bool hnExists(string hname);	//check if house exists
	bool nnExists(string hname, string nname); //check if neighbor exists
	void deleteAll(); 
	void deleteConquered(string hname, string nname); //conquer nname and delete all nname house and delete nname neighbor from hname house
	void changeNname(string hname, string nname); //change nname's name with the hname's name if hname is not their neighbor
	void addConqueredNeighbors(string hname, string nname);	//after conquer nname, add its neighbors to hname if they don't exist
private:
	houseNode * head;
};