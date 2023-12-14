#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include <fstream>
using namespace std;
string recentPath = "Other Projects\\TermFlow\\recentFile.txt";
const string directory = "C:\\Users\\Jereniah\\3D Objects\\Projects";
vector<string> filePaths;

void pipeRead(FILE *listFilePipe, string &selectedPath)
{
    char buffer[128];
    while (fgets(buffer, 128, listFilePipe) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        selectedPath += buffer;
    }
}
void readRecentProjects()
{
    ifstream readFile(recentPath, ios::in);
    string line;
    if (readFile.is_open())
    {
        if (readFile)
        {
            int i = 0;
            while (!readFile.eof() && i <= 10)
            {
                getline(readFile, line);
                if (!line.empty())
                {
                    filePaths.push_back(line);
                }
                i++;
            }
            readFile.close();
        }
    }
}
void writeRecentProjects()
{
    ofstream writeFile;
    writeFile.open(recentPath, ios::out);
    if (writeFile.is_open())
    {
        for (const auto &filePath : filePaths)
        {
            if (!filePath.empty())
            {
                writeFile << filePath + "\n";
            }
        }
    }
}
int vecLength()
{
    int count = 0;
    for (const auto &filePath : filePaths)
    {
        count += 1;
    }
    return count;
}
int checkMembership(string line)
{
    for (int i = 0; i < vecLength(); i++)
    {
        if (filePaths[i] == line)
        {
            return i;
        }
    }
    return -1;
}
void insertFilePaths()
{
    if (vecLength() == 10)
    {
        if (checkMembership(selectedPath) != -1)
        {
            int index = checkMembership(selectedPath);
            filePaths.erase(filePaths.begin() + index);
            filePaths.push_back(selectedPath);
        }
        else
        {
            filePaths.erase(filePaths.begin());
            filePaths.push_back(selectedPath);
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
        }
    }
}
int openFile(string selectedPath)
{
    if (!selectedPath.empty())
    {
        readRecentProjects();
        insertFilePaths();
        string fullPath = directory + "\\" + selectedPath;
        const string vscodeCommand = "code";
        string command = vscodeCommand + " \"" + fullPath + "\"";
        writeRecentProjects();
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
