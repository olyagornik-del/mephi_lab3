#ifndef LAB2_MENU_H
#define LAB2_MENU_H

#include <iostream> // std::cin, std::cout
inline void printBanner() {
    std::cout << "\n";
    std::cout << "   ____                                        \n";
    std::cout << "  / ___|  ___  __ _ _   _  ___ _ __   ___ ___  \n";
    std::cout << "  \\___ \\ / _ \\/ _` | | | |/ _ \\ '_ \\ / __/ _ \\ \n";
    std::cout << "   ___) |  __/ (_| | |_| |  __/ | | | (_|  __/ \n";
    std::cout << "  |____/ \\___|\\__, |\\__,_|\\___|_| |_|\\___\\___| \n";
    std::cout << "                 |_|                           \n";
    std::cout << "\n";
    std::cout << "  int  ·  double  ·  bool                      \n";
    std::cout << "  ──────────────────────────────────────────── \n\n";
}
inline void printTypeMenu() {
    std::cout << "\n  ┌─────────────────────────────┐\n";
    std::cout << "  │  Выберите тип элементов:    │\n";
    std::cout << "  ├─────────────────────────────┤\n";
    std::cout << "  │  1. int                     │\n";
    std::cout << "  │  2. double                  │\n";
    std::cout << "  │  3. bool                    │\n";
    std::cout << "  └─────────────────────────────┘\n";
    std::cout << "  Тип: ";
}
inline void printCommandMenu(bool showBitOps) {
    std::cout << "\n  ┌──────────────────────────────────────┐\n";
    std::cout << "  │  1. Создать A                        │\n";
    std::cout << "  │  2. Создать B                        │\n";
    std::cout << "  │  3. Показать A и B                   │\n";
    std::cout << "  │  4. Append/Prepend/InsertAt в A/B    │\n";
    std::cout << "  │  5. Concat A + B                     │\n";
    std::cout << "  │  6. GetSubsequence от A/B            │\n";
    std::cout << "  │  7. Map / Where / Reduce             │\n";
    if (showBitOps) {
        std::cout << "  │  8. AND / OR / XOR / NOT (bit)       │\n";
    }
    std::cout << "  │  0. Выход                            │\n";
    std::cout << "  └──────────────────────────────────────┘\n";
    std::cout << "  Выберите: ";
}
inline void printFamilyMenu() {
    std::cout << "\n  Семейство контейнера:\n";
    std::cout << "  1. ArraySequence\n";
    std::cout << "  2. ListSequence\n";
    std::cout << "  Выбор: ";
}

inline void printMutabilityMenu() {
    std::cout << "\n  Изменяемость:\n";
    std::cout << "  1. Mutable\n";
    std::cout << "  2. Immutable\n";
    std::cout << "  Выбор: ";
}

inline void printAddMenu() {
    std::cout << "\n  ┌─────────────────────┐\n";
    std::cout << "  │  1. Append          │\n";
    std::cout << "  │  2. Prepend         │\n";
    std::cout << "  │  3. InsertAt        │\n";
    std::cout << "  └─────────────────────┘\n";
    std::cout << "  Выбор: ";
}

inline void printMWRMenu() {
    std::cout << "\n  ┌──────────────┐\n";
    std::cout << "  │  1. Map      │\n";
    std::cout << "  │  2. Where    │\n";
    std::cout << "  │  3. Reduce   │\n";
    std::cout << "  └──────────────┘\n";
    std::cout << "  Выбор: ";
}

inline void printABMenu() {
    std::cout << "\n  С какой работаем?\n";
    std::cout << "  1. A\n";
    std::cout << "  2. B\n";
    std::cout << "  Выбор: ";
}

inline void printBitOpMenu() {
    std::cout << "\n  ┌──────────────┐\n";
    std::cout << "  │  1. AND      │\n";
    std::cout << "  │  2. OR       │\n";
    std::cout << "  │  3. XOR      │\n";
    std::cout << "  │  4. NOT      │\n";
    std::cout << "  └──────────────┘\n";
    std::cout << "  Выбор: ";
}

#endif //LAB2_MENU_H