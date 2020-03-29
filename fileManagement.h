#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "avltree.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
using namespace std;

string workOnString(string s) {     //lower letters and work with "." "," etc
    
    while( (int)s[0] == 124 || (int)s[0] == 59 || (int)s[0] == 58 ||(int)s[0] == 46 || (int)s[0] == 44 || (int)s[0] == 34 || (int)s[0] == 63 || (int)s[0] == 33 || (int)s[0] == 40 || (int)s[0] == 41 || (int)s[0] == 39 || (int)s[s.size()-1] == 46 || (int)s[s.size()-1] == 44 || (int)s[s.size()-1] == 63 || (int)s[s.size()-1] == 33|| (int)s[s.size()-1] == 40|| (int)s[s.size()-1] == 41 || (int)s[s.size()-1] == 39 || (int)s[s.size()-1] == 34 || (int)s[s.size()-1] == 58 || (int)s[s.size()-1] == 59 || (int)s[s.size()-1] == 124) {

        if((int)s[0] == 124 || (int)s[0] == 59 || (int)s[0] == 58 ||(int)s[0] == 46 || (int)s[0] == 44 || (int)s[0] == 63 || (int)s[0] == 33 || (int)s[0] == 40 || (int)s[0] == 41 || (int)s[0] == 39 || (int)s[0] == 34 )s.erase(0,1);

        if((int)s[s.size()-1] == 124 || (int)s[s.size()-1] == 59 || (int)s[s.size()-1] == 58 ||(int)s[s.size()-1] == 46 || (int)s[s.size()-1] == 44 || (int)s[s.size()-1] == 63 || (int)s[s.size()-1] == 33|| (int)s[s.size()-1] == 40|| (int)s[s.size()-1] == 41 || (int)s[s.size()-1] == 39 || (int)s[s.size()-1] == 34 )s.erase(s.size()-1,1);

    }

    for(int i=0; i<s.size(); i++) s[i] = tolower(s[i]);

    return s;
}

int countWords(AVLTree<string, int>& cut,ifstream& source, bool unique) {      //send words from txt to tree

    if(!source.is_open()) {
        cout << "Error: File not loaded!" << endl;
        return 0;
    }

    string t;

    while(source >> t) {
        t = workOnString(t);
        if(!unique)cut.insertForCounter(t, 1);
        else cut.insert(t, 1);
    }
    
    source.close();

    return cut.length();
}

int countWordsMap(ifstream& source) {     //send words from txt to map

    if(!source.is_open()) {
        cout << "Error: File not loaded!" << endl;
        return 0;
    }

    map<string, int> count_map;
    string t;

    while(source >> t) {
        t = workOnString(t);
        count_map[t]++;
    }

    return count_map.size();
}

#endif