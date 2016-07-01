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

#include "game.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestGame : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestGame);
    CPPUNIT_TEST(testInit);
    CPPUNIT_TEST(testUpdate);   
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testInit(void);
        void testUpdate(void);

    private:
        Game * mTestObj;
};

//-----------------------------------------------------------------------------

void TestGame::testInit(void) {
    mTestObj->init();
    CPPUNIT_ASSERT(false == mTestObj->getQuitGame());
    CPPUNIT_ASSERT(false ==  mTestObj->isLevelFinished());
}

void TestGame::testUpdate(void){
    //gameOver = true;
    //this->quitLevel = true;
    mTestObj->update();
    CPPUNIT_ASSERT(true ==  mTestObj->isLevelFinished());
}

void TestGame::setUp(void) {
    mTestObj = new Game("../resources/game.png");
}

void TestGame::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestBox );

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
    ofstream xmlFileOut("test/xml/testBox.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}