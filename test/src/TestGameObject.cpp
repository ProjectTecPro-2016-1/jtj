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

#include "gameobject.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestGameObject : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestGameObject);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testDestructor(void);

    private:
        GameObject * mTestGameObj;
};

//-----------------------------------------------------------------------------

void TestGameObject::testDestructor(void) {
        CPPUNIT_ASSERT(mTestGameObj->gameobject == NULL);
}

void TestGameObject::setUp(void) {
    mTestGameObj = new TestGameObject("../resources/gameobject.png");
}

void TestBox::tearDown(void) {
    delete mTestGameObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestGameObject );

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
    ofstream xmlFileOut("test/xml/testGameObject.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}