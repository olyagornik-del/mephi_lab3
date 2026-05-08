#ifndef LAB2_IMMUTABLELISTSEQUENCE_H
#define LAB2_IMMUTABLELISTSEQUENCE_H

#include "ListSequence.h"

template <class T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* MakeInstance() override {
        return new ImmutableListSequence<T>(*this);
    }
public:
    ImmutableListSequence(): ListSequence<T>() {}
    explicit ImmutableListSequence(int size): ListSequence<T>(size) {}
    ImmutableListSequence(T *items, int size): ListSequence<T>(items, size) {}
};
#endif //LAB2_IMMUTABLELISTSEQUENCE_H