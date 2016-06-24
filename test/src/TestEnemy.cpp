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

#include "enemy.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestEnemy : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestEnemy);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST(testGetXPosition);
    CPPUNIT_TEST(testGetYPosition);
    CPPUNIT_TEST(testGetMovesLeft);
    CPPUNIT_TEST(testGetMoveDirection);
    CPPUNIT_TEST(testMoveFirstIf);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
       void testDestructor(void);
       void testGetXPosition(void);
       void testGetYPosition(void);
       void testGetMovesLeft(void);
       void testGetMoveDirection(void);
       void testMoveFirstIf(void);
    private:
        Enemy * mTestObj;
};

//-----------------------------------------------------------------------------
void TestEnemy::testDestructor(void) {
    mTestObj->~Enemy();
    CPPUNIT_ASSERT(mTestObj->enemy == NULL);
}

void TestEnemy::testGetXPosition(void) {
    mTestObj->setXPosition(5);
    CPPUNIT_ASSERT(5 == mTestObj->getXPosition());
}

void TestEnemy::testGetYPosition(void) {
    mTestObj->setYPosition(2);
    CPPUNIT_ASSERT(2 == mTestObj->getYPosition());
}

void TestEnemy::testGetMovesLeft(void) {
    mTestObj->setMovesLeft(2);
    CPPUNIT_ASSERT(2 == mTestObj->getMovesLeft());
}

void TestEnemy::testGetMoveDirection(void) {
    mTestObj->setMoveDirection(2);
    CPPUNIT_ASSERT(2 == mTestObj->getMoveDirection());
}

void TestEnemy::testMoveFirstIf(void) {
    mTestObj->setXPosition(54);
    mTestObj->setMovesLeft(10);
    mTestObj->setMoveDirection(4);
    mTestObj->move();
    CPPUNIT_ASSERT(56 == mTestObj->getXPosition());
    CPPUNIT_ASSERT(8 == mTestObj->getMovesLeft());
}

void TestEnemy::setUp(void) {
    mTestObj = new Enemy("../resources/enemy_sprites.png");
}

void TestEnemy::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestEnemy );

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
    ofstream xmlFileOut("test/xml/testEnemy.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();

    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}