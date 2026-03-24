#include "doctest.h"
#include <compiler/utils/file_reader.h>

TEST_SUITE_BEGIN("Tests File Reader");

TEST_CASE("Read File")
{
    // Setup
    // ===============================
    std::filesystem::path file_path = "tests-resources/test_cypp_code.cypp";
    std::string file_content;
    
    // Execute
    // ===============================
    bool result = file_reader::read_file(file_path, ".cypp", file_content);
    
    // Verify
    // ===============================
    CHECK(result == true);
    CHECK(file_content == 
        "// Declare constants\n"
        "const string print_val = \"Hello from cy++\";\n"
        "const int exit_val = 3;\n"
        "\n"
        "// Execute instructions\n"
        "print(print_val);\n"
        "print(\"You can try this at home!\");\n"
        "\n"
        "exit(exit_val);"
    );
    
}

TEST_CASE("Read File Not Existing")
{
    // Setup
    // ===============================
    std::filesystem::path file_path = "tests-resources/non_existing_file.cypp";
    std::string error_message;
    
    // Execute
    // ===============================
    bool result = file_reader::read_file(file_path, ".cypp", error_message);
    
    // Verify
    // ===============================
    CHECK(result == false);
    CHECK(error_message == "Given path doesn't exists!");
}

TEST_CASE("Read File Wrong Extension")
{
    // Setup
    // ===============================
    std::filesystem::path file_path = "tests-resources/test_cypp_code.cypp";
    std::string error_message;
    
    // Execute
    // ===============================
    bool result = file_reader::read_file(file_path, ".cpp", error_message);
    
    // Verify
    // ===============================
    CHECK(result == false);
    CHECK(error_message == "File extension is not .cpp!");
}

TEST_SUITE_END;