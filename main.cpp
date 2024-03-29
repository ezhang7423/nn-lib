#include "gamestate.cpp"
#include "logic/baseline.cpp"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>
typedef std::pair<int, int> tupl;

using namespace std;
bool prod = true;
game parseArgs(char *arg1, char *ovalue, char *arg2 = (char *)"-d") {
  int size = 11;
  bool first;
  if (!strncmp(arg1, "-n", 2)) {
    size = atoi(ovalue);
  };
  first = (bool)(!strncmp(arg2, "-l", 2));
  return game(size, first);
};

game startup(int argc, char **argv) {
  if (std::getenv("PROD")) {
    prod = strncmp(std::getenv("PROD"), "FALSE", 5);
  }

  if (argc != 1) {
    if (argc == 2 && !strncmp(argv[1], "-l", 2)) {
      return game(11, true);
    } else if (argc == 3) {
      return parseArgs(argv[1], argv[2]);
    } else if (argc == 4) {
      return parseArgs(argv[1], argv[2], argv[3]);
    } else {
      cout << "USAGE: ./gobang -n <size> -l <bool> (first vs second)" << endl;
      exit(1);
    }
  } else {
    return game(11, false);
  }
}

string toLetters(tupl move) {
  char c[3] = {(char)(move.second + 97), (char)move.first, '\0'};
  return string(c);
};

tupl getMove(game &g) {
  string s;
  print("What's your move?");
  cin >> s;
  try {
    int column = s[0] - 97;
    int row = stoi(s.substr(1, s.size() - 1)) - 1;
    assert(g.state3(row, column) == 0);
    return make_pair(row, column);
  } catch (...) {
    print("Invalid move");
    return getMove(g);
  }
}
int main(int argc, char **argv) {
  game g = startup(argc, argv);
  Madam c(10);
  g.prod = prod;
  g.printBoard();
  if (g.current == 1) { // com going first
    tupl move = c.think(g);
    g.update(move);
  }
  while (true) {
    tupl move = getMove(g);
    g.update(move);
    if (g.won() != "") {
      break;
    }
    move = c.think(g);
    g.update(move);
    if (g.won() != "") {
      break;
    }
    print("Move played: " + toLetters(move));
    g.printBoard();
  }
  g.printBoard();
  cout << "Game has ended. " << g.won() << " has won." << endl;
}