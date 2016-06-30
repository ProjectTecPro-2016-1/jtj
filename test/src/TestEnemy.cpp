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
    CPPUNIT_TEST(testMoveSecondIf);
    CPPUNIT_TEST(testMoveThirdIf);
    CPPUNIT_TEST(testMoveFourthIf);
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
        void testMoveSecondIf(void);
        void testMoveThirdIf(void);
        void testMoveFourthIf(void);
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

void TestEnemy::testMoveSecondIf(void) {
    mTestObj->setXPosition(54);
    mTestObj->setMovesLeft(10);
    mTestObj->setMoveDirection(5);
    mTestObj->move();

    CPPUNIT_ASSERT(52 == mTestObj->getXPosition());
    CPPUNIT_ASSERT(8 == mTestObj->getMovesLeft());
}

void TestEnemy::testMoveThirdIf(void){
    mTestObj->setXPosition(30);
    mTestObj->setMoveDirection(9);
    mTestObj->setMovesLeft(0);
    mTestObj->move();

    CPPUNIT_ASSERT(32 == mTestObj->getXPosition());
    CPPUNIT_ASSERT(36 == mTestObj->getMovesLeft());
    CPPUNIT_ASSERT(2 == mTestObj->getMoveDirection());
}

void TestEnemy::testMoveFourthIf(void){
    mTestObj->setXPosition(500);
    mTestObj->setMovesLeft(0);
    mTestObj->setMoveDirection(0);
    mTestObj->move();

    CPPUNIT_ASSERT(498 == mTestObj->getXPosition());
    CPPUNIT_ASSERT(36 == mTestObj->getMovesLeft());
    CPPUNIT_ASSERT(1 == mTestObj->getMoveDirection());
}

void TestEnemy::setUp(void) {
    mTestObj = new Enemy("../resources/enemy_sprites.png");
}

void TestEnemy::tearDown(void) {
    delete mTestObj;
}

/*
mTestObj->spriteClips[0].x = 0;
mTestObj->spriteClips[0].y = 0;
mTestObj->spriteClips[0].h = 0;
mTestObj->spriteClips[0].w = 0;
mTestObj->setStpriteEnemyMovementLeft();

CPPUNIT_ASSERT(mTestObj->spriteClips[0].x == 0);
CPPUNIT_ASSERT(mTestObj->spriteClips[0].y == ENEMY_HEIGHT);
CPPUNIT_ASSERT(mTestObj->spriteClips[0].h == ENEMY_HEIGHT);
CPPUNIT_ASSERT(mTestObj->spriteClips[0].w == ENEMY_WIDTH);

*/

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