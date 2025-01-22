#include <cstring>

#ifndef delete_h
#define delete_h

void data_delete(string index, int value) {
    
    int n = head_len();
    head_element now;
    data val, tmp(index, value);
    int i;
    for (i = n; i >= 1; i--) {
        head.read(now, i);
        body.read(val, now.startid);
        if (now.size && val <= tmp) break;
    }
    if (!i) return ;

    int j;
    for (j = 1; j <= now.size; j++) {
        body.read(val, now.startid + j - 1);
        if (val == tmp) break;
    }
    if (j == now.size + 1) return ;
    now.size--;
    for (int k = j; k < now.size; j++) {
        body.read(val, now.startid + k - 1 + 1);
        body.update(val, now.startid + k - 1);
    }
    head.update(now, i);
}

#define endif