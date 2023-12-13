#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <direct.h>
#include <fstream>
#include <sstream>
using namespace std;
// string recentPath = "Other Projects\\TermFlow\\recentFile.txt";
string recentPath = "File.txt";
const string vscodeCommand = "code";
const string directory = "C:\\Users\\Jereniah\\3D Objects\\Projects";
vector<string> filePaths;


int changeDirectory(string directory)
{
    int changeResult = _chdir(directory.c_str());
    return changeResult;
}

int openFile(string selectedPath )
{
    if (!selectedPath.empty())
    {
        string fullPath = directory + "\\" + selectedPath;
        
        string command = vscodeCommand + " \"" + fullPath + "\"";
        cout << selectedPath << endl;
        ofstream writeFile(recentPath, ios::app);
        if (writeFile.is_open())
        {
            if(!writeFile) {
                cout<<strerror(errno);
                return 1;
            }
            writeFile<<selectedPath;
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
            char buffer[128];
            if (fgets(buffer, sizeof(buffer), listFilePipe) != NULL)
            {
                buffer[strcspn(buffer, "\n")] = '\0';
                string selectedPath = buffer;
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
    }
    else if (argc == 2 && string(argv[1]) == "-r")
    {
        ifstream readFile("recentFile.txt");
        if (readFile)
        {
            string line;
            while (getline(readFile, line))
            {
                filePaths.push_back(line);
            }
            readFile.close();
        }
                const string listFilesCommand = "fzf < recentFile.txt";
                FILE *fzfPipe = _popen(listFilesCommand.c_str(), "r");
                char buffer[128];
                if (fgets(buffer, sizeof(buffer), fzfPipe) != NULL)
                {
                    buffer[strcspn(buffer, "\n")] = '\0';
                    string selectedPath = buffer;
                    cout<<selectedPath;
                    int closeResult = _pclose(fzfPipe);
                    if (closeResult == -1)
                    {
                        cout<<"Error closing pipe"<<endl;
                        return -1;
                    }
                    cout<<selectedPath<<endl;   
                    int fileresult = openFile(selectedPath);
                    if (fileresult != 0)
                    {
                        cout << "Error opening file in VS Code" << endl;
                        return 1;
                    }
                }
        }
    

    return 0;
}
