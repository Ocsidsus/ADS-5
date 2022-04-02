// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priority(char c);

std::string infx2pstfx(std::string inf) {
    std::string post = "";
    TStack<char, 100> stack1;

    for (int i = 0; i < inf.length(); i++) {
        if ((inf[i] >= '0') && (inf[i] <= '9')) {
            if (post != "") {
                if (!((inf[i - 1] >= '0') && (inf[i - 1] <= '9'))) {
                    post += ' ';
                }
            }
        post += inf[i];
        } else {
            int pr = priority(inf[i]);
            if (((pr == 0) || (stack1.isEmpty()) || (pr > priority(stack1.get())))
&& (pr != 1)) {
                stack1.push(inf[i]);
            } else {
                if (pr != 1) {
                    while ((priority(stack1.get()) >= pr) && !(stack1.isEmpty())) {
                        stack1.pop();
                    }
                    stack1.push(inf[i]);

                } else {
                    while (priority(stack1.get())) {
                        post += ' ';
                        post += stack1.get();
                        stack1.pop();
                    }
                    stack1.pop();
                }
            }
        }
    }
    while (!(stack1.isEmpty())) {
        post += ' ';
        post += stack1.get();
        stack1.pop();
    }
    return post;
}

int eval(std::string pref) {

    TStack<int, 100> stack2;
    int count = 0;
    std::string cash = "";

    for (int i = 0; i < pref.length(); i++) {
        if ((pref[i] >= '0') && (pref[i] <= '9')) {
            count = 1;
            cash += pref[i];
        } else {
            if (count == 1) {
                stack2.push(std::stoi(cash));
                count = 0;
                cash = "";
            }
            if (pref[i] != ' ') {
                int a = stack2.get();
                stack2.pop();
                int b = stack2.get();
                stack2.pop();
                switch (pref[i]) {
                case '+':
                    stack2.push(b + a);
                    break;
                case '-':
                    stack2.push(b - a);
                    break;
                case '*':
                    stack2.push(b * a);
                    break;
                case '/':
                    stack2.push(b / a);
                    break;
                }
            }
        }
    }
    return stack2.get();
}

int priority(char c) {
    switch (c) {
    case '(':
        return 0;
    case ')':
        return 1;
    case '+': case '-':
        return 2;
    case '*': case '/':
        return 3;
    default:
        std::cout << "FAILED DETERMINE PRIORITY!" << std::endl;
        return -1;
    }
};
