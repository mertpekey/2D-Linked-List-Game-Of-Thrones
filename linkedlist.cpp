#include <iostream>
#include "linkedList.h"

using namespace std;


linkedlist::linkedlist()	//Constructor
{
	head = NULL;
}

/* Begin: code taken from linkedlist.cpp and updated */
void linkedlist::addHouseNode(string n)  //add house node if not exists in houses
{
	houseNode *ptr = head;
	houseNode *temp = new houseNode(n, NULL, NULL);
	
	if(head == NULL)
	{
		head = temp;
	}
	else
	{
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = temp;
	}
}
/* End: code taken from linkedlist.cpp and updated */

void linkedlist::addNeighborNode (string hname, string nname) // add neighbor node if not exists in neighbors
{
	bool found = false;
	houseNode *ptr = head;
	neighborNode *temp = new neighborNode(nname, NULL);
	neighborNode *nhead;
	

	while (ptr != NULL)
	{
		nhead = ptr->neighborListHead;

		if (ptr->houseName == hname)
		{
			if (nhead == NULL)
			{
				ptr->neighborListHead = temp;
			}
			else
			{
				while (nhead->next != NULL)
				{
					nhead = nhead->next;
				}
				nhead->next = temp;
			}
			found = true;
		}
		ptr = ptr->next;
	}

	if (found == false)        //If it does not exist in the house nodes we add it with its neighbor
	{
		addHouseNode(hname);
		delete temp;
		addNeighborNode (hname, nname);
	}

}

/* Begin: code taken from linkedlist.cpp and updated */
void linkedlist::printAll() //printing all the linkedlist
{
	houseNode *ptr = head;
	neighborNode *nhead;

	while (ptr != NULL)
	{
		nhead = ptr->neighborListHead;

		cout << ptr->houseName << ": ";

		while (nhead != NULL)
		{
			cout << nhead->neighborName << ", ";
			nhead = nhead->next;
		}
		cout << endl;
		ptr = ptr->next;
	}
	cout << endl;
}
/* End: code taken from linkedlist.cpp and updated */

/* Begin: code taken from linkedlist.cpp and updated */
bool linkedlist::hnExists(string hname) //checking existence and return true if house exists
{
	houseNode *ptr = head;

	while (ptr != NULL)
	{
		if (ptr->houseName == hname)
		{
			return true;
		}
		ptr = ptr->next;
	}
	return false;
}
/* End: code taken from linkedlist.cpp and updated */

/* Begin: code taken from linkedlist.cpp and updated */
bool linkedlist::nnExists(string hname, string nname) //checking existence and return true if neighbor exists
{
	houseNode *ptr = head;
	neighborNode *nhead;

	if(hnExists(hname) == false)         // If house not exist, neighbor is also not exists
		return false;
	else
	{
		while (ptr != NULL)
		{
			nhead = ptr->neighborListHead;

			if (ptr->houseName == hname)
			{
				while (nhead != NULL)
				{
					if (nhead->neighborName == nname)
					{
						return true;
					}
					nhead = nhead->next;
				}
				return false;
			}
			ptr = ptr->next;
		}
	}
}
/* End: code taken from linkedlist.cpp and updated */

/* Begin: code taken from linkedlist.cpp and updated */
void linkedlist::deleteAll()   //delete the linked list to deallocate the all dynamic data
{
	houseNode *ptr;
	neighborNode *nhead;
	neighborNode *nptr;   //it is like a temp and used for deletion of neighbors

	while (head != NULL)
	{
		ptr = head;
		nhead = ptr->neighborListHead;
		while (nhead != NULL)
		{
			nptr = nhead;
			nhead = nhead->next;
			delete nptr;
		}
		head = head->next;
		delete ptr;
	}
}
/* End: code taken from linkedlist.cpp and updated */

void linkedlist::deleteConquered(string hname, string nname)	//when hname tried to conquer nname
{                                                               // delete all neighbors and then itself of conquered(nname)
	houseNode *head_copy = head;                                // delete this neighbor from hname's neighbors
	houseNode *ptr;
	neighborNode *nhead; // neighbors' head
	neighborNode *nptr;  //for deletion of neighbors
	bool onlyonce=true; // this is for if the deletion will be on the head of house nodes
	bool ordered=false; // if an house tried to conquer its consecutive house, this helps us to avoid crash because we use head_copy->next for checking hname

	while (head_copy != NULL && head_copy->next != NULL)
	{
		ptr = head_copy;
		nhead = ptr->neighborListHead; 

		if (head->houseName == hname && onlyonce == true) //If deletion will be on head of house nodes
		{
			//delete conquered neighbor from house's neighbor
			if (nhead->neighborName == nname)
			{
				ptr->neighborListHead = nhead->next;
				delete nhead;			

			}
			else
			{			
				while (nhead->next != NULL)
				{
					if (nhead->next->neighborName == nname)
					{
						nptr = nhead->next;
						nhead->next = nhead->next->next;
						delete nptr;
						break;
					}
					nhead = nhead->next;
				}
			}
			onlyonce = false;
		}
		else if (head_copy->next->houseName == hname)
		{
			ptr = ptr->next;
			nhead = ptr->neighborListHead;
			//delete conquered neighbor from house's neighbor
			if (nhead->neighborName == nname)
			{
				ptr->neighborListHead = nhead->next;
				delete nhead;			
			}
			else
			{			
				while (nhead->next != NULL)
				{
					if (nhead->next->neighborName == nname)
					{
						nptr = nhead->next;
						nhead->next = nhead->next->next;
						delete nptr;
						break;
					}
					nhead = nhead->next;
				}
			}
			onlyonce = false;
			ordered = false;
		}
		else if (ordered == true && head_copy->houseName == hname) //For the consecutive pair
		{
			nhead = ptr->neighborListHead;
			//delete conquered neighbor from house's neighbor
			if (nhead->neighborName == nname)
			{
				ptr->neighborListHead = nhead->next;
				delete nhead;			
			}
			else
			{			
				while (nhead->next != NULL)
				{
					if (nhead->next->neighborName == nname)
					{
						nptr = nhead->next;
						nhead->next = nhead->next->next;
						delete nptr;
						break;
					}
					nhead = nhead->next;
				}
			}
			onlyonce = false;
		} 

		ptr = head_copy;
		nhead = ptr->neighborListHead;

		//delete all of the conquered house and its neighbors
		if (head->houseName == nname)
		{
			while (nhead != NULL)
			{
				nptr = nhead;
				nhead = nhead->next;
				delete nptr;
			}

			head = head->next;
			head_copy = head;
			delete ptr;
			ordered = true;
		}
		else
		{
			if (head_copy->next->houseName == nname)
			{
				ptr = ptr->next;
				nhead = ptr->neighborListHead;
				while (nhead != NULL)
				{
					nptr = nhead;
					nhead = nhead->next;
					delete nptr;
				}

				head_copy->next = head_copy->next->next;
				delete ptr;
				ordered = true;
			}		
		}
		head_copy = head_copy->next;
	}
}

void linkedlist::changeNname(string hname, string nname) // change conquered house name with the conquerer name in other houses if conquerer is not neighbor of other houses
{                                                        // If conquerer is their neigbor then only delete conquered neighbor.
	houseNode *ptr = head;
	neighborNode *nhead;
	neighborNode *nhead_c;
	neighborNode *nptr;
	bool doesexist;

	while (ptr != NULL)
	{
		doesexist = false;     //checking if conquerer exists to decide to change conquered name or delete it.
		nhead = ptr->neighborListHead;
		nhead_c = ptr->neighborListHead;

		while (nhead_c != NULL)
		{
			if (nhead_c->neighborName == hname)
			{
				doesexist = true;
			}
			nhead_c = nhead_c->next;
		}

		if(doesexist == false)
		{
			while (nhead != NULL)
			{
				if (nhead->neighborName == nname)
				{
					nhead->neighborName = hname;
				}
				nhead = nhead->next;
			}
		}
		else
		{
			if (nhead->neighborName == nname)
			{
				ptr->neighborListHead = nhead->next;
				delete nhead;			
			}
			else
			{			
				while (nhead->next != NULL)
				{
					if (nhead->next->neighborName == nname)
					{
						nptr = nhead->next;
						nhead->next = nhead->next->next;
						delete nptr;
						break;
					}
					nhead = nhead->next;
				}
			}
		}
		ptr = ptr->next;
	}
}

void linkedlist::addConqueredNeighbors(string hname, string nname) //When we conquered a neighbor, we will be neighbor with its neighbors if they are not already our neighbor
{
	houseNode *ptrneighbor = head;
	houseNode *ptrhouse = head;
	houseNode *ptr = head;
	neighborNode *nhead;

	while (ptr != NULL)
	{
		nhead = ptr->neighborListHead;
		if (ptr->houseName == nname)
		{
			while (nhead != NULL)
			{
				if (!nnExists(hname, nhead->neighborName))
				{
					if(nhead->neighborName != hname)
						addNeighborNode(hname, nhead->neighborName);
				}
				nhead = nhead->next;
			}
		}	
		ptr = ptr->next;
	}


}