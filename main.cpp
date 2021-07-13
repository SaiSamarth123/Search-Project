/**
 * @file: main.cpp
 *
 * @description: Program used to test the search.h file. Used to check if the
 * functions that run the search engine work properly.
 *
 * Code Written by
 * @author: Sai Samarth Patipati Umesh
 * U. of Illinois, Chicago
 * @date: 2/7/21
 *
 */

#include <iostream>
#include <set>
#include <map>
#include "search.h"
using namespace std;

int main() {
    
    // Use this function to call and test the functions you write inside of
    // search.h.  If you do not call the functions here, nothing will run.
   string ans = "hello";

    // cout << "1. " << ans << endl;

   // cout << "2. " << cleanToken("@(uic)") << endl;
  // cout << "3. " << cleanToken("doesn't-call") << endl;
  //  cout << "4. " << cleanToken("133444a") << endl;
  //  cout << "5. " << cleanToken("it ai") << endl;
  //  cout << "hi" << endl;
    
   // set<string> tokens = gatherTokens("it's ai");

    set<string> tokensANS;

  //  tokensANS.insert("its");

   // tokensANS.insert("ai");

    //tokensANS.insert("or");

   // tokensANS.insert("not");
    
    
//for (auto elem : tokens) {
 //   cout << elem << endl;
//}
   // cout << "1. " << (tokens.size() == 2) << endl;

  //  cout << "2. " << (tokens == tokensANS) << endl;
     
    map<string, set<string> > index;
    map<string, set<int> > index2;
   //int l = buildIndex("uiccs-news.txt", index);
   //cout << l << endl;
   //cout << index.size() << endl;
   // cout << index.size() << endl;
   // cout << "wassup" << endl;
  //  cout << l << endl;
 //   if (l > 0) {
     //   for (auto elem: index) {
           // cout << elem.first << ". ";
       //    for (auto url: elem.second) {
          //  cout << url << ", " << endl;
     //    }
    //   }
  //  }
   // cout << cleanToken("!blue!");
    //set<string> result = findQueryMatches(index, "urban +chicago +campus");
   //searchEngine("tiny.txt");
   searchEngine("cplusplus.txt");
  //  for (auto s: result) {
    ///     cout << s << endl;
    // }
     
 return 0;   
}

