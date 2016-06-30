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

#include "jack.hpp"

using namespace CppUnit;
using namespace std;

//-----------------------------------------------------------------------------

class TestJack : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestJack);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetXPosition);
    CPPUNIT_TEST(testGetYPosition);
    CPPUNIT_TEST(testDie);
    CPPUNIT_TEST(testSetLimitFirstIf);
    CPPUNIT_TEST(testSetLimitSecondIf);
    CPPUNIT_TEST(testSetLimitSecondIfLimitValues);
    CPPUNIT_TEST(testSetLimitElse);
    CPPUNIT_TEST(testMove);
    CPPUNIT_TEST(testPushMoveFirstIf);
    CPPUNIT_TEST(testPushMoveSecondIf);
    CPPUNIT_TEST(testPushMoveElse);
    CPPUNIT_TEST(testSetSpriteClipsStopped);
    CPPUNIT_TEST(testDestructor);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp(void);
        void tearDown(void);

    protected:
        void testConstructor(void);
        void testGetXPosition(void);
        void testGetYPosition(void);
        void testDie(void);
        void testSetLimitFirstIf(void);
        void testSetLimitSecondIf(void);
        void testSetLimitSecondIfLimitValues(void);
        void testSetLimitElse(void);
        void testMove(void);
        void testPushMoveFirstIf(void);
        void testPushMoveSecondIf(void);
        void testPushMoveElse(void);
        void testSetSpriteClipsStopped(void);
        void testDestructor(void);

    private:
        Jack * mTestObj;
};

//-----------------------------------------------------------------------------

void TestJack::testConstructor(void) {
    CPPUNIT_ASSERT(mTestObj->getXPosition() != 0);
    CPPUNIT_ASSERT(mTestObj->getYPosition() != 0);
}

void TestJack::testGetXPosition(void) {
    mTestObj->setXPosition(10);
    CPPUNIT_ASSERT(10 == mTestObj->getXPosition());
}

void TestJack::testGetYPosition(void) {
    mTestObj->setYPosition(10);
    CPPUNIT_ASSERT(10 == mTestObj->getYPosition());
}

void TestJack::testDie(void) {
    mTestObj->setDead(false);
    mTestObj->die();
    CPPUNIT_ASSERT(true == mTestObj->getDead());
}

// void TestJack::testIsDead(void) {

// }

void TestJack::testSetLimitFirstIf(void) {
    int returnValue = mTestObj->setLimit(0, 1, -18);
    CPPUNIT_ASSERT(returnValue == 1);
}

void TestJack::testSetLimitSecondIf(void) {
    int returnValue = mTestObj->setLimit(3, 1, 1);
    CPPUNIT_ASSERT(returnValue == 2);
}

void TestJack::testSetLimitSecondIfLimitValues(void) {
    int returnValue = mTestObj->setLimit(2, 0, 2);
    CPPUNIT_ASSERT(returnValue == 2);
}

void TestJack::testSetLimitElse(void) {
    int returnValue = mTestObj->setLimit(0, 0, 2);
    CPPUNIT_ASSERT(returnValue == 0);
}

void TestJack::testMove(void) {
    mTestObj->setXPosition(0);
    mTestObj->setYPosition(0);
    mTestObj->setSpeed(2);

    mTestObj->move(1, 1, 1, 1);
    CPPUNIT_ASSERT(mTestObj->getXPosition() == -36);
    CPPUNIT_ASSERT(mTestObj->getYPosition() == 1);
}

// void TestJack::testJump(void) {

// }

void TestJack::testPushMoveFirstIf(void) {
    mTestObj->setSpeed(0);
    mTestObj->setLastMove(0);
    mTestObj->setLastButOneMove(1);
    mTestObj->pushMove(99);
    CPPUNIT_ASSERT(mTestObj->getSpeed() == 99);
    CPPUNIT_ASSERT(mTestObj->getLastMove() == 99);
}

void TestJack::testPushMoveSecondIf(void) {
    mTestObj->setSpeed(0);
    mTestObj->setLastMove(1);
    mTestObj->setLastButOneMove(0);
    mTestObj->pushMove(99);
    CPPUNIT_ASSERT(mTestObj->getSpeed() == 99);
    CPPUNIT_ASSERT(mTestObj->getLastButOneMove() == 99);
}

void TestJack::testPushMoveElse(void) {
    mTestObj->setSpeed(0);
    mTestObj->setLastMove(1);
    mTestObj->setLastButOneMove(1);
    mTestObj->pushMove(99);
    CPPUNIT_ASSERT(mTestObj->getSpeed() == 0);
    CPPUNIT_ASSERT(mTestObj->getLastMove() == 1);
    CPPUNIT_ASSERT(mTestObj->getLastButOneMove() == 1);
}

// void TestJack::testPopMove(void) {

// }

void TestJack::testSetSpriteClipsStopped(void) {
    mTestObj->spriteClips[0].x = 20;
    mTestObj->spriteClips[0].y = 20;
    mTestObj->spriteClips[0].w = 20;
    mTestObj->spriteClips[0].h = 20;

    mTestObj->setSpriteClipsStopped();

    CPPUNIT_ASSERT(mTestObj->spriteClips[0].x == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[0].y == mTestObj->JACK_HEIGHT);
    CPPUNIT_ASSERT(mTestObj->spriteClips[0].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[0].h == mTestObj->JACK_HEIGHT);

}

void TestJack::testDestructor(void) {
    CPPUNIT_ASSERT(mTestObj->jack == NULL);
}

void TestJack::setUp(void) {
    mTestObj = new Jack("../resources/jack.png");
}

void TestJack::tearDown(void) {
    delete mTestObj;
}

//-----------------------------------------------------------------------------

CPPUNIT_TEST_SUITE_REGISTRATION( TestJack );

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