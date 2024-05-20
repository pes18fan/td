#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

struct Todo {
    std::string name;
    bool done;

    Todo(std::string n, bool d) : name(n), done(d) {}
};

class TodoList {
  private:
    std::string file_location = "./todo.txt";

    void add(std::string& todo) {
        std::ofstream file(file_location, std::ios::out | std::ios::app);
        todos.push_back(Todo(todo, false));

        for (auto& t : todos) {
            file << t.name << " "
                 << "false"
                 << "\n";
        }

        file.close();
    }

    void done(std::string& todo) {
        std::ofstream file(file_location, std::ios::out);

        for (auto& t : todos) {
            if (!t.done) {
                file << t.name << " "
                     << "true"
                     << "\n";
            } else {
                file << t.name << " "
                     << "false"
                     << "\n";
            }
        }

        file.close();
    }

  public:
    std::vector<Todo> todos;

    TodoList() : todos(std::vector<Todo>()) {
        std::ifstream file(file_location, std::ios::in | std::ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open todo file");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);

            std::string name;
            bool done;
            iss >> name >> done;
            todos.push_back(Todo(name, done));
        }

        file.close();
    }

    void handle_command(std::string& command, std::string& arg) {
        if (command == "add") {
            add(arg);
        } else if (command == "done") {
            done(arg);
        } else {
            throw std::invalid_argument("No command " + command + " exists.");
        }
    }

    void list() {
        if (todos.empty()) {
            std::cout << "No todos.\n";
            return;
        }

        int i = 1;
        for (auto& todo : todos) {
            std::cout << i << ": " << todo.name << ", "
                      << (todo.done ? "\x1b[32mdone\x1b[0m"
                                    : "\x1b[31mnot done\x1b[0m")
                      << "\n";
        }
    }
};

void print_help() {
    std::cout << "todo version \x1b[32m0.0.1\x1b[0m\n";
    std::cout << "Simple todo app.\n\n";

    std::cout << "\x1b[32mUsage:\x1b[0m\n";
    std::cout << "  todo add <task> : add new task\n";
    std::cout << "  todo done <task> : mark task as done\n";
    std::cout << "  todo list : list all tasks\n";
    std::cout << "  todo help : show this help\n";
    std::cout << "  todo version : show version\n";
}

int main(int argc, const char** argv) {
    try {
        TodoList todo;

        if (argc == 1) {
            todo.list();
        } else if (argc == 2) {
            if (std::string(argv[1]) == "version") {
                std::cout << "todo version \x1b[32m0.0.1\x1b[0m\n";
                std::cout << "Written with <3 by pes18fan\n";
            } else if (std::string(argv[1]) == "help") {
                print_help();
            } else {
                throw std::invalid_argument(
                    "You need to provide an argument for the command!");
            }
        } else {
            std::string command = argv[1];
            std::string arg = argv[2];
            todo.handle_command(command, arg);
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }

    return 0;
}
