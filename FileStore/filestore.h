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
    bool operator <=(const data other) const {
        if (*this == other) return 1;
        if (index != other.index) return index < other.index;
        return value < other.value;
    }
    bool operator >(const data other) const {
        return !(*this <= other);
    }
    bool operator >=(const data other) const {
        return !(*this < other);
    }
    bool operator !=(const data other) const {
        return !(*this == other);
    }

    int get_value() {
        return value;
    }

    string get_index() {
        return index;
    }
};

const int B = 400;

MemoryRiver <data, 1> body;

class head_element {
    int id, startid, size;

    head_element(int id) : id(id) {
        chain_element tmp;
        size = 0;
        startid = body.write(tmp);
        for (int i = 1; i < B; i++)
            body.write(tmp);
    }
};

void get_element(data &x, head_element now, int id) {
    body.read(x, now.startid + id - 1);
}

void update_element(data &x, head_element now, int id) {
    body.update(x, now.startid + id - 1);
}

MemoryRiver <head_element, 1> head;

void body_Init() {
    body.initialise("Body");
}

void head_Init() {
    head.initialise("Head");
    int x = 1;
    head.write_info(x, 1);

    head_element now(1);
    head.write(now);
}

int head_len() {
    int x;
    head.get_info(x, 1);
    return x;
}

void Init() {
    body_Init();
    head_Init();
}

#endif//filestore_h