#ifndef LAB2_MUTABLELISTSEQUENCE_H
#define LAB2_MUTABLELISTSEQUENCE_H

#include "ListSequence.h"

template <class T>
class MutableListSequence : public ListSequence<T> {
public:
    using ListSequence<T>::ListSequence;
};
#endif //LAB2_MUTABLELISTSEQUENCE_H