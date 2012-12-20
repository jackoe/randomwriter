//
//  main.cpp
//  randomWriter
//
//  Created by Jack Wines on 6/21/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <iterator>
#include "time.h"

using namespace std;

const int ORDER = 3;
const int OUTPUT_LENGTH = 1000;

void fileReading(string &text);
void GoThroughString(map <string, string> &followings, string randomWriterText);
string FindMostCommonKey(map<string, string> following);
int main (int argc, const char * argv[]);
char GrabARandomChar(string charsToGrabFrom, string &endtext, map<string, string> &followings);
char GimmieThatNextLetter(string threeLetterInput, string &endtext, map <string, string> &followings);

void fileReading(string &text) {
    string line;
    ifstream myfile("source.txt");
    
    if (myfile.is_open()) {
        while (myfile.good()) {
            getline(myfile, line);
            text += line;
        }
        myfile.close();
    } else {
        cout << "Unable to open file.";
    }
    
    return;
}

void GoThroughString(map <string, string> &followings, string randomWriterText) {
    for (size_t i = 0; i+ORDER < randomWriterText.length(); i++) {
        string key = randomWriterText.substr(i,ORDER);
        char nextChar = randomWriterText[i+ORDER];

        if (followings.count(key)) {
            string value = followings[key];
            value += nextChar;
            followings[key] = value;
        } else {
            followings[key] = nextChar;
        }
    }
    
    return;
}

string FindMostCommonKey(map<string, string> following) {
    string mostCommonKey;
    int highestLength = 0;
    for (map<string, string>::iterator it = following.begin(); it != following.end(); it++) {
        string key = it->first;
        string value = it->second;
        if (value.length()>highestLength) {
            highestLength = (int)value.length();
            mostCommonKey = key; 
        }
    }
    
    return mostCommonKey;
}

char GrabARandomChar(string charsToGrabFrom, string &endtext, map<string, string> &followings){
    if (charsToGrabFrom.length() == 0) {
        endtext+=endtext.substr(0,3);
        return GimmieThatNextLetter(endtext.substr(0,3), endtext, followings);
    }
    
    int index = rand() % (int)charsToGrabFrom.length();
    return charsToGrabFrom[index];
    
}

char GimmieThatNextLetter(string threeLetterInput, string &endtext, map <string, string> &followings){
    return GrabARandomChar(followings[threeLetterInput], endtext, followings);
}

int main (int argc, const char * argv[]) {
    srand((int)time(NULL));
    
    string randomWriterText;
    fileReading(randomWriterText);
    
    map<string, string> followings;
    GoThroughString(followings, randomWriterText);

    string endtext = FindMostCommonKey(followings);
    
    while (endtext.length() < OUTPUT_LENGTH) {
        int startIndex = (int)endtext.length()-(ORDER);
        string lastThreeLetters = endtext.substr(startIndex,ORDER);

        char nextChar = GimmieThatNextLetter(lastThreeLetters, endtext, followings);
        endtext += nextChar;
    }
    
    cout << endtext;
    return 0;
}