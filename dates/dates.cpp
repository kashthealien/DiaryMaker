/***************************************************************************************************
 * 
 * Author    : Kashyap R Puranik <kashthealien at gmail dot com>
 * Date      : 30/12/2010 
 * 
 * Purpose	 : Identifies dates/days in input
 * Compile   :
 * Usage     :
 * Example   :
 *
 **************************************************************************************************/
 
#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
list<list<string> > Week;
list<list<string> > Months;
list<list<string> > Days;
void init(){
	string mon[] = {"monday",  "mon", "mond", "monda"};
	string tue[] = {"tuesday", "tue", "tues", "tuesd"};
	string wed[] = {"wednesday", "wed", "wedn", "wedns"};
	string thu[] = {"thursday", "thu", "thur", "thurs"};
	string fri[] = {"friday", "fri", "frid", "frida"};
	string sat[] = {"saturday", "sat", "satd", "satur"};
	string sun[] = {"sunday","sun", "sund", "sunda"};

	list<string> Mon(mon, mon+4); Week.push_back(Mon);
	list<string> Tue(tue, tue+4); Week.push_back(Tue);
	list<string> Wed(wed, wed+4); Week.push_back(Wed);
	list<string> Thu(thu, thu+4); Week.push_back(Thu);
	list<string> Fri(fri, fri+4); Week.push_back(Fri);
	list<string> Sat(sat, sat+4); Week.push_back(Sat);
	list<string> Sun(sun, sun+4); Week.push_back(Sun);
	
	string jan[] = {"january", "jan", "janu", "janry"};
	string feb[] = {"february", "feb", "febr", "febry"};
	string mar[] = {"march", "marc", "mar"};
	string apr[] = {"april", "apr", "aprl"};
	string may[] = {"may"};
	string jun[] = {"june", "jun"};
	string jul[] = {"july", "jul"};
	string aug[] = {"august","aug", "augst"};
	string sep[] = {"september", "sept", "sep", "septbr"};
	string oct[] = {"october", "oct", "octobr", "octr"};
	string nov[] = {"nov", "novm", "novmbr"};
	string dec[] = {"dec", "decbr", "decb"};

	list<string> Jan(jan, jan+4); Months.push_back(Jan);
	list<string> Feb(feb, feb+4); Months.push_back(Feb);
	list<string> Mar(mar, mar+3); Months.push_back(Mar);
	list<string> Apr(apr, apr+3); Months.push_back(Apr);
	list<string> May(may, may+1); Months.push_back(May);
	list<string> Jun(jun, jun+2); Months.push_back(Jun);
	list<string> Jul(jul, jul+2); Months.push_back(Jul);
	list<string> Aug(aug, aug+3); Months.push_back(Aug);
	list<string> Sep(sep, sep+4); Months.push_back(Sep);
	list<string> Oct(oct, oct+4); Months.push_back(Oct);
	list<string> Nov(nov, nov+3); Months.push_back(Nov);
	list<string> Dec(dec, dec+3); Months.push_back(Dec);
	
	string day[] = {"day", "da"};
	string before[] = {"before", "befor", "bef", "b4", "befo"};
	string after[] = {"after", "aft", "aftr", "afte"};
	string yester[] = {"yesterday", "yestday", "yest", "yestd", "yesday", "yester"};
	string tomo[] = {"tomorrow", "tomor", "tomo", "tomm", "tomorr"};
	string today[] = {"today", "toda", "tod"};
	
	list<string> Day(day, day+2);
	list<string> Before(before, before+5);
	list<string> After(after, after+4);
	list<string> Yester(yester, yester+6);
	list<string> Tomo(tomo, tomo+5);
	list<string Today(today, today+3);
	
	
}
int matchMonth(string input)
{
	return -1;
}

int matchDate(string input)
{
	
	return -1;
}

int matchYear(string input)
{
	return -1;
}

int containsDate(string input)
{
	// Pattern 1
	int month = matchMonth(input);
	int date = matchDate(input);
	int year = matchYear(input);
	// aug 4th
	if (matchMonth(input) > 0 && matchDate(input) > 0)
		;
	
	// Pattern 2
	// Pattern 2
	return 0;
}

list<string> getInput( string fileName)
{
	ifstream myfile ("example.txt");
	list <string> lines;

	if ( myfile.is_open() )
	{
		while ( myfile.good() )
	    {
			string line;
			getline (myfile, line);
	        lines.push_back(line);
	    }
    	myfile.close();
    }
	
	return lines;
}

int main(int argc, char** argv)
{
	int mode = 0;
	string fileName;
	list<string> lines;
	list<string> output;
	string line;

	// Argument handling
	if (argc > 1) {
		mode = atoi(argv[1]);							// Get the mode
		if (mode < 0 || mode > 1)
			mode = 0;
	} if (argc > 2) {									// if fileName is specified
		if (mode == 0) {
			fileName = string(argv[2]);					// Get the filename
			lines = getInput(fileName);					// Read all lines from the file
		}
	}
	
	// Processing
	init();
	if ( mode == 0) {
		for ( list<string>::iterator iter = lines.begin() ; iter != lines.end() ; iter ++ ) {
			if (containsDate(*iter)) {
				output.push_back(*iter);
			}
		}
	} else {
		while (cin >> line) {
			if (containsDate(line)) {
				output.push_back(line);
			}
		}
	}	
}
