#include "Analysis.hpp"
#include "BSTree.hpp"
void menuLoop(const std::vector<std::string> &choices, int &highlight) {
  int choice = 0;
  while (choice != 10) {
    for (int i = 0; i < choices.size(); i++) {
      if (i == highlight) {
        attron(A_REVERSE);
      }
      mvprintw(i, 0, "%s", choices[i].c_str());
      attroff(A_REVERSE);
    }
    choice = getch();

    switch (choice) {
      case KEY_UP: {
        if (highlight != 0) highlight--;
        break;
      }
      case KEY_DOWN: {
        if (highlight != choices.size() - 1) highlight++;
        break;
      }
      default:
        break;
    }
  }
}

int getInput(const std::string &message) {
  clear();
  int input = 0;
  while (true) {
    printw("%s", message.c_str());
    scanw("%d", &input);
    if (input < 1) {
      printw("Niepoprawny wybor. Sprobuj ponownie.\n");
      continue;
    }
    return input;
  }
}

int main() {
  initscr();
  keypad(stdscr, true);
  curs_set(0);
  std::unique_ptr<HashMap> collection;
  std::vector<std::string> CHOICES{
      "1. BST", "2. AVLTree", "3. DoublyLinkedList", "4. Analiza", "5. Wyjdz"};
  int highlight = 0;
  menuLoop(CHOICES, highlight);
  switch (highlight) {
    case 0: {
      collection = std::make_unique<HashMap>(BucketType::BST);
      break;
    }
    case 1: {
      collection = std::make_unique<HashMap>(BucketType::AVL);
      break;
    }
    case 2: {
      collection = std::make_unique<HashMap>(BucketType::DLL);
      break;
    }
    case 3: {
      Analysis::analysis();
      endwin();
      return 0;
    }
    default: {
      endwin();
      return 0;
    }
  }
  CHOICES = {"1. Dane z pliku numbers.txt",
             "2. Losowe dane",
             "3. Wypisz",
             "4. Wstaw",
             "5. Usun",
             "6. Wyjdz"};
  do {
    highlight = 0;
    clear();
    menuLoop(CHOICES, highlight);
    switch (highlight) {
      case 0: {
        HashMap::fillFromFile(*collection, "numbers.txt",
                              getInput("Podaj rozmiar: "));
        clear();
        printw("Wypelniono danymi z pliku\n");
        getch();
        break;
      }
      case 1: {
        HashMap::fillWithRandom(collection, getInput("Podaj rozmiar: "));
        clear();
        printw("Wypelniono losowymi danymi\n");
        getch();
        break;
      }
      case 2: {
        collection->print();
        getch();
        break;
      }
      case 3: {
        const Element element(getInput("Podaj klucz do dodania: "),
                              getInput("Podaj wartosc do dodania: "));
        collection->insert(element);
        clear();
        printw("Dodano element\n");
        getch();
        break;
      }
      case 4: {
        const Element element(getInput("Podaj klucz do usuniecia: "), -1);
        const bool res = collection->remove(element);
        clear();
        res ? printw("Usunieto element\n")
            : printw("Nie znaleziono elementu\n");
        getch();
        break;
      }
      default: {
        endwin();
        return 0;
      }
    }
  } while (highlight != 6);
  endwin();
  return 0;
}
