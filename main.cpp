#include <iterator>
#include <algorithm>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <set>
using namespace std;

void parse(string &str1, string &str2) {
  string s;
  getline(cin, s);
  stringstream strstr(s);
  istream_iterator<string> it(strstr);
  istream_iterator<string> end;
  vector<string> results(it, end);
  str1 = results[0];
  str2 = results[1];
}

int LCS(const string &str1, const string &str2, vector< vector<int> > &c) {
  for (int i = 0; i <= str1.length(); i++) c[i][0] = 0;
  for (int j = 0; j <= str2.length(); j++) c[0][j] = 0;
  int i, j;
  for (i = 1; i <= str1.length(); i++) {
    for (j = 1; j <= str2.length(); j++) {
      if (str1.at(i-1) == str2.at(j-1)) c[i][j] = c[i-1][j-1] + 1;
      else if (c[i-1][j] > c[i][j-1]) c[i][j] = c[i-1][j];
      else c[i][j] = c[i][j-1];
      //            cout << c[i][j] << " ";
    }
    //       cout << endl;
  }
  return c[i-1][j-1];
}

void printLCS(const string &str1, const string &str2, const vector< vector<int> > &c) {
  ostringstream os;
  string ans;
  int i = str1.length();
  int j = str2.length();
  while (i != 0 && j != 0) {
    if (c[i][j] == c[i-1][j-1] + 1) {
      os << str1.at(i-1);
      i--;
      j--;
    }
    else if (c[i][j] == c[i-1][j]) i--;
    else j--;
  }
  ans = os.str();
  reverse(ans.begin(), ans.end());
  cout << ans << endl;
}

void printVectorsInReverse(vector< vector<int> > v) {
  set< vector<int> > s;
  for (int i = 0; i < v.size(); i++) {
    s.insert(v[i]);
  }

  for (set< vector<int> >::iterator it = s.begin(); it != s.end(); ++it) {
    cout << "(";
    for (int j = (*it).size() -1; j >= 0; j -= 2) {
      cout << "<" << (*it)[j] << ", " << (*it)[j-1] << ">";
      if (j != 1) cout << ", ";
    }
    cout << ")" << endl;
  }
}

void printAllLCS(const string &str1, const string &str2, const vector< vector<int> > &c, int i, int j, vector< vector<int> > &ans, int spliton, int addto) {
  if (i != 0 && j != 0) {
    if (str1.at(i-1) == str2.at(j-1)) {
      if (addto == -2) {
	vector<int> v2;
	v2.push_back(j);
	v2.push_back(i);
	//		bool flag = false;
	//	for (int z = 0; z < ans.size(); z++) {
	// if (v2 == ans[z]) flag = true;
	//	}
	//	if (!flag)
	ans.push_back(v2);
	int currvec = ans.size() - 1;
	printAllLCS(str1, str2, c, i-1, j-1, ans, currvec, currvec);
	if (c[i][j] == c[i-1][j]) printAllLCS(str1, str2, c, i-1, j, ans, currvec, -2);
	if (c[i][j] == c[i][j-1]) printAllLCS(str1, str2, c, i, j-1, ans, currvec, -2);
      }
      else if (addto == -1) {
	vector<int> v2(ans[spliton]);
	int temp = 0;
	int temp2 = 0;
	if (v2.size() >= 2) {
	  //	  temp = v2[v2.size() - 1];
	  // temp2 = v2[v2.size() - 2];
	  v2.pop_back();
	  v2.pop_back();
	}
	  if (v2.size () < 2) {
	    v2.push_back(j);
	    v2.push_back(i);
	  }
	  else if (v2[v2.size() -1] > i && v2[v2.size() - 2] > j) { 
	  v2.push_back(j);
	  v2.push_back(i);
	  }
	  //  bool flag = false;
	  //for (int z = 0; z < ans.size(); z++) {
	  // if (v2 == ans[z]) flag = true;
	  // }
	  //if (!flag)
	  // if (temp != i && temp2 != j) {
	  ans.push_back(v2);
	  // }
	  int currvec = ans.size() - 1;
	  printAllLCS(str1, str2, c, i-1, j-1, ans, currvec, currvec);
	  if (c[i][j] == c[i-1][j]) printAllLCS(str1, str2, c, i-1, j, ans, spliton, -1);
	  if (c[i][j] == c[i][j-1]) printAllLCS(str1, str2, c, i, j-1, ans, spliton, -1);
      }
      else {
	if (ans[addto].size() < 2) {
	    ans[addto].push_back(j);
	   ans[addto].push_back(i);
	  	}
		else if (ans[addto][ans[addto].size()-1] > i && ans[addto][ans[addto].size()-2] > j) {
	ans[addto].push_back(j);
	ans[addto].push_back(i);
		}
	printAllLCS(str1, str2, c, i- 1, j-1, ans, spliton, addto);
	if (c[i][j] == c[i-1][j]) printAllLCS(str1, str2, c, i-1, j, ans, spliton, -1);
	if (c[i][j] == c[i][j-1]) printAllLCS(str1, str2, c, i, j-1, ans, spliton, -1);
      }
    }
    else {
      if (c[i][j] == c[i-1][j]) printAllLCS(str1, str2, c, i-1, j, ans, spliton, addto);
      if (c[i][j] == c[i][j-1]) printAllLCS(str1, str2, c, i, j-1, ans, spliton, addto);
    }
  }
}

int main(int args, char *argv[]) {
  int numpairs;
  string s;
  getline(cin, s);
  numpairs = stoi(s);
  for (int i = 0; i < numpairs; i++) {
    string str1, str2;
    parse(str1, str2);
    vector< vector<int> > c;
    for (int z = 0; z <= str1.length(); z++) {
      vector<int> v(str2.length() + 1, 0);
      c.push_back(v);
    }
    LCS(str1, str2, c);
    if (args == 2) {
      char all[] = "-all"; 
      if (strcmp(argv[1], all) == 0) {
	vector< vector<int> > ans;
	printAllLCS(str1, str2, c, str1.length(), str2.length(), ans, 0, -2);
	printVectorsInReverse(ans);
	if (i != numpairs - 1) cout << endl;
      }
    }
    else {
      cout << c[str1.length()][str2.length()] << " ";
      printLCS(str1, str2, c);
    }
  }
}
