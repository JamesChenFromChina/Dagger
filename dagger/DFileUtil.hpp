
#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <string>

namespace Dagger {
    namespace Utils {
        enum DirEntryType {
            DIR_ENTRY_TYPE_FILE = 0,
            DIR_ENTRY_TYPE_DIR = 1,
            DIR_ENTRY_TYPE_ERR_STAT = 2,
            DIR_ENTRY_TYPE_ERR_RDIR = 3
        };


        class DFileUtil {
        public:
            typedef int (*TraversePred)(const std::string &path,
                                        DirEntryType type,
                                        void *param);
        public:
            static void SetCurrentDir(const ::std::string &dir);
            static void GetCurrentDir(::std::string &cur);
            static ::std::string GetCurrentDir();
            static void ResolvePath(const ::std::string &path,
                                    ::std::string *dir,::std::string *filename,
                                    ::std::string *extname);
            static void GetFullPath(::std::string &path);
            static int TraverseDir(const std::string &path,
                                    DFileUtil::TraversePred pred,
                                    void *param);

        private:
            static int traversesDirInner(std::string &path,DFileUtil::TraversePred pred,void *param);
        };
    }
}

#endif /* FILEUTIL_H */