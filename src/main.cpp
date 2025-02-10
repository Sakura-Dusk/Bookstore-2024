#include "read.hpp"
#include "user.hpp"
#include "UserStack.hpp"
#include "BookManager.hpp"

#include<string>
#include<iostream>

int main() {
    while (!std::cin.eof()) {
        try {
            std::string s;
            getline(std::cin, s);
            READ a(s);
            if (!a.length()) continue;

            std::string Type = a.get_string();
            // std::cerr << Type << std::endl;
            if (Type == "exit" || Type == "quit") return 0;
            if (Type == "su") {
                //work about login 登入
                // std::cerr << "Try Login\n";
                Stack.Login(a);
                continue;
            }
            if (Type == "logout") {
                //work about logout 登出
                Stack.Logout(a);
                continue;
            }
            if (Type == "register") {
                //work about register 注册
                Stack.regisiter_account(a);
                continue;
            }
            if (Type == "passwd") {
                //work about change passwork 修改密码
                Stack.change_Password(a);
                continue;
            }
            if (Type == "useradd") {
                //work about build account 创建账户
                Stack.create_account(a);
                continue;
            }
            if (Type == "delete") {
                //work about delete 删除账户
                Stack.delete_account(a);
                continue;
            }
            if (Type == "show") {
                if (!a.length()) {
                    //work about show 检索图书
                    Bookmanager.show_book(a);
                    continue;
                }
                READ b = a;
                std::string Type_more = b.get_string();
                if (Type_more == "finance") {
                    a = b;
                    //work about show finance 财务记录查询

                }
                else {
                    //work about show 检索图书
                    Bookmanager.show_book(a);
                }
                continue;
            }
            if (Type == "buy") {
                //work about buy book 购买图书
                Bookmanager.book_buy(a);
                continue;
            }
            if (Type == "select") {
                //work about select book 选择图书
                Bookmanager.book_select(a);
                continue;
            }
            if (Type == "modify") {
                //work about modify book 修改图书信息
                Bookmanager.book_modify(a);
                continue;
            }
            if (Type == "import") {
                //work about book import 图书进货
                Bookmanager.book_import(a);
                continue;
            }
            
            //this part need to design
            if (Type == "log") {
                //work about log generate 生成日志

                continue;
            }
            if (Type == "report") {
                std::string report_Type = a.get_string();
                if (report_Type == "finance") {
                    //work about report finance 生成财务记录报告指令

                    continue;
                }
                if (report_Type == "employee") {
                    //work about report finance 生成全体员工工作情况报告指令

                    continue;
                }
            }
            throw 0;
        }catch(int) {
            std::cout << "Invalid\n";
        }
    }

    return 0;
}