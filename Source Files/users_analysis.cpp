#include "users_analysis.h"
#include <iostream>

string mostInfluencer(map<string, vector<string>> users)
{
	string IDMax="";
	int MaxFollowers = 0;
	//knowing the user with the most followers by checking the size of followers vector
	for (auto user : users)
	{
		if (user.second.size() > MaxFollowers)
		{
			MaxFollowers = user.second.size();
			IDMax = user.first;
		}
	}
	return IDMax;
}
string mostActive(map<string, vector<string>> users)
{
	map<string, int>usersActivity;
	for (auto user : users)
	{
		//check followers of each user and increment activity if the user follows any other user
		for (auto follower : user.second)
		{
			usersActivity[follower]++;  
		}
	}
	string mostActive = "";
	int max = 0;
	for (auto user : usersActivity)
	{
		if (user.second >= max)
		{
			max = user.second;
			mostActive = user.first;
		}

	}
	return mostActive;
}
string mutualFollowers(map<string, vector<string>> users,string firstUser,string secondUser)
{
	auto first =users.find(firstUser);
	auto second = users.find(secondUser);
	string mutual;
	// loop for the mutual followers by searching for the first in second
	for (auto followerUser1 : first->second)
	{
		for (auto followerUser2 : second->second)
		{
			if (followerUser1 == followerUser2)
			{
				//add user
				mutual+=followerUser1;
				mutual += " ";
				break;
			}
		}
	}
	return mutual;
}

void NetworkAnalysis(map<string, vector<string>>& users, vector<string> data)
{
	string current = "";
	vector<string> v;
	bool newUser = false, follower = false;

	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] == "<user>") newUser = true;
		if (data[i] == "<id>" && newUser)
		{

			newUser = false;
			// checking the previous user
			
				if(!(current==""))
					users.insert({current ,v});
			current = data[i + 2];
			//cout << "current change";
			
			v.clear();

		}
		if (data[i] == "<follower>") follower = true;
		if (data[i] == "<id>" && follower) {
			follower = false;
			v.push_back(data[i + 2]);

		}
	}
	users.insert({ current ,v });
}

string followerSuggest(map<string, vector<string>> users, string user)
{
	auto userIterator = users.find(user);
	string suggestions;

	vector<string> visited; //to not check the user twice
	//insert nodes that cannot be suggested like the follower and the user itself
	visited.push_back(user);
	for (auto followers : userIterator->second) visited.push_back(followers);

	//loop to check each user followers and to check that it is not repeated
	for (auto followers : userIterator->second)
	{
		
		auto follower = users.find(followers);
		if (follower == userIterator) continue; 
		//check follow's followers
		bool visitedflag = false;
		if (follower == users.end()) break;
		for (auto suggest : follower->second) 
		{
			
			for (auto visit : visited)
			{
				visitedflag = false;
				if (visit == suggest)
				{
					visitedflag = true;
					break;
				}
			}
			
			if (visitedflag) continue;
			suggestions += suggest;
			suggestions += " ";
			visited.push_back(suggest);
			//if (visited.size() == users.size()) return suggestions;
		}
	}
	return suggestions;
}
/*bool newUser = false;
	for (int i = 0; i < data.size(); i++)
	{
		if (data[i] == "<user>") newUser = true;
		if (data[i] == "<id>" && newUser)
		{
			//intializing new user
			newUser = false;
			users.insert({ data[i + 2],0 });
		}
	}
	for (int i = 0; i < data.size(); i++)
	{
		//if (data[i] == "<user>") newUser = true;
		if (data[i] == "<id>")
		{
			//intializing new user
			users[data[i+2]]++;
		}
	}
	string mostActive = "";
	int max=0;
	for (auto user : users)
	{
		if (user.second >= max)
		{
			max = user.second;
			mostActive = user.first;
		}
	}*/