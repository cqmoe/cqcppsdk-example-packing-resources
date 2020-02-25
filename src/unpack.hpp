#pragma once

#include <cqcppsdk/cqcppsdk.hpp>

#include <string>

#include <Windows.h>

inline bool unpack_resource(const HMODULE module, const WORD id, const std::string &dst_path,
                            const std::string &type = "BIN") {
    using cq::utils::s2ws;

    auto res_id = FindResourceW(module, MAKEINTRESOURCEW(id), s2ws(type).c_str()); // 查找资源
    auto res = LoadResource(module, res_id); // 加载资源
    auto p_res = LockResource(res); // 锁定资源
    if (!p_res) {
        return false; // 锁定失败
    }

    auto res_size = SizeofResource(module, res_id); // 得到待释放资源文件大小
    auto res_file = CreateFileW(s2ws(dst_path).c_str(),
                                GENERIC_WRITE,
                                0,
                                nullptr,
                                CREATE_ALWAYS,
                                FILE_ATTRIBUTE_NORMAL,
                                nullptr); //创建文件

    if (INVALID_HANDLE_VALUE == res_file) {
        return false; // 创建文件失败
    }

    auto ret = WriteFile(res_file, p_res, res_size, nullptr, nullptr); // 写入文件
    if (!ret) {
        return false;
    }

    CloseHandle(res_file); // 关闭文件句柄
    return true;
}
