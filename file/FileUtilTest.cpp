#include "FileUtil.hpp"
#include "exceptions/FileExn.hpp"
#include "test/catch.hpp"

TEST_CASE("Test equivalentPaths") {
    std::vector<std::pair<std::string, std::string>> trueCases = {
        {".", "."},
        {"file/FileUtil.cpp", "file/FileUtil.cpp"},
        // Same file, different paths
        {"file/FileUtil.cpp", "./file/FileUtil.cpp"},
        // Convoluted path
        {"file/FileUtil.cpp", "./file/../file/././FileUtil.cpp"},
        // Multiple slashes in a row are ignored!
        {"file////FileUtil.cpp", "./file/../file/FileUtil.cpp"},
    };
    for (auto const &c : trueCases) {
        REQUIRE(equivalentPaths(c.first, c.second));
    }

    std::vector<std::pair<std::string, std::string>> falseCases = {
        {".", "file"},
        {"file/FileUtil.cpp", "file/FileUtil.hpp"},
        {"file////FileUtil.cpp", "."},
    };
    for (auto const &c : falseCases) {
        REQUIRE(!equivalentPaths(c.first, c.second));
    }

    std::vector<std::pair<std::string, std::string>> errCases = {
        // File does not exist
        {".", "fil"},
        {"fileFileUtil.cpp", "file/FileUtil.hpp"},
    };
    for (auto const &c : errCases) {
        REQUIRE_THROWS_AS(equivalentPaths(c.first, c.second), FileExn);
    }
}