#include "Array.cpp"
#include <iostream>

void printMenu() {
    std::cout << "Menu:\n"
              << "1. Add Element\n"
              << "2. Add Element at Position\n"
              << "3. Delete Element\n"
              << "4. Show All Elements\n"
              << "5. Sort All Elements\n"
              << "6. Balance Data Structure\n"
              << "7. Save to File\n"
              << "8. Load from File\n"
              << "9. Exit\n"
              << "Enter your choice: ";
}

int main() {
    Array<char*> dataStructure(10, 3);
    int choice;
    int position;
    char filename[65];

    while (true) {
        printMenu();
        std::cin >> choice;

        // Очищаем буфер после ввода числового значения
        std::cin.ignore(1024, '\n');

        switch (choice) {
            case 1:
                dataStructure.AddElem();
                break;
            case 2:
                std::cout << "Enter position: ";
                std::cin >> position;
                dataStructure.AddElem(position);
                break;
            case 3:
                std::cout << "Enter position: ";
                std::cin >> position;
                dataStructure.DelElem(position);
                break;
            case 4:
                dataStructure.ShowAll();
                break;
            case 5:
                dataStructure.SortALL();
                break;
            case 6:
                dataStructure.Balance();
                break;
            case 7:
                std::cout << "Enter filename: ";
                std::cin.getline(filename, sizeof(filename));
                dataStructure.SaveToFile(filename);
                break;
            case 8:
                std::cout << "Enter filename: ";
                std::cin.getline(filename, sizeof(filename));
                dataStructure.LoadFromFile(filename);
                break;
            case 9:
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}