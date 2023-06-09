#include "functions.h"
#include <stack>
#include <cmath>

std::vector<std::string> split(std::string str){
    std::vector<std::string> strings;
    std::istringstream f(str);
    std::string s;
    while (getline(f, s, ' ')) {
        strings.push_back(s);
    }
    return strings;
}

bool replace(std::string &str, const std::string &from, const std::string &to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

std::string getLastDigitShort(std::string str){
    replace(str, "+", " ");
    replace(str, "-", " ");
    replace(str, "/", " ");
    replace(str, "*", " ");
    std::vector<std::string> splitted = split(str);
    return splitted[splitted.size()-1];
}

double getLastDigit(std::string *str){
    *str = str->substr(0, str->length()-1);
    std::vector<std::string> splitted = split(*str);
    *str = "";
    for(int i = 0; i < (int) splitted.size()-1; i++) *str += splitted[i] + " ";
    return atof(splitted[splitted.size()-1].c_str());
}

double calculate(std::string sign, std::string *final_str){
    double result = 0;
    double first = getLastDigit(final_str);
    double second = getLastDigit(final_str);
    result += first;
    if(sign == "+")
        result = second + result;
    else if(sign == "-")
        result = second - result;
    else if(sign == "/")
        result = second / result;
    else if(sign == "*")
        result = second * result;
    if(result == INFINITY || result == -INFINITY)
        *final_str = "Ошибка!";
    return result;
}

std::string clearZero(std::string *final_str){
    (*final_str).erase ( (*final_str).find_last_not_of('0') + 1, std::string::npos );
    (*final_str).erase ( (*final_str).find_last_not_of('.') + 1, std::string::npos );
    return *final_str;
}

std::string reversePolskaFinal(std::string str){
    if(((std::string) "+-/*").find(str[0]) != std::string::npos)
        str = "0" + str;
    bool err = false;
    std::stack<std::string> st_oper;
    std::string final_str = ""; // std::string
    std::string local_num = "";
    int len = str.length();
    double result = 0;
    for(int i = 0; i < len; i++){
        std::string s(1, str[i]);
        std::string ch = s;
        //qDebug() << ch;
        if(((std::string) "+-*/").find(ch) == std::string::npos){
            local_num += ch;
        } else {
            final_str += local_num + " ";
            local_num = "";
            if(st_oper.empty() == false){
                std::string sign = st_oper.top();
                if(((sign == "+" || sign == "-") && (ch == "+" || ch == "-"))
                        || ((sign == "*" || sign == "/") && (ch == "*" || ch == "/"))
                        || ((sign == "*" || sign == "/") && (ch == "+" || ch == "-"))){
                    result = calculate(sign, &final_str);
                    if(result == INFINITY || result == -INFINITY){
                        err = true;
                        break;
                    }
                    final_str += std::to_string(result) + " ";
                    //final_str += sign + " ";
                    st_oper.pop();
                }
            }
            st_oper.push(ch);
        }
    }
    if(!err){
        final_str += local_num + " ";
        while(!st_oper.empty()){
            std::string sign = st_oper.top();
            //final_str += st_oper.top() + " ";
            result = calculate(sign, &final_str);
            if(result == INFINITY || result == -INFINITY){
                err = true;
                break;
            }
            final_str += std::to_string(result) + " ";
            st_oper.pop();
        }
        if(!err){
            final_str = final_str.substr(0, final_str.length()-1);
            final_str = clearZero(&final_str);
        }
    }
    return final_str;
}

std::string choose(struct option option){
    std::string result = "Error";
    if(option.opt == 1)
        result = reversePolskaFinal(option.str);
    else if(option.opt == 2)
        result = getLastDigitShort(option.str);

    return result;
}
