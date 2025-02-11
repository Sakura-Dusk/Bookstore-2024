#ifndef USER_HPP
#define USER_HPP

#include "Chars.hpp"

class User {
    private:
        chars UserID, Password, Username;
        int Privilege, select_book = -1;
        friend class UserStore;
        friend class UserStack;
        friend class BookManager;
        friend class Finance_system;

    public:
        User(){Privilege = 0;}
        User(chars UserID, chars Password, int Privilege, chars Username) : UserID(UserID), Password(Password), Privilege(Privilege), Username(Username) {}

        bool operator ==(const User &other) const {
            return UserID == other.UserID;
        }

        bool operator !=(const User &other) const {
            return !(*this == other);
        }

        bool operator <(const User &other) const {
            return UserID < other.UserID;
        }

        bool operator <=(const User &other) const {
            return UserID <= other.UserID;
        }

        bool operator >(const User &other) const {
            return !(*this <= other);
        }

        bool operator >=(const User &other) const {
            return !(*this < other);
        }
};

#endif