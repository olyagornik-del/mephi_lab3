#ifndef LAB2_SCANVALUES_H
#define LAB2_SCANVALUES_H

// Очищает после плохого ввода
void flushInput();
bool scanInt(int &out);
bool scanDouble(double &out);
// ввод размера или номера
int inputSize();

template <class T> bool scanValue(T &out);
template <> bool scanValue<int>(int &out);
template <> bool scanValue<double>(double &out);
template <> bool scanValue<bool>(bool &out);

#endif //LAB2_SCANVALUES_H
