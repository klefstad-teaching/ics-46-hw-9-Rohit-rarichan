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
    return edit_distance_within(word1, word2, 1);
}
// uses bfs
//creates a queue of stacks
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word){return{begin_word};}
    if (word_list.find(begin_word) == word_list.end()){return{};}

    queue<vector<string>> ladders;
    ladders.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);

    while (!ladders.empty()){
        int size = ladders.size();
        //set<string> level_visited;

        for (int i = 0; i < size; ++i){
            vector<string> ladder = ladders.front();
            ladders.pop();
            string last_word = ladder.back();

            if(last_word == end_word){return ladder;}

            for (const string & word : word_list){
                if (visited.find(word) == visited.end() && is_adjacent(last_word, word)){
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    ladders.push(new_ladder);
                    visited.insert(word);
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
    cout << "Word ladder found: ";
    for (size_t i = 0; i < ladder.size(); ++i){
        cout << ladder[i] << " ";
    }
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
