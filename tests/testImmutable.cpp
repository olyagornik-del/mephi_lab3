#include <cassert> // assert
#include <cstdio> //printf

#include "../Sequences/ImmutableArraySequence.h"
#include "../Sequences/ImmutableListSequence.h"

void testImmutableArraySequenceAppend() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> Seq(items, 3);

    Sequence<int>* result = Seq.Append(99);
    assert(result != &Seq);           // вернул новый объект
    assert(Seq.GetLength() == 3);     // оригинал не изменился
    assert(result->GetLength() == 4); // новый содержит добавленный элемент
    assert(result->GetLast() == 99);
    delete result;

    printf("  [OK] testImmutableArraySequenceAppend\n");
}

void testImmutableArraySequencePrepend() {
    int items[] = {1, 2, 3};
    ImmutableArraySequence<int> Seq(items, 3);

    Sequence<int>* result = Seq.Prepend(0);
    assert(result != &Seq);
    assert(Seq.GetLength() == 3);
    assert(Seq.GetFirst() == 1);      // оригинал не изменился
    assert(result->GetLength() == 4);
    assert(result->GetFirst() == 0);
    delete result;

    printf("  [OK] testImmutableArraySequencePrepend\n");
}

void testImmutableArraySequenceInsertAt() {
    int items[] = {1, 3};
    ImmutableArraySequence<int> Seq(items, 2);

    Sequence<int>* result = Seq.InsertAt(1, 2);
    assert(result != &Seq);
    assert(Seq.GetLength() == 2);     // оригинал не изменился
    assert(Seq.Get(1) == 3);
    assert(result->GetLength() == 3);
    assert(result->Get(1) == 2);
    delete result;

    bool threw = false;
    try { Seq.InsertAt(-1, 0); } catch (const OutOfRange&) { threw = true; }
    assert(threw);

    printf("  [OK] testImmutableArraySequenceInsertAt\n");
}

void testImmutableListSequenceAppend() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> Seq(items, 3);

    Sequence<int>* result = Seq.Append(99);
    assert(result != &Seq);
    assert(Seq.GetLength() == 3);
    assert(result->GetLength() == 4);
    assert(result->GetLast() == 99);
    delete result;

    printf("  [OK] testImmutableListSequenceAppend\n");
}

void testImmutableListSequencePrepend() {
    int items[] = {1, 2, 3};
    ImmutableListSequence<int> Seq(items, 3);

    Sequence<int>* result = Seq.Prepend(0);
    assert(result != &Seq);
    assert(Seq.GetLength() == 3);
    assert(Seq.GetFirst() == 1);
    assert(result->GetLength() == 4);
    assert(result->GetFirst() == 0);
    delete result;

    printf("  [OK] testImmutableListSequencePrepend\n");
}

void testImmutableListSequenceInsertAt() {
    int items[] = {1, 3};
    ImmutableListSequence<int> Seq(items, 2);

    Sequence<int>* result = Seq.InsertAt(1, 2);
    assert(result != &Seq);
    assert(Seq.GetLength() == 2);
    assert(Seq.Get(1) == 3);
    assert(result->GetLength() == 3);
    assert(result->Get(1) == 2);
    delete result;

    bool threw = false;
    try { Seq.InsertAt(-1, 0); } catch (const OutOfRange&) { threw = true; }
    assert(threw);

    printf("  [OK] testImmutableListSequenceInsertAt\n");
}

void testImmutableAll() {
    printf("=== Тесты Immutable (Array + List) ===\n");
    testImmutableArraySequenceAppend();
    testImmutableArraySequencePrepend();
    testImmutableArraySequenceInsertAt();
    testImmutableListSequenceAppend();
    testImmutableListSequencePrepend();
    testImmutableListSequenceInsertAt();
    printf("=== Все тесты пройдены! ===\n\n");
}
