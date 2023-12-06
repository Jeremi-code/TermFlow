#include <iostream>
#include <dirent.h>
#include<sys/stat.h>
using namespace std;
int main() {
    const char* directoryPath = "C:\\Users\\Jereniah\\3D Objects\\Projects";
    DIR* dir = opendir(directoryPath);

    if (dir) {
        cout << "Files in directory " << directoryPath << ":\n";

        dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            string filePath = string(directoryPath) + "/" + entry->d_name;
            struct stat fileStat;
            // Print only regular files (not directories)
            if(stat(filePath.c_str(), &fileStat) == 0 ) {
                cout << entry->d_name << "\n";
            }
        }

        closedir(dir);
    } else {
        std::cerr << "Error opening directory.\n";
    }

    return 0;
}
