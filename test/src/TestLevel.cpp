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

#include "level.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestLevel : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestLevel);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testQuantityOfBox);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testConstructor(void);
        void testQuantityOfBox(void);
        void testDestructor(void);

    private:
        Level * mTestObj;
};

//-----------------------------------------------------------------------------

void TestLevel::testConstructor(void) {
    // Level * mTestObj2;
    //CPPUT_CHECK_ASSERTION_FAIL(mTestObj2 = new Level(""));
}

void TestLevel::testDestructor(void) {
    CPPUNIT_ASSERT(mTestObj->level == NULL);
}

void TestLevel::testQuantityOfBox(void) {
    int nrBoxes = 10;

    for (int i = 0; i < nrBoxes; i++) {
        Box * box = new Box("../resources/box.png");
        mTestObj->boxes.push_back(box);
        mTestObj->addChild(box);
    }

    CPPUNIT_ASSERT(mTestObj->getBoxes().size() == 10);

}

void TestLevel::setUp(void) {
    mTestObj = new Level("../resources/level.png");
}

void TestLevel::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestLevel );

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