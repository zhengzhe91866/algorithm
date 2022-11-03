#ifndef TREE
#define TREE

namespace MyNamespace {
    //�qhole��parent��V����top
    template< typename RanIt, typename Ty, typename Pr >
    inline void pushHeapByIndex(RanIt first, //array
        ptrdiff_t hole, //���ʨ쪺��m
        ptrdiff_t top, //�i�H��root�a�A�u�O
        Ty& val, //�npush����
        Pr pred //������F�F
    ) {
        while (hole > top) {
            Ty parentVal = first[(hole - 1) / 2]; //����parent�d��
            //����node
            if (pred(parentVal, val)) //�����function�A�bxstddef�]�j��Τp��^
                first[hole] = parentVal;
            else {
                first[hole] = val;
                break;
            }
            hole = (hole - 1) / 2; //hole = hole->parent
        }

        if (hole == top) //�@���Whole->parent���p��hole�A�ҥHval�btop����m
            first[hole] = val;
    }

    //�s���ȩ�b�̫�@��A��tree�վ�n
    template< typename RanIt, typename Pr >
    inline void push_heap(RanIt first, RanIt last, Pr pred) {
        ptrdiff_t count = last - first;
        if (count >= 2) {
            --last;
            typename RanIt::value_type val = *last; //�s�W���ȡA���@�U�n���hsort
            --count;
            pushHeapByIndex(first, count, 0, val, pred); //sort
        }
    }

    //�qhole��child����V����bottom
    template< typename RanIt, typename Ty, typename Pr >
    inline void popHeapHoleByIndex(RanIt first, ptrdiff_t hole, ptrdiff_t bottom, Ty& val, Pr pred) {
        ptrdiff_t top = hole;

        while ((hole + 1) * 2 < bottom) {
            if (pred(*(first + (hole + 1) * 2), *(first + (hole + 1) * 2 - 1))) { //����child����A[hole]�|�� ����j�]�w�]��pred�Ұ����欰�^ ������
                *(first + hole) = *(first + (hole + 1) * 2 - 1);
                hole = (hole + 1) * 2 - 1; //����hole�令��child
            }
            else { //�P�W
                *(first + hole) = *(first + (hole + 1) * 2);
                hole = (hole + 1) * 2;
            }
        }

        if ((hole + 1) * 2 == bottom) { //bottom�o�椣�ݭn�A��bottom�e�@��
            *(first + hole) = *(first + (hole + 1) * 2 - 1);
            hole = (hole + 1) * 2 - 1;
        }

        //�{�b�Atree�W�����@�Ӽƭ��ƤF�Aval�h�٨S��itree
        pushHeapByIndex(first, hole, top, val, pred); //��val��^tree��
    }

    //�R��root���ȡA�ú���heap tree
    template< typename RanIt, typename Pr >
    inline void pop_heap(RanIt first, RanIt last, Pr pred) {
        if (last - first >= 2) {
            --last;                                 //�쥻�Oend()�A-1�|�]��̫�@��
            typename RanIt::value_type val = *last; //heap tree�̫�@�檺��
            *last = *first;                         //�̫�@���л\���̤j��
            popHeapHoleByIndex(first, 0, last - first, val, pred); //���nroot�A�M��n��val��itree�̭�
            //��ڤW�� size - 1 ���������b�o��
        }
    }

    //����array��i�Ӱ�heap
    template< typename RanIt, typename Pr >
    inline void make_heap(RanIt first, RanIt last, Pr pred) {
        ptrdiff_t bottom = last - first; //array size
        ptrdiff_t hole = bottom / 2;     //�̫�@�Ӫ�parent�}�l
        while (hole > 0) {
            --hole;
            typename RanIt::value_type val = *(first + hole);
            popHeapHoleByIndex(first, hole, bottom, val, pred); //�qhole���Uheap
            //�����hole�|�Q�Y���A��val�O�d
        }
    }
}

#endif // TREE