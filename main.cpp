#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main()
{
    const string vscodeCommand = "code";
    const string directory = "C:\\Users\\Jereniah\\3D Objects\\Projects";
    const string changeDirectory = "cd" + directory;
    int directoryResult = system(changeDirectory.c_str());
        // const string listFilesCommand = ("fd  --type f --type d --color=never . " + directory + "| fzf --print-query");
    const string listFilesCommand = "fd --type f --type d --color=never . | fzf --print-query";
    FILE *listFilePipe = _popen(listFilesCommand.c_str(), "r");
    cout << listFilePipe << endl;
    if (!listFilePipe)
    {
        cout << "Failed to open pipe" << endl;
        return 1;
    }
    char buffer[128];
    string selectedPath;
    while (fgets(buffer, 128, listFilePipe) != NULL)
    {
        selectedPath += buffer;
    }
    if (_pclose(listFilePipe) != 0)
    {
        cout << "Failed to close pipe" << endl;
        return 1;
    }
    // selectedPath.erase(remove(selectedPath.c_str().begin(), selectedPath.c_str().end(), '\n'), selectedPath.end());
    if (!selectedPath.empty())
    {
        string command = vscodeCommand + " " + selectedPath;
        int result = system(command.c_str());

        if (result != 0)
        {
            cout << "Failed to open vscode" << endl;
            return 1;
        }
    }
    else
    {
        cerr << "No file selected" << endl;
    }

    return 0;
}