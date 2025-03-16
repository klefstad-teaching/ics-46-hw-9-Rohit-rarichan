#include "ladder.h"
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
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
    /*int l1 = str1.size(), l2 = str2.size();
    if (abs(l1 - l2) > d){return false;}
    vector<vector<int>> dp(l1+1, vector<int>(l2+1,0));

    for(int i =0; i <= l1; ++i){
        for (int j = 0; j <= l2; ++j){
            if(i == 0){dp[i][j] = j;}
            else if (j == 0){dp[i][j] = i;}
            else if (str1[i-1] == str2[j-1]){dp[i][j] = dp[i - 1][j - 1];}
            else{dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});}
            if (dp[i][j] > d){return false;}
        }
    }
    return dp[l1][l2] <= d;*/
}

//examines the ladders that are one step away from the orginal word, where only one letter is changed
bool is_adjacent(const string& word1, const string& word2)
{
    //if (word1 == word2){return true;}
    return edit_distance_within(word1, word2, 1);/

}
// uses bfs
//creates a queue of stacks
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list)
{
    if(begin_word == end_word){return{};}
    //if (word_list.find(begin_word) == word_list.end()){return{};}

    unordered_set<string> dict(word_list.begin(), word_list.end());
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