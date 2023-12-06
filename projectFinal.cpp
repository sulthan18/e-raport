#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
using namespace std;

COORD coordinate;
void gotoxy(int x,int y){
    coordinate.X=x; coordinate.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coordinate);
}
COORD GetCursorPosition() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition;
}

#define backspace 8
#define tab 9
#define enter 13
#define esc 27
#define semicolon 59
#define arrowUP 72
#define arrowDOWN 80
#define arrowRIGHT 77
#define arrowLEFT 75
#define buttonB 66
#define buttonb 98
#define buttonC 67
#define buttonc 99
#define buttonD 68
#define buttond 100
#define buttonE 69
#define buttone 101
#define buttonN 78
#define buttonn 110
#define buttonY 89
#define buttony 121

bool getConfirmation() {
    int c = 0;
    while (true) {
        switch (c = getch()) {
            case esc:
            case buttonN:
            case buttonn:
                return false;
            case buttonY:
            case buttony:
                return true;
        }
    }
}

int menuChange(int x, int min, int max, bool ButtonB = false, bool ButtonC = false, bool ButtonD = false, bool ButtonE = false, bool ESC = false) {
    int index = min;
    int c = 0;

    if (max >= min) {
        gotoxy(x+2,index);
        cout << "\b\b  ";
        gotoxy(x,index);
        cout << "=> ";
    }

    while (true) {
        switch (c = getch()) {
            case esc:
                if (!ESC) break;
                return 0;
            case buttone:
            case buttonE:
                if (!ButtonE) break;
                system("CLS");
                return 99969;
            case buttonB:
            case buttonb:
                if (!ButtonB) break;
                return 99966;
            case buttonC:
            case buttonc:
                if (!ButtonC) break;
                system("CLS");
                return 99967;
            case buttonD:
            case buttond:
                if (!ButtonD) break;
                system("CLS");
                return 99968;
            case arrowUP:
                if (index <= min) break;
                gotoxy(x+2,index--);
                cout << "\b\b  ";
                gotoxy(x,index);
                cout << "=> ";
                break;
            case arrowDOWN:
                if (index >= max) break;
                gotoxy(x+2,index++);
                cout << "\b\b  ";
                gotoxy(x,index);
                cout << "=> ";
                break;
            case enter:
                return (index - min + 1);
        }
    }
}

void inputPassword(string& password, int max = 16, bool canThrow = false) {
    int c = 0;
    int length = 0;
    password = "";
    while (true) {
        switch (c = getch()) {
            case esc:
                if (canThrow) throw "";
                return;
            case tab:
            case semicolon:
                break;
            case backspace:
                if (length < 1) break;
                length--;
                password.pop_back();
                cout << "\b \b";
                break;
            case enter:
                if (length == 0) break;
                return;
            default:
                if (length >= max) break;
                length++;
                password += c;
                cout << "*";
        }
    }
}

void getInput(string& input, int max = 16, bool canThrow = false, bool hasValue = false, bool invalidArgs = false) {
    int c = 0;
    int length = 0;
    string str;
    if (!hasValue) input = "";
    else str = input, length = input.size();

    while (true) {
        switch (c = getch()) {
            case esc:
                if (canThrow && invalidArgs) throw invalid_argument("");
                if (canThrow) throw "";
                return;
            case tab:
            case semicolon:
                break;
            case backspace:
                if (length < 1) break;
                length--;
                input.pop_back();
                cout << "\b \b";
                break;
            case enter:
                if (length == 0) break;
                return;
            default:
                if (length >= max) break;
                length++;
                input += c;
                str = c;
                cout << str;
        }
    }
}

int selectGender(int x, int y, bool canThrow = false) {
    int c = 0;
    int index = 1;

    gotoxy(x,y); cout << "[L]/ P ";

    while (true) {
        switch (c = getch()) {
            case esc:
                if (canThrow) throw "";
            case arrowRIGHT:
                if (index >= 2) break;
                cout << "\b\b\b\b\b\b\b L /[P]";
                index++;
                break;
            case arrowLEFT:
                if (index <= 1) break;
                cout << "\b\b\b\b\b\b\b[L]/ P ";
                index--;
                break;
            case enter:
                return index;
        }
    }
}

class User {
protected:
    string username;
    string password;
    string name;
    char gender;
    string phone;
    string email;

public:
    User(const string& username, const string& password, const string& name, const char& gender, const string& phone, const string& email)
        : username(username), password(password), name(name), gender(gender), phone(phone), email(email) {}

    string getUsername() const {
        return username;
    }

    string getPassword() const {
        return password;
    }

    string getName() const {
        return name;
    }

    char getGender() const {
        return gender;
    }

    string getPhone() const {
        return phone;
    }

    string getEmail() const {
        return email;
    }

    void changePassword(const string& newPassword) {
        password = newPassword;

        cout << "Password berhasil diubah.";
        getch();
    }

    void editData(const string& newName, const char& newGender, const string& newPhone, const string& newEmail) {
        name = newName;
        gender = newGender;
        phone = newPhone;
        email = newEmail;

        cout << "Profile has been changed.";
        getch();
    }

    virtual string getRole() const = 0;
};

class Teacher : public User {
public:
    Teacher(const string& username, const string& password, const string& name, const char& gender, const string& phone, const string& email)
        : User(username, password, name, gender, phone, email) {}

    void mainMenu(int& tahun) {
        system("CLS");

        cout << ".-------------------------------------.\n"
             << "| Welcome, " << left << setw(26) << getName()+"!" << " |\n"
             << "+-------------------------------------+\n"
             << "|    1. View class                    |\n"
             << "|    2. View ranking                  |\n"
             << "|    3. Manage Nilai                  |\n"
             << "|    4. Edit account                  |\n"
             << "|    0. Logout                        |\n"
             << "+-------------------------------------+\n"
             << "Tahun ajaran: " << tahun << "/" << tahun+1 << endl;
    }

    string getRole() const override {
        return "teacher";
    }
};

class Student : public User {
private:
    struct Grade {
        string kelas;
        int tahun;
        float ganjil[9];
        float genap[9];
    };
    
    Grade grade[3] = {
        {
            "VII", 0000, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}
        },
        {
            "VIII", 0000, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}
        },
        {
            "IX", 0000, {0,0,0,0,0,0,0,0,0}, {0,0,0,0,0,0,0,0,0}
        }
    };

    float latestTotal;

public:
    Student(const string& username, const string& password, const string& name, const char& gender, const string& phone, const string& email)
        : User(username, password, name, gender, phone, email) {}

    void mainMenu(int& tahun) {
        system("CLS");

        cout << ".-------------------------------------.\n"
             << "| Welcome, " << left << setw(26) << getName()+"!" << " |\n"
             << "+-------------------------------------+\n"
             << "|    1. View report                   |\n"
             << "|    2. Edit account                  |\n"
             << "|    0. Logout                        |\n"
             << "+-------------------------------------+\n"
             << "Tahun ajaran: " << tahun << "/" << tahun+1 << endl;
    }

    void loadGrades(const int& semester, const Grade& data) {
        grade[semester] = data;
    }

    void saveGrades(ofstream& file) {
        for (Grade semes : grade) {
            file << semes.kelas << "\t" << semes.tahun << "\t" << semes.ganjil[0] << "\t" << semes.ganjil[1] << "\t" << semes.ganjil[2] << "\t" << semes.ganjil[3] << "\t" << semes.ganjil[4] << "\t" << semes.ganjil[5] << "\t" << semes.ganjil[6] << "\t" << semes.ganjil[7] << "\t" << semes.ganjil[8] << "\t" << semes.genap[0] << "\t" << semes.genap[1] << "\t" << semes.genap[2] << "\t" << semes.genap[3] << "\t" << semes.genap[4] << "\t" << semes.genap[5] << "\t" << semes.genap[6] << "\t" << semes.genap[7] << "\t" << semes.genap[8] << ";";
        }
    }

    void exportGrade(const int& semester) {
        int tipeSemester = semester % 2;
        string tipeSemesterStr = (tipeSemester ? "GANJIL" : "GENAP");
        int kelas = (tipeSemester + (semester/2));
        string strKelas = kelas <= 1 ? "VII" : (kelas <= 2 ? "VIII" : (kelas <= 3 ? "IX" : "XXX"));
        int tahun = grade[kelas-1].tahun;
        string namafile = to_string(tahun) + to_string(tahun+1) + " " + strKelas + " " + tipeSemesterStr + " - " + username + " " + name + ".txt";
        float* selected = (tipeSemester ? grade[kelas-1].ganjil : grade[kelas-1].genap);

        ofstream file(namafile);
        if (file.is_open()) {
            file << ".--------------------------------------.\n"
                 << "| Tahun    : " << left << setw(25) << to_string(tahun) + "/" + to_string(tahun+1) << " |\n"
                 << "| Semester : " << setw(25) << tipeSemesterStr << " |\n"
                 << "| NIS      : " << setw(25) << username << " |\n"
                 << "| Nama     : " << setw(25) << name << " |\n"
                 << "| Kelas    : " << setw(25) << strKelas << " |\n"
                 << "+--------------------------------------+\n" << fixed << setprecision(2) << right
                 << "| Pendidikan Agama         | " << setw(9) << selected[0] << " |\n"
                 << "| P. Kewarganegaraan       | " << setw(9) << selected[1] << " |\n"
                 << "| Bahasa Indonesia         | " << setw(9) << selected[2] << " |\n"
                 << "| Bahasa Inggris           | " << setw(9) << selected[3] << " |\n"
                 << "| Matematika               | " << setw(9) << selected[4] << " |\n"
                 << "| Ilmu Pengetahuan Alam    | " << setw(9) << selected[5] << " |\n"
                 << "| Ilmu Pengetahuan Sosial  | " << setw(9) << selected[6] << " |\n"
                 << "+--------------------------------------+\n"
                 << "| Total                    | " << setw(9) << selected[7] << " |\n"
                 << "+--------------------------------------+\n"
                 << "| Rata-rata                | " << setw(9) << selected[8] << " |\n"
                 << "+--------------------------------------+\n";
            file.close();
            cout << "Export berhasil...\nSilahkan buka file dengan nama \"" << namafile << "\"" << endl;
        }
        else {
            cout << "Error: Failed to open file for saving user data." << endl;
        }
        getch();
    }

    void setGrade(const int& semester, const int& tahunAjaran) {
        float agama, pkn, b_indo, b_ing, mtk, ipa, ips;

        int tipeSemester = semester % 2;
        int kelas = (tipeSemester + (semester/2));
        string strKelas = kelas <= 1 ? "VII" : (kelas <= 2 ? "VIII" : (kelas <= 3 ? "IX" : "XXX"));

        int tahun = grade[kelas-1].tahun ? grade[kelas-1].tahun : 0;
        string tempInput;

        float* selected = (tipeSemester == 0 ? grade[kelas-1].genap : grade[kelas-1].ganjil);

        system("CLS");
        cout << ".-------------------------------------.\n"
             << "| NIS      : " << left << setw(24) << username << " |\n"
             << "| Nama     : " << setw(24) << name << " |\n"
             << "| Semester : " << setw(24) << (tipeSemester == 0 ? "Genap" : "Ganjil") << " |\n"
             << "| Kelas    : " << setw(24) << strKelas << " |\n"
             << "| Tahun    : " << setw(24) << tahun << " |\n";
        cout << "+-------------------------------------+\n"
             << "| Agama                    |          |\n"
             << "| PKN                      |          |\n"
             << "| Bahasa Indonesia         |          |\n"
             << "| Bahasa Inggris           |          |\n"
             << "| Matematika               |          |\n"
             << "| Ilmu Pengetahuan Alam    |          |\n"
             << "| Ilmu Pengetahuan Sosial  |          |\n"
             << "+-------------------------------------+\n\n\n"
             << "[ESC] Back";

        COORD cursorPosition = GetCursorPosition();
        try {
            if (grade[kelas-1].tahun == 0) {
                gotoxy(13, cursorPosition.Y-12);
                getInput(tempInput, 4, true, false, true);
                tahun = stoi(tempInput);
                if ((kelas-1) == 0) grade[kelas].tahun = tahun+1, grade[kelas+1].tahun = tahun+2;
                if ((kelas-1) == 1) grade[kelas-2].tahun = tahun-1, grade[kelas].tahun = tahun+1;
                if ((kelas-1) == 2) grade[kelas-3].tahun = tahun-2, grade[kelas-2].tahun = tahun-1;
            }

            gotoxy(29, cursorPosition.Y-10); getInput(tempInput, 5, true, false, true); agama = stof(tempInput);
            gotoxy(29, GetCursorPosition().Y+1); getInput(tempInput, 5, true, false, true); pkn = stof(tempInput);
            gotoxy(29, GetCursorPosition().Y+1); getInput(tempInput, 5, true, false, true); b_indo = stof(tempInput);
            gotoxy(29, GetCursorPosition().Y+1); getInput(tempInput, 5, true, false, true); b_ing = stof(tempInput);
            gotoxy(29, GetCursorPosition().Y+1); getInput(tempInput, 5, true, false, true); mtk = stof(tempInput);
            gotoxy(29, GetCursorPosition().Y+1); getInput(tempInput, 5, true, false, true); ipa = stof(tempInput);
            gotoxy(29, GetCursorPosition().Y+1); getInput(tempInput, 5, true, false, true); ips = stof(tempInput);
            gotoxy(0, GetCursorPosition().Y+2);
        }
        catch (const invalid_argument& e) {
            return;
        }

        if (tahun > tahunAjaran || 
        agama < 0 || agama > 100 || 
        pkn < 0 || pkn > 100 || 
        b_indo < 0 || b_indo > 100 || 
        b_ing < 0 || b_ing > 100 || 
        mtk < 0 || mtk > 100 || 
        ipa < 0 || ipa > 100 || 
        ips < 0 || ips > 100) {
            cout << "* input error, please try again.\n";
        }
        else {
            grade[kelas-1].tahun = tahun;
            selected[0] = agama;
            selected[1] = pkn;
            selected[2] = b_indo;
            selected[3] = b_ing;
            selected[4] = mtk;
            selected[5] = ipa;
            selected[6] = ips;
            selected[7] = (agama + pkn + b_indo + b_ing + mtk + ipa + ips);
            selected[8] = selected[7] / 7;
        }

        cout << "Input nilai berhasil";
        getch();
    }
    
    void getGrade(int& semester) {
        int tipeSemester = semester % 2;
        string tipeSemesterStr = (tipeSemester ? "GANJIL" : "GENAP");
        int kelas = (tipeSemester + (semester/2));
        string strKelas = kelas <= 1 ? "VII" : (kelas <= 2 ? "VIII" : (kelas <= 3 ? "IX" : "XXX"));
        int i = kelas-1;
        
        float* nilai = (tipeSemester == 0 ? grade[i].genap : grade[i].ganjil);
        
        system("CLS");
        cout << ".--------------------------------------.\n"
             << "| Tahun    : " << left << setw(25) << grade[i].tahun << " |\n"
             << "| Semester : " << setw(25) << tipeSemesterStr << " |\n"
             << "| NIS      : " << setw(25) << username << " |\n"
             << "| Name     : " << setw(25) << name << " |\n"
             << "| Kelas    : " << setw(25) << grade[i].kelas << " |\n"
             << "+--------------------------------------+\n"
             << "| Agama                    | " << right << setw(9) << nilai[0] << " |\n"
             << "| PKN                      | " << setw(9) << nilai[1] << " |\n"
             << "| Bahasa Indonesia         | " << setw(9) << nilai[2] << " |\n"
             << "| Bahasa Inggris           | " << setw(9) << nilai[3] << " |\n"
             << "| Matematika               | " << setw(9) << nilai[4] << " |\n"
             << "| Ilmu Pengetahuan Alam    | " << setw(9) << nilai[5] << " |\n"
             << "| Ilmu Pengetahuan Sosial  | " << setw(9) << nilai[6] << " |\n"
             << "+--------------------------------------+\n"
             << "| Total                    | " << setw(9) << nilai[7] << " |\n"
             << "+--------------------------------------+\n"
             << "| Rata-rata                | " << setw(9) << nilai[8] << " |\n"
             << "+--------------------------------------+\n\n"
             << "[B] Back           [E] Export\n";
    }

    void* getAverage(float semester[6]) {
        semester[0] = grade[0].ganjil[8];
        semester[1] = grade[0].genap[8];
        semester[2] = grade[1].ganjil[8];
        semester[3] = grade[1].genap[8];
        semester[4] = grade[2].ganjil[8];
        semester[5] = grade[2].genap[8];
        return 0;
    }

    bool findKelasTahun(const int& i, const int& tahun, bool semesterGanjil = true) {
        string kelas = i <= 1 ? "VII" : (i <= 2 ? "VIII" : (i <= 3 ? "IX" : "XXX"));
        for (Grade semes : grade) {
            if (semes.kelas == kelas && semes.tahun == tahun) {
                latestTotal = (semesterGanjil ? semes.ganjil[7] : semes.genap[7]);
                return true;
            }
        }
        return false;
    }

    float getLatestTotal() {
        return latestTotal;
    }

    string getRole() const override {
        return "student";
    }
};

class Admin : public User {
public:
    Admin(const string& username, const string& password, const string& name, const char& gender, const string& phone, const string& email)
        : User(username, password, name, gender, phone, email) {}

    void mainMenu(int& tahun) {
        system("CLS");

        cout << ".-------------------------------------.\n"
             << "| Welcome, " << left << setw(26) << getName()+"!" << " |\n"
             << "+-------------------------------------+\n"
             << "|    1. Manage Teacher                |\n"
             << "|    2. Manage Student                |\n"
             << "|    3. Manage Nilai                  |\n"
             << "|    4. View class                    |\n"
             << "|    5. View ranking                  |\n"
             << "|    6. Ganti tahun ajaran            |\n"
             << "|    0. Logout                        |\n"
             << "+-------------------------------------+\n"
             << "Tahun ajaran: " << tahun << "/" << tahun+1 << endl;
    }

    void createTeacher(vector<User*>& users, const string& uid, const string& name, const char& gender, const string& phone, const string& email) {
        User* teacher = new Teacher(uid, uid, name, gender, phone, email);
        users.push_back(teacher);
        cout << "Teacher created successfully!" << endl;
        getch();
    }

    void createStudent(vector<User*>& users, const string& uid, const string& name, const char& gender, const string& phone, const string& email) {
        User* student = new Student(uid, uid, name, gender, phone, email);
        users.push_back(student);
        cout << "Student created successfully!" << endl;
        getch();
    }
    
    void removeUser(vector<User*>& users, const int& index) {
        users.erase(users.begin()+index-1);

        cout << "\nUser has been deleted.";
        getch();
    }

    string getRole() const override {
        return "admin";
    }
};

void saveUserData(const vector<User*>& users) {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (User* user : users) {
            if (user->getRole() != "student") {
                file << user->getRole() << "\t" << user->getUsername() << "\t" << user->getPassword() << "\t" << user->getGender() << "\t" << user->getPhone() << "\t" << user->getEmail() << "\t" << user->getName() << endl;
                continue;
            }

            Student* student = dynamic_cast<Student*>(user);
            file << user->getRole() << "\t" << user->getUsername() << "\t" << user->getPassword() << "\t" << user->getGender() << "\t" << user->getPhone() << "\t" << user->getEmail() << "\t" << user->getName() << ";" << fixed << setprecision(2);

            student->saveGrades(file);

            file << endl;
        }
        file.close();
        cout << "User data saved successfully!" << endl;
    } else {
        cout << "Error: Failed to open file for saving user data." << endl;
    }
}

void loadUserData(vector<User*>& users, int& teacherID, int& studentID, int& tahunAjaran) {
    int usernameID;
    ifstream file("users.txt");

    string role, username, password, name, kelas, phone, email;
    char gender;
    int tahun;
    float agama, pkn, b_indo, b_ing, mtk, ipa, ips, total, ratarata, agama2, pkn2, b_indo2, b_ing2, mtk2, ipa2, ips2, total2, ratarata2;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {

            // line tipe datanya "string" kita ubah jadi input stream
            istringstream fullLine(line);

            // inputstream masukin data ke role, username, password, nama pake getline biar spasi kebaca
            fullLine >> role >> username >> password >> gender >> phone >> email;
            getline(fullLine >> ws, name, ';');

            User* user = nullptr;

            // bikin user sesuai role, simpen ke variabel "users"
            if (role == "admin") {
                user = new Admin(username, password, name, gender, phone, email);
                users.push_back(user);
                continue;
            }
            else if (role == "teacher") {
                user = new Teacher(username, password, name, gender, phone, email);
                users.push_back(user);
                usernameID = stoi(user->getUsername());
                if (usernameID > teacherID) {
                    teacherID = usernameID;
                }
                continue;
            }
            else if (role == "student") {
                user = new Student(username, password, name, gender, phone, email);
                users.push_back(user);
                usernameID = stoi(user->getUsername());
                if (usernameID > studentID) {
                    studentID = usernameID;
                }
            }
            
            // Khusus student aja ada nilai
            string semester;
            int semesterCount = 0;
            while(getline(fullLine, semester, ';')) {
                tahun = 0;
                agama = pkn = b_indo = b_ing = mtk = ipa = ips = total = ratarata = agama2 = pkn2 = b_indo2 = b_ing2 = mtk2 = ipa2 = ips2 = total2 = ratarata2 = 0;

                istringstream Semester(semester);

                Semester >> kelas >> tahun >> agama >> pkn >> b_indo >> b_ing >> mtk >> ipa >> ips >> total >> ratarata >> agama2 >> pkn2 >> b_indo2 >> b_ing2 >> mtk2 >> ipa2 >> ips2 >> total2 >> ratarata2;

                if (tahun > tahunAjaran) tahunAjaran = tahun;

                string strKelas = semesterCount == 0 ? "VII" : (semesterCount == 1 ? "VIII" : (semesterCount == 2 ? "IX" : "XXX"));

                Student* student = dynamic_cast<Student*>(user);
                student->loadGrades(semesterCount, {
                    strKelas, 
                    tahun, {
                        agama, 
                        pkn, 
                        b_indo, 
                        b_ing, 
                        mtk, 
                        ipa, 
                        ips,
                        total,
                        ratarata
                        }, 
                        {
                        agama2, 
                        pkn2, 
                        b_indo2, 
                        b_ing2, 
                        mtk2, 
                        ipa2, 
                        ips2,
                        total2,
                        ratarata2
                        }
                    }
                );

                semesterCount++;
            }
        }
        file.close();
        cout << "User data loaded successfully!" << endl;
    } else {
        cout << "Error: Failed to open file for loading user data." << endl;
    }
}

void detailsAccount(string role, string username, string name) {
    system("CLS");
    cout << ".------------------------------------------.\n"
         << "| User account                             |\n"
         << "+------------------------------------------+\n"
         << "| Role         : " << left << setw(25) << role << " |\n"
         << "| Username     : " << setw(25) << username << " |\n"
         << "| Name         : " << setw(25) << name << " |\n"
         << "+------------------------------------------+\n\n"
         << "[B] Back        [C] Change password\n"
         << "[D] Delete      [E] Edit profile\n";
}

void editAccount(string role, string username, string name, char gender) {
    system("CLS");
    cout << ".------------------------------------------.\n"
         << "| User account                             |\n"
         << "+------------------------------------------+\n"
         << "| Role         : " << left << setw(25) << role << " |\n"
         << "| Username     : " << setw(25) << username << " |\n"
         << "| Name         : " << setw(25) << name << " |\n"
         << "| Gender       : " << setw(25) << gender << " |\n"
         << "+------------------------------------------+\n\n"
         << "[B] Back           [C] Change password\n"
         << "[E] Edit profile\n";
}

void editProfile(string username, string& name, char& gender, string& phone, string& email) {
    system("CLS");
    cout << ".--------------------------------------------------.\n"
         << "| Profile                                          |\n"
         << "+--------------------------------------------------+\n"
         << "| NIS      : " << setw(37) << username << " |\n"
         << "| Name     : " << setw(37) << name << " |\n"
         << "| Gender   : " << setw(37) << gender << " |\n"
         << "| Phone    : " << setw(37) << phone << " |\n"
         << "| Email    : " << setw(37) << email << " |\n"
         << "+--------------------------------------------------+\n\n\n"
         << "[ESC] Back";

        try {
            gotoxy(13+name.size(), 4); getInput(name, 25, true, true);
            int SelectGender = selectGender(13, GetCursorPosition().Y+1, true);
            gender = (SelectGender == 1 ? 'L' : 'P');
            gotoxy(13+phone.size(), GetCursorPosition().Y+1); getInput(phone, 13, true, true);
            gotoxy(13+email.size(), GetCursorPosition().Y+1); getInput(email, 37, true, true);
            gotoxy(0, GetCursorPosition().Y+2);
        }
        catch (const char* e) {
            throw "";
        }
}

void createAccount(string& uid, string& name, char& gender, string& phone, string& email) {
    system("CLS");
    cout << ".------------------------------------------------------.\n"
         << "| Create account                                       |\n"
         << "+------------------------------------------------------+\n"
         << "| Name         :                                       |\n"
         << "| Gender       :                                       |\n"
         << "| Phone        :                                       |\n"
         << "| Email        :                                       |\n"
         << "+------------------------------------------------------+\n"
         << "| Username     : " << left << setw(37) << uid << " |\n"
         << "| Password     : " << setw(37) << uid << " |\n"
         << "+------------------------------------------------------+\n\n\n"
         << "[ESC] Back\n";

    try {
        gotoxy(17, GetCursorPosition().Y-11); getInput(name, 25, true);

        int SelectGender = selectGender(17, GetCursorPosition().Y+1, true);
        gender = (SelectGender == 1 ? 'L' : 'P');

        gotoxy(17, GetCursorPosition().Y+1); getInput(phone, 13, true);
        gotoxy(17, GetCursorPosition().Y+1); getInput(email, 37, true);
        gotoxy(0, GetCursorPosition().Y+5);
    }
    catch (const char* e) {
        throw "";
    }
}

bool changePassword(string oldPassword, string& newPassword) {
    string inputOldPassword, inputNewPassword;
    bool wrong, notEqual;
    changePassword:
    system("CLS");
    cout << ".--------------------------------------.\n"
         << "| Change Password                      |\n"
         << "+--------------------------------------+\n"
         << "| Old password     :                   |\n"
         << "| New password     :                   |\n"
         << "| Re-enter         :                   |\n"
         << "+--------------------------------------+\n";

    if (wrong) cout << "* wrong password...\n";
    else if (notEqual) cout << "* passwords don't match...\n";
    cout << "\n[ESC] Back\n";

    try {
        gotoxy(21, 3); inputPassword(inputOldPassword, 16, true);
        if (oldPassword != inputOldPassword) {
            wrong = true;
            goto changePassword;
        }
        wrong = false;

        gotoxy(21, 4); inputPassword(newPassword, 16, true);
        gotoxy(21, 5); inputPassword(inputNewPassword, 16, true);
        gotoxy(0, GetCursorPosition().Y+2);

        if (newPassword != inputNewPassword) {
            notEqual = true;
            goto changePassword;
        }
        notEqual = false;
    }
    catch (const char* e) {
        return false;
    }

    return true;
}

int menuSelectClass() {
    system("CLS");
    cout << ".--------------------------------------.\n"
         << "| Pilih kelas                          |\n"
         << "+--------------------------------------+\n"
         << "|    VII  (Tujuh)                      |\n"
         << "|    VIII (Delapan)                    |\n"
         << "|    IX   (Sembilan)                   |\n"
         << "+--------------------------------------+\n"
         << "| > Tahun ajaran:                      |\n"
         << "+--------------------------------------+\n\n"
         << "[B] Back       [Enter] Select\n";
    return menuChange(2, 3, 5, true);
}

int menuSelectSemester() {
    system("CLS");
    cout << ".--------------------------------------.\n"
         << "| Pilih kelas                          |\n"
         << "+--------------------------------------+\n"
         << "|    VII  - Ganjil                     |\n"
         << "|    VII  - Genap                      |\n"
         << "|    VIII - Ganjil                     |\n"
         << "|    VIII - Genap                      |\n"
         << "|    IX   - Ganjil                     |\n"
         << "|    IX   - Genap                      |\n"
         << "+--------------------------------------+\n"
         << "| > Tahun ajaran:                      |\n"
         << "+--------------------------------------+\n\n"
         << "[B] Back       [Enter] Select\n";
    return menuChange(2, 3, 8, true);
}

void* menuSelectNilai(string username, string name, float semester[6]) {
    system("CLS");
    cout << ".--------------------------------------.\n"
         << "| Data Nilai                           |\n"
         << "| " << left << setw(36) << username + " - " + name << " |\n"
         << "+--------------------------------------+\n" << fixed << setprecision(2)
         << "|    VII  - Ganjil : " << setw(17) << semester[0] << " |\n"
         << "|    VII  - Genap  : " << setw(17) << semester[1] << " |\n"
         << "|    VIII - Ganjil : " << setw(17) << semester[2] << " |\n"
         << "|    VIII - Genap  : " << setw(17) << semester[3] << " |\n"
         << "|    IX   - Ganjil : " << setw(17) << semester[4] << " |\n"
         << "|    IX   - Genap  : " << setw(17) << semester[5] << " |\n"
         << "+--------------------------------------+\n\n"
         << "[B] Back       [Enter] Select\n"
         << "\x18\x19  Move\n";
    return 0;
}

void listUser(vector<User*>& users, string role = "student") {
    int total = 1;
    cout << ".---------------------------------------------.\n"
         << "| No. | Unique ID | Nama                      |\n"
         << "+---------------------------------------------+\n";
    for (User* user : users) {
        if (user->getRole() == role) {
            cout << "| " << right << setw(3) << total++
                 << " | " << left << setw(9) << user->getUsername()
                 << " | " << setw(25) << user->getName() << " |\n";
        }
    }
    if (total == 1) {
        cout << "|                   NO DATA                   |\n";
    }
    cout << "+---------------------------------------------+\n";
}

User* findUser(vector<User*>& users, string role) {
    string inputUID;
    cout << "> Enter NIS/UID : ";
    while (true) {
        try {
            getInput(inputUID, (role == "teacher" ? 4 : 5), true);
        }
        catch (const char* e) {
            return nullptr;
        }
        for (User* user : users) {
            if (user->getRole() == role && user->getUsername() == inputUID) return user;
        }
        gotoxy(0, GetCursorPosition().Y+1);
        cout << "* can't find user, make sure UID is correct";
        gotoxy(23, GetCursorPosition().Y-1);
        cout << "\b\b\b\b\b     \b\b\b\b\b";
    }
}

int findUserIndex(vector<User*>& users, const string& role, string uid, bool& indexed) {
    int indexUser = 0;

    for (User* user : users) {
        indexUser++;
        if (user->getRole() != role || user->getUsername() != uid) continue;
        indexed = true;
        return indexUser;
    }

    return 0;
}

void printRanking(vector<User*>& users, const int& semester, const int& tahun) {
    int tipeSemester = semester % 2;
    int kelas = (tipeSemester + (semester/2));
    bool boolTipeSemester = tipeSemester == 0 ? false : true; 
    
    vector<Student*> match;
    Student* tempStudent;

    for (User* user : users) {
        if (user->getRole() != "student") continue;

        Student* student = dynamic_cast<Student*>(user);

        if (!student->findKelasTahun(kelas, tahun, boolTipeSemester)) continue;

        match.push_back(student);
    }

    for (int x = 1; x < match.size(); x++) {
        for (int y = match.size()-1; y >= x; y--) {
            if (match[y]->getLatestTotal() > match[y-1]->getLatestTotal()) {
                tempStudent = match[y];
                match[y] = match[y-1];
                match[y-1] = tempStudent;
            }
        }
    }

    int i = 1;
    string strKelas = kelas <= 1 ? "VII" : (kelas <= 2 ? "VIII" : (kelas <= 3 ? "IX" : "XXX"));

    system("CLS");
    cout << "Tahun Ajaran : " << tahun << "/" << (tahun+1) << "\n"
         << "Kelas        : " << strKelas << "\n"
         << ".---------------------------------------------------------.\n"
         << "| No. | Unique ID | Nama                      | Rata-rata |\n"
         << "+---------------------------------------------------------+\n" << fixed << setprecision(2) << right;

    if (match.size() <= 0) {
        cout << "|                         NO DATA                         |\n";
    }
    for (Student* user : match) {
        cout << "| " << setw(3) << i++
             << " | " << left << setw(9) << user->getUsername()
             << " | " << setw(25) << user->getName()
             << " | " << right << setw(9) << (user->getLatestTotal()/7) << " |\n";
    }
    cout << "+---------------------------------------------------------+\n\n"
         << "[B] Back\n";

    getch();
}

void viewClass(vector<User*>& users, const int& kelas, const int& tahun) {
    vector<Student*> match;

    for (User* user : users) {
        if (user->getRole() != "student") continue;

        Student* student = dynamic_cast<Student*>(user);

        if (!student->findKelasTahun(kelas, tahun)) continue;

        match.push_back(student);
    }

    int i = 1;
    string strKelas = kelas <= 1 ? "VII" : (kelas <= 2 ? "VIII" : (kelas <= 3 ? "IX" : "XXX"));

    system("CLS");
    cout << "Tahun Ajaran : " << tahun << "/" << (tahun+1) << "\n"
         << "Kelas        : " << strKelas << "\n"
         << ".---------------------------------------------.\n"
         << "| No. | Unique ID | Nama                      |\n"
         << "+---------------------------------------------+\n";

    if (match.size() <= 0) {
        cout << "|                   NO DATA                   |\n";
    }
    for (Student* user : match) {
        cout << "| " << right << setw(3) << i++
            << " | " << left << setw(9) << user->getUsername()
            << " | " << setw(25) << user->getName() << " |\n";
    }
    cout << "+---------------------------------------------+\n\n"
         << "[B] Back\n";

    getch();
}

User* loginUser(vector<User*>& users, const int& loginAs) {
    string username, password;
    // string username = "1001", password = "1001";
    bool invalidLogin = false;
    User* loggedInUser = nullptr;
    string role = loginAs == 1 ? "admin" : (loginAs == 2 ? "teacher" : (loginAs == 3 ? "student" : ""));
    do {
        system("CLS");
        cout << ".--------------------------------------.\n"
             << "| Login account                        |\n"
             << "+--------------------------------------+\n"
             << "| Username     :                       |\n"
             << "| Password     :                       |\n"
             << "+--------------------------------------+\n";

        if (invalidLogin) cout << "* invalid login credentials.\n";
        cout << "\n[ESC] Back\n";

        try {
            gotoxy(17, 3);
            getInput(username, 16, true);
            gotoxy(17, 4);
            inputPassword(password, 16, true);
        }
        catch (const char* e) {
            throw "";
        }

        for (User* user : users) {
            if (user->getRole() == role && user->getUsername() == username && user->getPassword() == password) {
                loggedInUser = user;
                break;
            }
        }

        invalidLogin = true;
    } while (loggedInUser == nullptr);

    return loggedInUser;
}

int main() {
    int teacherID = 1000;
    int studentID = 10000;
    int tahunAjaran = 2023;
    vector<User*> users;
    
    loadUserData(users, teacherID, studentID, tahunAjaran);

    loginAsRole:
    system("CLS");
    cout << "\n           WELCOME TO E-RAPOT\n\n"
         << ".--------------------------------------.\n"
         << "| Login as                             |\n"
         << "+--------------------------------------+\n"
         << "|    Admin                             |\n"
         << "|    Teacher                           |\n"
         << "|    Student                           |\n"
         << "+--------------------------------------+\n"
         << "\x18\x19  Move\n"
         << "[ESC] Exit program\n\n";
    int loginAs = menuChange(2, 6, 8, false, false, false, false, true);
    if (!loginAs) {
        system("CLS");
        return 0;
    }

    while (true) {
        User* loggedInUser;
        try {
            loggedInUser = loginUser(users, loginAs);
        }
        catch (const char* e) {
            goto loginAsRole;
        }

        if (loggedInUser->getRole() == "admin") {
            Admin* admin = dynamic_cast<Admin*>(loggedInUser);
            if (admin == nullptr) continue;

            // print main menu admin
            adminMenu: admin->mainMenu(tahunAjaran);
            int pilihMenu = menuChange(2, 3, 9);

            // print menu manage teacher
            if (pilihMenu == 1) {
                adminTeacher:
                system("CLS");
                cout << "             Manage Teacher Account\n";

                listUser(users, "teacher");

                cout << "\n\n\n"
                     << "[B] Back       [Enter] Search by UID\n"
                     << "[C] Create\n";

                int pilihOpsi = menuChange(0, 1, 0, true, true);

                if (pilihOpsi == 99966) {
                    goto adminMenu;
                }
                else if (pilihOpsi == 99967) {
                    string name, phone, email, uid = to_string(++teacherID);
                    char gender;

                    try {
                        createAccount(uid, name, gender, phone, email);
                        admin->createTeacher(users, uid, name, gender, phone, email);
                    }
                    catch (const char* e) {}

                    goto adminTeacher;
                }
                else {
                    gotoxy(0, GetCursorPosition().Y-5);

                    User* user = findUser(users, "teacher");
                    if (user == nullptr) goto adminTeacher;
                    Teacher* teacher = dynamic_cast<Teacher*>(user);

                    adminTeacherAccount:
                    detailsAccount(teacher->getRole(), teacher->getUsername(), teacher->getName());

                    int selectOption = menuChange(0, 1, 0, true, true, true, true);

                    if (selectOption == 99966) goto adminTeacher;
                    else if (selectOption == 99967) {
                        string newPassword;
                        if (changePassword(teacher->getPassword(), newPassword)) teacher->changePassword(newPassword);
                    }
                    else if (selectOption == 99968) {
                        cout << "Remove User " << teacher->getUsername() << " - " << teacher->getName()
                             << "\nAre you sure?\n\n"
                             << "[Y] Yes    [N] No\n";
                        
                        bool isIndexed = false;
                        int indexUser = findUserIndex(users, "teacher", teacher->getUsername(), isIndexed);
                        if (isIndexed && getConfirmation()) {
                            admin->removeUser(users, indexUser);
                            goto adminTeacher;
                        }
                    }
                    else if (selectOption == 99969) {
                        string name = teacher->getName(),
                               phone = teacher->getPhone(), 
                               email = teacher->getEmail();
                        char gender = teacher->getGender();

                        try {
                            editProfile(teacher->getUsername(), name, gender, phone, email);
                            teacher->editData(name, gender, phone, email);
                        }
                        catch (const char* e) {}
                    }
                    goto adminTeacherAccount;
                }
            }
            // print menu manage student
            else if (pilihMenu == 2) {
                adminStudent:
                system("CLS");
                cout << "             Manage Student Account\n";

                listUser(users);

                cout << "\n\n\n"
                     << "[B] Back       [Enter] Search by UID\n"
                     << "[C] Create\n";

                int pilihOpsi = menuChange(0, 1, 0, true, true);

                if (pilihOpsi == 99966) {
                    goto adminMenu;
                }
                else if (pilihOpsi == 99967) {
                    string name, phone, email, uid = to_string(++studentID);
                    char gender;

                    try {
                        createAccount(uid, name, gender, phone, email);
                        admin->createStudent(users, uid, name, gender, phone, email);
                    }
                    catch (const char* e) {}

                    goto adminStudent;
                }
                else {
                    gotoxy(0, GetCursorPosition().Y-5);

                    User* user = findUser(users, "student");
                    if (user == nullptr) goto adminStudent;
                    Student* student = dynamic_cast<Student*>(user);

                    adminStudentAccount:
                    detailsAccount(student->getRole(), student->getUsername(), student->getName());
                                
                    int selectOption = menuChange(0, 1, 0, true, true, true, true);

                    if (selectOption == 99966) goto adminStudent;
                    else if (selectOption == 99967) {
                        string newPassword;
                        if (changePassword(student->getPassword(), newPassword)) student->changePassword(newPassword);
                    }
                    else if (selectOption == 99968) {
                        cout << "Remove User " << student->getUsername() << " - " << student->getName()
                             << "\nAre you sure?\n\n"
                             << "[Y] Yes    [N] No\n";
                        
                        bool isIndexed = false;
                        int indexUser = findUserIndex(users, "student", student->getUsername(), isIndexed);
                        if (isIndexed && getConfirmation()) {
                            admin->removeUser(users, indexUser);
                            goto adminStudent;
                        }
                    }
                    else if (selectOption == 99969) {
                        string name = student->getName(),
                               phone = student->getPhone(), 
                               email = student->getEmail();
                        char gender = student->getGender();

                        try {
                            editProfile(student->getUsername(), name, gender, phone, email);
                            student->editData(name, gender, phone, email);
                        }
                        catch (const char* e) {}
                    }
                    goto adminStudentAccount;
                }
            }
            else if (pilihMenu == 3) {
                adminNilai:
                system("CLS");
                cout << "              Manage Nilai Student\n";

                listUser(users);

                cout << "\n\n\n"
                     << "[B] Back       [Enter] Search by UID\n"
                     << "\x18\x19  Move\n";

                int pilihOpsi = menuChange(0, 1, 0, true);

                if (pilihOpsi == 99966) goto adminMenu;
                
                gotoxy(0, GetCursorPosition().Y-5);

                User* user = findUser(users, "student");
                if (user == nullptr) goto adminNilai;
                Student* student = dynamic_cast<Student*>(user);

                adminNilaiSelect:
                float getAverage[6];
                student->getAverage(getAverage);
                menuSelectNilai(student->getUsername(), student->getName(), getAverage);

                int selectSemester = menuChange(2, 4, 9, true);
                pilihOpsi = selectSemester;

                if (pilihOpsi == 99966) goto adminNilai;

                student->getGrade(selectSemester);
                cout << "[Enter] Input\n";

                int selectOptions = menuChange(0, 1, 0, true, false, false, true);
                if (selectOptions == 99966) goto adminNilaiSelect;
                else if (selectOptions == 99969) student->exportGrade(selectSemester);
                else student->setGrade(selectSemester, tahunAjaran);

                goto adminNilaiSelect;
            }
            else if (pilihMenu == 4) {
                int pilihKelas;
                string tahun;

                adminViewClass:
                pilihKelas = menuSelectClass();

                if (pilihKelas == 99966) goto adminMenu;

                gotoxy(18, GetCursorPosition().Y + (5 - pilihKelas));
                getInput(tahun, 4);

                try {
                    viewClass(users, pilihKelas, stoi(tahun));
                }
                catch (const invalid_argument& e) {}
                goto adminViewClass;
            }
            else if (pilihMenu == 5) {
                int pilihKelas;
                string tahun;

                adminViewRanking:
                pilihKelas = menuSelectSemester();

                if (pilihKelas == 99966) goto adminMenu;

                gotoxy(18, GetCursorPosition().Y + (8 - pilihKelas));
                getInput(tahun, 4);

                printRanking(users, pilihKelas, stoi(tahun));
                goto adminViewRanking;
            }
            else if (pilihMenu == 6) {
                int newTahunAjaran;
                string tahun;
                system("CLS");

                do {
                    cout << "Tahun ajaran sekarang  : " << tahunAjaran << endl;
                    cout << "Tahun ajaran baru      : "; getInput(tahun, 4);
                    
                    if (newTahunAjaran < tahunAjaran) {
                        cout << "\n* invalid input\n  TA baru tidak dapat lebih kecil dari yang sekarang\n  hubungi developer bila menginginkan hal ini\n";
                        getch();
                        system("CLS");
                    };
                }
                while (newTahunAjaran < tahunAjaran);

                cout << "\nSetelah perubahan terjadi,\n"
                     << "tahun ajaran tidak dapat diturunkan kembali,\n"
                     << "silahkan hubungi developer untuk lebih lanjut.\n"
                     << "Lanjutkan?\n\n"
                     << "[Y] Yes    [N] No\n";
                
                if (!getConfirmation()) goto adminMenu;

                tahunAjaran = newTahunAjaran;
                cout << "\nTahun ajaran berhasil diubah.";
            }
            if (pilihMenu != 7) goto adminMenu;
        } else if (loggedInUser->getRole() == "teacher") {
            Teacher* teacher = dynamic_cast<Teacher*>(loggedInUser);
            if (teacher == nullptr) continue;

            teacherMenu: teacher->mainMenu(tahunAjaran);
            int pilihMenu = menuChange(2, 3, 7);

            if (pilihMenu == 1) {
                int pilihKelas;
                string tahun;

                teacherViewClass:
                pilihKelas = menuSelectClass();

                if (pilihKelas == 99966) goto teacherMenu;

                gotoxy(18, GetCursorPosition().Y + (5 - pilihKelas));
                getInput(tahun, 4);

                try {
                    viewClass(users, pilihKelas, stoi(tahun));
                }
                catch (const invalid_argument& e) {}
                goto teacherViewClass;
            }
            else if (pilihMenu == 2) {
                int pilihKelas;
                string tahun;

                teacherViewRanking:
                pilihKelas = menuSelectSemester();

                if (pilihKelas == 99966) goto teacherMenu;

                gotoxy(18, GetCursorPosition().Y + (8 - pilihKelas));
                getInput(tahun, 4);

                printRanking(users, pilihKelas, stoi(tahun));
                goto teacherViewRanking;
            }
            else if (pilihMenu == 3) {
                teacherNilai:
                system("CLS");
                cout << "              Manage Nilai Student\n";

                listUser(users);

                cout << "\n\n\n"
                     << "[B] Back       [Enter] Search by UID\n"
                     << "\x18\x19  Move\n";

                int pilihOpsi = menuChange(0, 1, 0, true);

                if (pilihOpsi == 99966) goto teacherMenu;

                gotoxy(0, GetCursorPosition().Y-5);

                User* user = findUser(users, "student");
                if (user == nullptr) goto teacherNilai;
                Student* student = dynamic_cast<Student*>(user);

                teacherNilaiSelect:
                float getAverage[6];
                student->getAverage(getAverage);
                menuSelectNilai(student->getUsername(), student->getName(), getAverage);

                int selectSemester = menuChange(2, 4, 9, true);
                pilihOpsi = selectSemester;

                if (pilihOpsi == 99966) goto teacherNilai;

                student->getGrade(selectSemester);
                cout << "[Enter] Input\n";

                int selectOptions = menuChange(0, 1, 0, true, false, false, true);
                if (selectOptions == 99966) goto teacherNilaiSelect;
                else if (selectOptions == 99969) student->exportGrade(selectSemester);
                else student->setGrade(selectSemester, tahunAjaran);

                goto teacherNilaiSelect;
            }
            else if (pilihMenu == 4) {
                teacherEdit:
                editAccount(teacher->getRole(), teacher->getUsername(), teacher->getName(), teacher->getGender());

                int selectOption = menuChange(0, 1, 0, true, true, false, true);
                
                if (selectOption == 99966) goto teacherMenu;
                else if (selectOption == 99967) {
                    string newPassword;
                    if (changePassword(teacher->getPassword(), newPassword)) teacher->changePassword(newPassword);
                }
                else if (selectOption == 99969) {
                    string name = teacher->getName(),
                           phone = teacher->getPhone(), 
                           email = teacher->getEmail();
                    char gender = teacher->getGender();

                    editProfile(teacher->getUsername(), name, gender, phone, email);

                    teacher->editData(name, gender, phone, email);
                }
                goto teacherEdit;
            }
            if (pilihMenu != 5) goto teacherMenu;
        } else if (loggedInUser->getRole() == "student") {
            Student* student = dynamic_cast<Student*>(loggedInUser);
            if (student == nullptr) continue;

            studentMenu: student->mainMenu(tahunAjaran);
            int pilihMenu = menuChange(2, 3, 5);

            if (pilihMenu == 1) {
                float getAverage[6];
                student->getAverage(getAverage);

                studentNilaiSelect:
                menuSelectNilai(student->getUsername(), student->getName(), getAverage);

                int selectSemester = menuChange(2, 4, 9, true);
                int pilihOpsi = selectSemester;

                if (pilihOpsi == 99966) goto studentMenu;
                
                student->getGrade(selectSemester);

                int selectOptions = menuChange(0, 1, 0, true, false, false, true);
                if (selectOptions == 99969) student->exportGrade(selectSemester);

                goto studentNilaiSelect;
            }
            else if (pilihMenu == 2) {
                studentEdit:
                editAccount(student->getRole(), student->getUsername(), student->getName(), student->getGender());

                int selectOption = menuChange(0, 1, 0, true, true, false, true);
                
                if (selectOption == 99966) goto studentMenu;
                else if (selectOption == 99967) {
                    string newPassword;
                    if (changePassword(student->getPassword(), newPassword)) student->changePassword(newPassword);
                }
                else if (selectOption == 99969) {
                    string name = student->getName(),
                           phone = student->getPhone(), 
                           email = student->getEmail();
                    char gender = student->getGender();

                    editProfile(student->getUsername(), name, gender, phone, email);

                    student->editData(name, gender, phone, email);
                }
                goto studentEdit;
            }
            if (pilihMenu != 3) goto studentMenu;
        }
        else continue;
        system("CLS");
        cout << "Logout...\n";
        saveUserData(users);
        getch();
    }

    return 0;
}