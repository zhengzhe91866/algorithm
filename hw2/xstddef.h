#ifndef XSTDDEF
#define XSTDDEF

template< typename Ty = void >
struct greater {
    const bool operator()(const Ty& left, const Ty& right) const {
        return left > right;
    }
};

template< typename Ty = void >
struct less {
    const bool operator()(const Ty& left, const Ty& right) const {
        return left < right;
    }
};

#endif // XSTDDEF