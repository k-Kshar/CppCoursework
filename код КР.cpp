#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <map>
using namespace std;

class Human {// Базовый класс "Человек"
public:
    virtual void Set_name(const string& name) = 0;
    virtual string Get_name() const = 0;

    virtual void Set_surname(const string& surname) = 0;
    virtual string Get_surname() const = 0;

    virtual void Set_patronymic(const string& patronymic) = 0;
    virtual string Get_patronymic() const = 0;

    virtual void Set_salary(int salary) = 0;
    virtual int Get_salary() const = 0;

    virtual void display() const = 0; // Виртуальный метод для отображения информации
    virtual ~Human() = default;
};


// Класс Директор
class Director : public Human {
private:
    string firstName, lastName, patronymic;
    int salary;
    map<string, double> employees;
    bool hasAccountant = false;
    bool hasSecretary = false;

public:
    Director(const string& fn, const string& ln, const string& pt, int sal)
        : firstName(fn), lastName(ln), patronymic(pt), salary(sal) {
        if (sal <= 0) throw invalid_argument("Некорректная зарплата.");
    }

    void Set_name(const string& name) override { firstName = name; }
    string Get_name() const override { return firstName; }

    void Set_surname(const string& surname) override { lastName = surname; }
    string Get_surname() const override { return lastName; }

    void Set_patronymic(const string& patronymic) override { this->patronymic = patronymic; }
    string Get_patronymic() const override { return patronymic; }

    void Set_salary(int salary) override {
        if (salary <= 0) throw invalid_argument("Некорректная зарплата.");
        this->salary = salary;
    }
    int Get_salary() const override { return salary; }

    void addEmployee(const string& empName, double empSalary, const string& role) {
        if (empName.empty() || empSalary <= 0)
            throw invalid_argument("Некорректные данные сотрудника.");

        if (role == "Бухгалтер" && hasAccountant) {
            throw invalid_argument("У директора уже есть бухгалтер.");
        }
        else if (role == "Секретарь" && hasSecretary) {
            throw invalid_argument("У директора уже есть секретарь.");
        }
        employees[empName] = empSalary;

        if (role == "Бухгалтер") hasAccountant = true;
        else if (role == "Секретарь") hasSecretary = true;
    }

    void removeEmployee(const string& empName) {
        auto it = employees.find(empName);
        if (it == employees.end())
            throw invalid_argument("Сотрудник не найден.");
        employees.erase(it);
    }

    void display() const override {
        cout << "Директор: " << Get_name() << " " << Get_surname() << " " << Get_patronymic() << ", Ставка: " << Get_salary() << endl;
        if (!employees.empty()) {
            cout << "Сотрудники под руководством:\n";

            for (const auto& emp : employees) {
                cout << " - " << emp.first << ", Ставка: " << emp.second << endl;
            }
        }
    }

    bool hasAllRequiredEmployees() const {
        return hasAccountant;
    }
};

// Класс Бухгалтер
class Accountant : public Human {
private:
    string firstName, lastName, patronymic;
    int salary;
    double salaryDirector;
    double salaryAccountant;
    double salarySecretary;
    double salarySysAdmin;
    double salaryProgrammer;
public:
    Accountant(string fn, string ln, string pt, double sal,
        double salD, double salA, double salS, double salSA, double salP)
        : firstName(fn), lastName(ln), patronymic(pt), salary(sal), salaryDirector(salD), salaryAccountant(salA),
        salarySecretary(salS), salarySysAdmin(salSA), salaryProgrammer(salP) {
        if (salD <= 0 || salA <= 0 || salS <= 0 || salSA <= 0 || salP <= 0) {
            throw invalid_argument("Некорректные оклады для должностей.");
        }
    }

    void Set_name(const string& name) override { firstName = name; }
    string Get_name() const override { return firstName; }

    void Set_surname(const string& surname) override { lastName = surname; }
    string Get_surname() const override { return lastName; }

    void Set_patronymic(const string& patronymic) override { this->patronymic = patronymic; }
    string Get_patronymic() const override { return patronymic; }

    void Set_salary(int salary) override {
        if (salary <= 0) throw invalid_argument("Некорректная зарплата.");
        this->salary = salary;
    }
    int Get_salary() const override { return salary; }

    double calculateSalary(double baseSalary, double* rate) const {
        if (baseSalary <= 0 || rate == nullptr)
            throw invalid_argument("Некорректная ставка или оклад.");
        return baseSalary * (*rate);
    }

    void display() const override {
        cout << "Бухгалтер: " << Get_name() << " " << Get_surname() << " " << Get_patronymic() << ", Ставка: " << Get_salary() << endl;
        cout << "Оклады всех должностей: Директор - " << salaryDirector
            << ", Бухгалтер - " << salaryAccountant
            << ", Секретарь - " << salarySecretary
            << ", Системный администратор - " << salarySysAdmin
            << ", Программист - " << salaryProgrammer << endl;
    }


    double getSalaryForPosition(const string& position) const {
        if (position == "Director") return salaryDirector;
        else if (position == "Accountant") return salaryAccountant;
        else if (position == "Secretary") return salarySecretary;
        else if (position == "SysAdmin") return salarySysAdmin;
        else if (position == "Programmer") return salaryProgrammer;
        throw invalid_argument("Некорректная профессия.");
    }
};

// Класс Секретарь
class Secretary : public Human {
private: 
    string firstName, lastName, patronymic;
    int salary;
public:
    Secretary(const string& fn, const string& ln, const string& pt, int sal)
        : firstName(fn), lastName(ln), patronymic(pt), salary(sal) {
        if (sal <= 0) throw invalid_argument("Некорректная зарплата.");
    }

    void Set_name(const string& name) override { firstName = name; }
    string Get_name() const override { return firstName; }

    void Set_surname(const string& surname) override { lastName = surname; }
    string Get_surname() const override { return lastName; }

    void Set_patronymic(const string& patronymic) override { this->patronymic = patronymic; }
    string Get_patronymic() const override { return patronymic; }

    void Set_salary(int salary) override {
        if (salary <= 0) throw invalid_argument("Некорректная зарплата.");
        this->salary = salary;
    }
    int Get_salary() const override { return salary; }

    void display() const override {
        cout << "Секретарь: " << Get_name() << " " << Get_patronymic() << " " << Get_surname()
            << ", Ставка: " << Get_salary() << "\n";
    }
};

// Класс Системный администратор
class SysAdmin : public Human {
private:
    vector<string> equipment;
    string firstName, lastName, patronymic;
    int salary;

public:
    SysAdmin(const string& fn, const string& ln, const string& pt, int sal)
        : firstName(fn), lastName(ln), patronymic(pt), salary(sal) {
        if (sal <= 0) throw invalid_argument("Некорректная зарплата.");
    }

    void Set_name(const string& name) override { firstName = name; }
    string Get_name() const override { return firstName; }

    void Set_surname(const string& surname) override { lastName = surname; }
    string Get_surname() const override { return lastName; }

    void Set_patronymic(const string& patronymic) override { this->patronymic = patronymic; }
    string Get_patronymic() const override { return patronymic; }

    void Set_salary(int salary) override {
        if (salary <= 0) throw invalid_argument("Некорректная зарплата.");
        this->salary = salary;
    }
    int Get_salary() const override { return salary; }

    void addEquipment(const string& eq) {
        if (eq.empty())
            throw invalid_argument("Некорректное оборудование.");
        equipment.push_back(eq);
    }

    void clearEquipment() {
        equipment.clear();
    }


    void displayEquipment() const {
        cout << "Оборудование:\n";
        for (const auto& eq : equipment) {
            cout << " - " << eq << endl;
        }
    }

    void display() const override {
        cout << "Системный администратор: " << Get_name() << " " << Get_patronymic() << " " << Get_surname()
            << ", Ставка: " << Get_salary() << "\n";
        displayEquipment();
    }
};

// Класс Программист
class Programmer : public Human {
private:
    string level;
    vector<string> technologies;
    string firstName, lastName, patronymic;
    int salary;

public:
    Programmer(const string& fn, const string& ln, const string& pt, double sal, string lvl)
        : firstName(fn), lastName(ln), patronymic(pt), salary(sal), level(lvl) {
        if (sal <= 0) throw invalid_argument("Некорректная зарплата.");
    }

    void Set_name(const string& name) override { firstName = name; }
    string Get_name() const override { return firstName; }

    void Set_surname(const string& surname) override { lastName = surname; }
    string Get_surname() const override { return lastName; }

    void Set_patronymic(const string& patronymic) override { this->patronymic = patronymic; }
    string Get_patronymic() const override { return patronymic; }

    void Set_salary(int salary) override {
        if (salary <= 0) throw invalid_argument("Некорректная зарплата.");
        this->salary = salary;
    }
    int Get_salary() const override { return salary; }

    void addTechnology(const string& tech) {
        if (tech.empty())
            throw invalid_argument("Некорректная технология.");
        technologies.push_back(tech);
    }

    void displayTechnologies() const {
        cout << "Технологии:\n";
        for (const auto& tech : technologies) {
            cout << " - " << tech << endl;
        }
    }
    void clearTechnologies() {
        technologies.clear();
    }

    void Set_level(const string& newLevel) {
        if (newLevel == "Junior" || newLevel == "Middle" ||
            newLevel == "Senior" || newLevel == "Lead") {
            level = newLevel;
        }
        else {
            throw invalid_argument("Некорректный уровень программиста.");
        }
    }

    void display() const override {
        cout << "Программист: " << Get_name() << " " << Get_patronymic() << " " << Get_surname() << ", Уровень: " << level
            << ", Ставка: " << Get_salary() << "\n";
        displayTechnologies();
    }
};

// Класс для управления сотрудниками
class EmployeeManager {
private:
    vector<Human*> employees;
    Accountant* findAccountant() const {
        for (auto emp : employees) {
            if (auto accountant = dynamic_cast<Accountant*>(emp)) {
                return accountant;
            }
        }
        return nullptr;
    }
    vector<Director*> directors; // список директоров

public:


    void hireEmployee(Human* employee) {
        employees.push_back(employee);
        if (Director* director = dynamic_cast<Director*>(employee)) { // Если сотрудник - директор, добавляем его в список директоров

            directors.push_back(director);
        }
    }

    Director* chooseDirector() {//функция для выбора директора
        if (directors.empty()) {
            cout << "Директоров еще нет. Добавьте хотя бы одного директора.\n";
            return nullptr;
        }

        cout << "Выберите директора:\n";
        for (size_t i = 0; i < directors.size(); ++i) {
            cout << i + 1 << ". ";
            directors[i]->display();
        }
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > directors.size()) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        return directors[choice - 1];
    }


    void displayAllEmployees() const {
        cout << "Список сотрудников:\n";
        Accountant* accountant = findAccountant();
        if (!accountant) {
            cout << "Бухгалтер не найден. Невозможно рассчитать зарплаты.\n";
            return;
        }

        int numsotr = 0;
        for (const auto& emp : employees) {
            cout << "#" << ++numsotr << " ";
            emp->display();

            // Рассчитываем зарплату в зависимости от типа сотрудника
            double salary = 0.0;
            if (dynamic_cast<Director*>(emp)) {
                salary = emp->Get_salary() * accountant->getSalaryForPosition("Director");
            }
            else if (dynamic_cast<Accountant*>(emp)) {
                salary = emp->Get_salary() * accountant->getSalaryForPosition("Accountant");
            }
            else if (dynamic_cast<Secretary*>(emp)) {
                salary = emp->Get_salary() * accountant->getSalaryForPosition("Secretary");
            }
            else if (dynamic_cast<SysAdmin*>(emp)) {
                salary = emp->Get_salary() * accountant->getSalaryForPosition("SysAdmin");
            }
            else if (dynamic_cast<Programmer*>(emp)) {
                salary = emp->Get_salary() * accountant->getSalaryForPosition("Programmer");
            }

            cout << "Полная зарплата: " << salary << endl;
        }
        if (numsotr == 0) cout << "Сотрудников ещё нет. Добавьте несколько.\n";
    }


    void removeEmployee(int index, string f) {
        if (index < 0 || index >= employees.size()) {
            cout << "Неверный индекс. Сотрудник не найден.\n";
            return;
        }
        delete employees[index];
        employees.erase(employees.begin() + index);
        cout << f << " был удален\n";
    }

    bool displayEmployeesByProfession(const string& profession) const {
        bool found = false;
        cout << "Список сотрудников профессии " << profession << ":\n";
        for (size_t i = 0; i < employees.size(); ++i) {
            if ((profession == "Director" && dynamic_cast<Director*>(employees[i])) ||
                (profession == "Accountant" && dynamic_cast<Accountant*>(employees[i])) ||
                (profession == "Secretary" && dynamic_cast<Secretary*>(employees[i])) ||
                (profession == "SysAdmin" && dynamic_cast<SysAdmin*>(employees[i])) ||
                (profession == "Programmer" && dynamic_cast<Programmer*>(employees[i]))) {
                cout << i + 1 << ". ";
                employees[i]->display();
                found = true;
            }
        }
        if (!found) {
            cout << "Сотрудников данной профессии не найдено.\n";

        }
        return found;
    }

    int getEmployeeCount() const {
        return employees.size();
    }

    Human* getEmployee(int index) {
        if (index < 0 || index >= employees.size()) {
            throw invalid_argument("Неверный индекс.");
        }
        return employees[index];
    }


    ~EmployeeManager() {
        for (auto& emp : employees) {
            delete emp;
        }
    }
};

void employeeSubMenu(EmployeeManager& manager, int choice) {
    string firstName, lastName, patronymic;
    double salary;
    int levelChoice;
    string level;

    // Переменные для ставок вынесены за блок switch
    double salD, salA, salS, salSA, salP;

    Director* chosenDirector = nullptr;
    if (choice != 1) { // Если сотрудник не является директором, предложить выбрать директора
        chosenDirector = manager.chooseDirector();
        if (!chosenDirector) return; // Прекратить выполнение, если директора нет
    }

    switch (choice) {
    case 1: {
        cout << "Введите имя, фамилию и отчество директора:\n";
        cin >> firstName >> lastName >> patronymic;
        cout << "Введите ставку директора:\n";
        while (!(cin >> salary) || salary < 1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        manager.hireEmployee(new Director(firstName, lastName, patronymic, salary));
        break;
    }
    case 2: {
        cout << "Введите имя, фамилию и отчество бухгалтера:\n";
        cin >> firstName >> lastName >> patronymic;
        cout << "Введите ставку бухгалтера:\n";
        while (!(cin >> salary) || salary < 1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        // Ввод ставок для различных должностей
        double salD, salA, salS, salSA, salP;

        cout << "Введите оклад для директора: ";
        while (!(cin >> salD) || salD < 0.1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Введите оклад для бухгалтера: ";
        while (!(cin >> salA) || salA < 0.1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Введите оклад для секретаря: ";
        while (!(cin >> salS) || salS < 0.1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Введите оклад для системного администратора: ";
        while (!(cin >> salSA) || salSA < 0.1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Введите оклад для программиста: ";
        while (!(cin >> salP) || salP < 0.1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }

        // Создаем объект бухгалтера с введенными данными
        manager.hireEmployee(new Accountant(firstName, lastName, patronymic, salary, salD, salary, salS, salSA, salP));
        chosenDirector->addEmployee(firstName + " " + patronymic + " " + lastName, salary, "Бухгалтер");
        break;
    }
    case 3: {
        cout << "Введите имя, фамилию и отчество секретаря:\n";
        cin >> firstName >> lastName >> patronymic;
        cout << "Введите ставку секретаря:\n";
        while (!(cin >> salary) || salary < 1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        manager.hireEmployee(new Secretary(firstName, lastName, patronymic, salary));
        chosenDirector->addEmployee(firstName + " " + patronymic + " " + lastName, salary, "Секретарь");
        break;
    }
    case 4: {
        cout << "Введите имя, фамилию и отчество системного администратора:\n";
        cin >> firstName >> lastName >> patronymic;
        cout << "Введите ставку системного администратора:\n";
        while (!(cin >> salary) || salary < 1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        SysAdmin* sysadmin = new SysAdmin(firstName, lastName, patronymic, salary);

        // Ввод оборудования
        cout << "Введите количество оборудования:\n";
        int kolobor;
        cin >> kolobor;
        string obor;
        for (int i = 0; i < kolobor; i++) {
            cin >> obor;
            sysadmin->addEquipment(obor);

        }
        manager.hireEmployee(sysadmin);
        chosenDirector->addEmployee(firstName + " " + patronymic + " " + lastName, salary, "Системный администратор");
        break;
    }
    case 5: {
        cout << "Введите имя, фамилию и отчество программиста:\n";
        cin >> firstName >> lastName >> patronymic;
        cout << "Введите ставку программиста:\n";
        while (!(cin >> salary) || salary < 1) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Выберите уровень программиста:\n";
        cout << "1. Junior\n2. Middle\n3. Senior\n4. Lead\n";
        while (!(cin >> levelChoice) || levelChoice < 1 || levelChoice > 4) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        switch (levelChoice) {
        case 1: level = "Junior"; break;
        case 2: level = "Middle"; break;
        case 3: level = "Senior"; break;
        case 4: level = "Lead"; break;
        }

        // Создаем объект программиста
        Programmer* programmer = new Programmer(firstName, lastName, patronymic, salary, level);

        // Ввод технологий
        cout << "Введите количество технологий:\n";
        int koltech;
        cin >> koltech;
        string tech;
        for (int i = 0; i < koltech; i++) {
            cin >> tech;
            programmer->addTechnology(tech);

        }
        manager.hireEmployee(programmer);
        chosenDirector->addEmployee(firstName + " " + patronymic + " " + lastName, salary, "Программист");
        break;
    }
    default:
        cout << "Некорректный выбор.\n";
    }
}


void mainMenu(EmployeeManager& manager) {
    int option;
    while (true) {
        cout << "\nГлавное меню: \n";
        cout << "1. Нанять нового сотрудника\n";
        cout << "2. Уволить сотрудника\n";
        cout << "3. Изменить данные сотрудника\n";
        cout << "4. Показать всех сотрудников\n";
        cout << "5. Выход\n";
        cout << "Выберите опцию: ";
        while (!(cin >> option) || option < 1 || option > 5) {
            cout << "Некорректный выбор. Попробуйте еще раз: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        //if (option == 5) break;
        cout << endl;

        switch (option) {
        case 1: {
            cout << "Выберите профессию сотрудника:\n";
            cout << "1. Директор\n2. Бухгалтер\n3. Секретарь\n4. Системный администратор\n5. Программист\n";
            int professionChoice;
            while (!(cin >> professionChoice) || professionChoice < 1 || professionChoice > 5) {
                cout << "Некорректный выбор. Попробуйте еще раз: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            employeeSubMenu(manager, professionChoice);
            break;
        }
        case 2: {
            cout << "Выберите профессию сотрудника для увольнения:\n";
            cout << "1. Директор\n2. Бухгалтер\n3. Секретарь\n4. Системный администратор\n5. Программист\n";
            int professionChoice;
            while (!(cin >> professionChoice) || professionChoice < 1 || professionChoice > 5) {
                cout << "Некорректный выбор. Попробуйте еще раз: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            string profession;
            switch (professionChoice) {
            case 1: profession = "Director"; break;
            case 2: profession = "Accountant"; break;
            case 3: profession = "Secretary"; break;
            case 4: profession = "SysAdmin"; break;
            case 5: profession = "Programmer"; break;
            default: cout << "Некорректный выбор.\n"; continue; // Если некорректный выбор, возвращаемся в главное меню
            }

            // Показываем сотрудников по выбранной профессии
            if(manager.displayEmployeesByProfession(profession) == true) {
                // Проверяем количество сотрудников
                if (manager.getEmployeeCount() != 0) {
                    cout << "Введите номер сотрудника для удаления:\n";
                    int employeeIndex;
                    cin >> employeeIndex;
                    // Удаляем сотрудника по индексу
                    manager.removeEmployee(employeeIndex - 1, profession); // вычитаем 1, чтобы корректно соотнести с индексом в векторе
                }
                else break;
            }            
            break;
        }

        case 3: {
            cout << "Выберите профессию сотрудника для изменения:\n";
            cout << "1. Директор\n2. Бухгалтер\n3. Секретарь\n4. Системный администратор\n5. Программист\n";
            int professionChoice;
            while (!(cin >> professionChoice) || professionChoice < 1 || professionChoice > 5) {
                cout << "Некорректный выбор. Попробуйте еще раз: ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
            string profession;
            switch (professionChoice) {
            case 1: profession = "Director"; break;
            case 2: profession = "Accountant"; break;
            case 3: profession = "Secretary"; break;
            case 4: profession = "SysAdmin"; break;
            case 5: profession = "Programmer"; break;
            default: cout << "Некорректный выбор.\n"; continue;
            }

            if (manager.displayEmployeesByProfession(profession) == true) { // Проверяем, есть ли сотрудники
                if (manager.getEmployeeCount() != 0) {
                    cout << "Введите номер сотрудника для изменения данных:\n";
                    int employeeIndex;
                    while (!(cin >> employeeIndex) || employeeIndex > manager.getEmployeeCount()) {
                        cout << "Некорректный выбор. Попробуйте еще раз: ";
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }

                    // Получаем указатель на сотрудника
                    Human* employee = manager.getEmployee(employeeIndex - 1);

                    // Изменяем данные сотрудника
                    string newFirstName, newLastName, newPatronymic;
                    cout << "Введите новое имя (оставьте пустым, если не хотите изменять): ";
                    cin.ignore();
                    getline(cin, newFirstName);
                    if (!newFirstName.empty()) employee->Set_name(newFirstName);

                    cout << "Введите новую фамилию (оставьте пустым, если не хотите изменять): ";
                    getline(cin, newLastName);
                    if (!newLastName.empty()) employee->Set_surname(newLastName);

                    cout << "Введите новое отчество (оставьте пустым, если не хотите изменять): ";
                    getline(cin, newPatronymic);
                    if (!newPatronymic.empty()) employee->Set_patronymic(newPatronymic);

                    // Проверка типа сотрудника и изменение специфичных данных
                    if (auto accountant = dynamic_cast<Accountant*>(employee)) {
                        double newSalary;
                        cout << "Введите новую ставку (оставьте 0, если не хотите изменять): ";
                        if (cin >> newSalary && newSalary > 0) {
                            accountant->Set_salary(newSalary);
                        }
                    }
                    else if (auto sysadmin = dynamic_cast<SysAdmin*>(employee)) {
                        cout << "Хотите обновить список оборудования? (да/нет): ";
                        string choice;
                        cin >> choice;
                        if (choice == "да") {
                            sysadmin->clearEquipment(); // Очищаем текущий список
                            cout << "Введите количество нового оборудования: ";
                            int equipmentCount;
                            cin >> equipmentCount;
                            cout << "Введите новое оборудование:\n";
                            for (int i = 0; i < equipmentCount; ++i) {
                                string equipment;
                                cin >> equipment;
                                sysadmin->addEquipment(equipment);
                            }
                        }
                    }
                    else if (auto programmer = dynamic_cast<Programmer*>(employee)) {
                        cout << "Хотите обновить список технологий? (yes/no): ";
                        string choice;
                        cin >> choice;
                        if (choice == "yes") {
                            programmer->clearTechnologies(); // Очищаем текущий список
                            cout << "Введите количество новых технологий: ";
                            int techCount;
                            cin >> techCount;
                            cout << "Введите новые технологии:\n";
                            for (int i = 0; i < techCount; ++i) {
                                string technology;
                                cin >> technology;
                                programmer->addTechnology(technology);
                            }
                        }
                        cout << "Хотите изменить уровень программиста? (да/нет): ";
                        cin >> choice;
                        if (choice == "no") {
                            cout << "Выберите новый уровень:\n1. Junior\n2. Middle\n3. Senior\n4. Lead\n";
                            int levelChoice;
                            cin >> levelChoice;
                            string newLevel;
                            switch (levelChoice) {
                            case 1: newLevel = "Junior"; break;
                            case 2: newLevel = "Middle"; break;
                            case 3: newLevel = "Senior"; break;
                            case 4: newLevel = "Lead"; break;
                            default: cout << "Некорректный выбор.\n"; continue;
                            }
                            programmer->Set_level(newLevel);
                        }
                    }
                    else if (auto secretary = dynamic_cast<Secretary*>(employee)) {
                        double newSalary;
                        cout << "Введите новую ставку секретаря (оставьте 0, если не хотите изменять): ";
                        if (cin >> newSalary && newSalary > 0) {
                            secretary->Set_salary(newSalary);
                        }
                    }
                    else if (auto director = dynamic_cast<Director*>(employee)) {
                        double newSalary;
                        cout << "Введите новую ставку директора (оставьте 0, если не хотите изменять): ";
                        if (cin >> newSalary && newSalary > 0) {
                            director->Set_salary(newSalary);
                        }
                    }

                    cout << "Данные сотрудника успешно обновлены!\n";
                }
            }
            break;
        }

        case 4: {
            manager.displayAllEmployees();
            break;
        }
        case 5: {
            cout << "Выход из программы.\n";
            exit(0); // Завершаем программу
            break;
        }
        }
    }
}

void displayWelcomeMessage() {
    cout << "***************************************************\n";
    cout << "* Добро пожаловать!                               *\n";
    cout << "* Вас приветствует компания \"TechVision\"!         *\n";
    cout << "* Мы создаем инновационные IT-решения,            *\n";
    cout << "* объединяющие команды и технологии.              *\n";
    cout << "*                                                 *\n";
    cout << "* В нашей системе управления персоналом           *\n";
    cout << "* вы можете:                                      *\n";
    cout << "* - Нанимать  и увольнять сотрудников             *\n";
    cout << "* - Изменять их данные                            *\n";
    cout << "* - Просматривать список сотрудников              *\n";
    cout << "*                                                 *\n";
    cout << "* Спасибо, что выбрали нас!                       *\n";
    cout << "***************************************************\n\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    displayWelcomeMessage();

    try {
        EmployeeManager manager;
        mainMenu(manager);
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
    }
    return 0;
}