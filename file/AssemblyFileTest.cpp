#include "AssemblyFile.hpp"
#include "FirstPass.hpp"
#include "test/catch.hpp"
#include <cstdlib>
#include <unistd.h>
#include "FileUtil.hpp"

char const *TEST_FILE = R"(
label1:
    ADD EE      ; Operation, so program address should increment

label2: LDI 1
    .const const1 1234
    .org 25
label3:         ; Label after .org
    .const const2 3333
    NOP         ; Another instruction, to increment the program address
    .data 10    ; Exercise data address
    .byte 0F
)";

TEST_CASE("Test AssemblyFile FirstPass no include") {
    // Get temporary filename
    char tempFilename[] = "tmp/XXXXXX";
    int tempfd = mkstemp(tempFilename);

    // Write file
    FILE *tempf = fdopen(tempfd, "w");
    REQUIRE(fputs(TEST_FILE, tempf) >= 0);
    fclose(tempf);

    // Read file
    Context c;
    FirstPass firstPass(c);
    AssemblyFile assemblyFile(tempFilename);
    REQUIRE(assemblyFile.doPass(firstPass) == 0);

    // The file is no longer needed
    REQUIRE(remove(tempFilename) == 0);

    REQUIRE(c.getCurProgramAddress() == 0x26);
    REQUIRE(c.getCurDataAddress() == 0x11);
    REQUIRE(c.lookupLabel(Name("label1")) == Number(0x0));
    REQUIRE(c.lookupLabel(Name("label2")) == Number(0x1));
    REQUIRE(c.lookupLabel(Name("label3")) == Number(0x25));
    REQUIRE(c.lookupConstant(Name("const1")) == Number(0x1234));
    REQUIRE(c.lookupConstant(Name("const2")) == Number(0x3333));
}

char const *TEST_FILE_ROOT = R"(
root_label1:
    .include child1.asm
    CMP $number
    .include child2.asm
    ASR
root_label2:
)";

char const *TEST_FILE_CHILD1 = R"(
    .org 10
child1_label:
)";

char const *TEST_FILE_CHILD2 = R"(
child2_label:
    .const child2_const 22
)";

TEST_CASE("Test AssemblyFile FirstPass include") {
    // Make temp directory
    char tempDir[] = "tmp/dirXXXXXX";
    REQUIRE(mkdtemp(tempDir) != nullptr);

    std::string rootFile = joinPaths(tempDir, "root.asm");
    std::string child1File = joinPaths(tempDir, "child1.asm");
    std::string child2File = joinPaths(tempDir, "child2.asm");

    // Write files
    {
        std::ofstream(rootFile) << TEST_FILE_ROOT;
        std::ofstream(child1File) << TEST_FILE_CHILD1;
        std::ofstream(child2File) << TEST_FILE_CHILD2;
        // All files go out of scope and are closed
    }

    // Read file
    Context c;
    FirstPass firstPass(c);
    AssemblyFile assemblyFile(rootFile);
    REQUIRE(assemblyFile.doPass(firstPass) == 0);

    // The files are no longer needed
    REQUIRE(remove(rootFile.c_str()) == 0);
    REQUIRE(remove(child1File.c_str()) == 0);
    REQUIRE(remove(child2File.c_str()) == 0);
    REQUIRE(rmdir(tempDir) == 0);

    REQUIRE(c.getCurProgramAddress() == 0x12);
    REQUIRE(c.getCurDataAddress() == 0x0);
    REQUIRE(c.lookupLabel(Name("root_label1")) == Number(0x0));
    REQUIRE(c.lookupLabel(Name("child1_label")) == Number(0x10));
    REQUIRE(c.lookupLabel(Name("child2_label")) == Number(0x11));
    REQUIRE(c.lookupLabel(Name("root_label2")) == Number(0x12));
    REQUIRE(c.lookupConstant(Name("child2_const")) == Number(0x22));
}


char const *TEST_FILE_LOOP1 = R"(
    CALL label
    .include loop2.asm
)";

char const *TEST_FILE_LOOP2 = R"(
    .const hello 1
    .include loop1.asm
)";

TEST_CASE("Test AssemblyFile include loop") {
    // Make temp directory
    char tempDir[] = "tmp/dirXXXXXX";
    REQUIRE(mkdtemp(tempDir) != nullptr);

    std::string loop1File = joinPaths(tempDir, "loop1.asm");
    std::string loop2File = joinPaths(tempDir, "loop2.asm");

    // Write files
    {
        std::ofstream(loop1File) << TEST_FILE_LOOP1;
        std::ofstream(loop2File) << TEST_FILE_LOOP2;
        // All files go out of scope and are closed
    }

    // Read file
    Context c;
    FirstPass firstPass(c);
    AssemblyFile assemblyFile(loop1File);
    REQUIRE(assemblyFile.doPass(firstPass) == 1);
    // Unfortunately, we aren't able to check why the FilePass failed,
    // i.e. we are not able to check stderr

    // The files are no longer needed
    REQUIRE(remove(loop1File.c_str()) == 0);
    REQUIRE(remove(loop2File.c_str()) == 0);
    REQUIRE(rmdir(tempDir) == 0);
}

