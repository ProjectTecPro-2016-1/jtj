#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>

#include "scorescreen.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestScoreScreen : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestScoreScreen);
    // CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetLine);
    CPPUNIT_TEST(testGetScorePoints);
    CPPUNIT_TEST(testPopLine);
    CPPUNIT_TEST(testIncreaseScore);
    CPPUNIT_TEST(testUpdateSelf);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        // void testConstructor(void);
        void testGetLine(void);
        void testGetScorePoints(void);
        void testPopLine(void);
        void testIncreaseScore(void);
        void testUpdateSelf(void);
        void testDestructor(void);

    private:
        ScoreScreen * mTestObj;
};

//-----------------------------------------------------------------------------

// void TestScoreScreen::testConstructor(void) {
//     CPPUNIT_ASSERT(NULL != mTestObj->armario);
//     CPPUNIT_ASSERT(NULL != mTestObj->scoreFont);
//     CPPUNIT_ASSERT(NULL != mTestObj->scoreMessage);
    
//     CPPUNIT_ASSERT(225 == mTestObj->scoreTextColor.r);
//     CPPUNIT_ASSERT(225 == mTestObj->scoreTextColor.g);
//     CPPUNIT_ASSERT(225 == mTestObj->scoreTextColor.b);

//     CPPUNIT_ASSERT(0 == mTestObj->scorePoints);
//     CPPUNIT_ASSERT(99 == mTestObj->lineLeft);
// }

void TestScoreScreen::testGetLine(void){
    mTestObj->lines(3);
    
    CPPUNIT_ASSERT(3 == mTestObj->getLine());
}

void TestScoreScreen::testGetScorePoints(void){
    mTestObj->scoring(30);
    
    CPPUNIT_ASSERT(30 == mTestObj->getScorePoints());
}

void TestScoreScreen::testPopLine(void){
    mTestObj->lines(3);
    mTestObj->popLine();
    
    CPPUNIT_ASSERT(2 == mTestObj->getLine());   
}

void TestScoreScreen::testIncreaseScore(void){
    mTestObj->scoring(30);
    mTestObj->increaseScore(10);
    
    CPPUNIT_ASSERT(40 == mTestObj->getScorePoints());   
}

void TestScoreScreen::testUpdateSelf(void){
    mTestObj->updateSelf();

    CPPUNIT_ASSERT(NULL != mTestObj->scoreMessage);
    CPPUNIT_ASSERT(NULL != mTestObj->boxMessage);
}

void TestScoreScreen::testDestructor(void) {
    mTestObj->~ScoreScreen();
    
    CPPUNIT_ASSERT(mTestObj->scoreFont == NULL);
    CPPUNIT_ASSERT(mTestObj->armario == NULL);
    CPPUNIT_ASSERT(mTestObj->scoreMessage == NULL);
}

void TestScoreScreen::setUp(void) {
    mTestObj = new ScoreScreen();
}

void TestScoreScreen::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestScoreScreen );

int main() {
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;

    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);

    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);

    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);

    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();

    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("test/xml/testScoreScreen.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}