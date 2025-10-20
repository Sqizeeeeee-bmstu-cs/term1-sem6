#include "helpers.h"


int main() {
    int choice;
    std::cout << "Выберите программу для запуска:\n";
    std::cout << "1 - Task1 (HTML валидация)\n";
    std::cout << "2 - Task2 (Парсинг строки в очередь)\n";
    std::cout << "3 - Task3 (LRU-кэш)\n";
    std::cout << "5 - Task5 (Граф коммитов)\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    std::cin.ignore();
    
    switch (choice) {
        case 1: {
            std::string s;
            std::cout << "Введите HTML строку (или нажмите Enter для использования по умолчанию): ";
            std::getline(std::cin, s);
            if (s.empty()) {
                s = "<div> </div> <p> </p>";
            }
            
            try {
                bool res = task1(s);
                std::cout << std::boolalpha << "Результат: " << res << "\n";
            }
            catch (const std::exception& e) {
                std::cout << "false " << "Ошибка: " << e.what() << std::endl;
            }
            break;
        }
        
        case 2: {
            std::string s;
            std::cout << "Введите строку для парсинга (или нажмите Enter для использования по умолчанию): ";
            std::getline(std::cin, s);
            if (s.empty()) {
                s = "Login Task1 Task2 LogOut";
            }
            task2(s);
            break;
        }
        
        case 3: {
            std::string s;
            std::cout << "Введите последовательность для LRU-кэша (или нажмите Enter для использования по умолчанию): ";
            std::getline(std::cin, s);
            if (s.empty()) {
                s = "A B C A D";
            }
            task3(s);
            break;
        }
        
        case 5: {
            std::cout << "Запуск Task5 (Граф коммитов)\n";
            task5();
            break;
        }
        
        default:
            std::cout << "Неверный выбор!\n";
            break;
    }
    
    return 0;
}