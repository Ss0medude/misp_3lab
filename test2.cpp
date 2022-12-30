#include <UnitTest++/UnitTest++.h>
#include "/home/stud/modAlphaCipher.h"
#include "/home/stud/modAlphaCipher.cpp"
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("LLEHO",modAlphaCipher("4").encrypt("HELLO"));
    }
    TEST(LetterInKey) {
        CHECK_THROW(modAlphaCipher cp("А1"),error_cipher);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("1,1"),error_cipher);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("1 1"),error_cipher);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),error_cipher);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("1"),error_cipher);
    }
}

struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher("4");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("IMOWATEHLLSIN",
                    p->encrypt("LEWISHAMILTON"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("IMOWATEHLLSIN",
                    p->encrypt("lewishamilton"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("IMOWATEHLLSIN",
                    p->encrypt("LEWIS HAMILTON!"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
        CHECK_EQUAL("IMOWATEHLLSIN", p->encrypt("LEWIS!HAMILTON"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""),error_cipher);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("123456789"),error_cipher);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("NOTLIMAHSIWEL",
                    modAlphaCipher("13").encrypt("LEWISHAMILTON"));
    }
}

SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("LEWISHAMILTON",
                    p->decrypt("IMOWATEHLLSIN"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p->decrypt("imowatehllsin"),error_cipher);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("IMO WATEHLLSIN"),error_cipher);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("123IMOWATEHLLSIN"),error_cipher);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("IMOWATEHLLSIN!"),error_cipher);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),error_cipher);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("NOTLIMAHSIWEL",
                    modAlphaCipher("13").encrypt("LEWISHAMILTON"));
    }
}

int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
