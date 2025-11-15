#include "builtins.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int start(vector<char *> args) {
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args.data()) == -1) {
      perror("Error from my shell.");
    }
    exit(EXIT_FAILURE);
  } else if (pid == -1) {
    perror("Error from my shell.");
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

vector<char *> split(string line) {
  stringstream ss(line);
  vector<string> tokens(line.size());

  for (auto &i : tokens) {
    ss >> i;
  }

  // After tokenize, return vector of pointers to tokens
  vector<char *> args(tokens.size() + 1);

  // The function, execvp() provides an array of pointers to null-terminated
  // strings, so add 1 for null
  for (size_t i = 0; i < tokens.size(); i++) {
    args[i] = &tokens[i][0];
  }

  return args;
}

int exec(vector<char *> args) {
  if (args[0] == NULL) {
    return 1;
  }

  for (int i = 0; i < builtin_str.size(); i++) {
    const char *str = builtin_str[i].c_str();
    if (strcmp(args[0], str) == 0) {
      return 1;
    }
  }

  return start(args);
}

void shell() {
  string line;
  vector<char *> args;
  int status;

  do {
    printf(">");

    cin >> line;
    args = split(line);
    status = exec(args);
  } while (status);
}

int main(int argc, char *argv[]) {
  // Load config

  // main loop to read stdin
  shell();

  // shutdown/cleanup
  return EXIT_SUCCESS;
}
