#include "Array.cpp"
#include <iostream>


void printMenu() {
    std::cout << "Menu:\n"
              << "1. Add Element\n"                     // AddElem()
              << "2. Add Element at Position\n"         // AddElem(position)
              << "3. Delete Element\n"                  // DelElem(position)
              << "4. Show All Elements\n"               // ShowAll()
              << "5. Sort All Elements\n"               // SortALL()
              << "6. Balance Data Structure\n"          // Balance()
              << "7. Save to File\n"                    // SaveToFile()
              << "8. Load from File\n"                  // LoadFromFile()
              << "9. Add to Array Index\n"              // AddToArrayIndex()
              << "10. Add to List Node\n"               // AddToListNode()
              << "11. Add Single Element at Position\n" // AddElementAtPosition()
              << "12. Show Total Elements\n"            // CountTotalElements()
              << "13. Resize Array\n"                   // ResizeArray()
              << "14. Delete Elements Range\n"          // DelElemRange()
              << "15. Exit\n"
              << "Enter your choice: ";
}

int main() {
    Array<char*> dataStructure(10, 3);
    int choice;
    int position;
    int arrayIndex;
    int nodeIndex;
    int startPos;
    int endPos;
    char filename[65];
    char element[100];

    while (true) {
        printMenu();
        std::cin >> choice;
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
                std::cout << "Enter array index: ";
                std::cin >> arrayIndex;
                std::cout << "Enter node index: ";
                std::cin >> nodeIndex;
                std::cout << "Enter position: ";
                std::cin >> position;
                dataStructure.DelElem(arrayIndex, nodeIndex, position);
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
                std::cout << "Enter array index: ";
                std::cin >> arrayIndex;
                dataStructure.AddToArrayIndex(arrayIndex);
                break;
                
            case 10:
                std::cout << "Enter array index: ";
                std::cin >> arrayIndex;
                std::cout << "Enter node index: ";
                std::cin >> nodeIndex;
                dataStructure.AddToListNode(arrayIndex, nodeIndex);
                break;
                
            case 11:
                std::cout << "Enter array index: ";
                std::cin >> arrayIndex;
                std::cout << "Enter node index: ";
                std::cin >> nodeIndex;
                std::cout << "Enter position: ";
                std::cin >> position;
                std::cout << "Enter element: ";
                std::cin >> element;
                dataStructure.AddElementAtPosition(element, arrayIndex, nodeIndex, position);
                break;
                
            case 12:
                std::cout << "Total elements: " << dataStructure.CountTotalElements() << "\n";
                break;
                
            case 13:
                std::cout << "Enter new size: ";
                std::cin >> position;
                if (!dataStructure.ResizeArray(position)) {
                    std::cout << "Failed to resize array\n";
                }
                break;
                
            case 14:
                std::cout << "Enter array index: ";
                std::cin >> arrayIndex;
                std::cout << "Enter node index: ";
                std::cin >> nodeIndex;
                std::cout << "Enter start position: ";
                std::cin >> startPos;
                std::cout << "Enter end position: ";
                std::cin >> endPos;
                if (startPos > endPos) {
                    std::cout << "Start position cannot be greater than end position" << std::endl;
                    break;
                }
                dataStructure.DelElemRange(arrayIndex, nodeIndex, startPos, endPos);
                break;
                
            case 15:
                return 0;
                
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
}