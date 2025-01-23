#ifndef FILESOTRE_HPP
#define FILESOTRE_HPP

#include<iostream>
#include<vector>
#include<cstring>
#include "MemoryRiver.hpp"

const int BLOCK_SIZE = 300;

template<typename indextype, typename valuetype>
//需要 indextype 和 valuetype 可比较
class FileStore {
    class data {
        private:
        
            indextype index;
            valuetype value;
            friend class head_element;
            friend class FileStore;

        public:

            data() {
                index = indextype(); value = valuetype();
            }
            data(indextype index_, valuetype value_) : index(index_), value(value_) {}
            
            bool operator ==(const data &other) const {
                return index == other.index && value == other.value;
            }
            bool operator !=(const data &other) const {
                return !(*this == other);
            }
            bool operator <(const data &other) const {
                if (index != other.index) return index < other.index;
                return value < other.value;
            }
            bool operator <=(const data &other) const {
                if (*this == other) return 1;
                if (index != other.index) return index < other.index;
                return value < other.value;
            }
            bool operator >(const data &other) const {
                return !(*this <= other);
            }
            bool operator >=(const data &other) const {
                return !(*this < other);
            }
    };

    class point {//链表中一个点
        private:
            data x;
            int size, id, next;
            friend class FileStore;
        
        public:
            point(int size = 0, int id = 0, int next = -1) : size(size), id(id), next(next){x = data();}
    };

    class head_element {//一个块
        private:
            data a[BLOCK_SIZE];
            friend class FileStore;
        
        public:
            head_element(){}

            data& operator[](int id) {
                return a[id];
            }
    };

    private:
        int head;
        MemoryRiver <head_element, 0> body_file;//直接用数组记录链里每个的信息
        MemoryRiver <point, 1> head_file;//记录这条链的信息（大小，下一条链的下标，这条链对应 body_file 的 id）
        //head_file 的常数用来记录 head
    
    public:
        FileStore(string s = "") {
            head_file.initialise(s + "_head");
            if (!std::filesystem::exists(s + "_body")) head = -1;
                else head_file.get_info(head, 1);
            body_file.initialise(s + "_body");
        }

        ~FileStore() {
            head_file.write_info(head, 1);
        }

        void data_insert(const indextype index, const valuetype &value) {
            data now_data(index, value);
            // std::cerr << now_data.index.a << " and " << now_data.value << std::endl;
            point now_point;
            head_element Store;
            int nowid = head;
            if (head == -1) {
                now_point.id = body_file.write(Store);
                head = head_file.write(now_point);
                nowid = head;
            }
            else {
                while (head != -1) {
                    head_file.read(now_point, nowid);
                    if (!now_point.size || now_point.next == -1 || now_point.x >= now_data) break;
                    nowid = now_point.next;
                }
                body_file.read(Store, now_point.id);
            }//找到新 data 到底要插入在那个链中

            int place = 0;
            // std::cerr << "size:" << now_point.size << std::endl;
            for (int i = now_point.size; i >= 1; i--) {
                // std::cerr << "check in Store:" << i - 1 << " " << Store[i - 1].index.a << " " << Store[i - 1].value << std::endl;
                if (Store.a[i - 1] < now_data) {place = i; break;}
                    else Store.a[i] = Store.a[i - 1];
            }
            Store[place] = now_data;
            // std::cerr << "new put in Store:" << place << " qwq " << Store[place].index.a << " " << Store[place].value << std::endl;
            now_point.size++;
            if (now_data > now_point.x) now_point.x = now_data;
            //插入，维护 size,id(这个不会变),x(x代表里面最大的那个)

            if (now_point.size >= BLOCK_SIZE) {//裂块
                head_element new_Store;
                point new_point(now_point.size / 2, 0, now_point.next);
                for (int i = now_point.size - now_point.size / 2, cnt = 0; i < now_point.size; i++, cnt++)
                    new_Store[cnt] = Store[i], Store[i] = data(), new_point.x = std::max(new_point.x, new_Store[cnt]);
                now_point.x = Store[0];
                for (int i = 1; i < now_point.size - now_point.size / 2; i++) now_point.x = std::max(now_point.x, Store[i]);
                now_point.size = now_point.size - now_point.size / 2;
                body_file.update(Store, now_point.id);
                new_point.id = body_file.write(new_Store);
                now_point.next = head_file.write(new_point);
                head_file.update(now_point, nowid);
            }
            else {
                // std::cerr << now_point.id << " " << nowid << " ----  store updateing\n";
                body_file.update(Store, now_point.id);
                head_file.update(now_point, nowid);
            }
        }

        void data_delete(const indextype &index, const valuetype &value) {
            if (head == -1) return ;
            data now_data(index, value);
            point now_point;
            int nowid = head, preid = head;
            while (nowid != -1) {
                head_file.read(now_point, nowid);
                if (!now_point.size || now_point.next == -1 || now_point.x >= now_data) break;
                preid = nowid;
                nowid = now_point.next;
            }//找到 data 到底在哪个链中

            head_element Store;
            body_file.read(Store, now_point.id);
            int place = -1;
            for (int i = 0; i < now_point.size; i++)
                if (Store[i] == now_data) {place = i; break;}
            if (place == -1) return ;
            for (int i = place + 1; i < now_point.size; i++) Store[i - 1] = Store[i];
            now_point.size--; Store[now_point.size] = data();
            
            if (!now_point.size) {//一个块消失了
                if (head == nowid) {
                    head = now_point.next;
                }
                else {
                    point pre_point;
                    head_file.read(pre_point, preid);
                    pre_point.next = now_point.next;
                    head_file.update(pre_point, preid);
                }
                return ;
            }
            else {
                now_point.x = Store[0];
                for (int i = 1; i < now_point.size; i++) now_point.x = std::max(now_point.x, Store[i]);
            }

            body_file.update(Store, now_point.id);
            head_file.update(now_point, nowid);
        }

        std::vector <valuetype> data_find(const indextype &index) {
            std::vector <valuetype> res;
            if (head == -1) return res;
            data now_data(index, -1);
            point now_point;
            int nowid = head;
            while (nowid != -1) {
                head_file.read(now_point, nowid);
                if (!now_point.size || now_point.next == -1 || now_point.x >= now_data) break;
                nowid = now_point.next;
            }//找到 data 到底在哪个链开始
            // std::cerr << "size:" << now_point.size << std::endl;
            
            head_element Store;
            body_file.read(Store, now_point.id);
            int place = -1;
            for (int i = 0; i < now_point.size; i++) {
                if (Store[i].index == index) {place = i; break;}
            }
            if (place == -1) return res;//找到第一个符合的 data，如果这个块没有直接 return

            data now = Store[place];
            while (now.index == index) {
                res.push_back(now.value);
                place++;
                if (place == now_point.size) {
                    place = 0;
                    nowid = now_point.next;
                    if (nowid == -1) break;
                    head_file.read(now_point, nowid);
                    body_file.read(Store, now_point.id);
                }
                now = Store[place];
            }
            return res;
        }
};


#endif

struct chars {
    public:
        char a[64];

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

int main() {
    int n; std::cin >> n;
    FileStore <chars, int> T;
    chars index;
    for (int i = 1; i <= n; i++) {
        std::string op; std::cin >> op;
        // std::cerr << op << std::endl;
        if (op == "insert") {
            int value; std::cin >> index.a >> value;
            T.data_insert(index, value);
            continue;
        }
        if (op == "delete") {
            int value; std::cin >> index.a >> value;
            T.data_delete(index, value);
            continue;
        }
        if (op == "find") {
            std::cin >> index.a;
            std::vector <int> ans = T.data_find(index);
            if (!ans.size()) std::cout << "null";
                else {
                    for (int i = 0; i < ans.size(); i++) std::cout << ans[i] << " ";
                }
            std::cout << std::endl;
        }
    }
    return 0;
}