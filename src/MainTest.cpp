#include "Timer.h"
#include "gtest/gtest.h"

namespace {

class TimerObserver: public ITimerObserver
{
public:
	TimerObserver(): mUpdateFlag(false) {}
	~TimerObserver() {}

	void Update() { mUpdateFlag = true;}

	bool mUpdateFlag;
};

// The fixture for testing class Foo.
class TimerTest : public ::testing::Test
{
 protected:
  // You can remove any or all of the following functions if its body
  // is empty.

  TimerTest()
  {
     // You can do set-up work for each test here.
  }

  ~TimerTest() override
  {
     // You can do clean-up work that doesn't throw exceptions here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  void SetUp() override
  {
     // Code here will be called immediately after the constructor (right
     // before each test).
  }

  void TearDown() override
  {
     // Code here will be called immediately after each test (right
     // before the destructor).
  }

  Timer mTimer;
};

TEST_F(TimerTest, NormalRun)
{
	EXPECT_FALSE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );

	mTimer.Reload(100);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );

	mTimer.Run(50);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );

	mTimer.Run(50);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_TRUE( mTimer.HasExpired() );
}

TEST_F(TimerTest, Stop)
{
	mTimer.Reload(100);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );

	mTimer.Run(50);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );
	mTimer.Stop();

	mTimer.Run(50);
	EXPECT_FALSE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );
}

TEST_F(TimerTest, Observer)
{
	TimerObserver timerObserver1;
	TimerObserver timerObserver2;
	mTimer.Register(&timerObserver1);
	mTimer.Register(&timerObserver2);

	EXPECT_FALSE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );
	EXPECT_FALSE( timerObserver1.mUpdateFlag );

	mTimer.Reload(100);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );
	EXPECT_FALSE( timerObserver1.mUpdateFlag );

	mTimer.Run(50);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );
	EXPECT_FALSE( timerObserver1.mUpdateFlag );

	mTimer.Run(50);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_TRUE( mTimer.HasExpired() );
	EXPECT_TRUE( timerObserver1.mUpdateFlag );
	EXPECT_TRUE( timerObserver2.mUpdateFlag );

	timerObserver1.mUpdateFlag = false;
	timerObserver2.mUpdateFlag = false;
	mTimer.Unregister(&timerObserver1);
	mTimer.Reload(100);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_FALSE( mTimer.HasExpired() );
	EXPECT_FALSE( timerObserver1.mUpdateFlag );
	EXPECT_FALSE( timerObserver2.mUpdateFlag );

	mTimer.Run(100);
	EXPECT_TRUE( mTimer.IsActive() );
	EXPECT_TRUE( mTimer.HasExpired() );
	EXPECT_FALSE( timerObserver1.mUpdateFlag );
	EXPECT_TRUE( timerObserver2.mUpdateFlag );
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
