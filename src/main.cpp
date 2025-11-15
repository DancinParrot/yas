#include "builtins.h"
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int start(vector<string> &tokens) {
  pid_t pid, wpid;
  int status;

  // The function, execvp() provides an array of pointers to null-terminated
  // strings, so add 1 for null
  vector<char *> args(tokens.size() + 1);

  // After tokenize, return vector of pointers to tokens
  for (size_t i = 0; i < tokens.size(); i++) {
    args[i] = &tokens[i][0];
  }

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

vector<string> token(string line) {
  stringstream ss(line);
  vector<string> tokens(line.size());

  for (auto &i : tokens) {
    ss >> i;
  }

  return tokens;
}

int exec(vector<string> tokens) {
  if (tokens[0] == "") {
    return 1;
  }

  for (int i = 0; i < builtin_str.size(); i++) {
    if (tokens[0] == builtin_str[i]) {
      return (*builtin_func[i])(tokens);
    }
  }

  return start(tokens);
}

void shell() {
  string line;
  vector<string> args;
  int status;

  do {
    cout << "> ";

    getline(cin, line);
    args = token(line);
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
