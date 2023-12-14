#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include <fstream>
#include <sstream>
#include <algorithm>
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
void readRecentProject()
{
    ifstream readFile(recentPath, ios::in);
    string line;
    string fakeLine;
    if (readFile.is_open())
    {
        if (readFile)
        {
            int i = 0;
            while (!readFile.eof() && i <= 10)
            {
                // readFile.peek() ==char_traits<char>::eof() 
                getline(readFile, line);
                if (!line.empty()) {
                    filePaths.push_back(line);
                }
                // readFile>>line;
                i++;
            }
            readFile.close();
        }
    }
}
int openFile(string selectedPath)
{
    if (!selectedPath.empty())
    {   
        readRecentProject();
        if (vecLength() == 10)
        {
            cout << "donaruma";
            if (checkMembership(selectedPath) != -1)
            {
                int index = checkMembership(selectedPath);
                filePaths.erase(filePaths.begin() + index);
                filePaths.push_back(selectedPath);
                cout<<"a";
            }
            else
            {
                filePaths.erase(filePaths.begin());
                filePaths.push_back(selectedPath);
                cout<<"b";
            }
        }
        else
        {
            if (checkMembership(selectedPath) != -1)
            {
                int index = checkMembership(selectedPath);
                filePaths.erase(filePaths.begin() + index);
                filePaths.push_back(selectedPath);
            }
            else
            {
                filePaths.push_back(selectedPath);
                cout<<filePaths[0];
            }
        }
        string fullPath = directory + "\\" + selectedPath;

        string command = vscodeCommand + " \"" + fullPath + "\"";
        ofstream writeFile;
        writeFile.open(recentPath,ios::out);
        if (writeFile.is_open())
        {
            for (const auto &filePath : filePaths)
            {
                if (!filePath.empty()) {
                writeFile << filePath + "\n";
                }
            }
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
