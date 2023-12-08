#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
using namespace std;
const string vscodeCommand = "code";
const string directory = "C:\\Users\\Jereniah\\3D Objects\\Projects";

int changeDirectory(string directory)
{
    int changeResult = _chdir(directory.c_str());
    if (changeResult != 0)
    {
        cout << "Failed to change directory" << endl;
        return 1;
    }
    return 0;
}
void pipeRead(FILE* listFilePipe, string& selectedPath)
{
    char buffer[128];
    while (fgets(buffer, 128, listFilePipe) != NULL)
    {
        selectedPath += buffer;
    }
}
int openFile(string selectedPath)
{
    if (!selectedPath.empty()) {

    string command = vscodeCommand + " " + selectedPath;
    int result = system(command.c_str());

    if (result != 0)
    {
        cout << "Failed to open vscode" << endl;
        return 1;
    }
    return 0;
    } else {
        cerr << "No file selected" << endl;
        return 1;
    }
}


int main(int argc, char **argv)
{
    if (argc == 1)
    {
        int changeResult = changeDirectory(directory);
        if (changeResult == 0)
        {
            const string listFilesCommand = "fd --type d --color=never . | fzf --print-query";
            FILE *listFilePipe = _popen(listFilesCommand.c_str(), "r");
            // const string listFilesCommand = ("fd  --type f --type d --color=never . " + directory + "| fzf --print-query");
            if (!listFilePipe)
            {
                cout << "Failed to open pipe" << endl;
                return 1;
            }
            string selectedPath;
            pipeRead(listFilePipe, selectedPath);
            if (_pclose(listFilePipe) != 0)
            {
                cout << "Failed to close pipe" << endl;
                return 1;
            }
            // selectedPath.erase(remove(selectedPath.c_str().begin(), selectedPath.c_str().end(), '\n'), selectedPath.end());
               }
    }
    return 0;
}

