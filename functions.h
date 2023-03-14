#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QMainWindow>
#include <QApplication>
#include <stdio.h>
#include <stack>
#include <sstream>
#include <cmath>

std::vector<std::string> split(std::string str);

std::string getLastDigitShort(std::string str);

double getLastDigit(std::string *str);

double calculate(std::string sign, std::string *final_str);

std::string reversePolskaFinal(std::string str);

bool replace(std::string &str, const std::string &from, const std::string &to);

std::string clearZero(std::string *final_str);

#endif // FUNCTIONS_H
