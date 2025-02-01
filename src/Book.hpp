#ifndef BOOK_HPP
#define BOOK_HPP

class Book {
    private:
        int BookID;
        chars ISBN, BookName, Author, Keyword;
        int Quantity;
        double Price, TotalCost;

    public:
        Book() {
            Quantity = 0; BookID = 0;
            Price = TotalCost = 0;
        }
        BookID(int id) : BookID(id) {
            Quantity = 0;
            Price = TotalCost = 0;
        }
        Book(string &s) {
            ISBN = Chars(s);
            Quantity = 0; BookID = 0;
            Price = TotalCost = 0;
        }
        Book(int id, string &s) : BookID(id) {
            ISBN = Chars(s);
            Quantity = 0; BookID = 0;
            Price = TotalCost = 0;
        }

        bool operator ==(const Book &other) const {
            return BookID == other.BookID;
        }

        bool operator !=(const Book &other) const {
            return !(*this == other);
        }

        bool operator <(const Book &other) const {
            return BookID < other.BookID;
        }

        bool operator <=(const Book &other) const {
            return BookID <= other.BookID;
        }

        bool operator >(const Book &other) const {
            return !(*this <= other);
        }

        bool operator >=(const Book &other) const {
            return !(*this < other);
        }

        std::ostream &operator <<(std::ostream &out, const Book &now) {
            std::cout;
            std::cout << now.ISBN << '\t' << now.BookName << '\t' << now.Author << '\t' << now.Keyword << '\t' << fixed << setprecision(2) << now.Price << '\t' << fixed << setprecision(0) << now.Quantity;
        }
};

//为了检索图书，需要把按所有检索信息排序的结果都存一次

class Book_Sort_by_ISBN {
    private:
        int BookID;
        chars ISBN;
    
    public:
        Book_Sort_by_ISBN() {
            BookID = 0;
        }
        Book_Sort_by_ISBN(int id) : BookID(id) {
        }
        Book_Sort_by_ISBN(string &s) {
            BookID = 0;
            ISBN = Chars(s);
        }
        Book_Sort_by_ISBN(int id, string &s) : BookID(id) {
            ISBN = Chars(s);
        }

        bool operator ==(const Book_Sort_by_ISBN &other) const {
            return BookID == other.BookID;
        }

        bool operator !=(const Book_Sort_by_ISBN &other) const {
            return !(*this == other);
        }

        bool operator <(const Book_Sort_by_ISBN &other) const {
            if (!ISBN[0] && !other.ISBN[0]) return BookID < other.BookID;
            return ISBN < other.iSBN;
        }

        bool operator <=(const Book_Sort_by_ISBN &other) const {
            if (!ISBN[0] && !other.ISBN[0]) return BookID <= other.BookID;
            return ISBN <= other.iSBN;
        }

        bool operator >(const Book_Sort_by_ISBN &other) const {
            return !(*this <= other);
        }

        bool operator >=(const Book_Sort_by_ISBN &other) const {
            return !(*this < other);
        }
};

class Book_Sort_by_BookName {
    private:
        int BookID;
        chars BookName;
    
    public:
        Book_Sort_by_BookName() {
            BookID = 0;
        }
        Book_Sort_by_BookName(int id) : BookID(id) {
        }
        Book_Sort_by_BookName(string &s) {
            BookID = 0;
            BookName = Chars(s);
        }
        Book_Sort_by_BookName(int id, string &s) : BookID(id) {
            BookName = Chars(s);
        }

        bool operator ==(const Book_Sort_by_BookName &other) const {
            return BookID == other.BookID;
        }

        bool operator !=(const Book_Sort_by_BookName &other) const {
            return !(*this == other);
        }

        bool operator <(const Book_Sort_by_BookName &other) const {
            if (!BookName[0] && !other.BookName[0]) return BookID < other.BookID;
            return BookName < other.BookName;
        }

        bool operator <=(const Book_Sort_by_BookName &other) const {
            if (!BookName[0] && !other.BookName[0]) return BookID <= other.BookID;
            return BookName <= other.BookName;
        }

        bool operator >(const Book_Sort_by_BookName &other) const {
            return !(*this <= other);
        }

        bool operator >=(const Book_Sort_by_BookName &other) const {
            return !(*this < other);
        }
};

class Book_Sort_by_Author {
    private:
        int BookID;
        chars Author;
    
    public:
        Book_Sort_by_Author() {
            BookID = 0;
        }
        Book_Sort_by_Author(int id) : BookID(id) {
        }
        Book_Sort_by_Author(string &s) {
            BookID = 0;
            Author = Chars(s);
        }
        Book_Sort_by_Author(int id, string &s) : BookID(id) {
            Author = Chars(s);
        }

        bool operator ==(const Book_Sort_by_Author &other) const {
            return BookID == other.BookID;
        }

        bool operator !=(const Book_Sort_by_Author &other) const {
            return !(*this == other);
        }

        bool operator <(const Book_Sort_by_Author &other) const {
            if (!Author[0] && !other.Author[0]) return BookID < other.BookID;
            return Author < other.Author;
        }

        bool operator <=(const Book_Sort_by_Author &other) const {
            if (!Author[0] && !other.Author[0]) return BookID <= other.BookID;
            return Author <= other.Author;
        }

        bool operator >(const Book_Sort_by_Author &other) const {
            return !(*this <= other);
        }

        bool operator >=(const Book_Sort_by_Author &other) const {
            return !(*this < other);
        }
};

class Book_Sort_by_Keyword {
    private:
        int BookID;
        chars Keyword;
    
    public:
        Book_Sort_by_Keyword() {
            BookID = 0;
        }
        Book_Sort_by_Keyword(int id) : BookID(id) {
        }
        Book_Sort_by_Keyword(string &s) {
            BookID = 0;
            Keyword = Chars(s);
        }
        Book_Sort_by_Keyword(int id, string &s) : BookID(id) {
            Keyword = Chars(s);
        }

        bool operator ==(const Book_Sort_by_Keyword &other) const {
            return BookID == other.BookID;
        }

        bool operator !=(const Book_Sort_by_Keyword &other) const {
            return !(*this == other);
        }

        bool operator <(const Book_Sort_by_Keyword &other) const {
            if (!Author[0] && !other.Author[0]) return BookID < other.BookID;
            return Keyword < other.Keyword;
        }

        bool operator <=(const Book_Sort_by_Keyword &other) const {
            if (!Author[0] && !other.Author[0]) return BookID <= other.BookID;
            return Keyword <= other.Keyword;
        }

        bool operator >(const Book_Sort_by_Keyword &other) const {
            return !(*this <= other);
        }

        bool operator >=(const Book_Sort_by_Keyword &other) const {
            return !(*this < other);
        }
};

#endif