#include <iostream>
#include <type_traits> //std::is_same

#include "Sequences/Sequence.h"
#include "Sequences/MutableArraySequence.h"
#include "Sequences/ImmutableArraySequence.h"
#include "Sequences/MutableListSequence.h"
#include "Sequences/ImmutableListSequence.h"
#include "Sequences/BitSequence.h"
#include "my_except.h"
#include "scanValues.h"
#include "menu.h"

// функции для выбора в map/reduce/ where для int / double
template <class T> static T fSquare(const T& x) { return x * x; }
template <class T> static T fNegate(const T& x) { return -x; }
template <class T> static bool fPositive(const T& x) { return x > 0; }
template <class T> static T fSum(const T& a, const T& b) { return a + b; }
template <class T> static T fMul(const T& a, const T& b) { return a * b; }
// для bool
static bool fNot(const bool& x) { return !x; }
static bool fIsTrue(const bool& x) { return x; }
static bool fAnd(const bool& a, const bool& b) { return a && b; }
static bool fOr (const bool& a, const bool& b) { return a || b; }

//вспомогательные ф
template <class T>
static T* readValues(int n) {
    T *temp = new T[n];
    for (int i = 0; i < n; i++) {
        std::cout << "  Элемент [" << i << "]: ";
        while (!scanValue<T>(temp[i])) {
            std::cout << "  Элемент [" << i << "]: ";
        }
    }
    return temp;
}

template <class T>
static Sequence<T>* makeArrayOrList(int family, int mutability, T *items, int n) {
    if (family == 1) { // Array
        if (mutability == 1) {
            return new MutableArraySequence<T>(items, n);
        }
        else {
            return new ImmutableArraySequence<T>(items, n);
        }
    } else { // List
        if (mutability == 1) {
            return new MutableListSequence<T>(items, n);
        }
        else {
            return new ImmutableListSequence<T>(items, n);
        }
    }
} // makeArrayOrList

template <class T>
static Sequence<T>* createSequence() {
    int family, mutability;
    do { printFamilyMenu(); } while (!scanInt(family) || family < 1 || family > 2);
    do { printMutabilityMenu(); } while (!scanInt(mutability) || mutability < 1 || mutability > 2);

    int n = inputSize();
    T *temp = readValues<T>(n);

    Sequence<T> *result = makeArrayOrList<T>(family, mutability, temp, n);
    delete[] temp;
    return result;
}

template <>
Sequence<bool>* createSequence<bool>() {
    std::cout << "  Контейнер: BitSequence (автоматически)\n";

    int n = inputSize();
    bool *temp = readValues<bool>(n);

    Sequence<bool> *result = new BitSequence(temp, n);
    delete[] temp;
    return result;
}

template <class T>
static void printSequence(const Sequence<T> *s) {
    std::cout << "[ ";
    for (int i = 0; i < s->GetLength(); i++) {
        std::cout << s->Get(i); //или (*s)[i]
        if (i + 1 < s->GetLength()) std::cout << ", ";
    }
    std::cout << " ]";
}

// для append/prepand/insert at
template <class T>
static void modifySequence(Sequence<T>* &seq, const char *name) {
    if (seq == nullptr) {
        std::cout << "  Сначала создайте " << name << "!\n";
        return;
    }

    int operation;
    do { printAddMenu(); } while (!scanInt(operation) || operation < 1 || operation > 3);

    T value;
    std::cout << "  Значение: ";
    while (!scanValue<T>(value)) {
        std::cout << "  Значение: ";
    }

    Sequence<T> *old = seq;

    switch (operation) {
        case 1: // Append
            seq = seq->Append(value);
            break;
        case 2: // Prepend
            seq = seq->Prepend(value);
            break;
        case 3: { // InsertAt
            int index;
            std::cout << "  Куда вставить? Индекс в пределах [0, " << seq->GetLength() << "]\n";
            do {
                std::cout << "  Индекс: ";
            } while (!scanInt(index) || index < 0 || index > seq->GetLength());
            seq = seq->InsertAt(index, value);
            break;
        }
    }

    if (seq != old) delete old;   // если Immutable вернул новую — старую освобождаем

    std::cout << "  " << name << " = ";
    printSequence(seq);
    std::cout << "\n";
}

// подпоследовательность
template <class T>
static void subsequenceOf(const Sequence<T> *seq, const char *name) {
    if (seq == nullptr) {
        std::cout << "  Сначала создайте " << name << " >:/ \n";
        return;
    }
    if (seq->GetLength() == 0) {
        std::cout << "  " << name << " пуст, нечего выделять\n";
        return;
    }

    int max = seq->GetLength() - 1;
    int start, end;

    do {
        std::cout << "  start_index в [0, " << max << "]: ";
    } while (!scanInt(start) || start < 0 || start > max);

    do {
        std::cout << "  end_index в [" << start << ", " << max << "]: ";
    } while (!scanInt(end) || end < start || end > max);

    Sequence<T> *result = seq->GetSubsequence(start, end);

    std::cout << "  " << name << "[" << start << ".." << end << "] = ";
    printSequence(result);
    std::cout << "\n";

    delete result;
}

template <class T>
static void mapWhereReduce(const Sequence<T> *seq, const char *name) {
    int operation;
    do { printMWRMenu(); } while (!scanInt(operation) || operation < 1 || operation > 3);

    if (operation == 1) { // Map
        std::cout << "  1. Square (x*x)\n  2. Negate (-x)\n  Выбор: ";
        int f;
        while (!scanInt(f) || f < 1 || f > 2) std::cout << "  Выбор: ";

        Sequence<T> *result = (f == 1) ? seq->Map(fSquare<T>) : seq->Map(fNegate<T>);
        std::cout << "  " << name << " после Map = ";
        printSequence(result);
        std::cout << "\n";
        delete result;
    }
    else if (operation == 2) { // Where
        std::cout << "  1. Положительные (x > 0)\n  Выбор: ";
        int f;
        while (!scanInt(f) || f != 1) std::cout << "  Выбор: ";

        Sequence<T> *result = seq->Where(fPositive<T>);
        std::cout << "  " << name << " после Where = ";
        printSequence(result);
        std::cout << "\n";
        delete result;
    }
    else { // Reduce
        std::cout << "  1. Сумма (a+b)\n  2. Произведение (a*b)\n  Выбор: ";
        int f;
        while (!scanInt(f) || f < 1 || f > 2) std::cout << "  Выбор: ";

        T start;
        std::cout << "  Начальное значение: ";
        while (!scanValue<T>(start)) std::cout << "  Начальное значение: ";

        T result = (f == 1) ? seq->Reduce(fSum<T>, start) : seq->Reduce(fMul<T>, start);
        std::cout << "  Reduce(" << name << ") = " << result << "\n";
    }
}

template <>
void mapWhereReduce<bool>(const Sequence<bool> *seq, const char *name) {
    int operation;
    do { printMWRMenu(); } while (!scanInt(operation) || operation < 1 || operation > 3);

    if (operation == 1) { // Map = NOT
        Sequence<bool> *result = seq->Map(fNot);
        std::cout << "  " << name << " после NOT = ";
        printSequence(result);
        std::cout << "\n";
        delete result;
    }
    else if (operation == 2) { // Where = только true
        Sequence<bool> *result = seq->Where(fIsTrue);
        std::cout << "  " << name << " после фильтра (true) = ";
        printSequence(result);
        std::cout << "\n";
        delete result;
    }
    else { // Reduce = AND или OR
        std::cout << "  1. AND\n  2. OR\n  Выбор: ";
        int f;
        while (!scanInt(f) || f < 1 || f > 2) std::cout << "  Выбор: ";

        bool start;
        std::cout << "  Начальное значение (0/1): ";
        while (!scanValue<bool>(start)) std::cout << "  Начальное значение (0/1): ";

        bool result = (f == 1) ? seq->Reduce(fAnd, start) : seq->Reduce(fOr, start);
        std::cout << "  Reduce(" << name << ") = " << result << "\n";
    } //else
} //mapWhereReduce

// Сама работа с последовательностями:
template <class T>
static void runSequenceMenu() {
    Sequence<T> *A = nullptr;
    Sequence<T> *B = nullptr;

    bool isBit = std::is_same<T, bool>::value;  //

    int choice;
    while (true) {
        printCommandMenu(isBit);
        if (!scanInt(choice)) continue;

        switch (choice) {
            case 1: {
                std::cout << "  Удаляем старый А(если он был), чтобы записать новый\n";
                delete A;
                A = nullptr;
                A = createSequence<T>();
                if (A != nullptr) {
                    std::cout << "  A = ";
                    printSequence(A);
                    std::cout << "\n";
                }
                break;
            }
            case 2: {
                std::cout << "  Удаляем старый B(если он был), чтобы записать новый\n";
                delete B;
                B = nullptr;
                B = createSequence<T>();
                if (B != nullptr) {
                    std::cout << "  B = ";
                    printSequence(B);
                    std::cout << "\n";
                }
                break;
            }
            case 3: {
                if (A == nullptr && B == nullptr) {
                    std::cout << "  Сначала создайте хотя бы одну >:/\n";
                    break;
                }
                if (A != nullptr) { std::cout << "  A = "; printSequence(A); std::cout << "\n"; }
                else { std::cout << "  A = (не создан)\n"; }
                if (B != nullptr) { std::cout << "  B = "; printSequence(B); std::cout << "\n"; }
                else { std::cout << "  B = (не создан)\n"; }
                break;
            }
            case 4: {  // Append/Prepend/InsertAt — A или B
                int who;
                do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                if (who == 1) modifySequence(A, "A");
                else modifySequence(B, "B");
                break;
            }
            case 5: {
                if (A == nullptr || B == nullptr) {
                    std::cout<< "  Перед склеиванием сначала создайте >:/ \n";
                    break;
                }
                Sequence<T> *result = A->Concat(B);
                std::cout << "  A + B = ";
                printSequence(result);
                std::cout << "\n";
                delete result;
                break;
            }
            case 6: { // GetSubsequence A/B
                int who;
                do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                if (who == 1) subsequenceOf(A, "A");
                else subsequenceOf(B, "B");
                break;
            }
            case 7: {  // Map / Where / Reduce A/B
                int who;
                do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);
                Sequence<T> *target = (who == 1) ? A : B;
                const char *name    = (who == 1) ? "A" : "B";
                if (target == nullptr) {
                    std::cout << "  " << name << " не создан\n";
                    break;
                }
                mapWhereReduce(target, name);
                break;
            }
            case 8: {
                if (!isBit) {
                    std::cout << "  Битовые операции доступны только для bool\n";
                    break;
                }

                int operation;
                do { printBitOpMenu(); } while (!scanInt(operation) || operation < 1 || operation > 4);

                if (operation == 4) { // NOT — один аргумет
                    int who;
                    do { printABMenu(); } while (!scanInt(who) || who < 1 || who > 2);

                    Sequence<T> *target = (who == 1) ? A : B;
                    const char *name = (who == 1) ? "A" : "B";

                    if (target == nullptr) {
                        std::cout << "  " << name << " не создан\n";
                        break;
                    }
                    BitSequence *bs = dynamic_cast<BitSequence*>(target); //чтобы из Sequence<Bit> привести в BitS
                    if (bs == nullptr) { std::cout << "  Это не BitSequence\n"; break; }

                    BitSequence *result = bs->Not();
                    std::cout << "  NOT(" << name << ") = ";
                    printSequence<bool>(result);
                    std::cout << "\n";
                    delete result;
                }
                else { // AND / OR / XOR — 2 аргумента
                    if (A == nullptr || B == nullptr) {
                        std::cout << "  Сначала создайте оба!\n";
                        break;
                    }
                    if (A->GetLength() != B->GetLength()) {
                        std::cout << "  Длины должны совпадать\n";
                        break;
                    }
                    BitSequence *bA = dynamic_cast<BitSequence*>(A);
                    BitSequence *bB = dynamic_cast<BitSequence*>(B);
                    if (bA == nullptr || bB == nullptr) { std::cout << "  Не BitSequence\n"; break; }

                    BitSequence *result = nullptr;
                    const char *operationName  = "?";
                    if (operation == 1) { result = bA->And(bB); operationName = "AND"; }
                    else if (operation == 2) { result = bA->Or (bB); operationName = "OR";  }
                    else { result = bA->Xor(bB); operationName = "XOR"; }

                    std::cout << "  A " << operationName << " B = ";
                    printSequence<bool>(result);
                    std::cout << "\n";
                    delete result;
                }
                break;
            }
            case 0: {
                std::cout << "\n  Освобождаем память и уходим...\n";
                delete A;
                delete B;
                std::cout << "  Хорошего дня! :)\n\n";
                return;
            }
            default:
                std::cout << "  Неверная команда\n";
                flushInput();
                break;
        }
    }
}

void RunMenu() {
    printBanner();

    int typeChoice;
    do { printTypeMenu(); } while (!scanInt(typeChoice) || typeChoice < 1 || typeChoice > 3);

    switch (typeChoice) {
        case 1: runSequenceMenu<int>();    break;
        case 2: runSequenceMenu<double>(); break;
        case 3: runSequenceMenu<bool>();   break;
    }
}
