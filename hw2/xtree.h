#ifndef TREE
#define TREE

namespace MyNamespace {
    //從hole往parent方向走到top
    template< typename RanIt, typename Ty, typename Pr >
    inline void pushHeapByIndex(RanIt first, //array
        ptrdiff_t hole, //移動到的位置
        ptrdiff_t top, //可以當root吧，只是
        Ty& val, //要push的值
        Pr pred //比較的東東
    ) {
        while (hole > top) {
            Ty parentVal = first[(hole - 1) / 2]; //先把parent留著
            //移動node
            if (pred(parentVal, val)) //比較的function，在xstddef（大於或小於）
                first[hole] = parentVal;
            else {
                first[hole] = val;
                break;
            }
            hole = (hole - 1) / 2; //hole = hole->parent
        }

        if (hole == top) //一路上hole->parent都小於hole，所以val在top的位置
            first[hole] = val;
    }

    //新的值放在最後一格，把tree調整好
    template< typename RanIt, typename Pr >
    inline void push_heap(RanIt first, RanIt last, Pr pred) {
        ptrdiff_t count = last - first;
        if (count >= 2) {
            --last;
            typename RanIt::value_type val = *last; //新增的值，等一下要拿去sort
            --count;
            pushHeapByIndex(first, count, 0, val, pred); //sort
        }
    }

    //從hole往child的方向走到bottom
    template< typename RanIt, typename Ty, typename Pr >
    inline void popHeapHoleByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t bottom, Ty& val, Pr pred) {
        ptrdiff_t top = hole;

        while ((hole + 1) * 2 < bottom) {
            if (pred(*(first + (hole + 1) * 2), *(first + (hole + 1) * 2 - 1))) { //跟兩個child比較，[hole]會放 比較大（預設的pred所做的行為） 的那個
                *(first + hole) = *(first + (hole + 1) * 2 - 1);
                hole = (hole + 1) * 2 - 1; //接著hole改成該child
            }
            else { //同上
                *(first + hole) = *(first + (hole + 1) * 2);
                hole = (hole + 1) * 2;
            }
        }

        if ((hole + 1) * 2 == bottom) { //bottom這格不需要，放bottom前一格
            *(first + hole) = *(first + (hole + 1) * 2 - 1);
            hole = (hole + 1) * 2 - 1;
        }

        //現在，tree上面有一個數重複了，val則還沒放進tree
        pushHeapByIndex(first, hole, top, val, pred); //把val放回tree裡
    }

    //刪掉root的值，並維持heap tree
    template< typename RanIt, typename Pr >
    inline void pop_heap(RanIt first, RanIt last, Pr pred) {
        if (last - first >= 2) {
            --last;                                 //原本是end()，-1會跑到最後一格
            typename RanIt::value_type val = *last; //heap tree最後一格的值
            *last = *first;                         //最後一格覆蓋成最大值
            popHeapHoleByIndex(first, 0, last - first, val, pred); //不要root，然後要把val放進tree裡面
            //實際上把 size - 1 的部分不在這裡
        }
    }

    //把整個array丟進來做heap
    template< typename RanIt, typename Pr >
    inline void make_heap(RanIt first, RanIt last, Pr pred) {
        ptrdiff_t bottom = last - first; //array size
        ptrdiff_t hole = bottom / 2;     //最後一個的parent開始
        while (hole > 0) {
            --hole;
            typename RanIt::value_type val = *(first + hole);
            popHeapHoleByIndex(first, hole, bottom, val, pred); //從hole往下heap
            //執行時hole會被吃掉，用val保留
        }
    }
}

#endif // TREE