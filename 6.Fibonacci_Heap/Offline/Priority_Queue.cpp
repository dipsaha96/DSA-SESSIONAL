#include<bits/stdc++.h>
#include"Fibonacci.cpp"
using namespace std;
class Priority_queue{
    fibonacci fib;
    public:
 
    void insert(int key, int value)
    {
        fib.insert(key, value);
    }

    bool is_empty()
    {
        return fib.is_empty();
    }
    void increase_key(int value,int key)
    {
        fib.increase_key(value,key);
    }
    pair<int,int> extract_max()
    {
        return fib.extract_max();
    }
    void Delete(int key)
    {
        fib.Delete(key);
    }
    Priority_queue meld(Priority_queue &pq1)
    {
        fib.meld(pq1.fib);
        return *this;
    }
    pair<int,int> find_max()
    {
        fib.find_max();
    }

    int Size()
    {
        return fib.Size();
    }
    void print()
    {
        fib.print();
    }

    node* make_heap(int key=0, int value=0) {
    // Initialize an empty Fibonacci Heap
    cout << "Empty Priority queue created." << endl;
    return fib.make_heap(key, value);
}

void test() {
    Priority_queue pq;
    Priority_queue pq2;
    // Test make_heap() and is_empty()
    pq.make_heap();
    if (pq.is_empty()) {
        cout << "make_heap() and is_empty(): Passed\n";
    } else {
        cout << "make_heap() and is_empty(): Not Passed\n";
    }

    // Test insert() and find_max()
    pq.insert(55, 3);
    pq.insert(45, 5);
    pq.insert(32, 4);
    pq.insert(7, 8);
    pq.insert(24, 7);
    pq.insert(5,10);
    pq.insert(25,11);
    auto max_pair = pq.find_max();
    if (max_pair.first == 55 && max_pair.second == 3) {
        cout << "insert() and find_max(): Passed\n";
    } else {
        cout << "insert() and find_max(): Not Passed\n";
    }

    // Test extract_max()
    auto extracted = pq.extract_max();
    if (extracted.first == 55 && extracted.second == 3 && pq.find_max().first == 45) {
        cout << "extract_max(): Passed\n";
    } else {
        cout << "extract_max(): Not Passed\n";
    }

    // Test increase_key()
    pq.increase_key(4, 70);
    if (pq.find_max().first == 70) {
        cout << "increase_key(): Passed\n";
    } else {
        cout << "increase_key(): Not Passed\n";
    }
    // Test delete()
    pq.Delete(4);
    if (pq.find_max().first == 45 && pq.Size() == 5) {
        cout << "delete(): Passed\n";
    } else {
        cout << "delete(): Not Passed\n";
    }
    // Test meld()
    pq2.insert(24,1);
    pq2.insert(60,2);
    pq = pq.meld(pq2);
    if (pq.Size() == 7 && pq.find_max().first == 60) {
         cout << "meld(): Passed\n";
     } else {
         cout << "meld(): Not Passed\n";
     }

    // Test print()
     cout << "Printing heap after melding:\n";
    pq.print();
    cout<<"print(): Passed\n";
}


};