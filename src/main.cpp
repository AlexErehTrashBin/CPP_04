#include "main.h"

#include <cstdint>


// Функция для добавления нового сотрудника
auto addEmployee(Employee** employees, const size_t index) -> void {
    auto* employee = new Employee;

    wcout << "Введите имя сотрудника: ";
    employee->name = getWideCStringFromInput();

    wcout << "Введите пол сотрудника: ";
    employee->gender = getWideCStringFromInput();

    wcout << "Введите возраст сотрудника: ";
    employee->age = getIntFromInput();

    wcout << "Введите адрес проживания сотрудника: ";
    employee->address = getWideCStringFromInput();

    wcout << "Введите номер телефона сотрудника: ";
    employee->phone = getWideCStringFromInput();

    wcout << "Введите название отдела сотрудника: ";
    employee->department = getWideCStringFromInput();

    wcout << "Введите должность сотрудника: ";
    employee->position = getWideCStringFromInput();

    wcout << "Введите стаж сотрудника (в годах): ";
    employee->experience = getIntFromInput();

    wcout << "Введите оклад сотрудника: ";
    employee->salary = getFloatFromInput();

    employees[index] = employee;

    wcout << "Сотрудник успешно добавлен." << endl;
}

// Функция для сохранения данных в файл
auto saveData(Employee** employees, const size_t size) -> void {
    if (wofstream file("employees.csv"); file.is_open()) {
        for (int i = 0; i < size; ++i) {
            constexpr auto separator = L';';
            file << employees[i]->name << separator;
            file << employees[i]->gender << separator;
            file << employees[i]->age << separator;
            file << employees[i]->address << separator;
            file << employees[i]->phone << separator;
            file << employees[i]->department << separator;
            file << employees[i]->position << separator;
            file << employees[i]->experience << separator;
            file << employees[i]->salary << endl;
        }

        file.close();
    }
    else {
        wcout << "Ошибка открытия файла." << endl;
    }
}

// Функция для вывода информации о сотрудниках заданного возраста
auto printEmployeesByAge(Employee** employees, const size_t elements, const int age) -> void {
    for (int i = 0; i < elements; ++i) {
        if (const Employee* employee = employees[i]; employee->age == age) {
            printEmployee(employee);
        }
    }
}

// Функция для вывода информации о сотрудниках заданного возраста
auto printAllEmployees(Employee** employees, const size_t size) -> void {
    wcout << endl;
    for (int i = 0; i < size; ++i) {
        printEmployee(employees[i]);
    }
}

auto printEmployee(const Employee* employee) -> void {
    wcout << "ФИО: " << employee->name << endl;
    wcout << "Пол: " << employee->gender << endl;
    wcout << "Возраст: " << employee->age << endl;
    wcout << "Адрес: " << employee->address << endl;
    wcout << "Телефон: " << employee->phone << endl;
    wcout << "Отдел: " << employee->department << endl;
    wcout << "Должность: " << employee->position << endl;
    wcout << "Стаж: " << employee->experience << " лет" << endl;
    wcout << "Оклад: " << employee->salary << endl;
    wcout << endl;
}

auto getLinesInFile(wifstream* iss) -> size_t {
    const auto prevPos = iss->tellg();
    size_t result = 1;
    wchar_t symbol;
    while (!iss->eof()) {
        iss->get(symbol);
        if (symbol == '\n') result++;
    }
    iss->clear();
    iss->seekg(0, ios::end);
    if (iss->get() == '\n') result--;
    iss->clear();
    iss->seekg(prevPos, ios::beg);
    return result;
}

auto deleteEmployee(Employee** employees, size_t&size) -> void {
    wcout << "Введите ФИО сотрудника для удаления: ";
    const wchar_t* fioToDelete = getWideCStringFromInput();

    int personsCount = 0;
    for (int i = 0; i < size; ++i) {
        if (areStringsEqual(employees[i]->name, fioToDelete)) {
            personsCount++;
        }
    }
    if (personsCount == 0) {
        wcout << "Не было обнаружено человек с таким ФИО" << endl;
        return;
    }
    wcout << "Было обнаружено " << personsCount << " человек(-a) с таким ФИО" << endl << endl;

    const auto indices = new int[personsCount];
    int currentIndex = 0;
    for (int i = 0; i < size; ++i) {
        if (areStringsEqual(employees[i]->name, fioToDelete)) {
            indices[currentIndex] = i;
            currentIndex++;
        }
    }



    for (int i = 0; i < personsCount; ++i) {
        wcout << "--- " << i << " ---" << endl;
        printEmployee(employees[indices[i]]);
    }

    wcout << "Выберите какого сотрудника удалить: ";

    int choice;
    wcin >> choice;

    const int employeeToDeleteIndex = indices[choice];
    int lastPersistingEmployeeIndex = INT64_MAX;
    for (int i = size - 1; i >= 0; --i) {
        if (lastPersistingEmployeeIndex!=employeeToDeleteIndex && employees[i] != nullptr) {
            lastPersistingEmployeeIndex = i;
            break;
        }
    }

    if (lastPersistingEmployeeIndex < 0) {
        return;
    }

    employees[employeeToDeleteIndex] = nullptr;
    employees[employeeToDeleteIndex] = employees[lastPersistingEmployeeIndex];
    size--;

    delete[] indices;
    //free(fioToDelete);
}

bool areStringsEqual(const wchar_t* first, const wchar_t* second) {
    if (first == nullptr || second == nullptr) return false;
    const size_t firstSize = getStringSize(first);
    const size_t secondSize = getStringSize(second);
    if (firstSize != secondSize) return false;
    const size_t size = firstSize;
    for (int i = 0; i < size; ++i) {
        if (first[i] != second[i]) return false;
    }
    return true;
}

int main() {
    size_t elements = 0;
    constexpr size_t maxSize = INT8_MAX;
    auto** employees = new Employee *[maxSize];

    // Загрузка данных из файла (если файл существует)
    wifstream file(L"employees.csv");
    if (file.is_open()) {
        const size_t linesInFile = getLinesInFile(&file);
        employees = new Employee *[linesInFile];
        wstring line;
        int currentLineIndex = 0;
        while (getline(file, line) && elements < maxSize) {
            employees[currentLineIndex] = static_cast<Employee *>(malloc(sizeof(Employee)));
            parseEmployeeFromLine(employees[currentLineIndex], line.data());
            elements++;
            currentLineIndex++;
        }

        file.close();
    }

    int choice;
    do {
        wcout << "Выберите действие:" << endl;
        wcout << "1. Добавить нового сотрудника" << endl;
        wcout << "2. Вывести информацию о сотрудниках заданного возраста" << endl;
        wcout << "3. Вывести информацию о всех сотрудниках" << endl;
        wcout << "4. Удалить сотрудника" << endl;
        wcout << "5. Сохранить в файл" << endl;
        wcout << "6. Выйти" << endl;
        wcout << "Ваш выбор: ";
        cin >> choice;
        wcin.ignore();

        switch (choice) {
            case 1:
                if (elements >= maxSize) {
                    wcout << "Офис не настолько жирный" << endl;
                }
                addEmployee(employees, elements);
                elements++;
                break;
            case 2:
                int age;
                wcout << "Введите возраст для поиска: ";
                wcin >> age;
                printEmployeesByAge(employees, elements, age);
                break;
            case 3:
                printAllEmployees(employees, elements);
                break;
            case 4:
                deleteEmployee(employees, elements);
                break;
            case 5:
                saveData(employees, elements);
                break;
            case 6:
                wcout << "Программа завершена." << endl;
                break;
            default:
                wcout << "Некорректный выбор. Повторите попытку." << endl;
                break;
        }
        wcout << endl;
    } while (choice != 6);
    for (int i = 0; i < elements; ++i) {
        delete employees[i];
    }
    delete[] employees;

    system("pause");
    return 0;
}

auto parseEmployeeFromLine(Employee* employee, wchar_t* line) -> void {
    const wchar_t* separator = new wchar_t[]{';', '\0'};
    constexpr int maxTokens = 9;
    auto** tokens = new wchar_t *[maxTokens];
    int tokenSizes[maxTokens];

    int tokenCount = 0;
    wchar_t* buffer;
    const wchar_t* token = wcstok_s(line, separator, &buffer);
    while (token != nullptr && tokenCount < maxTokens) {
        tokenSizes[tokenCount] = getStringSize(token);
        tokens[tokenCount] = new wchar_t[tokenSizes[tokenCount]];
        //wcsncpy(tokens[tokenCount], token, tokenSizes[tokenCount] + 1);
        wcsncpy_s(tokens[tokenCount], tokenSizes[tokenCount] + 1, token, wcslen(token) + 1);
        tokens[tokenCount][tokenSizes[tokenCount] + 1] = '\0';
        ++tokenCount;
        token = wcstok_s(nullptr, separator, &buffer);
    }

    if (tokenCount == maxTokens) {
        employee->name = new wchar_t[tokenSizes[0] + 1];
        wcsncpy_s(employee->name, tokenSizes[0] + 1, tokens[0], wcslen(tokens[0]) + 1);
        employee->name[tokenSizes[0] + 1] = '\0';

        employee->gender = new wchar_t[tokenSizes[1]];
        wcsncpy_s(employee->gender, tokenSizes[1] + 1, tokens[1], wcslen(tokens[1]) + 1);
        employee->gender[tokenSizes[1] + 1] = '\0';

        employee->age = stoi(tokens[2]);

        employee->address = new wchar_t[tokenSizes[3]];
        wcsncpy_s(employee->address, tokenSizes[3] + 1, tokens[3], wcslen(tokens[3]) + 1);
        employee->address[tokenSizes[3] + 1] = '\0';

        employee->phone = new wchar_t[tokenSizes[4]];
        wcsncpy_s(employee->phone, tokenSizes[4] + 1, tokens[4], wcslen(tokens[4]) + 1);
        employee->phone[tokenSizes[4] + 1] = '\0';

        employee->department = new wchar_t[tokenSizes[5]];
        wcsncpy_s(employee->department, tokenSizes[5] + 1, tokens[5], wcslen(tokens[5]) + 1);
        employee->department[tokenSizes[5] + 1] = '\0';

        employee->position = new wchar_t[tokenSizes[6]];
        wcsncpy_s(employee->position, tokenSizes[6] + 1, tokens[6], wcslen(tokens[6]) + 1);
        employee->position[tokenSizes[6] + 1] = '\0';

        employee->experience = _wtoi(tokens[7]);

        employee->salary = _wtof(tokens[8]);
    }
}

auto getStringSize(const wchar_t* str) -> int {
    int counter = 0;
    while (str[counter] != '\0') counter++;
    return counter;
}
