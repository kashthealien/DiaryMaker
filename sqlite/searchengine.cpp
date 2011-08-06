/* Utility : search engine
   Given a set of words, get the files in which these words appear 
   Uses wordindex file created using index.cpp
*/

#include "sqlitehandler.h"
#include <QList>
#include <QString>
#include <QSet>
#include <QApplication>
#include <QMessageBox>

#include <fstream>
#include <iostream>
#include <iomanip>

#include <vector> 
#include <string>
#include <set>
#include <map> 
#include <algorithm> 

using namespace std;

int main(int argc, char* argv[]){

     QApplication app(argc, argv);
     
     
     if(argc != 3){
	  cout << "Usage: ./exe <word-1> <word-2>\n";
	  exit(1);
     }

     SqliteHandler sh;
     sh.openDB();
     
     sh.createConnection();
     
     string query;
     QSet<int> files[argc-1];
     QSet<int>::iterator it, it1;

     int i = 1;
     while(i < argc){
	  
	  query = "select chatNum from WORDINDEX where word = \"";
	  query += argv[i];
	  query += "\"";
     
	  sh.getFiles(query.c_str(), files[i-1]);
	  i++;
     }

     cout << "hello" << endl;
     
     QSet<int> searchResult;
     QSet<int>::iterator rit, rit1;
     QVector<int> v;

//     rit = set_intersection(files[0].begin(), files[0].end(), files[1].begin(), files[1].end(), v.begin());
     
     
     for(it = files[0].begin(); it != files[0].end(); it++)
	  for(it1 = files[1].begin(); it1 != files[1].end(); it1++){
	       if(*it == *it1)
		    searchResult.insert(*it);
	  }


//      it = files[0].begin();
//      it1 = files[1].begin();
     
//      while(it != files[0].end() && it1 != files[1].end()){
// 	  cout << *it << '\t' << *it1 << '\n';
	  
// 	  if(*it < *it1)
// 	       ++it;
// 	  else if(*it1 < *it)
// 	       ++it1;
// 	  else{
// 	       searchResult.insert(*it);
// 	       it++;
// 	       it1++;
// 	  }
//      }
     
     
     for(rit = searchResult.begin(); rit != searchResult.end(); rit++){
	  cout << *rit << '\n';
     }

//      for(rit1 = v.begin(); rit1 != rit; rit1++)
// 	  cout << *rit1 << '\n';
     

     return 0;
}

