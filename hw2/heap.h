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
    using size_type = size_t;
    using value_type = Ty;
    using const_reference = const Ty&;

    Heap() = default;

    template< typename Init >
    Heap(Init first, Init last) : c(first, last), comp(), maxSize(0) {
        MyNamespace::make_heap(c.begin(), c.end(), comp);

        size_type len;
        for (int i = 0; i < c.size(); i++) {
            len = length(c[i]);
            if (len > maxSize)
                maxSize = len;
        }
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
        size_type len = length(val);
        if (len > maxSize)
            maxSize = len;

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

    size_type length(value_type n) {
        size_type len = n ? 0 : 1;
        while (n) {
            len++;
            n /= 10;
        }
        return len;
    }

    void space(size_type n) {
        for (int i = 0; i < n; i++)
            cout << " ";
    }

    void details() { //��Xtree�Ϊ���function
        if (size() == 0) return;

        size_type s = size(); //�`�@���X�Ӽ�
        size_type pos = 0;    //�{�b������m
        size_type sp = 0;     //�Ʀr�������Z��
        const int maxLevel = log2(s) + 1; //tree���h��
        int n = pow(2, maxLevel) - 2;     //�Ĥ@�ӼƸ���ت��Z��

        for (int i = 0; i < maxLevel; i++) {
            int num = pow(2, i); //�o��n��X�X�ӼƦr
            space(n);
            for (int k = 0; k < num; k++) {
                int len = length(c[pos]);
                space(maxSize - len); //�ƪ�
                cout << c[pos];

                if (k != num - 1) space(sp); //�Ʀr�������ť�

                pos++;
                if (pos == s) break; //�Ʀr���]���F
            }
            //��W��
            sp = n;
            n /= 2;
            n--;
            cout << endl;
        }
        cout << endl;
    }
    
    void array() {
        cout << "Array: [";
        for (int i = 0; i < c.size(); i++) {
            if (i != 0)
                cout << ", ";
            cout << c[i];
        }
        cout << "]" << endl << endl;
    }

    void outputWithDetails() {
        cout << "Origin tree: " << endl;
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

    void outputWithArray() {
        cout << "Origin array: " << endl;
        array();
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
            array();
        }
        cout << endl;
    }

protected:
    container c{};
    Pr comp{};
    size_type maxSize;
};

#endif //HEAP