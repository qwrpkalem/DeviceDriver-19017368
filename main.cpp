#include "gmock/gmock.h"
#include "device_driver.h"
#include <string>

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

//TEST(DeviceDriver, ReadFromHW) {
//	// TODO : replace hardware with a Test Double
//	FlashMemoryDevice* hardware = nullptr;
//	DeviceDriver driver{ hardware };
//	int data = driver.read(0xFF);
//	EXPECT_EQ(0, data);
//}

TEST(DeviceDriver, FiveRead) {
	NiceMock<FlashMock> mock;

	EXPECT_CALL(mock, read(0xB))
		.Times(5);

	DeviceDriver driver{ &mock };
	int data = driver.read((long)0xB);
}

TEST(DeviceDriver, FiveReadNotSame) {
	NiceMock<FlashMock> mock;

	EXPECT_CALL(mock, read(0xB))
		.Times(5)
		.WillOnce(Return(999))
		.WillRepeatedly(Return(0));

	DeviceDriver driver{ &mock };
	try {
		int data = driver.read((long)0xB);
		FAIL();
	}
	catch (std::runtime_error& e) {
		// assert
		EXPECT_EQ(std::string{ e.what() }, std::string{ "Read resut not same error." });

	}
}



int main() {
	::testing::InitGoogleMock();
	return RUN_ALL_TESTS();
}
