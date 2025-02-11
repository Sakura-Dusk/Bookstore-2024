#ifndef FINANCE_HPP
#define FINANCE_HPP

#include "MemoryRiver.hpp"
#include "FileStore.hpp"
#include "UserStack.hpp"
#include "read.hpp"

#include<iostream>

struct Finance {
    int id;
    double income, outcome;
    
    Finance() : id(0), income(0), outcome(0){}
    Finance(int id) : id(id), income(0), outcome(0){}
    Finance(int id, double income, double outcome) : id(id), income(income), outcome(outcome){}
    bool operator ==(const Finance &other) const {
        return id == other.id;
    }
    bool operator <(const Finance &other) const {
        return id < other.id;
    }
    bool operator <=(const Finance &other) const {
        return id <= other.id;
    }
    bool operator >(const Finance &other) const {
        return !(*this <= other);
    }
    bool operator >=(const Finance &other) const {
        return !(*this < other);
    }
    Finance operator +(const Finance &other) const {
        Finance res = *this;
        res.income += other.income;
        res.outcome += other.outcome;
        return res;
    }
    void operator +=(const Finance &other) {
        income += other.income; outcome += other.outcome;
    }
    Finance operator -(const Finance &other) const {
        Finance res = *this;
        res.income -= other.income;
        res.outcome -= other.outcome;
        return res;
    }
    void operator -=(const Finance &other) {
        income -= other.income; outcome -= other.outcome;
    }
};

std::ostream &operator <<(std::ostream &out, const Finance &now) {
    out << std::fixed << std::setprecision(2) << "+ " << now.income << " - " << now.outcome << std::fixed << std::setprecision(0);
    return out;
}

class Finance_system {
    private:
        MemoryRiver <Finance, 1> TOT;
        FileStore <int, Finance> Finance_Store;
        int tot;

        friend class BookManager;

    public:
        Finance_system() {
            if (std::filesystem::exists("Finance_File_tot")) {
                TOT.get_info(tot, 1);
            }
            else TOT.initialise("Finance_File_tot"), tot = 0;
            Finance_Store.Init("Finance_File");
        }

        ~Finance_system() {
            TOT.write_info(tot, 1);
        }

        void update_finance(Finance now) {
            if (!tot) {
                Finance res = now;
                tot++;
                Finance_Store.data_insert(tot, res);
                return ;
            }
            Finance res = *Finance_Store.data_find(tot).begin();
            tot++; res += now;
            Finance_Store.data_insert(tot, res);
        }

        void show_finance(READ &a) {
            if (Stack.get_User().Privilege < 7) throw 0;
            if (!a.length()) {
                Finance res;
                if (tot) res = *Finance_Store.data_find(tot).begin();
                std::cout << res << '\n';
                return ;
            }
            string temp = a.get_string();
            int count = string_to_int(temp);
            if (a.length()) throw 0;
            if (count > tot) throw 0;
            if (!count) {
                std::cout << '\n'; return ;
            }
            Finance res = *Finance_Store.data_find(tot).begin();
            if (count == tot) {
                std::cout << res << '\n'; return ;
            }
            Finance tmp = *Finance_Store.data_find(tot - count).begin();
            res = res - tmp;
            std::cout << res << '\n';
        }
}finance_file;

#endif