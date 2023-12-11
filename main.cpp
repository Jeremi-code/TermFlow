#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include <fstream>
#include <sstream>
using namespace std;
const string vscodeCommand = "code";
const string directory = "C:\\Users\\Jereniah\\3D Objects\\Projects";
vector<string> filePaths;
// string filePaths[10];
fstream writeFile("recentFile.txt",ios::app);


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
        cout<<fullPath;
        // writeFile.open("recentFile.txt",ios::out);
        if (writeFile) {
            writeFile<<fullPath;
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
        int changeResult = changeDirectory(directory);
        if (changeResult == 0)
        {
            const string listFilesCommand = "fd --type d --color=never . | fzf ";
            FILE *listFilePipe = _popen(listFilesCommand.c_str(), "r");
            string selectedPath;
            pipeRead(listFilePipe, selectedPath);
            int result = openFile(selectedPath);
            if (result != 0)
            {
                return 1;
            }
        }
    }
    else if (argc == 2)
    {
        ostringstream oss;
        if (string(argv[1]) == "-r")
        {
            ifstream readFile;
            char fileDir[128];
            string line;
            char buffer[128];
            readFile.open("recentFile.txt",ios::in);
            if (readFile) {
                while(!readFile.eof()) {
                    for (int i=0;i<3;i++){
                    readFile>>fileDir;
                    line += string(" ")+fileDir;

                    }
                    filePaths.push_back(line);
                }
            readFile.close();
            }
            FILE* fzfPipe = _popen("fzf","w");
            if (fzfPipe) {
            for (const auto& filePath : filePaths) {
                fprintf(fzfPipe, "%s\n", filePath.c_str());
            }
            }
            fclose(fzfPipe);
        }
    }
    return 0;
}
