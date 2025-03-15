#include "ladder.h"
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <iostream>
#include <fstream>
using namespace std;



void error(string word1, string word2, string msg)
{
    cerr << word1 << " " << word2 << " " << "has error " << msg; 
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d)
{
    int l1 = str1.length();
    int l2 = str2.length();

    if (l1 == 0) {return l2;}
    if (l2 == 0) {return l1;}

    vector<vector<int>> arr(l1+1,vector<int>(l2 + 1));

    for (int i = 0; i <= l1; ++i){arr[i][0] = i;}
    for (int j = 0; j <= l2; ++j){arr[0][j] = j;}

    for (int i = 1; i <= l1; ++i){
        char ch1 = str1[i - 1];

        for (int j = 1; j <= l2; ++j){
            char ch2 = str2[j - 1];
            int m = ch1 == ch2 ? 0 : 1;
            arr[i][j] = min(min((arr[i - 1][j] + 1), (arr[i][j - 1]+ 1)), arr[i - 1][j - 1] + m);
            if (arr[i][j] > d){return false;}
        }
    }
    return arr[l1][l2] <= d;
    
}
//examines the ladders that are one step away from the orginal word, where only one letter is changed
bool is_adjacent(const string& word1, const string& word2)
{
    return edit_distance_within(word1, word2, 1) == 1;
}
// uses bfs
//creates a queue of stacks
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()){
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        for (string word : word_list){
            if (is_adjacent(last_word, word)){
                if (find(visited.begin(),visited.end(),word) == visited.end()){
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if(word == end_word){return new_ladder;}
                    ladder_queue.push(new_ladder);
                }
            }
        }
        //visited.insert(level_visited.begin(), level_visited.end());
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
    }
    file.close();
}
void print_word_ladder(const vector<string>& ladder)
{
    for (size_t i = 0; i < ladder.size(); ++i){
        cout << ladder[i] << " -> ";
    }
}
void verify_word_ladder()
{
    set<string> word_list;
    load_words(word_list, "words.txt");
    string start, end;
    cin >> start;
    cin >> end;
    vector<string> ladder = generate_word_ladder(start, end, word_list);
    print_word_ladder(ladder);
}
