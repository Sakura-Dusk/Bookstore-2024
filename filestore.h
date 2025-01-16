#include<cstring>
#include<string>

#ifndef filestore_h
#define filestore_h

class data {
    private:
    
    std::string index; int value;

    public:

    data(std::string index_ = "", int value_ = 0) : index(index_), value(value_) {}
    
    bool operator <(const data other) const {
        if (index != other.index) return index < other.index;
        return value < other.value;
    }

    int get_value() {
        return value;
    }
};

class chain_element {
    private:
    
    // data* x;
    int x;
    chain_element *prv, *nxt;

    public:

    chain_element(chain_element* prv_ = nullptr, chain_element* nxt_ = nullptr) : prv(prv_), nxt(nxt_) {
        x = -1;
    }

    chain_element(int x_, chain_element* prv_ = nullptr, chain_element* nxt_ = nullptr) : x(x_), prv(prv_), nxt(nxt_) {}
};

const int B = 400;



#endif//filestore_h