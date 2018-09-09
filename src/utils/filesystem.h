#ifndef _LL_FILE_H_
#define _LL_FILE_H_


#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

// Encapsulation of filesystem library
// https://en.cppreference.com/w/cpp/filesystem
// compile option: -std=c++17 -lstdc++fs

// TODO: need test

namespace LLib
{

namespace utils
{

    bool is_directory(const std::string &path_str)
    {
        fs::path path(path_str);
        return is_directory(path);
    }

    void remove(const std::string &path_str)
    {
        fs::path path(path_str);
        fs::remove(path);
    }

    void remove_dir(const std::string &path_str)
    {
        fs::path path(path_str);
        fs::remove_all(path);
    }

    bool equivalent(const std::string &path_str_1, const std::string &path_str_2)
    {
        fs::path path_1(path_str_1);
        fs::path path_2(path_str_2);
        return fs::equivalent(path_1, path_2);
    }

    void rename(const std::string &path_str_old, const std::string &path_str_new)
    {
        fs::path path_old(path_str_old);
        fs::path path_new(path_str_new);
        return fs::rename(path_old, path_new);
    }

    std::string current_path()
    {
        return fs::current_path().string();
    }

    void change_path(const std::string &path_str)
    {
        fs::path path(path_str);
        fs::current_path(path);
    }

    std::string absolute(const std::string &path_str)
    {
        fs::path path(path_str);
        return fs::absolute(path).string();
    }

    bool create_directory(const std::string &path_str)
    {
        fs::path path(path_str);
        return fs::create_directory(path);
    }

    std::string replace_extension(const std::string &path_str, const std::string &new_extension)
    {
        fs::path path(path_str);
        path.replace_extension(new_extension);
        return path.string();
    }

    std::string replace_filename(const std::string &path_str, const std::string &new_filename)
    {
        fs::path path(path_str);
        path.replace_filename(new_filename);
        return path.string();
    }

    std::string remove_filename(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.remove_filename().string();
    }

    // Decompose

    std::string root_name(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.root_name().string();
    }

    std::string root_directory(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.root_directory().string();
    }

    std::string root_path(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.root_path().string();
    }

    std::string relative_path(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.relative_path().string();
    }

    std::string parent_path(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.parent_path().string();
    }

    std::string filename(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.filename().string();
    }

    std::string stem(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.stem().string();
    }

    std::string extension(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.extension().string();
    }


    // Inquire

    bool is_absolute(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.is_absolute();
    }

    bool is_relative(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.is_relative();
    }

    bool is_empty(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.empty();
    }

    bool has_root_path(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_root_path();
    }

    bool has_root_name(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_root_name();
    }

    bool has_root_directory(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_root_directory();
    }

    bool has_relative_path(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_relative_path();
    }

    bool has_parent_path(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_parent_path();
    }

    bool has_filename(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_filename();
    }

    bool has_stem(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_stem();
    }

    bool has_extension(const std::string &path_str)
    {
        fs::path path(path_str);
        return path.has_extension();
    }

    std::string path_concat(const std::string& path_str_1, const std::string &path_str_2)
    {
        fs::path path(path_str_1);
        path /= path_str_2;
        return path.string();
    }

    std::vector<std::string> get_files(const std::string &path, bool isSort = false)
    {
        std::vector<std::string> file_list;

        for(auto& p: fs::directory_iterator(path))
            file_list.push_back(p.path().string());

        if(isSort) std::sort(file_list.begin(), file_list.end());

        return std::move(file_list);
    }

}   // namespace utils

}   // namespace LLib


#endif  // _LL_FILE_H_