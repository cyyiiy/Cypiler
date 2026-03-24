#include "doctest.h"
#include <compiler/utils/file_writer.h>

TEST_SUITE_BEGIN("Tests File Writer");

TEST_CASE("Write File")
{
    // Setup
    // ===============================
    std::filesystem::path file_path = "tests-resources/test_write_file.asm";
    std::string file_content = "file content";
    std::string error_message;
    
    // Execute
    // ===============================
    bool result = file_writer::write_file(file_path, file_content, error_message);
    
    // Verify
    // ===============================
    CHECK(result == true);
    CHECK(error_message.empty());
    
    // Teardown
    // ===============================
    std::filesystem::remove(file_path);
}

TEST_SUITE_END;