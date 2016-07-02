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

#include "label.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestLabel : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestLabel);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testWasClickedIf);
    CPPUNIT_TEST(testWasClickedElse);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testConstructor(void);
        void testWasClickedIf(void);
        void testWasClickedElse(void);
        void testDestructor(void);

    private:
        Label * mTestObj;
};

//-----------------------------------------------------------------------------

void TestLabel::testConstructor(void) {
    CPPUNIT_ASSERT(0 < mTestObj->xPosition);
    CPPUNIT_ASSERT(0 < mTestObj->yPosition);
}

void TestLabel::testWasClickedIf() {
    mTestObj->xPosition = 10;
    mTestObj->yPosition = 10;

    CPPUNIT_ASSERT(true == mTestObj->wasClicked(150, 80));
}

void TestLabel::testWasClickedElse() {
    mTestObj->xPosition = 10;
    mTestObj->yPosition = 10;

    CPPUNIT_ASSERT(false == mTestObj->wasClicked(200, 150));
}

void TestLabel::testDestructor(void) {
    mTestObj->~Label();
    CPPUNIT_ASSERT(mTestObj->label == NULL);
}

void TestLabel::setUp(void) {
    mTestObj = new Label("../resources/mutebutton.png", 483, 68);
}

void TestLabel::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestLabel );

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
    ofstream xmlFileOut("test/xml/testLabel.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}