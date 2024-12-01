#include <iostream>
#include <fstream>
#include <istream>
#include <stack>
#include<string>

using namespace std;


void printFile(istream &dictfile) {

        int lineCount = 1;
	    string line;
	    while (getline(dictfile, line)) {
	        cout << lineCount << " " << line << endl;  //prints line number + line
		    lineCount++; //number of lines in file
	    }
	    dictfile.clear();
        dictfile.seekg(0, dictfile.beg);
}


bool balanceFile(istream &dictfile) {
//Takes a file dictfile and prints the matching code elements. Returns true if the file is balanced, false otherwise.
   stack<char> S; 
   stack<int> L; //store line numbers
   
   char c, d;
   bool match = true;
   string line;
   int lineCount = 1;
   
   //bool commentFlag = false;
   bool sQuoteFlag = false;
   bool blockFlag = false;
   bool dQuoteFlag = false;
   

   while (getline(dictfile, line)) {
        for (int i = 0; i < line.size(); i++) {   // read in next char
            c = line[i];
            d = line[i+1];
            
            if (blockFlag == true) {
                if (c == '*' && d == '/') {
                    blockFlag = false;
                    cout << "pair matching /* and */" << endl;
                } 
                continue;
            }
            else if (sQuoteFlag == true || dQuoteFlag == true) {
                if (sQuoteFlag == true) {
                    if (c == '\'') {
                        sQuoteFlag = false;
                        cout << "pair matching \' and \'" << endl;
                    }
                    else if (i == line.size() - 1) {
                        cout <<  "Unmatched \' symbol at line " << (lineCount - 1) << endl;
                        return false;
                    }
                    continue;
                }
                else if (dQuoteFlag == true) {
                    if (c == '\"') {
                        dQuoteFlag = false;
                        cout << "pair matching \" and \"" << endl;
                    }
                    else if (i == line.size() - 1) {
                        cout <<  "Unmatched \" symbol at line " << (lineCount - 1) << endl;
                        return false;
                    }
                    continue;
                }
            }
            
            if (c == '/' && d == '*') {
                blockFlag = true;
                i++;
                continue;
            }
            if (c == '\'') {
                sQuoteFlag = true;
                continue;
            }
            if (c == '\"') {
                dQuoteFlag = true;
                continue;
            }
            if (c == '/' && d == '/') {
                break;
            }
            
            if (c == '(' || c == '{' || c == '[' ) {
                S.push(c);
                L.push(lineCount);
                continue;
            }
            
            if (!S.empty()) {
                char t = S.top();
                
                if ((t == '(' && c == '}') || (t == '(' && c == ']')) {
                    cout <<  "Unmatched " << t << " symbol at line " << L.top() << endl;
                        return false;
                }
                if ((t == '{' && c == ')') || (t == '{' && c == ']')) {
                    cout <<  "Unmatched " << t << " symbol at line " << L.top() << endl;
                        return false;
                }
                if ((t == '[' && c == ')') || (t == '[' && c == '}')) {
                    cout <<  "Unmatched " << t << " symbol at line " << L.top() << endl;
                        return false;
                }
                
                if (c == ')' || c == '}' || c == ']') {
                    S.pop();
                    L.pop();
                    cout << "pair matching " << t << " and " << c << endl;
                    continue;
                }
            } 
            else if (S.empty()) {
                if (c == ')' || c == '}' || c == ']') {
                    cout <<  "Unmatched " << S.top() << " symbol at line " << L.top() << endl;
                    return false;
                }
            }
        }
        lineCount++;
    }
    if (blockFlag == true) {
        cout <<  "Unmatched /* symbol at line " << (lineCount - 1) << endl;
        return false;
    }
    
    if (!S.empty()) {
        cout <<  "Unmatched " << S.top() << " symbol at line " << L.top() << endl;
        return false;
    }
    else if (S.empty()) {
        return true;
    }
}

int main()
{
    ifstream infile;
    string filename;
    
    cout << "Please enter filename for C++ code: ";
    cin >> filename;
    infile.open(filename.c_str());

    if (!infile) {
        cout << "File not found!" << endl;
        return (1);
    }
    
    printFile(infile);
    
    if (balanceFile(infile))
        cout << "balance ok" << endl;
}





