#include <bits/stdc++.h>

using namespace std;

int cd(vector<string> tokens);
int help(vector<string> tokens);
int exit(vector<string> tokens);
void pointers(vector<string> tokens, char **args);
extern vector<string> builtin_str;
extern int (*builtin_func[])(vector<string>);
