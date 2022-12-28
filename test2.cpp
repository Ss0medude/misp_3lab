#include <UnitTest++/UnitTest++.h>
#include "/home/stud/modAlphaCipher.h"
#include "/home/stud/modAlphaCipher.cpp"
SUITE(KeyTest)
{
    TEST(ValidKey) {
        CHECK_EQUAL("LLEHO",modAlphaCipher("4").encrypt("HELLO"));
    }
    TEST(LetterInKey) {
        CHECK_THROW(modAlphaCipher cp("А1"),Wrong key);
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("1,1"),Wrong key);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("1 1"),Wrong key);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""),Wrong key);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("1"),Wrong key);
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
        CHECK_THROW(p->encrypt(""),Wrong text);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("123456789"),Wrong text);
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
        CHECK_THROW(p->decrypt("imowatehllsin"),Wrong text);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("IMO WATEHLLSIN"),Wrong text);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p->decrypt("123IMOWATEHLLSIN"),Wrong text);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p->decrypt("IMOWATEHLLSIN!"),Wrong text);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""),Wrong text);
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
