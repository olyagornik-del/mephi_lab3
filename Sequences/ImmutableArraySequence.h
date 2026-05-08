#ifndef LAB2_IMMUTABLEARRAYSEQUENCE_H
#define LAB2_IMMUTABLEARRAYSEQUENCE_H

#include "ArraySequence.h"

template <class T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    ArraySequence<T>* MakeInstance() override {
        return new ImmutableArraySequence<T>(*this); // копия через конструктор копирования
    }
public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    explicit ImmutableArraySequence(int size) : ArraySequence<T>(size) {}
    ImmutableArraySequence(T *items, int size) : ArraySequence<T>(items, size) {}
};

#endif //LAB2_IMMUTABLEARRAYSEQUENCE_H