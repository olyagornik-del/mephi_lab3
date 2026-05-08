#ifndef LAB2_ARRAYSEQUENCE_H
#define LAB2_ARRAYSEQUENCE_H

#include "../DynamicArray.h"
#include "Sequence.h"

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> data;
protected:
    virtual ArraySequence<T>* MakeInstance(){ return this; }
public:
    //конструкторы;
    ArraySequence(): data() {}
    explicit ArraySequence(int size): data(size) {}
    ArraySequence(T *items, int size): data(items, size) {}
    explicit ArraySequence(const DynamicArray<T> &other_arr) : data(other_arr) {}

    //получаем длину
    int GetLength() const override{
        return data.GetSize();
    }
    // получаем элемент по индексу
    T Get(int index) const override {
        if (GetLength() == 0)
            throw OutOfRange("Последовательность пуста");
        if (index < 0 || index >= GetLength())
            throw OutOfRange("index", index, 0, GetLength() - 1);
        return data.Get(index);
    }
    // получаем подсписок
    Sequence<T>* GetSubsequence(int start_index, int end_index) const override {
        if (start_index < 0 || start_index > end_index || end_index >= GetLength()) {
            throw OutOfRange("неверные индексы start_index, end_index");
        }
        int sub_size = end_index - start_index +1;
        T *temp = new T[sub_size];
        for (int i=0; i<sub_size; i++) {
            temp[i] = Get(i+start_index);
        }
        Sequence<T> *result = new ArraySequence(temp, sub_size);
        delete[] temp;
        return  result;
    }

    // добавляем в конец
    Sequence<T>* Append(const T &item) override {
        ArraySequence<T> *result = MakeInstance();
        int old_size = GetLength();
        result->data.Resize(old_size + 1);
        result->data.Set(old_size, item);
        return result;
    }
    //добавляем в начало
    Sequence<T>* Prepend(const T &item) override {
        ArraySequence<T> *result =MakeInstance();
        int size = GetLength();
        result->data.Resize(size + 1);
        for (int i = size; i > 0; i--)
            result->data.Set(i, Get(i - 1));
        result->data.Set(0, item);
        return result;
    }
    //вставить по индексу
    Sequence<T>* InsertAt(int index, const T &item) override {
        if (index < 0 || index > GetLength()) {
            throw OutOfRange("index", index, 0, GetLength());
        }
        if (index == 0)
            return Prepend(item);
        if (index == GetLength())
            return Append(item);
        ArraySequence<T> *result = MakeInstance();
        int size = GetLength();
        result->data.Resize(size + 1);
        for (int i = size; i > index; i--)
            result->data.Set(i, Get(i - 1));
        result->data.Set(index, item);
        return result;
    }
    //склеивание списков
    Sequence<T>* Concat(Sequence<T> *other) const override{
        int new_size = GetLength()+other->GetLength();
        ArraySequence<T> *result = new ArraySequence(new_size); // можно сразу дм
        for (int i = 0; i < GetLength(); i++) {
            result->data.Set(i, Get(i));
        }
        for (int i = 0; i < other->GetLength(); i++) {
            result->data.Set(GetLength() + i, other->Get(i));
        }
        return result;
    }

    //map
    Sequence<T>* Map(T (*f)(T)) const override {
        ArraySequence<T>* result = new ArraySequence<T>(GetLength());
        for (int i = 0; i < GetLength(); i++)
            result->data.Set(i, f(Get(i)));
        return result;
    }
    // where
    Sequence<T>* Where(bool (*f)(T)) const override {
        ArraySequence<T>* result = new ArraySequence<T>();
        for (int i = 0; i < GetLength(); i++) {
            if (f(Get(i))) {
                result->Append(Get(i));
            }
        }
        return result;
    }
};

#endif //LAB2_ARRAYSEQUENCE_H