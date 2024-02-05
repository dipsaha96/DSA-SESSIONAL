#include <bits/stdc++.h>
#include "Priority_Queue.cpp"
using namespace std;

int main()
{
    Priority_queue fibHeap;

    int choice;
    cout << "Enter your choice:\n"
         << "1. make_heap()\n"
         << "2. is_empty(heap)\n"
         << "3. insert(heap, key, value)\n"
         << "4. extract_max(heap)\n"
         << "5. increase_key(heap, value, new_key)\n"
         << "6. delete(heap, value)\n"
         << "7. meld(heap1, heap2)\n"
         << "8. find_max(heap)\n"
         << "9. print(heap)\n"
         << "10. test()\n"
         << "0. Exit\n";
    do
    {
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            fibHeap.make_heap();
            break;
        case 2:
            if (fibHeap.is_empty())
                cout << "Heap is empty" << endl;
            else{
                cout << "Heap is not empty" << endl;
                fibHeap.print();
            }
            break;
        case 3:
        {
            int key, value;
            cout << "Enter key and value to insert: ";
            cin >> key >> value;
            fibHeap.insert(key, value);
            fibHeap.print();
            break;
        }
        case 4:
        {
            auto max_pair = fibHeap.extract_max();
            if(!fibHeap.is_empty())
            cout << "Max element extracted: (" << max_pair.first << ", " << max_pair.second << ")" << endl;
            if(!fibHeap.is_empty())
                fibHeap.print();
            break;
        }
        case 5:
        {
            int value, new_key;
            cout << "Enter value and new key: ";
            cin >> value >> new_key;
            fibHeap.increase_key(value, new_key);
            if(!fibHeap.is_empty())
                fibHeap.print();
            break;
        }
        case 6:
        {
            int key;
            cout << "Enter value to delete: ";
            cin >> key;
            fibHeap.Delete(key);
            if(!fibHeap.is_empty())
                fibHeap.print();
            break;
        }
        case 7:
        {
            Priority_queue heap2;
            heap2.insert(30, 40);
            heap2.insert(40, 50);
            fibHeap = fibHeap.meld(heap2);
            break;
        }
        case 8:
        {
            auto max_pair = fibHeap.find_max();
            cout << "Max element in the heap: (" << max_pair.first << ", " << max_pair.second << ")" << endl;
            if(!fibHeap.is_empty())
                fibHeap.print();
            break;
        }
        case 9:
            fibHeap.print();
            break;
        case 10:
            fibHeap.test();
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 0);

    return 0;
}
