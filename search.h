/**
 * @file: search.h
 *
 * @description: Program is a search engine that lets the user find
 * words using intersection, union and remove. Maps, sets and vectors are
 * used in order to make the search engine efficient.
 *
 * Code Written by
 * @author: Sai Samarth Patipati Umesh
 * U. of Illinois, Chicago
 * @date: 2/7/21
 *
 */

#pragma once
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <ctype.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
//#include<bits/stdc++.h>
using namespace std;

/**
 * alphabets()
 * Checks if the given string contains alphabets
 *
 * @param: string s and int count.
 * @return: void but return count of alphabets through parameter.
 */
void alphabets(string s, int& count) {
    for (unsigned int j = 0; j < s.length(); j++) {
      if (isalpha(s.at(j))) {
          count++;
      }
  }
}

/**
 * frontPunct()
 * Removes punctuation from the front of the string
 *
 * @param: string s to be concatenated and unsigned int k of the initial value.
 * @return: void, changed string through the parameter.
 */
void frontPunct(string& s, unsigned int k) {
  while (k < s.length()) {
      // if the character is not a punct break out of the loop
      if (!(ispunct(s.at(k)))) {
          break;
      } else {
          // else keep reducing the string by removing the punctuation
          s = s.substr(k + 1, s.length() - k);
          k--;
      }
      k++;
  }
}

/**
 * backpunct()
 * Removes punctaution from the back of the string
 *
 * @param: string s to be concatenated and unsigned int k with initial value
 * @return: void, return changed string through parameter.
 */
void backPunct(string& s, unsigned int k) {
     while (k >=0) {
      if (!(ispunct(s.at(k)))) {
          break;
      } else {
          s = s.substr(0, k);
      }
      k--;
  }
}
/**
 * token()
 * Given a string the function converts the string to lower case and makes sure there are no punctuations.
 *
 * @param: string output and string s to be converted
 * @return: void, string output will contain the changed string.
 */
void token(string& output, string& s) {
    for (unsigned int i = 0; i < s.length(); i++) {
    if (i != 0 || i != s.length() - 1) {
        if (!ispunct(s.at(i))) {
           output += tolower(s.at(i));
        } else if (s.at(i) == 0x20) {
            output += ' ';
        } else {
            output+= s.at(i);
        }
    } else {
        if (!ispunct(s.at(i))) {
            output += tolower(s.at(i));
        }
    }
}
}

/**
 * cleanToken()
 * Cleans a given string by removing punctuations before and after the word.
 * String needs to contain atleast one alphabet to be valid. This function uses helped functions.
 *
 * @param: string s to be checked and changed.
 * @return: string output of the cleaned string.
 */
string cleanToken(string s) {
    string output = "";
    string input;
    int count = 0;
    alphabets(s, count);
    // checks if the string is empty or contains atleast one alphabet.
    if (s.empty()) {
      return output;
    }
    if (count == 0) {
      return output;
    }
    // if the string contains alphabets, the helped functions clean the token.
    unsigned int k = 0;
    if (count > 0) {
        frontPunct(s, k);
        k = s.length() - 1;
        backPunct(s, k);
        token(output, s);
    }
    return output;
}

/**
 * gatherTokens()
 * Given a string of body text, this function returns a set of strings
 * containing individual and unique words.
 * 
 * @param: string text containing body text
 * @return: set<string> containing individual tokens
 */
set<string> gatherTokens(string text) {
    set<string> tokens;
    string word;
    stringstream iss(text);
    string s;
    while (iss >> word) {
        s  = cleanToken(word);
        if (s != "") {
        tokens.insert(s);
        }
    }
    return tokens;
}

/**
 * buildIndex()
 * Builds the map index using the file passed as the parameter.
 * This function calls gatherTokens() to get the key(words).
 *
 * @param: string filename, map<string, set<string>>& index
 * @return: int of the number of urls
 */
int buildIndex(string filename, map<string, set<string>>& index) {
    string url, body;
    int count = 0;
    ifstream infile(filename);
    if (!(infile.good())) {
        return 0;
    }
    getline(infile, url);
     count++;
    int size = 0;
    // while loop to run till the file is empty or failed
    while (!infile.eof() && !infile.fail()) {
    getline(infile, body);
    set<string> tokens = gatherTokens(body);
    for (auto s : tokens) {
        size++;
        index[s].insert(url);
    }
    getline(infile, url);
    count++;
    }
    return count - 1;
}

/**
 * intersected()
 * Finds searches when the user enters + or wants the keys to be
 * intersected. The two words must be present in the same url for the url
 * to be matched
 *
 * @param: map<string, set<string>>& index, string word, 
 * string check , set<string>& minuswords, set<string>& result,
 * set<string>& test1, set<string>& temp
 * @return: void, results filled with the intersected urls.
 */
void intersected(map<string, set<string>>& index, string& word,
string& check, set<string>& minuswords, set<string>& result,
set<string>& test1, set<string>& temp) {
    for (auto elem : index) {
        word = cleanToken(check);
                if (!(minuswords.empty())) {
                for (auto minus : minuswords) {
                if (elem.first == word && word != minus) {
                    for (auto url : elem.second) {
                       if (!(result.empty())) {
                        for (auto addedUrl : result) {
                     if (!test1.empty())  {
                       for (auto deleteUrl : test1) {
                        if (url == addedUrl && url != deleteUrl) {
                                temp.insert(addedUrl);
                        }
                       }
                     } else {
                         if (url == addedUrl) {
                         temp.insert(addedUrl);
                         }
                     }
                       }
                       } else {
                           for (auto url : elem.second) {
                                       temp.insert(url);
                           }
                       }
                    }
                }
            }
            } else {
                   if (elem.first == word) {
                    for (auto url : elem.second) {
                        if (!(result.empty())) {
                            for (auto addedUrl : result) {
                                if (!(test1.empty())) {
                                    for (auto deleteUrl : test1) {
                                        if (url == addedUrl &&
                                        url != deleteUrl) {
                                            temp.insert(addedUrl);
                                        }
                                    }
                                } else {
                                    if (url == addedUrl) {
                                        temp.insert(addedUrl);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        result = temp;
}

/**
 * removed()
 * Function removed an url if user enters two keys with - in between. Urls
 * with the first and not the second key are matched.
 *
 * @param: map<string, set<string>>& index, string check,
 * set<string>& minuswords, set<string>& result,
 * set<string>& test1, set<string>& temp
 * @return:void, set<string> results filled with urls
 */
void removed(map<string, set<string>>& index, string& check,
set<string>& minuswords, set<string>& result,
set<string>& test1, set<string>& temp) {
    check = cleanToken(check);
     minuswords.insert(check);
              for (auto elem : index) {
                  if (elem.first == check) {
                      for (auto url : elem.second) {
                          for (auto deleteUrl : result) {
                              if (url == deleteUrl) {
                                test1.insert(url);
                                temp.erase(deleteUrl);
                              }
                          }
                      }
                  }
              }
              result = temp;
}

/**
 * unioned()
 * Function unions two keys if there is nothing between them.
 * Urls with either the first, second or both the keys are added to results
 *
 * @param: map<string, set<string>>& index,
 * string check,set<string>& minuswords,
 * set<string>& result, set<string>& test1,
 * set<string>& temp
* @return: void
 */
void unioned(map<string, set<string>>& index, string& check,
set<string>& minuswords, set<string>& result,
set<string>& test1, set<string>& temp) {
    check = cleanToken(check);
    for (auto elem : index) {
                 if (minuswords.empty()) {
                     if (elem.first == check) {
                     for (auto url : elem.second) {
                         temp.insert(url);
                     }
                     }
                 } else {
                    for (auto minus : minuswords) {
                  if (elem.first == check && check != minus) {
                      for (auto url : elem.second) {
                           temp.insert(url);
                          }
                      }
             }
                 }
                  }
                  result = temp;
}

/**
 * singleKey()
 * Adds the urls that contain the key.
 * Helper function used when there is only one key.
 * @param: map<string, set<string>>& index,
 * string& input, string& check,
 * set<string>& result
 * @return: void
 */
void singleKey(map<string, set<string>>& index,
string& input, string& check, set<string>& result) {
     input = cleanToken(check);
        for (auto elem : index) {
            if (elem.first == input) {
                for (auto url : elem.second) {
                    result.insert(url);
                }
            }
        }
}

/**
 * convertToLower()
 * Converts the given sentence into lower case.
 *
 * @param: string sentence
 * @return: string with the sentence in lower case
 */
string convertToLower(string sentence) {
    string input = "";
    for (unsigned int i = 0; i < sentence.length(); i++) {
       input += tolower(sentence.at(i));
    }
    return input;
}

/**
 * findQueryMatches()
 * Finds the matches to the keys entered by the user.
 * Can use intersection, union and remove while searching.
 *
 * @param: map<string, set<string>>& index, string sentence
 * @return: set<string> result containing urls of query.
 */
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    set<string> result, temp, minuswords, test1;
    string input = convertToLower(sentence);
    stringstream ss(input);
    string word, check;
    int count = 0;
    // counts the number of key in the query
    while (ss >> word) {
        count++;
    }
    stringstream iss(input);
    // if one key calls singleKey function
    if (count == 1) {
       while (iss >> check) {
           singleKey(index, input, check, result);
       }
       // if more than two key
    } else if (count > 1) {
     while (iss >> check) {
         // checks if the key starts with + and
         // calls intersected function if it does.
        if (check.at(0) == '+') {
         temp.clear();
           intersected(index, word, check, minuswords, result, test1, temp);
           // checks if the key starts with - and calls the removed function.
          } else if (check.at(0) == '-') {
             removed(index, check, minuswords, result, test1, temp);
          } else {
              // calls the unioned function if
              // the key doesn't have anything before.
              unioned(index, check, minuswords, result, test1, temp);
              }
     }
    } else {
        // if it's not a valid string/word error statement is printed.
        cout << "Enter a valid search term." << endl;
    }
    return result;
}

/**
 * CREATIVE COMPONENT HELPER FUNCTION
 * stopWords()
 * Function responsible for filling a vector with stop words
 * from a given file.
 *
 * @param: string filename, vector<string>& stopwords
 * @return: int of the number of words
 */
int stopWords(string filename, vector<string>& stopwords) {
    string word;
    int count = 0;
    ifstream infile(filename);
    // checks if the file is good
    if (!(infile.good())) {
        return 0;
    }
    getline(infile, word);
     count++;
    while (!infile.eof() && !infile.fail()) {
        // gets a word until the file is empty and checks if it's not empty.
        if (word != "") {
            // adds to vector if not empty.
            stopwords.push_back(word);
        }
        getline(infile, word);
        count++;
    }
    return count;
}

/**
 * CREATIVE COMPONENT HELPER FUNCTION
 * checkStopWords()
 * Checks if the index has any stop words and removes them.
 * 
 * @param: vector<string> stopwords, map<string,
 * set<string>>& index2, map<string, set<string>> index
 * @return: void
 */
void checkStopWords(vector<string> stopwords, map<string,
set<string>>& index2, map<string, set<string>> index) {
    map<string, set<string> > input = index;
        for (int i = 0; i < stopwords.size(); i++) {
            // erases the stop words from temporary copy of index
                input.erase(stopwords.at(i));
        }
        // assigning the temp to new index2
        index2 = input;
}

/**
 * CREATIVE COMPONENT MAIN FUNCTION
 * stopwordsMode()
 * Function is called when user enters rm stop words.
 * This allows the user to access a shortened index without stop words.
 * The funtion runs as long as the user enters enter.
 *
 * @param: string filename, vector<string>& stopwords, map<string,
 * set<string>>& index, map<string, set<string>>& index2,
 * int i, set<string>& urls
 * @return: void
 */
void stopwordsMode(string filename, vector<string>& stopwords, map<string,
set<string>>& index, map<string, set<string>>& index2,
int i, set<string>& urls) {
     string query;
           stopWords(filename, stopwords);
           checkStopWords(stopwords, index2, index);
           cout << "Removing stop words..." << endl;
           cout << "Indexed " << i <<
           " pages containing " << index2.size() <<
           " unique terms, excluding " << index.size() - index2.size() <<
           " stop words." << endl;
           cout << "\nEnter query sentence "<<
           "(press enter to go back to normal mode): ";
           getline(cin, query);
           while (query != "") {
           urls = findQueryMatches(index2, query);
           cout << "Found " << urls.size() << " matching pages" << endl;
           for (auto e : urls) {
               cout << e << endl;
           }
           cout << "\nEnter query sentence " <<
           "(press enter to go back to normal mode): ";
           getline(cin, query);
           }
           cout << "Mode ended. Stop words will be" <<
           " added to the index again." << endl;
}

/**
 * searchEngine()
 * Function responsible for the search engine that the user interacts with.
 * User needs to press enter to quit and the search engine runs based on a
 * pre-set file. Calls the various helper functions to build the index, find queries
 * and remove stop words.
 *
 * @param: string filename
 * @return: void
 */
void searchEngine(string filename) {
    map<string, set<string>> index;
    map<string, set<string>> index2;
    vector<string> stopwords;
    set <string> urls;
    cout << "Stand by while building index..." << endl;
    int i = buildIndex(filename, index);
    cout << "Indexed " << i << " pages containing "
    << index.size() << " unique terms" << endl;
    string sent;
    cout << "\nEnter query sentence (press enter to quit): ";
    getline(cin, sent);
    while (sent != "") {
        if (sent == "rm stop words") {
            stopwordsMode("stopwords.txt", stopwords, index, index2, i, urls);
        } else {
        urls = findQueryMatches(index, sent);
        cout << "Found " << urls.size() << " matching pages" << endl;
        for (auto s : urls) {
            cout << s << endl;
        }
        }
     cout << "\nEnter query sentence (press enter to quit): ";
     getline(cin, sent);
    }
    cout << "Thank you for searching!" << endl;
}
