/* John Greathouse
 * CS302 Challenge 05: Graph Paths
 * Due Feb 22nd, 2020
 * This lab takes in graphs from standard input and determines if
 *   there's a path between two nodes.
 */

#include <vector>
#include <map>
#include <iostream>
#include <set>
using namespace std;

/* These are so I don't have to type ".find" a million times */
#define adj_list(x) (adj_list.find(x))
#define has_been(x) (has_been.find(x))
#define hB(x) (hB.find(x))

/* Functions used to determine paths */
bool recurs_dfs_nissan(const map<char, vector<char> > &adj_list, 
                char curr, char n2, set<char> &hB);
bool check_path(const map<char, vector<char> > &adj_list, char n1, char n2);

int main(int argc, char *argv[]) 
{
	int t, graphCnt;
	char n1, n2;
	vector<char> *temp_ptr, temp;
	map< char, vector<char> > adj_list;

	graphCnt = 1; // Tracks the amount of graphs tested

	while(cin >> t)
	{/* Loop that takes in input per graph */
		adj_list.clear(); // Resets each map

		if(graphCnt != 1) cout << endl; // Formatting

		for(; t > 0; --t) {
		 /* Makes a map the stores the graph */
			cin >> n1;
			cin >> n2;

			if(adj_list(n1) == adj_list.end() ) {
			/* Inserts a new element into map */
				temp.clear();
				temp.push_back(n2);
				adj_list.emplace(n1,temp);
			} else { 
			/* Just adds to the edge vector */
				temp_ptr = &((adj_list(n1))->second);
				temp_ptr->push_back(n2);
			}	
			if(adj_list(n2) == adj_list.end() ) {
			/* Inserts a new element for second edge into map */
				temp.clear();
				adj_list.emplace(n2,temp);
			} 
		}
		
		cin >> t; // Gets path-checking values
		for(; t > 0; --t)
		{
			cin >> n1; // Takes in test nodes
			cin >> n2;
			
			cout << "In Graph ";
			cout << graphCnt; // Prints out first half of format
			cout << " there is";

			if(check_path(adj_list, n1, n2) ) cout << " a ";
			else cout << " no "; // Conditional for whether it has a path or not

			cout << "path from " << n1 << " to " << n2 << endl; // Last half
		}
		/* Keeps track of how many graphs have been tested */
		++graphCnt;
	}
	return (0);
}


bool check_path(const map<char, vector<char> > &adj_list, 
                char n1, char n2)
{/* This is mostly just a syntax function, it creates a "has_been" set */
	set<char> has_been;
	
	if(recurs_dfs_nissan(adj_list, n1, n2, has_been) ) return 1;
	return 0;
}

bool recurs_dfs_nissan(const map<char, vector<char> > &adj_list, 
                char curr, char n2, set<char> &hB)
{/* It's called "nissan" because Pathfinder. It's a dfs search */
	int i;
	const vector<char> *temp;

	if(hB(curr) != hB.end() || adj_list(curr)->second.empty() )
	/* Base case: if either root or "has_been", return */	
		return curr == n2;
	
	if(curr != n2) {
	/* Calls dfs on all its children if it isn't a path */
		hB.insert(curr);
		temp = &(adj_list(curr)->second);
		for(i = 0; i < (int)temp->size(); ++i) {
		/* If any children are true, return true */
			if(recurs_dfs_nissan(adj_list, (*temp).at(i), n2, hB) ) 
				return 1;
		} /* Otherwise, just return false */
		return 0;
	} else return 1; // If it's a path it returns true
}
