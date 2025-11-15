#include "builtins.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>

using namespace std;

vector<string> builtin_str = {"cd", "help", "exit"};

int (*builtin_func[3])(vector<string>) = {&cd, &help, &exit};

// TODO
void pointers(vector<string> tokens, char **args);

int cd(vector<string> args) {
  if (args[1] == NULL) {
    cerr << "shell: expected argument to \"cd\"\n";
  } else {
    if (chdir(args[1]) != 0) {
      perror("my shell");
    }
  }
  return 1;
}

int help(vector<string> args) {
  cout << "My Shell\n";
  cout << "Available commands are below:\n";

  for (auto i : builtin_str) {
    cout << i << '\n';
  }

  return 1;
}

int exit(vector<string> args) { return 0; }
