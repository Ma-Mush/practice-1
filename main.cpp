#include <iostream>
#include <fstream>
#include <cstring>


bool charInWord(char* word, char charToFind) {
  charToFind = tolower(charToFind);
  for (int i = 0; i < strlen(word); i++) {
    if (tolower(word[i]) == charToFind) 
      return true;
  }
  return false;
}

void parseArgs(int argc, char ** argv, char ** word, char ** filename) {
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i - 1], "--word") == 0) {
      *word = argv[i];
    } else if (strcmp(argv[i - 1], "--file") == 0) {
      *filename = argv[i];
    }
  }
}

void countWords(char * word, char * nowWord, int * counter) {
  for (int i = 0; i < strlen(word); i++) {
    if (!charInWord(nowWord, word[i])){
      (*counter)--;
      break;
    }
  }
  (*counter)++;
}

void readFileAndCount(std::ifstream * filein, char * word, int * count) {
  const int buffSize = 1024;
  char buffer[buffSize];
  char nowWord[32]; 
  int nowIndex = 0;
  while (!(*filein).eof()) {
    (*filein).read(buffer, buffSize);
    int bytesRead = (*filein).gcount();
    for (int i = 0; i < bytesRead; i++) {
      char c = buffer[i];
      if (std::isalpha(c)) {
        nowWord[nowIndex++] = c;
      } else {
        nowWord[nowIndex] = '\0';
        if (nowIndex != 0)
          countWords(word, nowWord, count);
        nowIndex = 0;
      }
    }
  }
  nowWord[nowIndex] = '\0';
  countWords(word, nowWord, count);
}

int main(int argc, char** argv) {
  char* word = nullptr;
  char* filename = nullptr;
  parseArgs(argc, argv, &word, &filename);

  if (word == nullptr || filename == nullptr) {
    std::cout << "Arguments Error: ./neatcounter --word <word> --file <file>";
    return 1;
  }
  
  std::ifstream filein{filename};
  if (!filein.is_open()) {
    std::cout << "File Error: Cannot open file";
    return 2;
  }
  int count = 0;
  readFileAndCount(&filein, word, &count);
  std::cout << count;
  return 0;
}
