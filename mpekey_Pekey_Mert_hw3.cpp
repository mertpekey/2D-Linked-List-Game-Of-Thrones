#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "linkedlist.h"

using namespace std;

//Mert Pekey 23646

int main()
{

	linkedlist newlist;	//our linkedlist object

	bool errorbool=false;
	int decision;
	string file1, linefile, firstword, secondword,pathline;
	string housename, neighborname, firsthouse, secondhouse;
	ifstream got;
	cout<<"Please enter a file name."<<endl;
	cin>>file1;

	got.open(file1);

	while (got.fail())	//asking user until file opened correctly
	{
		cout<<"File could not be opened."<<endl;
		cout<<"Please enter a file name."<<endl;
		cin>>file1;
		got.clear();
		got.open(file1);
	}


	cout<<"Successfully opened file "<<file1<<endl<<endl;

	cout<<"######## TOPOLOGY ########"<<endl<<endl;

	while (!got.eof())		//getting file information line by line until end of file
	{

		getline(got, linefile);

		istringstream iss;

		iss.str(linefile);

		if(linefile != "")		// If there is an empty line, we pass it
		{
			iss>>housename>>neighborname;	// getting house name and neighbor name separately and assign to variables

			cout<<"Processing "<<housename<<", "<<neighborname<<endl;

			bool found = true;		//to decide if the process already processed we have a boolean variable named "found"

			if (newlist.hnExists(housename) == false)	//If house does not exist we add it with its neighbor
			{
				newlist.addHouseNode(housename);
				newlist.addNeighborNode(housename, neighborname);

				if (newlist.hnExists(neighborname) == false)	//If the neighbor does not exist as a house we add it to house list
				{
					newlist.addHouseNode(neighborname);
					newlist.addNeighborNode(neighborname, housename);
				}
				else											// If it exist, we add our housename as a neighbor if this house is not a neighbor of it
				{
					if (newlist.nnExists(neighborname, housename) == false)
					{
						newlist.addNeighborNode(neighborname, housename);
					}
				}

				found = false;
			}

			else                                               //If house exist already, we only look for the same conditions for neighbor.
			{
				if (newlist.nnExists(housename, neighborname) == false)
				{
					newlist.addNeighborNode(housename, neighborname);

					if (newlist.hnExists(neighborname) == false)
					{
						newlist.addHouseNode(neighborname);
						newlist.addNeighborNode(neighborname, housename);
					}

					found = false;
				}

				if (newlist.nnExists(neighborname, housename) == false)
				{
					newlist.addNeighborNode(neighborname, housename);
					found = false;
				}
			}

			if (found == true)
				cout<<"Redundant information! An entry with "<<housename<<" and "<<neighborname<<" is already processed."<<endl<<endl;
			else
				cout<<"Topology information successfully added."<<endl<<endl;

		}
	}

	cout << "######## MAP ########" << endl<<endl;
	newlist.printAll();   //Print Our LinkedList

	decision = 0;         //for selection of option

	while (decision != 3)
	{
		cout<<"Please select an option [1-2-3]."<<endl;
		cout<<"1. Annexation! War for the iron throne continues..."<<endl;
		cout<<"2. Tyrion must travel, do a path check for the famous imp."<<endl;
		cout<<"3. Exit"<<endl;

		cin>>decision;

		if (decision == 1)		//to conquer somewhere we use 1 and first name conquer other name if they are neighbor
		{
			cout<<"Please enter two houses first the annexer and the annexed. (ex: Tyrell Stark)."<<endl;
			cin>>firsthouse>>secondhouse;

			if (firsthouse != secondhouse)         //noone can conquer itself
			{

				if (newlist.hnExists(firsthouse) == true)													
				{                                                    //both house and neighbor must exist and be neighbor
					if (newlist.hnExists(secondhouse) == true)
					{
						if (newlist.nnExists(firsthouse, secondhouse) == true) 
						{
							cout<<firsthouse<<" conquered "<<secondhouse<<endl;
							newlist.addConqueredNeighbors(firsthouse, secondhouse);     //add the neighbors of conquered neighbor to the conquerer house
							newlist.deleteConquered(firsthouse, secondhouse);			//delete all of the neighbor and house of conquered neighbor and delete neighbor from house's neighbors
							newlist.changeNname(firsthouse,secondhouse);				//Change conquerd neighbors name from other houses with the conquered house name
							cout << "######## MAP ########" << endl;
							newlist.printAll();
						}
						else
						{
							cout<<"A house can only conquer a neighboring house! "<<secondhouse<<" is not a neighbor of "<<firsthouse<<"."<<endl;
							cout<<"Update failed."<<endl<<endl;
							cin.clear();
						}
					}
					else
					{
						cout<<secondhouse<<" does not exist!"<<endl;
						cout<<"Update failed."<<endl<<endl;
						cin.clear();
					}

				}
				else
				{
					cout<<firsthouse<<" does not exist!"<<endl;
					cout<<"Update failed."<<endl<<endl;
					cin.clear();
				}
			}
			else
			{
				cout<<"A House cannot conquer itself"<<endl;
				cout<<"Update failed."<<endl<<endl;
				cin.clear();
			}
		}



		else if (decision == 2)         //Checking if the path exist by looking each pair with each other 
		{
			cout<<"Please enter a path. (ex: Tyrell Martell Tully)"<<endl;
			cin.ignore();
			getline(cin, pathline);
			istringstream iss2;
			iss2.str(pathline);
			iss2>>firstword;					//get the firstword separately and then change it with the second word en of the while and update secondword
			while (iss2>>secondword)
			{
				if (newlist.hnExists(firstword))
				{                                              //Checking the conditions for existence
					if (newlist.hnExists(secondword))
					{
						if (firstword != secondword)
						{
							if (newlist.nnExists(firstword, secondword))
							{
								cout<<"Path found between "<<firstword<<" and "<<secondword<<endl;
								errorbool = false;
							}
							else
							{
								cout<<secondword<<" is not a neighbor of "<<firstword<<endl;
								cout<<"Path search failed!"<<endl<<endl;
								errorbool = true;
								break;
							}
						}
						else
							cout<<"You are already in "<<firstword<<endl;
					}
					else
					{
						cout<<secondword<<" is not a neighbor of "<<firstword<<endl;
						cout<<"Path search failed!"<<endl<<endl;
						errorbool = true;
						break;
					}
				}
				else
				{
					cout<<firstword<<" does not exist in the map."<<endl;
					cout<<"Path search failed!"<<endl<<endl;
					errorbool = true;
					break;
				}

				firstword = secondword;
			}

			if (errorbool == false)
			{
				cout<<"Path search succeeded."<<endl<<endl;
			}


		}

		else if(decision !=3)	//Options are only 1-2-3
			cout<<"Invalid option please select from the menu."<<endl<<endl;


	}


	newlist.deleteAll(); //to deallocate all dynamic data
	cout<<"List deleted and program ended."<<endl;


	return 0;
}

















































