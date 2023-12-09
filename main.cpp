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
    return changeResult;
}
void pipeRead(FILE *listFilePipe, string &selectedPath)
{
    char buffer[128];
    while (fgets(buffer, 128, listFilePipe) != NULL)
    {
        buffer[strcspn(buffer,"\n")] = '\0';
        selectedPath += buffer;
    }
}
int openFile(string selectedPath)
{
    if (!selectedPath.empty())
    {
        string fullPath  = directory + "\\" + selectedPath;
        string command = vscodeCommand + " \"" + fullPath + "\"";
        int result = system(command.c_str());
        return result;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        int changeResult = changeDirectory(directory);
        if (changeResult == 0)
        {
            const string listFilesCommand = "fd --type d --color=never . | fzf ";
            FILE *listFilePipe = _popen(listFilesCommand.c_str(), "r");
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
            int result = openFile(selectedPath);
            if (result != 0)  {
                return 1;
            }
            
        }
    }
    return 0;
}
