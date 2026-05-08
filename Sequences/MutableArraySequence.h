#ifndef LAB2_MUTABLEARRAYSEQUENCE_H
#define LAB2_MUTABLEARRAYSEQUENCE_H

#include "ArraySequence.h"

template <class T>
class MutableArraySequence : public ArraySequence<T> {
public:
    using ArraySequence<T>::ArraySequence; // наследуем все конструкторы
};

#endif //LAB2_MUTABLEARRAYSEQUENCE_H