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

#include "optionsscreen.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestOptionsScreen : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestOptionsScreen);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testConstructor(void);
        void testDestructor(void);

    private:
        OptionsScreen * mTestObj;
};

//-----------------------------------------------------------------------------

void TestOptionsScreen::testConstructor(void) {
    // For test, the oprtionsScreen attribute needs to be passed for public.
    CPPUNIT_ASSERT(NULL != mTestObj->optionsScreen);
    CPPUNIT_ASSERT(NULL != mTestObj->helpMessage );
}

void TestOptionsScreen::testDestructor(void) {
    CPPUNIT_ASSERT(mTestObj->optionsScreen == NULL);
}

void TestOptionsScreen::setUp(void) {
    mTestObj = new OptionsScreen("../../resources/backgroundoptionsscreen.png");
}

void TestOptionsScreen::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestOptionsScreen );

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
    ofstream xmlFileOut("test/xml/testOptionsScreen.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}