#include "builtins.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>

using namespace std;

vector<string> builtin_str = {"cd", "help", "exit"};

int (*builtin_func[3])(vector<string>) = {&cd, &help, &exit};

void pointers(vector<string> tokens, vector<char *> &args) {
  // After tokenize, return vector of pointers to tokens
  for (size_t i = 0; i < tokens.size(); i++) {
    args[i] = &tokens[i][0];
  }
}

int cd(vector<string> tokens) {

  vector<char *> args(tokens.size() + 1);

  pointers(tokens, args);

  if (args[1] == NULL) {
    cerr << "shell: expected argument to \"cd\"\n";
  } else {
    if (chdir(args[1]) != 0) {
      perror("my shell");
    }
  }
  return 1;
}

int help(vector<string> tokens) {

  cout << "My Shell\n";
  cout << "Available commands are below:\n";

  for (auto i : builtin_str) {
    cout << i << '\n';
  }

  return 1;
}

int exit(vector<string> tokens) { return 0; }
