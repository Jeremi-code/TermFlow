#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include <fstream>
#include <sstream>
using namespace std;
string recentPath = "Other Projects\\TermFlow\\recentFile.txt";
// string recentPath = "File.txt";
const string vscodeCommand = "code";
const string directory = "C:\\Users\\Jereniah\\3D Objects\\Projects";
vector<string> filePaths;

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
        buffer[strcspn(buffer, "\n")] = '\0';
        selectedPath += buffer;
    }
}

int openFile(string selectedPath)
{
    if (!selectedPath.empty())
    {
        string fullPath = directory + "\\" + selectedPath;

        string command = vscodeCommand + " \"" + fullPath + "\"";
        ofstream writeFile(recentPath, ios::app);
        if (writeFile.is_open())
        {
            if (!writeFile)
            {
                cout << strerror(errno);
                return 1;
            }
            writeFile << selectedPath<<endl;
            writeFile.flush();
            writeFile.close();
        }

        int result = system(command.c_str());
        return result;
    }
    return 1;
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        const string listFilesCommand = "fd --type d --color=never . | fzf ";
        FILE *listFilePipe = _popen(listFilesCommand.c_str(), "r");
        string selectedPath;
        pipeRead(listFilePipe, selectedPath);
        int closeResult = _pclose(listFilePipe);
        if (closeResult != 0)
        {
            return -1;
        }
        int result = openFile(selectedPath);
        if (result != 0)
        {
            return 1;
        }
    }
    else if (argc == 2 && string(argv[1]) == "-r")
    {
        ifstream readFile(recentPath);
        if (readFile)
        {
            cout<<"file exists";
            string line;
            while (getline(readFile, line))
            {
                filePaths.push_back(line);
            }
            readFile.close();
        }
        string selectedPath;
        const string listFilesCommand = "fzf < \"Other Projects\\TermFlow\\recentFile.txt\" ";
        FILE *fzfPipe = _popen(listFilesCommand.c_str(), "r");
        pipeRead(fzfPipe, selectedPath);
        int closeResult = _pclose(fzfPipe);
        if (closeResult != 0)
        {
            return -1;
        }
        int result = openFile(selectedPath);
        if (result != 0)
        {
            return 1;
        }
    }

    return 0;
}
