#include "read.hpp"
#inlcude "user.hpp"

#include<iostream>

int main() {
    while (!std::cin.eof()) {
        try {
            string s;
            getline(std::cin, s);
            READ a(s);
            if (!a.length()) continue;

            string type = a.get_string();
            if (type == "exit" || type == "quit") return 0;
            if (type == "su") {
                //work about login 登入

                continue;
            }
            if (type == "logout") {
                //work about logout 登出

                continue;
            }
            if (type == "register") {
                //work about register 注册

                continue;
            }
            if (type == "passwd") {
                //work about change passwork 修改密码

                continue;
            }
            if (type == "useradd") {
                //work about build account 创建账户

                continue;
            }
            if (type == "delete") {
                //work about delete 删除账户
                
                continue;
            }
            if (type == "show") {
                if (!a.length()) throw error;
                READ b = a;
                string type_more = b.get_string();
                if (type_more == "finance") {
                    a = b;
                    //work about show finance 财务记录查询

                }
                else {
                    //work about show 检索图书

                }
                continue;
            }
            if (type == "buy") {
                //work about buy book 购买图书

                continue;
            }
            if (type == "select") {
                //work about select book 选择图书

                continue;
            }
            if (type == "modify") {
                //work about modify book 修改图书信息

                continue;
            }
            if (type == "import") {
                //work about book import 图书进货
                
                continue;
            }
            
            //this part need to design
            if (type == "log") {
                //work about log generate 生成日志

                continue;
            }
            if (type == "report") {
                string report_type = a.get_string();
                if (report_type == "finance") {
                    //work about report finance 生成财务记录报告指令

                    continue;
                }
                if (report_type == "employee") {
                    //work about report finance 生成全体员工工作情况报告指令

                    continue;
                }
            }
        }catch(error) {
            cout << "Invalid\n";
        }
    }

    return 0;
}