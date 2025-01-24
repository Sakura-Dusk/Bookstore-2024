#ifndef USER_HPP
#define USER_HPP

#include "Chars.hpp"

struct visitor {
    private:
        chars UserID, Password, Username;
        int Privilege;

    public:
        virtual int level() {return 0;} 

        visitor(chars UserID, chars Password, int Privilege, chars Username) : UserID(UserID), Password(Password), Privilege(Privilege), Username(Username) {}

        bool opearator ==(const visitor &other) const {
            return UserID == other.UserID;
        }

        bool operator !=(const visitor &other) const {
            return !(*this == other);
        }

        bool operator <(const visitor &other) const {
            return UserID < other.UserID;
        }

        bool operator <=(const visitor &other) const {
            return UserID <= other.UserID;
        }

        bool operator >(const visitor &other) const {
            return !(*this <= other);
        }

        bool operator >=(const visitor &other) const {
            return !(*this < other);
        }
};

#endif