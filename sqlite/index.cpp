#include <QApplication>

#include "sqlitehandler.h"
#include <QSqlQuery>
#include <QString>

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#include <iostream> 
#include <fstream>
#include <iomanip>

#include <vector>
#include <string>
#include <set>
#include <map>
#include <algorithm> 

using namespace std;

#define NUM_TOP_WORDS 250
vector<string> topwords;
set<string> wordsSet;

map<string, set<int> > wordIndex;


string strlwr(string word)
{
     unsigned int i;
     int len = strlen(word.c_str()) + 1;
     char ret[len];
     
     
     for(i = 0; i < len - 1; i++)
	  ret[i] = tolower(word[i]);

     ret[i] = '\0';
     
     return ret;
     
}

void insertWordIndex(string word, int fname)
{
     map<string, set<int> >::iterator it;
     it = wordIndex.find(word);
     
     if(it == wordIndex.end()){      // word not present
	  set<int> filenames;
	  filenames.insert(fname);
	  wordIndex.insert(pair<string, set<int> >(word, filenames));
     }
     else{
	  (it->second).insert(fname);
     }
}


bool isTopWord(string word)
{
     vector<string>::iterator it;
     it = find(topwords.begin(), topwords.end(), word);
     if(it == topwords.end())
	  return false;
     else
	  return true;
}


void getTopWords(char* fname)
{
     string word;
     string lwrword;
     
     topwords.reserve(NUM_TOP_WORDS);
     
     ifstream fin(fname);
     while(!fin.eof()){
	  fin >> word;
	  lwrword = strlwr(word);

	  topwords.push_back(lwrword);
     }
     fin.close();
}


void getWords(const char* dirname, const char* fname)
{
     string word, lwrword;     
     
     string filename = dirname;
     filename += fname;
     
     ifstream fin(filename.c_str());
     if(fin){
	  while(!fin.eof()){
	       fin >> word;
	       lwrword = strlwr(word);
	       
	       if(!isTopWord(lwrword)){
		    insertWordIndex(lwrword, atoi(fname));
		    wordsSet.insert(lwrword);
	       }
	  }
     }
     fin.close();
}

/*
int main(int argc, char* argv[])
{

     QApplication app(argc, argv);
	  
     if(argc != 3){
	  cout << "Usage: ./exe <directory-name> <top-words>\n";
	  exit(1);
     }

     getTopWords(argv[2]);     
     
     struct dirent *dir;
     DIR *d = opendir(argv[1]);
     
     vector<set<string> > chatIndex;
     set<int>::iterator it;
     map<string, set<int> >::iterator wordIndexIt;
     
     string dirname = argv[1];
     
     ifstream fin;
     ofstream fout1(argv[4]);     
//fout(argv[3]), 
     
     if(d){
	  while( (dir = readdir(d)) != NULL){
	       if(strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){
//		    fout << dirname + dir->d_name << ":" << endl;
		    
		    getWords( argv[1], dir->d_name );
		    
//		    chatIndex.push_back(wordsSet);
		    
// 		    for(it = wordsSet.begin(); it != wordsSet.end(); it++)
// 			 fout << *it << '\n';
// 		    fout << "\n\n";
		    		    
		    wordsSet.erase(wordsSet.begin(), wordsSet.end());
	       }
	  }    
	  closedir(d);
     }
     
     SqliteHandler sh;
     sh.openDB();
     
     if(!sh.createConnection()){
	  return 1;
     }
     
     sh.createTable();

     cout << "hello" << endl;
     
     for(wordIndexIt = wordIndex.begin(); wordIndexIt != wordIndex.end(); wordIndexIt++){

	  for(it = (wordIndexIt->second).begin(); it != (wordIndexIt->second).end(); it++){
	       string query;
	       char str[10];
	       sprintf(str, "%d", *it);
	       
	       query = "insert into WORDINDEX (word, chatNum) values(\"" + wordIndexIt->first 
		    + "\", " + str + ")";
	       
	       sh.insertWord(query.c_str());
	  }
	  
	  // fout1 << wordIndexIt->first << ":\n";
// 	  for(it = (wordIndexIt->second).begin(); it != (wordIndexIt->second).end(); it++)
// 	       fout1 << *it << '\n';

// 	       fout1 << "\n\n"; 
     }
     
     return 0;
}

*/
