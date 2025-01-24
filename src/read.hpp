#ifndef READ_HPP
#define READ_HPP

class READ {
    private:
        string a;
    
    public:
        void check() {
            while (!a.empty() && a[0] == ' ') a.erase(0, 1);
            int k = a.length();
            while (k && a[k - 1] == ' ') k--, a.erase(k, 1);
        }

        READ() {}
        READ(string a) : a(a) {
            check();
        }

        int length() {
            return a.length();
        }

        string get_string() {
            check();
            if (!a.length()) throw error;
            string re = "";
            while (!a.empty() && a[0] != ' ') {
                re += a[0];
                a.erase(0, 1);
            }
            return re;
        }
};

int string_to_int(string x) {
    long long res = 0; bool zf = 0;
    int k = x.length();
    for (int i = 0; i < k; i++) {
        if (x[i] < '0' || x[i] > '9') {
            if (x[i] == '-' && !i) {zf = 1; continue;}
            throw error;
        }
        res = res * 10 + x[i] - '0';
        if (res > 2147483647) throw error;
    }
    return zf ? -res : res;
}

#endif