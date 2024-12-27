#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <windows.h>
#include <limits>

#include "PointersArray.h"

void printMenu() {
    std::cout << "\n=== Меню ===\n"
              << "1. Добавить элемент\n"
              << "2. Вставить элемент по позиции\n"
              << "3. Удалить элемент по позиции\n"
              << "4. Показать структуру\n"
              << "5. Сортировать\n"
              << "6. Сбалансировать структуру\n"
              << "7. Сохранить в файл\n"
              << "8. Загрузить из файла\n"
              << "0. Выход\n"
              << "Выберите действие: ";
}

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    
    const int MAX_LIST_SIZE = 3;
    const int ARRAY_LENGTH = 3;
    
    PointersArray<char*> array(MAX_LIST_SIZE, ARRAY_LENGTH);
    int choice;
    
    try {
        do {
            printMenu();
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Неверный ввод. Попробуйте снова.\n";
                continue;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            switch (choice) {
                case 1: {
                    char buffer[100];
                    std::cout << "Введите строку: ";
                    std::cin.getline(buffer, 100);
                    
                    if (strlen(buffer) == 0) {
                        std::cout << "Ошибка: пустая строка\n";
                        break;
                    }
                    
                    if (strchr(buffer, ' ') != nullptr) {
                        std::cout << "Ошибка: строка не должна содержать пробелы\n";
                        break;
                    }
                    
                    char* str = new char[strlen(buffer) + 1];
                    strcpy(str, buffer);
                    
                    try {
                        array.add(str);
                        std::cout << "Элемент добавлен\n";
                    }
                    catch (const std::exception& e) {
                        delete[] str;
                        std::cout << "Ошибка: " << e.what() << "\n";
                    }
                    break;
                }
                case 2: {
                    int list_index, pos;
                    char buffer[100];
                    bool valid_input = false;
                    
                    while (!valid_input) {
                        try {
                            std::cout << "Выберите List index (0-" << ARRAY_LENGTH-1 << "): ";
                            if (!(std::cin >> list_index)) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw std::invalid_argument("введено не число");
                            }

                            if (list_index < 0 || list_index >= ARRAY_LENGTH) {
                                throw std::out_of_range("некорректный индекс списка");
                            }
                            
                            if (!array.can_insert(list_index)) {
                                std::cout << "Ошибка: список " << list_index << " переполнен. Выберите другой список.\n";
                                continue;
                            }
                            
                            int current_size = array.get_list_size(list_index);
                            std::cout << "Выберите позицию в списке (0-" << current_size << "): ";
                            if (!(std::cin >> pos)) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw std::invalid_argument("введено не число");
                            }
                            
                            if (pos < 0 || pos > current_size) {
                                throw std::out_of_range("некорректная позиция");
                            }
                            
                            std::cout << "Введите строку: ";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.getline(buffer, 100);
                            
                            if (strlen(buffer) == 0) {
                                throw std::invalid_argument("пустая строка");
                            }
                            
                            if (strchr(buffer, ' ') != nullptr) {
                                throw std::invalid_argument("строка не должна содержать пробелы");
                            }
                            
                            char* str = new char[strlen(buffer) + 1];
                            strcpy(str, buffer);
                            
                            try {
                                array.insert(list_index, pos, str);
                                std::cout << "Элемент вставлен\n";
                                valid_input = true;
                            }
                            catch (const std::exception& e) {
                                delete[] str;
                                throw;
                            }
                        }
                        catch (const std::exception& e) {
                            std::cout << "Ошибка: " << e.what() << ". Повторите ввод.\n";
                        }
                    }
                    break;
                }
                case 3: {
                    int list_index, pos;
                    bool valid_input = false;
                    
                    while (!valid_input) {
                        try {
                            std::cout << "Выберите List index (0-" << ARRAY_LENGTH-1 << "): ";
                            if (!(std::cin >> list_index)) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw std::invalid_argument("введено не число");
                            }

                            if (list_index < 0 || list_index >= ARRAY_LENGTH) {
                                throw std::out_of_range("некорректный индекс списка");
                            }
                            
                            int current_size = array.get_list_size(list_index);
                            if (current_size == 0) {
                                std::cout << "Ошибка: список пуст\n";
                                continue;
                            }
                            
                            std::cout << "Выберите позицию в списке (0-" << current_size-1 << "): ";
                            if (!(std::cin >> pos)) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                throw std::invalid_argument("введено не число");
                            }
                            
                            if (pos < 0 || pos >= current_size) {
                                throw std::out_of_range("некорректная позиция");
                            }
                            
                            array.remove(list_index, pos);
                            std::cout << "Элемент удален\n";
                            valid_input = true;
                        }
                        catch (const std::invalid_argument& e) {
                            std::cout << "Ошибка: " << e.what() << ". Повторите ввод.\n";
                        }
                        catch (const std::out_of_range& e) {
                            std::cout << "Ошибка: " << e.what() << ". Повторите ввод.\n";
                        }
                        catch (const std::exception& e) {
                            std::cout << "Ошибка: " << e.what() << ". Повторите ввод.\n";
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    break;
                }
                case 4: {
                    std::cout << "Структура данных:\n";
                    array.display();
                    break;
                }
                case 5: {
                    array.sort();
                    std::cout << "Структура отсортирована\n";
                    break;
                }
                case 6: {
                    array.balance();
                    std::cout << "Структура сбалансирована\n";
                    break;
                }
                case 7: {
                    array.save("data.bin");
                    std::cout << "Данные сохранены в файл\n";
                    break;
                }
                case 8: {
                    array.load("data.bin");
                    std::cout << "Данные загружены из файла\n";
                    break;
                }
                case 0:
                    std::cout << "Программа завершена\n";
                    break;
                default:
                    std::cout << "Неверный выбор\n";
            }
        } while (choice != 0);
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
