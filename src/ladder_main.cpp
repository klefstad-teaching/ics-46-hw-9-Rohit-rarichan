//Prompts users for a start and end word and finds the minimum length from there
//check if the start and end words are the same to avoid infinite loop
//use the implementation in ladder.cpp to find the shortest path using bfs
#include "ladder.h"
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    //verify_word_ladder();
    //set<string> word_list;
    //load_words(word_list, "words.txt");
    //vector<string> ladder = generate_word_ladder("cat", "dog", word_list);
    //print_word_ladder(ladder);
    bool ans = is_adjacent("hit", "halter");
    cout << ans << endl;
    return 0;
}