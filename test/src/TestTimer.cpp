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

#include "timer.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestTimer : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestTimer);
    CPPUNIT_TEST(testStart);
    CPPUNIT_TEST(testStop);
    CPPUNIT_TEST(testPause);
    CPPUNIT_TEST(testUnpause);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testStart(void);
        void testStop(void);
        void testPause(void);
        void testUnpause(void);

    private:
        Timer * mTestObj;
};

//-----------------------------------------------------------------------------

void TestTimer::testStart(void){
    mTestObj->start();

    CPPUNIT_ASSERT(true == mTestObj->is_started());
    CPPUNIT_ASSERT(false == mTestObj->is_paused());
    CPPUNIT_ASSERT(0 == mTestObj->get_ticks());
}

void TestTimer::testStop(void){
    mTestObj->stop();

    CPPUNIT_ASSERT(false == mTestObj->is_started());
    CPPUNIT_ASSERT(false == mTestObj->is_paused());
}

void TestTimer::testPause(void){
    mTestObj->start();
    mTestObj->pause();

    CPPUNIT_ASSERT(true == mTestObj->is_paused());   
}

void TestTimer::testUnpause(void){
    mTestObj->start();
    mTestObj->pause();
    mTestObj->unpause();

    CPPUNIT_ASSERT(false == mTestObj->is_paused());
    CPPUNIT_ASSERT(0 == mTestObj->getPausedTicks());
}

void TestTimer::setUp(void) {
    mTestObj = new Timer();
}

void TestTimer::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestTimer );

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
    ofstream xmlFileOut("test/xml/testTimer.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}