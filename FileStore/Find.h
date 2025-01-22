#include <cstring>

#ifndef insert_h
#define insert_h

bool data_find(string index) {
    int n = head_len();
    head_element now;
    data val, tmp(index, -1);
    int i;
    for (i = n; i >= 1; i--) {
        head.read(now, i);
        body.read(val, now.startid);
        if (now.size && val <= tmp) break;
    }
    if (!i) return 0;

    int j;
    for (j = 1; j <= now.size; j++) {
        body.read(val, now.startid + j - 1);
        if (val >= tmp) break;
    }
    if (j == now.size + 1) return ;

    bool count = 0;
    while (j <= now.size && val.index == index) {
        cout << val.index << " "; count = 1;
        j++; if (j <= now.size) body.read(val, now.startid + j - 1);
    }
    while (j == now.size + 1 && i < n) {
        i++; head.read(now, i);
        j = 1; body.read(val, now.startid + j - 1);
        while (j <= now && val.index == index) {
            cout << val.index << " "; count = 1;
            j++; if (j <= now.size) body.read(val, now.startid + j - 1);
        }
    }
    return count;
}

#endif