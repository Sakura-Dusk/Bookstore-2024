#ifndef USERSTORE_HPP
#define USERSTORE_HPP

#include "user.hpp"
#include "Chars.hpp"
#include "FileStore.hpp"

#include<vector>
#include<iostream>

struct UserStore {
    private:
        FileStore <chars, User> List;
        friend class Finance_system;
        friend class BookManager;
        friend class UserStack;

    public:
        UserStore() {
            // std::cerr << "User_data_Init start\n";
            List.Init("User_data");
            User root(Chars("root"), Chars("sjtu"), 7, Chars("root"));
            if (!List.data_find_bool(Chars("root"))) List.data_insert(Chars("root"), root);
        }

        void User_create(string &UserID, string &password, int privilege, string &name) {
            User new_User(UserID, password, privilege, name);
            if (List.data_find_bool(Chars(UserID))) throw 0;
            List.data_insert(Chars(UserID), new_User);
        }

        bool User_get(string &UserID, User &now) {
            // std::cerr << UserID << std::endl;
            std::vector <User> res = List.data_find(Chars(UserID));
            // std::cerr << res.size() << std::endl;
            if (!res.size()) return 0;
            now = res[0];
            return 1;
        }

        void User_delete(string &UserID) {
            User now;
            if (!User_get(UserID, now)) throw 0;
            List.data_delete(UserID, now);
        }

        void User_password_change(string &UserID, string &CurrentPassword, string &NewPassword) {
            User now;
            if (!User_get(UserID, now)) throw 0;
            if (now.Password != Chars(CurrentPassword)) throw 0;
            List.data_delete(Chars(UserID), now);
            now.Password = (chars)NewPassword;
            List.data_insert(Chars(UserID), now);
        }

        void User_password_change(string &UserID, string &NewPassword) {
            User now;
            if (!User_get(UserID, now)) throw 0;
            List.data_delete(UserID, now);
            now.Password = Chars(NewPassword);
            List.data_insert(Chars(UserID), now);
        }
};

#endif