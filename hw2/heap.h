#ifndef HEAP
#define HEAP

#include "xstddef.h"
#include "xtree.h"

#include <vector>
using std::vector;

template< typename Ty, typename Pr = less< typename vector<Ty>::value_type > >
class Heap {
public:
    using container = vector<Ty>;
    using size_type = typename Ty;
    using value_type = typename Ty;
    using const_reference = typename const Ty&;

    Heap() = default;

    template< typename Init >
    Heap(Init first, Init last) : c(first, last), comp() {
        MyNamespace::make_heap(c.begin(), c.end(), comp);
    }

    bool empty() const {
        return c.empty();
    }

    size_type size() const {
        return c.size();
    }

    const_reference top() const {
        return c.front();
    }

    void push(const value_type& val) {
        c.push_back(val);
        MyNamespace::push_heap(c.begin(), c.end(), comp);
    }

    void pop() {
        MyNamespace::pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

    void output() {
        container temp;
        while (!empty()) {
            temp.push_back(*c.begin());
            cout << "Sorted numbers: ";
            for (int k = 0; k < temp.size(); k++) {
                if (k != 0)
                    cout << ", ";
                cout << temp[k];
            }
            cout << endl;
            pop();
        }
        cout << endl;
    }
    
    void details() {
        cout << "Array: [";
        for (int i = 0; i < c.size(); i++) {
            if (i != 0)
                cout << ", ";
            cout << c[i];
        }
        cout << "]" << endl << endl;
    }

    void outputWithDetails() {
        cout << "Origin array: " << endl;
        details();

        container temp;
        while (!empty()) {
            temp.push_back(*c.begin());
            cout << "Sorted numbers: ";
            for (int k = 0; k < temp.size(); k++) {
                if (k != 0)
                    cout << ", ";
                cout << temp[k];
            }
            cout << endl;
            pop();
            details();
        }
        cout << endl;
    }


protected:
    container c{};
    Pr comp{};
};

#endif //HEAP