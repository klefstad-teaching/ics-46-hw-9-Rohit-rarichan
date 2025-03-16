#include "ladder.h"
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


void error(string word1, string word2, string msg)
{
    cerr << word1 << " " << word2 << " " << "has error " << msg; 
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int l1 = str1.length(), l2 = str2.length();
    if (abs(l1 - l2) > d){return false;}

    int i = 0; 
    int j = 0; 
    int count = 0;
    while (i < l1 && j < l2){
        if (str1[i] != str2[j]){
            ++count;
            if (count > d){return false;}
            if (l1 > l2){++i;}
            else if(l1 < l2){++j;}
            else {++i, ++j;}
        }else{
            ++i;
            ++j;
        }
    } 
    count += (l1 - i) + (l2 - j);
    return count <= d;
}

//examines the ladders that are one step away from the orginal word, where only one letter is changed
bool is_adjacent(const string& word1, const string& word2)
{
    //return edit_distance_within(word1, word2, 1);
    int len1 = word1.length();
    int len2 = word2.length();

    if (len1 == len2){return true;}

    if (abs(len1 - len2) > 1) return false; // Length difference should be at most 1

    int diff_count = 0, i = 0, j = 0;

    while (i < len1 && j < len2) {
        if (word1[i] != word2[j]) {
            if (++diff_count > 1) return false;
            if (len1 > len2) ++i;  // Deletion case
            else if (len1 < len2) ++j; // Insertion case
            else { ++i; ++j; }  // Replacement case
        } else {
            ++i;
            ++j;
        }
    }
    
    return diff_count == 1 || (diff_count == 0 && abs(len1 - len2) == 1);

}
// uses bfs
//creates a queue of stacks
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word){return{};}
    //if (word_list.find(begin_word) == word_list.end()){return{};}

    queue<vector<string>> ladders;
    unordered_set<string> visited;

    ladders.push({begin_word});
    visited.insert(begin_word);

    while (!ladders.empty()){
        int size = ladders.size();
        unordered_set<string> level_visited;

        for (int i = 0; i < size; ++i){
            vector<string> ladder = ladders.front();
            ladders.pop();
            string last_word = ladder.back();

            if(last_word == end_word){return ladder;}

            for (const string & word : word_list){
                if (visited.find(word) == visited.end() && is_adjacent(last_word, word)){
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);

                    if (word == end_word){return new_ladder;}

                    ladders.push(new_ladder);
                    level_visited.insert(word);
                }
            }
        }
        visited.insert(level_visited.begin(), level_visited.end());
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name)
{
    ifstream file(file_name);
    if (!file){
        cerr << "Error: cannot open this file " << file_name << endl;
        return;
    }
    string word;
    while(file >> word){
        word_list.insert(word);
        //cout << word << " Inserted ";
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder)
{
    if (ladder.empty()){
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i){
        cout << ladder[i] << " ";
    }
    cout << endl;
}
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    string start = "hit";
    string end = "halt";
    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
}


/*vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    vector<string> words(word_list.begin(), word_list.end());
    int n = words.size();
    int start = -1;
    int end = -1;

    for (int i = 0; i < n; ++i){
        if (words[i] == begin_word){start = i;}
        if (words[i] == end_word){end = i;}
    }

    if (end == -1){return {};}
    if (start == -1){
        words.insert(words.begin(), begin_word);
        start = 0; 
        ++end;
        ++n;
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i){
        for (int j = i + 1; j < n; j++){
            if(is_adjacent(words[i], words[j])){
                adj[i].push_back(j);
                adj[i].push_back(i);
            }
        }
    }

    vector<vector<int>> parent(n);
    queue<int> q;
    vector<int> dist(n, 1005);
    q.push(start);
    parent[start].push_back(-1);
    dist[start] = 0;

    while (!q.empty()){
        int x = q.front();
        q.pop();
        for (int u : adj[x]){
            if (dist[u] > dist[x] + 1){
                dist[u] =  dist[x] + 1;
                q.push(u);
                parent[u].clear();
                parent[u].push_back(x);
            }else if (dist[u] == dist[x] + 1){
                parent[u].push_back(x);
            }
        }
    }
    vector<vector<int>> paths;
    vector<int> path;
    function<void(int)> shortestPaths = [&](int node){
        if (node == -1){
            paths.push_back(path);
            return;
        }
        for (int u : parent[node]){
            path.push_back(u);
            shortestPaths(u);
            path.pop_back();
        }
    };

    shortestPaths(end);
    if (paths.empty()){return {};}

    vector<string> shortest_ladder;
    for(int i = paths[0].size() - 1; i >= 0; --i){
        shortest_ladder.push_back(words[paths[0][i]]);
    }
    return shortest_ladder;
}*/