//////////////////////////////
//      AVLTree Project for EADS
//
//      Jakub Tomkiewicz
/////////////////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include "fileManagement.h"

using namespace std;
 
void treeTest() { 

    cout << "\nS1:\n\n";
    AVLTree<int, int> s1;
    s1.insert(10, 2);
    s1.insert(20, 4);
    s1.insert(30, 3);
    s1.insert(5, 3);
    s1.insert(0, 7);
    s1.insert(15, 3);
    s1.insert(7, 3);
    s1.insert(6, 11);

    //s1.print();
    s1.print2D();
    cout << "\n\nS1: length: " << s1.length() << endl;
    cout << "S1: searching for (7,8): " << s1.search(7,8) << endl;
    cout << "S1: searching for (7,3): " << s1.search(7,3) << endl;
    int h = s1.height();
    cout << "S1: height: " << h << endl;

    AVLTree<int, int> s2;
    s2 = s1;
    cout << "\n\nS2 = S1:\n\n";
    s2.print2D();

    //////////OPENING THE OUTPUT FILE
    ofstream output_file;
    output_file.open("test.txt");

    cout << "\n\nprinting S1 into output file" << endl;
    s1.printStream(output_file, false);      //true = ascending, false = descending
    cout << "S1 printed" << endl;

    output_file.close();

}

void counterTest() {

    ifstream input_file;
    input_file.open("the_bible.txt");   //here change txt file
    AVLTree<string, int> counter;

    //////////AVLTREE
    auto start = chrono::high_resolution_clock::now();

    int sumTree = countWords(counter, input_file, true); //true = unique words, false = all words
    cout << "TREE Amount of words = " << sumTree << endl;

    auto stop = chrono::high_resolution_clock::now();
    auto dur = chrono::duration_cast<chrono::milliseconds>(stop - start);

    cout << "TREE Time = " << dur.count() << " milliseconds" << endl;

    input_file.close();
    input_file.open("the_bible.txt");   //here change txt file

    //////////MAP
    auto start2 = chrono::high_resolution_clock::now();

    int sumMap = countWordsMap(input_file);
    cout << "\nSTD::MAP Amount of words = " << sumMap << endl;

    auto stop2 = chrono::high_resolution_clock::now();
    auto dur2 = chrono::duration_cast<chrono::milliseconds>(stop2 - start2);

    cout << "STD::MAP Time = " << dur2.count() << " milliseconds\n"  << endl;

    input_file.close();

}

int main() {

    cout << "\n\nFIRST PART OF PROGRAM\n";
    treeTest();
    cout << "\n\nSECOND PART OF PROGRAM\n\n";
    counterTest();

    return 0;
}