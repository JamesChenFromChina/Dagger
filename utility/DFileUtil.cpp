
#include "DFileUtil.hpp"

#ifdef WIN32
#include <windows.h>
#elif __linux__
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <string.h>

#include "DECode.h"

#endif

using namespace Dagger::Utils;

using namespace std;

void DFileUtil::SetCurrentDir(const ::std::string &path)
{
#ifdef WIN32
    SetCurrentDirectory(path.c_str());
#elif __linux__
    chdir(path.c_str());
#endif
}


void DFileUtil::GetCurrentDir(string &cur) {

#ifdef WIN32
    const int pathLen = 1000;
#elif __linux__
    const int pathLen = PATH_MAX;
#endif

    char buf[pathLen];
#ifdef WIN32
    GetCurrentDirectory(pathLen,buf);
#elif __linux__
    getcwd(buf,pathLen);
#endif
    cur = buf;
}

::std::string DFileUtil::GetCurrentDir()
{
    string cur;
    GetCurrentDir(cur);
    return cur;
}

void DFileUtil::ResolvePath(const ::std::string &path,
                            ::std::string *dir,
                            ::std::string *filename,
                            ::std::string *extname)
{
    string fullPath = path;
    GetFullPath(fullPath);
    string::size_type lastSlashPos = fullPath.find_last_of("/\\");

    if (dir)
    *dir = fullPath.substr(0,lastSlashPos);

    string::size_type dotaPos = fullPath.find_last_of(".");
    if (dotaPos == string::npos)
    {
        if (filename) {
            *filename = fullPath.substr(lastSlashPos + 1,string::npos);
        }

        if (extname) {
            *extname = "";
        }
        return;
    }

    if (filename) {
        *filename = fullPath.substr(lastSlashPos + 1,dotaPos - lastSlashPos - 1);
    }

    if (extname) {
        *extname = fullPath.substr(dotaPos + 1,string::npos);
    }
}

void DFileUtil::GetFullPath(::std::string &path) {
#ifdef WIN32
    if (path->at(1) != ':')
    path = (DFileUtil::GetCurrentDir() + path);
#elif __linux__
    if (path.size() > 0 && path.front() == '~') {
        path.erase(path.begin());
        const char *homeStr = getenv("HOME");
        path.insert(0,homeStr);
    }
    char realPath[PATH_MAX];
    realpath(path.c_str(),realPath);
    path = realPath;
#endif
}

int DFileUtil::traversesDirInner(std::string &path,DFileUtil::TraversePred pred,void *param) {
    struct stat statBuf;
    if (lstat(path.c_str(), &statBuf) < 0) {   /* stat error*/
        return pred(path.c_str(),DIR_ENTRY_TYPE_ERR_STAT,param);
    }

    if (S_ISDIR(statBuf.st_mode) == 0) {  /* not a directory */
        return pred(path.c_str(),DIR_ENTRY_TYPE_FILE,param);
    }

    int ret = (0);
    if ((ret = pred(path.c_str(),DIR_ENTRY_TYPE_DIR,param)) < 0) {
        return ret;
    }

    path.append("/");
    size_t pos = path.size();

    DIR *dp;
    if ((dp = opendir(path.c_str())) == NULL) {
        return pred(path.c_str(),DIR_ENTRY_TYPE_ERR_RDIR,param);
    }

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0
            || strcmp(dirp->d_name, "..") == 0) {
            continue;
        }
        path.append(dirp->d_name);
        if ((ret = traversesDirInner(path,pred,param)) < 0) {
            break;
        }
        path.erase(pos);
    }

    if (closedir(dp) < 0) {
        return -1;
    }

    return 0;
}

int DFileUtil::TraverseDir(const std::string &path,DFileUtil::TraversePred pred,void *param) {
    string localPath = path;
    GetFullPath(localPath);
    return traversesDirInner(localPath,pred,param);

#ifdef WIN32
    char save_path[200];
    char szFile[MAX_PATH] = {0};
    char szFind[MAX_PATH];

    WIN32_FIND_DATA FindFileData;
    strcpy(szFind,lpPath);

    strcat(szFind,"*");
    HANDLE hFind = FindFirstFile(szFind,&FindFileData);

    if(INVALID_HANDLE_VALUE == hFind) return;

    uint32_t foundCounter = 0;

    while(TRUE)
    {
        if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            if(FindFileData.cFileName[0]!='.')
            {
                strcpy(szFile,lpPath);
                strcat(szFile,FindFileData.cFileName);
                strcat(szFile,"\\");
                Traverse(szFile,pred,param);
            }
        }
        else
        {
            pred((::std::string(lpPath) + FindFileData.cFileName).c_str(),param);
        }

        if(!FindNextFile(hFind,&FindFileData)) break;
    }
    FindClose(hFind);
#endif
}
