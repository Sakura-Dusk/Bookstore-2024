#ifndef BOOKMANAGER_HPP
#define BOOKMANAGER_HPP

#include "Finance.hpp"
#include "Chars.hpp"
#include "Book.hpp"

#include<cstring>
#include<string>
#include<vector>
#include<map>

bool show_cmp(Book x, Book y) {
    return x.ISBN < y.ISBN;
}

class BookManager {
    private:
        // FileStore <Book, Book> Book_Store;
        // FileStore <Book_Sort_by_ISBN, Book_Sort_by_ISBN> ISBN_Store;
        // FileStore <Book_Sort_by_BookName, Book_Sort_by_BookName> BookName_Store;
        // FileStore <Book_Sort_by_Author, Book_Sort_by_Author> Author_Store;
        // FileStore <Book_Sort_by_Keyword, Book_Sort_by_Keyword> Keyword_Store;
        MemoryRiver <int, 1> tot_;
        int tot;
        FileStore <int, Book> Book_Store;
        FileStore <chars, int> ISBN_Store, BookName_Store, Author_Store, Keyword_Store;

    public:
        BookManager() {
            tot_.initialise("Book_Manager_tot");
            if (std::filesystem::exists("Book_Manager_tot")) tot_.get_info(tot, 1);
                else {
                    // std::cerr << "New File\n";
                    tot = 0;
                }
            // std::cerr << "Booknumber = " << tot << std::endl;
            Book_Store.Init("Book_Store");
            ISBN_Store.Init("ISBN_Store");
            BookName_Store.Init("BookName_Store");
            Author_Store.Init("Author_Store");
            Keyword_Store.Init("Keyword_Store");
        }
        
        ~BookManager() {
            // std::cerr << "update BookNumber = " << tot << std::endl;
            tot_.write_info(tot, 1);
        }

        int add_book() {//return id
            tot++;
            Book now(tot);
            Book_Store.data_insert(tot, now);
            return tot;
        }

        bool find_id(int id, Book &res) {
            std::vector <Book> re = Book_Store.data_find(id);
            if (!re.size()) return 0;
            res = re[0]; return 1;
        }

        bool find_ISBN(string &ISBN, Book &res) {
            std::vector <int> re = ISBN_Store.data_find(Chars(ISBN));
            if (!re.size()) return 0;
            find_id(re[0], res); return 1;
        }

        bool find_BookName(string &BookName, std::vector <Book> &res) {
            std::vector <int> re = BookName_Store.data_find(Chars(BookName));
            if (!re.size()) return 0;
            res.clear(); res.resize(re.size());
            for (int i = 0; i < re.size(); i++) find_id(re[i], res[i]);
            sort(res.begin(), res.end(), show_cmp);
            return 1;
        }

        bool find_Author(string &Author, std::vector <Book> &res) {
            std::vector <int> re = Author_Store.data_find(Chars(Author));
            if (!re.size()) return 0;
            res.clear(); res.resize(re.size());
            for (int i = 0; i < re.size(); i++) find_id(re[i], res[i]);
            sort(res.begin(), res.end(), show_cmp);
            return 1;
        }

        bool find_Keyword(string &Keyword, std::vector <Book> &res) {
            std::vector <int> re = Keyword_Store.data_find(Chars(Keyword));
            // std::cerr << Keyword << " found number: " << re.size() << "\n";
            if (!re.size()) return 0;
            res.clear(); res.resize(re.size());
            for (int i = 0; i < re.size(); i++) find_id(re[i], res[i]);
            sort(res.begin(), res.end(), show_cmp);
            return 1;
        }

        void cut_string(string &s, std::string &op) {
            int len = s.length();
            for (int i = 0; i < len; i++) {
                if (s[i] == '=') {
                    op = s.substr(0, i);
                    s.erase(0, i + 1);
                    return ;
                }
            }
            throw 0;
        }

        bool check_ISBN(string &ISBN) {
            int len = ISBN.length();
            if (len > 20 || !len) return 0;
            for (int i = 0; i < len; i++)
                if (!isprint(ISBN[i])) return 0;
            return 1;
        }
        bool check_Name(string &name) {
            if (name.length() < 3) throw 0;
            if (name[0] != '"' || name[name.length() - 1] != '"') throw 0;
            name.erase(0, 1); name.erase(name.length() - 1, 1);

            int len = name.length();
            if (len > 60 || !len) return 0;
            for (int i = 0; i < len; i++)
                if (!isprint(name[i]) || name[i] == '"') return 0;
            return 1;
        }
        bool check_Keyword(string &name) {
            if (name.length() < 3) throw 0;
            if (name[0] != '"' || name[name.length() - 1] != '"') throw 0;
            name.erase(0, 1); name.erase(name.length() - 1, 1);

            int len = name.length();
            if (len > 60 || !len) return 0;
            if (name[0] == '|') return 0;
            std::map <string, bool> occ; occ.clear();
            
            int lstid = 0;
            for (int i = 0; i < len; i++) {
                if (!isprint(name[i]) || name[i] == '"') return 0;
                if (i && name[i] == '|' && name[i - 1] == '|') return 0;
                if (i == len - 1 && name[i] == '|') return 0;
                if (name[i] == '|') {
                    std::string cut = name.substr(lstid, i - lstid);
                    if (!cut.length()) return 0;
                    if (occ[cut]) return 0; occ[cut] = 1;
                    lstid = i + 1;
                }
            }
            std::string cut = name.substr(lstid);
            if (occ[cut]) return 0;
            return 1;
        }
        bool check_Keyword_one(string &name) {
            if (name.length() < 3) throw 0;
            if (name[0] != '"' || name[name.length() - 1] != '"') throw 0;
            name.erase(0, 1); name.erase(name.length() - 1, 1);
            
            int len = name.length();
            if (len > 60 || !len) return 0;
            for (int i = 0; i < len; i++)
                if (!isprint(name[i]) || name[i] == '"' || name[i] == '|') return 0;
            return 1;
        }

        void show_book(READ &a) {
            if (Stack.get_User().Privilege < 1) throw 0;
            // std::cerr << a.length() << '\n';
            if (!a.length()) {//按 ISBN 输出所有图书
                // std::cerr << "show all\n";
                std::vector <Book> res;
                res.resize(tot);
                for (int i = 0; i < tot; i++) find_id(i + 1, res[i]);
                sort(res.begin(), res.end(), show_cmp);
                for (int i = 0; i < tot; i++) std::cout << res[i] << '\n';
                if (!tot) std::cout << '\n';
                return ;
            }
            std::string word = a.get_string();
            if (a.length()) throw 0;
            std::string op;
            cut_string(word, op);
            if (!word.length()) throw 0;
            if (op == "-ISBN") {
                if (!check_ISBN(word)) throw 0;
                Book res;
                if (!find_ISBN(word, res)) std::cout << '\n';
                    else std::cout << res << '\n';
                return ;
            }
            if (op == "-name") {
                if (!check_Name(word)) throw 0;
                std::vector <Book> res;
                if (!find_BookName(word, res)) std::cout << '\n';
                    else {
                        for (int i = 0; i < res.size(); i++) std::cout << res[i] << '\n';
                    }
                return ;
            }
            if (op == "-author") {
                if (!check_Name(word)) throw 0;
                std::vector <Book> res;
                if (!find_Author(word, res)) std::cout << '\n';
                    else {
                        for (int i = 0; i < res.size(); i++) std::cout << res[i] << '\n';
                    }
                return ;
            }
            if (op == "-keyword") {
                if (!check_Keyword_one(word)) throw 0;
                // std::cerr << word << '\n';
                std::vector <Book> res;
                if (!find_Keyword(word, res)) std::cout << '\n';
                    else {
                        for (int i = 0; i < res.size(); i++) std::cout << res[i] << '\n';
                    }
                return ;
            }
            throw 0;
        }

        void book_select(READ &a) {
            if (Stack.get_User().Privilege < 3) throw 0;
            if (!a.length()) throw 0;
            std::string ISBN = a.get_string();
            // std::cerr << ISBN << '\n';
            if (!check_ISBN(ISBN)) throw 0;
            if (a.length()) throw 0;
            User now = Stack.get_User();
            int last_id = now.select_book;
            // std::cerr << now.UserID << std::endl;
            // if (last_id != -1 && Chars(ISBN) == (*Book_Store.data_find(last_id).begin()).ISBN) throw 0;

            Stack.Store.List.data_delete(now.UserID, now);
            
            int nowid;
            std::vector <int> tmp = ISBN_Store.data_find(ISBN);
            // std::cerr << tmp.size() << std::endl;
            if (tmp.empty()) {
                // std::cerr << "create a new book\n";
                nowid = ++tot;
                Book nowbook(tot);//需要创建这本书，并给他 ISBN 的信息
                nowbook.ISBN = Chars(ISBN);
                Book_Store.data_insert(tot, nowbook);
                ISBN_Store.data_insert(nowbook.ISBN, tot);
                now.select_book = nowbook.BookID;
            }
            else {
                now.select_book = tmp[0];
            }
            
            // std::cerr << now.UserID << " " << now.select_book << "\n";
            Stack.Store.List.data_insert(now.UserID, now);
        }

        void book_buy(READ &a) {
            if (Stack.get_User().Privilege < 1) throw 0;
            if (!a.length()) throw 0;
            std::string ISBN = a.get_string();
            if (!check_ISBN(ISBN)) throw 0;
            if (!a.length()) throw 0;
            std::string tmp = a.get_string();
            int quantity = string_to_int(tmp);
            if (a.length()) throw 0;

            Book now;
            if (!find_ISBN(ISBN, now)) throw 0;
            
            if (quantity <= 0) throw 0;
            if (now.Quantity < quantity) throw 0;
            Book_Store.data_delete(now.BookID, now);
            now.Quantity -= quantity;
            now.TotalCost -= now.Price * quantity;
            std::cout << std::fixed << std::setprecision(2) << now.Price * quantity << '\t' << std::fixed << std::setprecision(0) << '\n';
            Book_Store.data_insert(now.BookID, now);

            Finance nw(finance_file.tot + 1, now.Price * quantity, 0);
            finance_file.update_finance(nw);
        }

        void book_import(READ &a) {
            if (Stack.get_User().Privilege < 3) throw 0;
            if (!a.length()) throw 0;
            std::string tmp = a.get_string();
            int quantity = string_to_int(tmp);
            if (quantity <= 0) throw 0;
            if (!a.length()) throw 0;
            tmp = a.get_string();
            double total_cost = string_to_double(tmp);
            if (total_cost <= 0) throw 0;
            if (a.length()) throw 0;

            User now = Stack.get_User();
            if (now.select_book == -1) throw 0;
            Book now_book; find_id(now.select_book, now_book);

            Book_Store.data_delete(now_book.BookID, now_book);
            now_book.Quantity += quantity;
            now_book.TotalCost += total_cost;
            Book_Store.data_insert(now_book.BookID, now_book);

            // std::cerr << "total_cost = " << total_cost << '\n';

            Finance nw(finance_file.tot + 1, 0, total_cost);
            // std::cerr << "Try to update finance\n";
            finance_file.update_finance(nw);
        }

        void book_modify_check(READ &a) {
            User now = Stack.get_User();
            Book now_book; find_id(now.select_book, now_book);
            bool fir[10];
            fir[0] = fir[1] = fir[2] = fir[3] = fir[4] = 0;
            while (a.length()) {
                std::string word = a.get_string();
                std::string op;
                cut_string(word, op);
                // std::cerr << "op=" << op << "\nword=" << word << '\n';
                if (!word.length()) throw 0;
                if (op == "-ISBN") {
                    if (fir[0]) throw 0; fir[0] = 1;
                    chars last_ISBN = now_book.ISBN;
                    if (!check_ISBN(word)) throw 0;
                    Book tmp;
                    if (find_ISBN(word, tmp)) throw 0;
                    continue;
                }
                if (op == "-name") {
                    if (fir[1]) throw 0; fir[1] = 1;
                    if (!check_Name(word)) throw 0;
                    continue;
                }
                if (op == "-author") {
                    if (fir[2]) throw 0; fir[2] = 1;
                    if (!check_Name(word)) throw 0;
                    continue;
                }
                if (op == "-keyword") {
                    if (fir[3]) throw 0; fir[3] = 1;
                    if (!check_Keyword(word)) throw 0;
                    continue;
                }
                if (op == "-price") {
                    if (fir[4]) throw 0; fir[4] = 1;
                    double price = string_to_double(word);
                    if (price < 0) throw 0;
                    continue;
                }
                throw 0;
            }
        }
        
        void book_modify(READ &a) {
            if (Stack.get_User().Privilege < 3) throw 0;
            // std::cerr << "User privilege fine\n";
            User now = Stack.get_User();
            // std::cerr << now.select_book << std::endl;
            if (now.select_book == -1) throw 0;
            Book now_book; find_id(now.select_book, now_book);

            READ b = a;
            book_modify_check(b);

            while (a.length()) {
                std::string word = a.get_string();
                std::string op;
                cut_string(word, op);
                // std::cerr << "op=" << op << "\nword=" << word << '\n';
                if (op == "-ISBN") {
                    chars last_ISBN = now_book.ISBN;
                    // std::cerr << "last_ISBN = " << last_ISBN << "\n";
                    if (last_ISBN == Chars(word)) throw 0;
                    if (last_ISBN[0]) ISBN_Store.data_delete(last_ISBN, now_book.BookID);
                    Book_Store.data_delete(now_book.BookID, now_book);
                    now_book.ISBN = Chars(word);
                    Book_Store.data_insert(now_book.BookID, now_book);
                    ISBN_Store.data_insert(now_book.ISBN, now_book.BookID);
                    continue;
                }
                if (op == "-name") {
                    word.erase(0, 1); word.erase(word.length() - 1, 1);
                    chars last_name = now_book.BookName;
                    if (last_name[0]) BookName_Store.data_delete(last_name, now_book.BookID);
                    Book_Store.data_delete(now_book.BookID, now_book);
                    now_book.BookName = Chars(word);
                    Book_Store.data_insert(now_book.BookID, now_book);
                    BookName_Store.data_insert(now_book.BookName, now_book.BookID);
                    continue;
                }
                if (op == "-author") {
                    word.erase(0, 1); word.erase(word.length() - 1, 1);
                    chars last_author = now_book.Author;
                    if (last_author[0]) Author_Store.data_delete(last_author, now_book.BookID);
                    Book_Store.data_delete(now_book.BookID, now_book);
                    now_book.Author = Chars(word);
                    Book_Store.data_insert(now_book.BookID, now_book);
                    Author_Store.data_insert(now_book.Author, now_book.BookID);
                    continue;
                }
                if (op == "-keyword") {
                    word.erase(0, 1); word.erase(word.length() - 1, 1);
                    std::string last_keyword = String(now_book.Keyword);
                    int lstid = 0, len = last_keyword.length();
                    for (int i = 0; i < len; i++) {
                        if (last_keyword[i] == '|') {
                            std::string cut = last_keyword.substr(lstid, i - lstid);
                            Keyword_Store.data_delete(Chars(cut), now_book.BookID);
                            lstid = i + 1;
                        }
                    }
                    if (!len) {
                        std::string cut = last_keyword.substr(lstid);
                        Keyword_Store.data_delete(Chars(cut), now_book.BookID);
                    }
                    Book_Store.data_delete(now_book.BookID, now_book);
                    now_book.Keyword = Chars(word);
                    Book_Store.data_insert(now_book.BookID, now_book);
                    len = word.length(); lstid = 0;
                    for (int i = 0; i < len; i++) {
                        if (word[i] == '|') {
                            std::string cut = word.substr(lstid, i - lstid);
                            Keyword_Store.data_insert(Chars(cut), now_book.BookID);
                            // std::cerr << "cut word = " << cut << std::endl;
                            lstid = i + 1;
                        }
                    }
                    std::string cut = word.substr(lstid);
                    // std::cerr << "cut word = " << cut << std::endl;
                    Keyword_Store.data_insert(Chars(cut), now_book.BookID);
                    continue;
                }
                if (op == "-price") {
                    Book_Store.data_delete(now_book.BookID, now_book);
                    now_book.Price = string_to_double(word);
                    Book_Store.data_insert(now_book.BookID, now_book);
                    continue;
                }
                throw 0;
            }
        }
}Bookmanager;

#endif