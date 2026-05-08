#ifndef LAB2_SEQUENCE_H
#define LAB2_SEQUENCE_H

template <class T>

class Sequence {
public:
    // получаем что-то
    virtual int GetLength() const = 0;
    virtual T Get(int index) const = 0;
    T GetFirst() const { return Get(0); }
    T GetLast() const { return Get(GetLength()-1); }
    virtual Sequence<T>* GetSubsequence(int start_index, int end_index) const = 0;

    // добавляем, получаем указатель на элемент/последовательность
    virtual Sequence<T>* Append(const T &item) = 0;
    virtual Sequence<T>* Prepend(const T &item) = 0;
    virtual Sequence<T>* InsertAt(int index, const T &item) = 0; 
    virtual Sequence<T>* Concat(Sequence<T>* other) const = 0;

    //функции map-where-reduce
    virtual Sequence<T>* Map(T (*f)(T)) const = 0;
    virtual Sequence<T>* Where(bool (*f)(T)) const = 0;
    T Reduce(T (*f)(T, T), T start) const {
        T result = start;
        for (int i=0; i<GetLength(); i++) {
            result = f(result, Get(i));
        }
        return result;
    };

    //перопределение оператора
    T operator[](int index) const { return Get(index); }; //поднять

    //Деструктор
    virtual ~Sequence() = default;
};

#endif //LAB2_SEQUENCE_H
