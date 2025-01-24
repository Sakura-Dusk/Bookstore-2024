#ifndef CHARS_HPP
#define CHARS_HPP

struct chars {
    public:
        char a[60];

        chars(){}

        char& operator[](int id) {
            return a[id];
        }

        bool operator ==(const chars other) const {
            if (strlen(a) != strlen(other.a)) return 0;
            for (int i = 0; i < strlen(a); i++) if (a[i] != other.a[i]) return 0;
            return 1;
        }
        bool operator !=(const chars other) const {
            return !(*this == other);
        }
        bool operator <(const chars other) const {
            if (*this == other) return 0;
            int k = std::min(strlen(a), strlen(other.a)) + 1;
            for (int i = 0; i < k; i++) if (a[i] != other.a[i]) return a[i] < other.a[i];
            return 0;
        }
        bool operator <=(const chars other) const {
            return (*this == other) || (*this < other);
        }
        bool operator >(const chars other) const {
            return !(*this <= other);
        }
        bool operator >=(const chars other) const {
            return !(*this < other);
        }
};

#endif