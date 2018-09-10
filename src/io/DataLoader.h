#ifndef _LL_DATALOADER_H_
#define _LL_DATALOADER_H_

#include <string>
#include <vector>

#include "../utils/filesystem.h"

namespace LLib
{

namespace IO
{

    class DataLoader
    {
        public:
            DataLoader(const std::string &path_, isSort = false) : path(path_), num(0) { 
                file_list = utils::get_files(path, isSort);
            }

            bool is_empty() const { return num == file_list.size(); }

            void reset() { num = 0; }

            std::string next() { return file_list[num++]; }

            void print() const { for(auto &f: file_list) std::cout << f << std::endl; }

            int num() const { return file_list.size(); }

        private:
            std::vector<std::string> file_list;
            int num;

    };  // class DataLoder

}   // namespace IO
}   // namespace LLib

#endif  // _LL_DATALOADER_H_