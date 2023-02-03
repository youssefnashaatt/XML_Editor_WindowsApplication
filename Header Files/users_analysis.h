#pragma once
#include <vector>
#include<string>
#include<map>
using namespace std;
string mostInfluencer(map<string, vector<string>> users);
string mostActive(map<string, vector<string>> users);
string mutualFollowers(map<string, vector<string>> users, string firstUser, string secondUser);
void NetworkAnalysis(map<string, vector<string>>& users, vector<string> data);
string followerSuggest(map<string, vector<string>> users, string user);
