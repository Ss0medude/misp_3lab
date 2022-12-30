#include <UnitTest++/UnitTest++.h>
#include "/home/stud/modAlphaCipher.h"
#include "/home/stud/modAlphaCipher.cpp"
using namespace std;


SUITE(KeyTest) //макрос для создания набора тестов
{
    TEST(ValidKey) {//макрос для создания одного теста
        CHECK_EQUAL("АБВАБ", modAlphaCipher("АБВ").encrypt("АВДАВ"));
    }
    TEST(LongKey) {
        CHECK_EQUAL("АБВГД",modAlphaCipher("АБВГДЕЁЖЗ").encrypt("АВДЁЗ"));//макрос для проверки полученного результата и ожидаемого
    }
    TEST(LowCaseKey) {
        CHECK_EQUAL("АБВАБ", modAlphaCipher("абвгдеёжз").encrypt("АВДЁЗ"));
    }
    TEST(DigitsInKey) {
        CHECK_THROW(modAlphaCipher cp("А1"), cipher_error);// марос для проверки на возбуждение исключения
    }
    TEST(PunctuationInKey) {
        CHECK_THROW(modAlphaCipher cp("А+Б"), cipher_error);
    }
    TEST(WhitespaceInKey) {
        CHECK_THROW(modAlphaCipher cp("А Б"), cipher_error);
    }
    TEST(EmptyKey) {
        CHECK_THROW(modAlphaCipher cp(""), cipher_error);
    }
    TEST(WeakKey) {
        CHECK_THROW(modAlphaCipher cp("ААА"), cipher_error);
    }
}
struct KeyB_fixture {//слово struct использовано вместо class чтобы сделать все
    modAlphaCipher* p;//члены класса открытыми
    KeyB_fixture()
    {
        p = new modAlphaCipher("АБВ");//класс, который в конструкторе создает динамический экземпляр шифратора с ключом «B», а в
    }                               //деструкторе — уничтожает:
    ~KeyB_fixture()
    {
        delete p;
    }
};
SUITE(EncryptTest)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {//использовать вместо макроса TEST потому что ключ один
        CHECK_EQUAL("ХПЩУТЁАУЮКФТСПДУЯ", p->encrypt("ХОЧУСДАТЬКУРСОВУЮ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_EQUAL("ХПЩУТЁАУЮКФТСПДУЯ", p->encrypt("хочусдатькурсовую"));
    }
    TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
        CHECK_EQUAL("ХПЩУТЁАУЮКФТСПДУЯ", p->encrypt("хочу СДАТЬ курсовую"));
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->encrypt(""), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
        CHECK_THROW(p->encrypt("123456789"), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ФНЦТРГЯСЫЙТПРНБТЭ",modAlphaCipher("Я").encrypt("ХОЧУСДАТЬКУРСОВУЮ"));
    }
}
SUITE(DecryptText)
{
    TEST_FIXTURE(KeyB_fixture, UpCaseString) {
        CHECK_EQUAL("ХОЧУСДАТЬКУРСОВУЮ", p->decrypt("ХПЩУТЁАУЮКФТСПДУЯ"));
    }
    TEST_FIXTURE(KeyB_fixture, LowCaseString) {
        CHECK_THROW(p -> decrypt("хпщутёауюкфтспдуя"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
        CHECK_THROW(p->decrypt("ХПЩУ ТЁАУЮКФ ТСП ДУЯ"),cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, DigitsString) {
        CHECK_THROW(p -> decrypt("123456789"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, PunctString) {
        CHECK_THROW(p -> decrypt("ХПЩУТЁАУЮКФТСПДУЯ!!!"), cipher_error);
    }
    TEST_FIXTURE(KeyB_fixture, EmptyString) {
        CHECK_THROW(p->decrypt(""), cipher_error);
    }
    TEST(MaxShiftKey) {
        CHECK_EQUAL("ФНЦТРГЯСЫЙТПРНБТЭ",modAlphaCipher("Я").encrypt("ХОЧУСДАТЬКУРСОВУЮ"));
    }
}
int main(int argc, char **argv)
{
    return UnitTest::RunAllTests();
}
