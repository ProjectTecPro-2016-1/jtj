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
    CPPUNIT_TEST(testStopEnemy);
    CPPUNIT_TEST(testStartingtRightEnemyMovement);
    CPPUNIT_TEST(testContinuingRightEnemyMovement);
    CPPUNIT_TEST(testFinishingRightEnemyMovement);
    CPPUNIT_TEST(testFinishingLeftEnemyMovement);
    CPPUNIT_TEST(testContinuingLeftEnemyMovement);
    CPPUNIT_TEST(testStartingtLeftEnemyMovement);
    CPPUNIT_TEST(testDropBox);
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
        void testStopEnemy(void);
        void testStartingtRightEnemyMovement(void);
        void testContinuingRightEnemyMovement(void);
        void testFinishingRightEnemyMovement(void);
        void testFinishingLeftEnemyMovement(void);
        void testContinuingLeftEnemyMovement(void);
        void testStartingtLeftEnemyMovement(void);
        void testDropBox(void);
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

void TestEnemy::testStopEnemy(void){
    mTestObj->spriteClips[0].x = 0;
    mTestObj->spriteClips[0].y = 0;
    mTestObj->spriteClips[0].h = 0;
    mTestObj->spriteClips[0].w = 0;
    mTestObj->setStopEnemy();

    CPPUNIT_ASSERT(mTestObj->spriteClips[0].x == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[0].y == 57);   // Value of ENEMY_HEIGHT
    CPPUNIT_ASSERT(mTestObj->spriteClips[0].h == 57);   // Value of ENEMY_HEIGHT
    CPPUNIT_ASSERT(mTestObj->spriteClips[0].w == 38);   // Value of ENEMY_WIDTH
}

void TestEnemy::testStartingtRightEnemyMovement(void){
    mTestObj->spriteClips[1].x = 1;    
    mTestObj->spriteClips[1].y = 1;    
    mTestObj->spriteClips[1].w = 1;    
    mTestObj->spriteClips[1].h = 1;    
    mTestObj->setStartingtRightEnemyMovement();

    CPPUNIT_ASSERT(mTestObj->spriteClips[1].x == 38);    // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[1].y ==57);    // Value of ENEMY_HEIGHT
    CPPUNIT_ASSERT(mTestObj->spriteClips[1].w == 38);    // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[1].h == 57);    // Value of ENEMY_HEIGHT
}

void TestEnemy::testContinuingRightEnemyMovement(void){
    mTestObj->spriteClips[2].x = 2;
    mTestObj->spriteClips[2].y = 2;
    mTestObj->spriteClips[2].w = 2;
    mTestObj->spriteClips[2].h = 2;
    mTestObj->setContinuingRightEnemyMovement();

    CPPUNIT_ASSERT(mTestObj->spriteClips[2].x == 38*2);  // Value of ENEMY_WIDTH * 2
    CPPUNIT_ASSERT(mTestObj->spriteClips[2].y == 57);    // Value of ENEMY_HEIGHT
    CPPUNIT_ASSERT(mTestObj->spriteClips[2].w == 38);    // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[2].h == 57);    // Value of ENEMY_HEIGHT
}

void TestEnemy::testFinishingRightEnemyMovement(void){
    mTestObj->spriteClips[3].x = 3;
    mTestObj->spriteClips[3].y = 3;
    mTestObj->spriteClips[3].w = 3;
    mTestObj->spriteClips[3].h = 3;
    mTestObj->setFinishingRightEnemyMovement();

    CPPUNIT_ASSERT(mTestObj->spriteClips[3].x == 38*3);  // Value of ENEMY_WIDTH * 3
    CPPUNIT_ASSERT(mTestObj->spriteClips[3].y == 57);    // Value of ENEMY_HEIGHT
    CPPUNIT_ASSERT(mTestObj->spriteClips[3].w == 38);    // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[3].h == 57);    // Value of ENEMY_HEIGHT
}

void TestEnemy::testFinishingLeftEnemyMovement(void) {
    mTestObj->spriteClips[4].x = 4;
    mTestObj->spriteClips[4].y = 4;
    mTestObj->spriteClips[4].w = 4;
    mTestObj->spriteClips[4].h = 4;     
    mTestObj->setFinishingLeftEnemyMovement();

    CPPUNIT_ASSERT(mTestObj->spriteClips[4].x == 38);    // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[4].y == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[4].w == 38);    // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[4].h == 57);    // Value of ENEMY_HEIGHT  
}

void TestEnemy::testContinuingLeftEnemyMovement(void) {
    mTestObj->spriteClips[5].x = 5;
    mTestObj->spriteClips[5].y = 5;
    mTestObj->spriteClips[5].w = 5;
    mTestObj->spriteClips[5].h = 5;    
    mTestObj->setContinuingLeftEnemyMovement();

    CPPUNIT_ASSERT(mTestObj->spriteClips[5].x == 38*2); // Value of ENEMY_WIDTH * 2
    CPPUNIT_ASSERT(mTestObj->spriteClips[5].y == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[5].w == 38);   // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[5].h == 57);   // Value of ENEMY_HEIGHT  
}

void TestEnemy::testStartingtLeftEnemyMovement(void) {
    mTestObj->spriteClips[6].x = 6;
    mTestObj->spriteClips[6].y = 6;
    mTestObj->spriteClips[6].w = 6;
    mTestObj->spriteClips[6].h = 6;
    mTestObj->setStartingtLeftEnemyMovement();

    CPPUNIT_ASSERT(mTestObj->spriteClips[6].x == 38*3); // Value of ENEMY_WIDTH * 3
    CPPUNIT_ASSERT(mTestObj->spriteClips[6].y == 0);
    CPPUNIT_ASSERT(mTestObj->spriteClips[6].w == 38);   // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[6].h == 57);  // Value of ENEMY_HEIGHT
}

void TestEnemy::testDropBox(void) {    
    mTestObj->spriteClips[7].x = 7; 
    mTestObj->spriteClips[7].y = 7;  
    mTestObj->spriteClips[7].w = 7;   
    mTestObj->spriteClips[7].h = 7;  
    mTestObj->setDropBox();

    CPPUNIT_ASSERT(mTestObj->spriteClips[7].x == 38*4); // Value of ENEMY_WIDTH * 4
    CPPUNIT_ASSERT(mTestObj->spriteClips[7].y == 57);   // Value of ENEMY_HEIGHT
    CPPUNIT_ASSERT(mTestObj->spriteClips[7].w == 38);   // Value of ENEMY_WIDTH
    CPPUNIT_ASSERT(mTestObj->spriteClips[7].h == 57);   // Value of ENEMY_HEIGHT
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