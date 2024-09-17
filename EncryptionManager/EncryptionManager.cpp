#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

class FileHandler {
public:
    static vector<string> Load(const string& fileName) {
        vector<string> data;
        ifstream file(fileName);
        if (!file.is_open()) {
            throw runtime_error("Error: File could not be opened.");
        }
        string line;
        while (getline(file, line)) {
            data.push_back(line);
        }
        file.close();
        return data;
    }

    static void Save(const string& fileName, const vector<string>& data) {
        ofstream file(fileName);
        if (!file.is_open()) {
            throw runtime_error("Error: File could not be saved.");
        }
        for (const auto& line : data) {
            file << line << "\n";
        }
        file.close();
    }
};

class SimpleCipher {
public:
    static void EncryptDecrypt(string& text, const string& key) {
        for (size_t i = 0; i < text.size(); ++i) {
            text[i] ^= key[i % key.size()];
        }
    }
};

class EncryptionManager {
public:
    void Run() {
        string title = "Welcome to monocode encryptionApp";
        string border(title.size() + 2, '=');

        while (true) {
            ShowMenu(border, title);
            int choice = GetChoice();
            try {
                switch (choice) {
                case 1:
                    EncryptFile();
                    break;
                case 2:
                    DecryptFile();
                    break;
                case 3:
                    ShowFileContents();
                    break;
                case 4:
                    ShowFileInfo();
                    break;
                case 5:
                    cout << "Exiting... Goodbye!\n";
                    return;
                default:
                    cout << "Invalid choice. Please enter a number between 1 and 5.\n";
                }
            }
            catch (const runtime_error& e) {
                cout << e.what() << "\n";
            }
        }
    }

private:
    void ShowMenu(const string& border, const string& title) {
        cout << "\n" << border << "\n";
        cout << "| " << setw(title.size()) << title << " |\n";
        cout << border << "\n";
        cout << "1. Encrypt File\n";
        cout << "2. Decrypt File\n";
        cout << "3. Show File Contents\n";
        cout << "4. Show File Info\n";
        cout << "5. Exit\n";
    }

    int GetChoice() {
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    void EncryptFile() {
        string fileName, key;
        cout << "\n*** Encrypt File ***\n";
        cout << "Enter file name to encrypt: ";
        cin >> fileName;
        cout << "Enter encryption key: ";
        cin >> key;

        auto data = FileHandler::Load(fileName);
        for (auto& line : data) {
            SimpleCipher::EncryptDecrypt(line, key);
        }
        FileHandler::Save(fileName, data);
        cout << "File encrypted successfully.\n";
    }

    void DecryptFile() {
        string fileName, key;
        cout << "\n*** Decrypt File ***\n";
        cout << "Enter file name to decrypt: ";
        cin >> fileName;
        cout << "Enter decryption key: ";
        cin >> key;

        auto data = FileHandler::Load(fileName);
        for (auto& line : data) {
            SimpleCipher::EncryptDecrypt(line, key);
        }
        FileHandler::Save(fileName, data);
        cout << "File decrypted successfully.\n";
    }

    void ShowFileContents() {
        string fileName;
        cout << "\n*** Show File Contents ***\n";
        cout << "Enter file name to display contents: ";
        cin >> fileName;

        auto data = FileHandler::Load(fileName);
        cout << "File Contents:\n";
        for (const auto& line : data) {
            cout << line << "\n";
        }
    }

    void ShowFileInfo() {
        string fileName;
        cout << "\n*** Show File Info ***\n";
        cout << "Enter file name to display info: ";
        cin >> fileName;

        ifstream file(fileName, ios::binary | ios::ate);
        if (!file.is_open()) {
            throw runtime_error("Error: File could not be opened.");
        }
        streampos size = file.tellg();
        file.close();
        cout << "File Info:\n";
        cout << "File Name: " << fileName << "\n";
        cout << "File Size: " << size << " bytes\n";
    }
};
int main() {
    EncryptionManager app;
    app.Run();
    return 0;
}
