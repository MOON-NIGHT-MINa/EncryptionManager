#ifndef ENCRYPTIONAPP_H
#define ENCRYPTIONAPP_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class EncryptionApp {
public:
    EncryptionApp();
    void Run();

private:
    void ShowMainMenu();
    void EncryptFile();
    void DecryptFile();
    void ViewFileContents();
    void SaveToFile(const std::string& fileName, const std::vector<std::string>& data);
    std::vector<std::string> LoadFromFile(const std::string& fileName);
    std::string ReadFileName(const std::string& message);
    void PrintMessage(const std::string& message);

    static const char ENCRYPTION_KEY = 'K'; // Simple XOR encryption key

    enum MenuChoice { Encrypt = 1, Decrypt, View, Exit };
};

#endif // ENCRYPTIONAPP_H
