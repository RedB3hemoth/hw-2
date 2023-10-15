#include <iostream>
#include <fstream>
#include <vector>
#include <string>
class user {
public:
    std::string _name;
    std::string _login;
    std::string _pass;
};

class message {
public:
    std::string _text;
    std::string _sender;
    std::string _receiver;
};

// Функция для считывания состояний объектов User и Message из файла
void readStateFromFile(const std::string& user_file, std::vector<user>& users, std::vector<message>& messages) {
    std::ifstream file(user_file);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line == "user") {
            std::string _name;
            std::string _login;
            std::string _pass;

            file >> _name >> _login >> _pass;
            users.emplace_back(_name, _login, _pass);
        }
        else if (line == "message") {
            std::string _text;
            std::string _sender;
            std::string _receiver;

            file >> _text >> _sender, _receiver;
            messages.emplace_back(_text, _sender, _receiver);
        }
    }

    file.close();
}

// Функция для записи состояний объектов User и Message в файл
void writeStateToFile(const std::string& user_file, const std::vector<user>& users, const std::vector<message>& messages) {
    std::ofstream file(user_file);
    if (!file.is_open()) {
        std::cerr << "Failed to open file!" << std::endl;
        return;
    }

    for (const user& user : users) {
        file << "user" << std::endl;
        file << user._name << " " << user._login << user._pass << std::endl;
    }

    for (const message& message : messages) {
        file << "message" << std::endl;
        file << message._text << " " << message._sender << message._receiver << std::endl;
    }

    file.close();
}

int main() {
    std::vector<user> users;
    std::vector<message> messages;

    // Считываем состояния объектов из файла
    readStateFromFile("state.txt", users, messages);

    // Добавляем нового пользователя и сообщение
    users.emplace_back("John Doe", 25);
    messages.emplace_back("Hello, world!", "John Doe");

    // Записываем состояния объектов в файл
    writeStateToFile("state.txt", users, messages);

    return 0;
}