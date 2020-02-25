#include <cqcppsdk/cqcppsdk.h>

#include "unpack.hpp"

#include "resource.h"

HMODULE gModule = nullptr;

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        gModule = module;
    }
    return TRUE;
}

CQ_INIT {
    using namespace cq;
    using std::filesystem::path;

    on_enable([] {
        logging::info("启用", "插件已启用");

        const auto ok = unpack_resource(gModule, IDR_WEB_INDEX_HTML, (path(dir::app("web")) / "index.html").string())
                        && unpack_resource(gModule, IDR_ZIP_FOO, (path(dir::app("zip")) / "foo.zip").string());
        if (ok) {
            logging::info("解包", "解包资源文件成功");
        } else {
            logging::error("解包", "解包资源文件失败");
        }
    });
}
