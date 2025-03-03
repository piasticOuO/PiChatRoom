#include "../include/Message.hpp"

void divideMessage(const std::string &s, std::function<void(Json)> callback) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == 'O') {
            int j = i + 1, len = 0;
            while (isdigit(s[j])) {
                len = len * 10 + s[j] - '0';
                j ++;
            }
            if (s[j] == 'X') {
                // std::cout << "[DEBUG] " << s.substr(j+1, len) << std::endl;
                Json json = Json::parse(s.substr(j + 1, len));
                callback(json);
            }
            i = j + len;
        } else {
            std::cerr << "[WARN] Incorrect message head" << std::endl;
        }
    }
}