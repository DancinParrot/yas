#include "builtins.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#include <unistd.h>

using namespace std;

vector<string> builtin_str = {"cd", "help", "exit"};

int (*builtin_func[])(vector<char *>) = {&cd, &help, &exit};

int cd(vector<char *> args) {

  if (args[1] == NULL) {
    cerr << "shell: expected argument to \"cd\"\n";
  } else {
    if (chdir(args[1]) != 0) {
      perror("my shell");
    }
  }
  return 1;
}

int help(vector<char *> args) {
  cout << "My Shell\n";
  cout << "Available commands are below:\n";

  for (auto i : builtin_str) {
    cout << i << '\n';
  }

  return 1;
}

int exit(vector<char *> args) { return 0; }
