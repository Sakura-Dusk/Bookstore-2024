#include <cstring>

#ifndef insert_h
#define insert_h

void data_insert(string index, int value) {
    int n = head_len();
    head_element now;
    data val, tmp(index, value);
    int i;
    for (i = n; i >= 1; i--) {
        head.read(now, i);
        body.read(val, now.startid);
        if (now.size && val <= tmp) break;
    }
    if (!i) i = 1;
    
    now.size++;
    for (int j = now.size - 1; j >= 0; j--) {
        if (!j) body.update(tmp, now.startid);
        body.read(val, now.startid + j - 1);
        if (val > tmp) body.update(val, now.startid + j - 1 + 1);
            else {
                body.update(tmp, now.startid + j - 1 + 1);
                break;
            }
    }

    if (now.size >= B) {
        n++;
        head.write_info(n, 1);
        head_element tmp;
        head.write(tmp);
        for (int j = n; j > i; j--) {
            head.read(tmp, j);
            head.update(tmp, j + 1);
        }
        int new_size = now.size / 2;
        head_element nxt; head(nxt, i + 1);
        int cnt = 0;
        for (int i = new_size + 1; i <= now.size; i++) {
            body.read(val, now.startid + i - 1);
            body.update(val, nxt.startid + (cnt++));
        }
        now.size = new_size;
        nxt.size = cnt;
        head.update(now, i); head.update(nxt, i + 1);
    }
}

#endif