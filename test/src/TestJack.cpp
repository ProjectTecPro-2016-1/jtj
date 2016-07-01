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
    CPPUNIT_TEST(testIsDead);
    CPPUNIT_TEST(testSetLimitFirstIf);
    CPPUNIT_TEST(testSetLimitSecondIf);
    CPPUNIT_TEST(testSetLimitSecondIfLimitValues);
    CPPUNIT_TEST(testSetLimitElse);
    CPPUNIT_TEST(testMove);
    CPPUNIT_TEST(testControlsMaxJump1IfBigger);
    CPPUNIT_TEST(testControlsMaxJump1IfEqual);
    CPPUNIT_TEST(testControlsMaxJump2FirstIfBigger);
    CPPUNIT_TEST(testControlsMaxJump2FirstIfEqual);
    CPPUNIT_TEST(testControlsMaxJump2SecondIfBigger);
    CPPUNIT_TEST(testControlsMaxJump2SecondIfEqual);
    CPPUNIT_TEST(testControlsMaxJump2Else);
    CPPUNIT_TEST(testPushMoveFirstIf);
    CPPUNIT_TEST(testPushMoveSecondIf);
    CPPUNIT_TEST(testPushMoveElse);
    CPPUNIT_TEST(testPopMoveFirstIf);
    CPPUNIT_TEST(testPopMoveSecondIf_if);
    CPPUNIT_TEST(testPopMoveSecondIf_else);
    CPPUNIT_TEST(testPopMoveElse);
    CPPUNIT_TEST(testSetSpriteClipsStopped);
    CPPUNIT_TEST(testSetSpriteClipsOneRight);
    CPPUNIT_TEST(testSetSpriteClipsSecondRight);
    CPPUNIT_TEST(testSetSpriteClipsThirdRight);
    CPPUNIT_TEST(testSetSpriteClipsJumpRight);
    CPPUNIT_TEST(testSetSpriteClipsOneLeft);
    CPPUNIT_TEST(testSetSpriteClipsSecondLeft);
    CPPUNIT_TEST(testSetSpriteClipsThirdLeft);
    CPPUNIT_TEST(testSetSpriteClipsJumpLeft);

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
        void testIsDead(void);
        void testSetLimitFirstIf(void);
        void testSetLimitSecondIf(void);
        void testSetLimitSecondIfLimitValues(void);
        void testSetLimitElse(void);
        void testMove(void);
        void testControlsMaxJump1IfBigger(void);
        void testControlsMaxJump1IfEqual(void);
        void testControlsMaxJump2FirstIfBigger(void);
        void testControlsMaxJump2FirstIfEqual(void);
        void testControlsMaxJump2SecondIfBigger(void);
        void testControlsMaxJump2SecondIfEqual(void);
        void testControlsMaxJump2Else(void);
        void testPushMoveFirstIf(void);
        void testPushMoveSecondIf(void);
        void testPushMoveElse(void);
        void testPopMoveFirstIf(void);
        void testPopMoveSecondIf_if(void);
        void testPopMoveSecondIf_else(void);
        void testPopMoveElse(void);
        void testSetSpriteClipsStopped(void);
        void testSetSpriteClipsOneRight(void);
        void testSetSpriteClipsSecondRight(void);
        void testSetSpriteClipsThirdRight(void);
        void testSetSpriteClipsJumpRight(void);
        void testSetSpriteClipsOneLeft(void);
        void testSetSpriteClipsSecondLeft(void);
        void testSetSpriteClipsThirdLeft(void);
        void testSetSpriteClipsJumpLeft(void);

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

void TestJack::testIsDead(void) {
    mTestObj->setDead(true);

    CPPUNIT_ASSERT(mTestObj->isDead() == true);
}

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

void TestJack::testControlsMaxJump1IfBigger(void){
    mTestObj->setJumping(true);
    mTestObj->setYPosition(10);
    mTestObj->setVerticalSpeed(2);

    mTestObj->controlsMaxJump1(9, 9);

    CPPUNIT_ASSERT(mTestObj->getJumping() == false);
    CPPUNIT_ASSERT(mTestObj->getVerticalSpeed() == 1);
}

void TestJack::testControlsMaxJump1IfEqual(void){
    mTestObj->setJumping(true);
    mTestObj->setYPosition(10);
    mTestObj->setVerticalSpeed(2);

    mTestObj->controlsMaxJump1(10, 9);

    CPPUNIT_ASSERT(mTestObj->getJumping() == false);
    CPPUNIT_ASSERT(mTestObj->getVerticalSpeed() == 1);
}

void TestJack::testControlsMaxJump2FirstIfBigger(void) {
    mTestObj->setYPosition(100);
    mTestObj->setVerticalSpeed(100);

    mTestObj->controlsMaxJump2(9, 11);
    CPPUNIT_ASSERT(mTestObj->getYPosition() == 9);
    CPPUNIT_ASSERT(mTestObj->getVerticalSpeed() == 1);
}

void TestJack::testControlsMaxJump2FirstIfEqual(void) {
    mTestObj->setYPosition(100);
    mTestObj->setVerticalSpeed(100);

    mTestObj->controlsMaxJump2(10, 11);
    CPPUNIT_ASSERT(mTestObj->getYPosition() == 10);
    CPPUNIT_ASSERT(mTestObj->getVerticalSpeed() == 1);
}

void TestJack::testControlsMaxJump2SecondIfBigger(void) {
    mTestObj->setYPosition(100);
    mTestObj->setVerticalSpeed(100);

    mTestObj->controlsMaxJump2(11, 9);
    CPPUNIT_ASSERT(mTestObj->getYPosition() == 11);
    CPPUNIT_ASSERT(mTestObj->getVerticalSpeed() == 1);
}

void TestJack::testControlsMaxJump2SecondIfEqual(void) {
    mTestObj->setYPosition(100);
    mTestObj->setVerticalSpeed(100);

    mTestObj->controlsMaxJump2(11, 10);
    CPPUNIT_ASSERT(mTestObj->getYPosition() == 11);
    CPPUNIT_ASSERT(mTestObj->getVerticalSpeed() == 1);
}

void TestJack::testControlsMaxJump2Else(void) {
    mTestObj->setYPosition(100);
    mTestObj->setVerticalSpeed(100);
    mTestObj->setJumping(false);

    mTestObj->controlsMaxJump2(101, 101);
    CPPUNIT_ASSERT(mTestObj->getJumping() == true);
}

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

void TestJack::testPopMoveFirstIf(void) {
    mTestObj->setLastButOneMove(10);
    mTestObj->setSpeed(0);
    mTestObj->setLastMove(1);

    mTestObj->popMove(10);

    CPPUNIT_ASSERT(mTestObj->getLastButOneMove() == 0);
    CPPUNIT_ASSERT(mTestObj->getSpeed() == 1);
}

void TestJack::testPopMoveSecondIf_if(void) {
    mTestObj->setLastButOneMove(1);
    mTestObj->setSpeed(0);
    mTestObj->setLastMove(99);

    mTestObj->popMove(99);

    CPPUNIT_ASSERT(mTestObj->getSpeed() == 1);
    CPPUNIT_ASSERT(mTestObj->getLastMove() == 1);
    CPPUNIT_ASSERT(mTestObj->getLastButOneMove() == 0);
}

void TestJack::testPopMoveSecondIf_else(void) {
    mTestObj->setLastButOneMove(0);
    mTestObj->setSpeed(20);
    mTestObj->setLastMove(10);

    mTestObj->popMove(10);

    CPPUNIT_ASSERT(mTestObj->getSpeed() == 0);
    CPPUNIT_ASSERT(mTestObj->getLastMove() == 0);
}

void TestJack::testPopMoveElse(void) {
    mTestObj->setLastButOneMove(1);
    mTestObj->setLastMove(1);

    mTestObj->popMove(99);

    CPPUNIT_ASSERT(mTestObj->getLastButOneMove() == 1);
    CPPUNIT_ASSERT(mTestObj->getLastMove() == 1);
}

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

void TestJack::testSetSpriteClipsOneRight(void) {
    mTestObj->spriteClips[1].x = 30;
    mTestObj->spriteClips[1].y = 30;
    mTestObj->spriteClips[1].w = 30;
    mTestObj->spriteClips[1].h = 30;

    mTestObj->setSpriteClipsOneRight();

    CPPUNIT_ASSERT(mTestObj->spriteClips[1].x == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[1].y == mTestObj->JACK_HEIGHT);
    CPPUNIT_ASSERT(mTestObj->spriteClips[1].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[1].h == mTestObj->JACK_HEIGHT);
}

void TestJack::testSetSpriteClipsSecondRight() {
    mTestObj->spriteClips[2].x = 40;
    mTestObj->spriteClips[2].y = 40;
    mTestObj->spriteClips[2].w = 40;
    mTestObj->spriteClips[2].h = 40;

    mTestObj->setSpriteClipsSecondRight();

    CPPUNIT_ASSERT(mTestObj->spriteClips[2].x == mTestObj->JACK_WIDTH*2);
    CPPUNIT_ASSERT(mTestObj->spriteClips[2].y == mTestObj->JACK_HEIGHT);
    CPPUNIT_ASSERT(mTestObj->spriteClips[2].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[2].h == mTestObj->JACK_HEIGHT);
}

void TestJack::testSetSpriteClipsThirdRight() {
    mTestObj->spriteClips[3].x = 50;
    mTestObj->spriteClips[3].y = 50;
    mTestObj->spriteClips[3].w = 50;
    mTestObj->spriteClips[3].h = 50;

    mTestObj->setSpriteClipsThirdRight();

    CPPUNIT_ASSERT(mTestObj->spriteClips[3].x == mTestObj->JACK_WIDTH*3);
    CPPUNIT_ASSERT(mTestObj->spriteClips[3].y == mTestObj->JACK_HEIGHT);
    CPPUNIT_ASSERT(mTestObj->spriteClips[3].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[3].h == mTestObj->JACK_HEIGHT);
}

void TestJack::testSetSpriteClipsJumpRight() {
    mTestObj->spriteClips[7].x = 60;
    mTestObj->spriteClips[7].y = 60;
    mTestObj->spriteClips[7].w = 60;
    mTestObj->spriteClips[7].h = 60;

    mTestObj->setSpriteClipsJumpRight();

    CPPUNIT_ASSERT(mTestObj->spriteClips[7].x == mTestObj->JACK_WIDTH*4);
    CPPUNIT_ASSERT(mTestObj->spriteClips[7].y == mTestObj->JACK_HEIGHT);
    CPPUNIT_ASSERT(mTestObj->spriteClips[7].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[7].h == mTestObj->JACK_HEIGHT);
}

void TestJack::testSetSpriteClipsOneLeft() {
    mTestObj->spriteClips[4].x = 70;
    mTestObj->spriteClips[4].y = 70;
    mTestObj->spriteClips[4].w = 70;
    mTestObj->spriteClips[4].h = 70;

    mTestObj->setSpriteClipsOneLeft();

    CPPUNIT_ASSERT(mTestObj->spriteClips[4].x == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[4].y == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[4].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[4].h == mTestObj->JACK_HEIGHT);
}

void TestJack::testSetSpriteClipsSecondLeft() {
    mTestObj->spriteClips[5].x = 80;
    mTestObj->spriteClips[5].y = 80;
    mTestObj->spriteClips[5].w = 80;
    mTestObj->spriteClips[5].h = 80;

    mTestObj->setSpriteClipsSecondLeft();

    CPPUNIT_ASSERT(mTestObj->spriteClips[5].x == mTestObj->JACK_WIDTH*2);
    CPPUNIT_ASSERT(mTestObj->spriteClips[5].y == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[5].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[5].h == mTestObj->JACK_HEIGHT);
}

void TestJack::testSetSpriteClipsThirdLeft() {
    mTestObj->spriteClips[6].x = 90;
    mTestObj->spriteClips[6].y = 90;
    mTestObj->spriteClips[6].w = 90;
    mTestObj->spriteClips[6].h = 90;

    mTestObj->setSpriteClipsThirdLeft();

    CPPUNIT_ASSERT(mTestObj->spriteClips[6].x == mTestObj->JACK_WIDTH*3);
    CPPUNIT_ASSERT(mTestObj->spriteClips[6].y == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[6].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[6].h == mTestObj->JACK_HEIGHT);
}

void TestJack::testSetSpriteClipsJumpLeft() {
    mTestObj->spriteClips[8].x = 100;
    mTestObj->spriteClips[8].y = 100;
    mTestObj->spriteClips[8].w = 100;
    mTestObj->spriteClips[8].h = 100;

    mTestObj->setSpriteClipsJumpLeft();

    CPPUNIT_ASSERT(mTestObj->spriteClips[8].x == mTestObj->JACK_WIDTH*4);
    CPPUNIT_ASSERT(mTestObj->spriteClips[8].y == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[8].w == mTestObj->JACK_WIDTH);
    CPPUNIT_ASSERT(mTestObj->spriteClips[8].h == mTestObj->JACK_HEIGHT);
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