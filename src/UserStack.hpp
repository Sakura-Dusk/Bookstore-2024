#ifndef USERSTACK_HPP
#define USERSTACK_HPP

#include "user.hpp"
#include "Chars.hpp"
#include "FileStore.hpp"
#include "UserStore.hpp"
#include<vector>
#include<iostream>

class UserStack {
    private:
        std::vector <User> Stack;
        UserStore Store;
        friend class BookManager;

    public:
        User get_User() {
            if (Stack.empty()) {
                // std::cerr << "no user" << std::endl;
                return User();
            }
            return Stack.back();
        }

        bool check_ID(string &now) {
            int len = now.length();
            if (len > 30) return 0;
            for (int i = 0; i < len; i++) {
                if ((now[i] < '0' || now[i] > '9') && (now[i] < 'a' || now[i] > 'z') && (now[i] < 'A' || now[i] > 'Z') && now[i] != '_') return 0;
            }
            return 1;
        }
        bool check_name(string &now) {
            int len = now.length();
            if (len > 30) return 0;
            for (int i = 0; i < len; i++) {
                if (!isprint(now[i])) return 0;
            }
            return 1;
        }

        void Login(READ &a) {
            string nxt = a.get_string();
            // std::cerr << nxt << std::endl;
            if (a.length()) {
                string Password = a.get_string();
                // std::cerr << Password << std::endl;
                if (a.length()) throw 0;
                User new_User;
                // std::cerr << "Read type correct\n";
                if (!Store.User_get(nxt, new_User)) throw 0;
                // std::cerr << new_User.Password.a << std::endl << Password << std::endl;
                if (new_User.Password != chars(Password)) throw 0;
                Stack.push_back(new_User);
            }
            else {
                User new_User;
                if (!Store.User_get(nxt, new_User)) throw 0;
                if (new_User.Privilege >= get_User().Privilege) throw 0;
                Stack.push_back(new_User);
            }
        }

        void Logout(READ &a) {
            if (a.length()) throw 0;
            if (Stack.empty()) throw 0;
            //取消当前选中的书
            User now = Stack.back();
            Store.List.data_delete(now.UserID, now);
            now.select_book = -1;
            Store.List.data_insert(now.UserID, now);
            Stack.pop_back();
        }

        void regisiter_account(READ &a) {
            if (!a.length()) throw 0;
            string UserID = a.get_string();
            if (!check_ID(UserID)) throw 0;
            if (!a.length()) throw 0;
            string Password = a.get_string();
            if (!check_ID(Password)) throw 0;
            if (!a.length()) throw 0;
            string Username = a.get_string();
            if (!check_name(Username)) throw 0;
            if (a.length()) throw 0;
            Store.User_create(UserID, Password, 1, Username);
        }

        void change_Password(READ &a) {
            if (get_User().Privilege < 1) throw 0;
            if (!a.length()) throw 0;
            string UserID = a.get_string();
            if (!a.length()) throw 0;
            string st1 = a.get_string();
            if (!a.length()) {
                // std::cerr << "Now Privilege :" << get_User().Privilege << std::endl;
                if (get_User().Privilege < 7) throw 0;
                if (!check_ID(st1)) throw 0;
                Store.User_password_change(UserID, st1);
            }
            else {
                string st2 = a.get_string();
                if (a.length()) throw 0;
                if (!check_ID(st2)) throw 0;
                Store.User_password_change(UserID, st1, st2);
            }
        }

        void create_account(READ &a) {
            if (get_User().Privilege < 3) throw 0;
            if (!a.length()) throw 0;
            string UserID = a.get_string();
            if (!check_ID(UserID)) throw 0;
            if (!a.length()) throw 0;
            string Password = a.get_string();
            if (!check_ID(Password)) throw 0;
            if (!a.length()) throw 0;
            string Privilege_string = a.get_string();
            int Privilege = string_to_int(Privilege_string);
            if (Privilege >= get_User().Privilege) throw 0;
            if (!a.length()) throw 0;
            string Username = a.get_string();
            if (!check_name(Username)) throw 0;
            if (a.length()) throw 0;
            Store.User_create(UserID, Password, Privilege, Username);
        }

        void delete_account(READ &a) {
            if (get_User().Privilege < 7) throw 0;
            if (!a.length()) throw 0;
            string UserID = a.get_string();
            if (a.length()) throw 0;
            User new_User;
            if (!Store.User_get(UserID, new_User)) throw 0;
            for (int i = 0; i < Stack.size(); i++) {
                if (Stack[i].UserID == UserID) throw 0;
            }
            Store.User_delete(UserID);
        }
}Stack;

#endif