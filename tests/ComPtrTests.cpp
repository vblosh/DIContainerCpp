#include <gtest/gtest.h>

#include "../src/ComPtr.h"
#include "TestComp.h"

TEST(ComPtr, TestBoolOperatorCtorDtor) {
	TestComp* pComp = new TestComp;
	ITestComp* pCmp = reinterpret_cast<ITestComp*>(pComp->QueryInterface(UIDTestComp));
	EXPECT_EQ(1, pComp->GetCount());

	{
		ComPtr<ITestComp, UIDTestComp> ptr;
		EXPECT_FALSE(ptr);
		ComPtr<ITestComp, UIDTestComp> ptr1(pCmp);
		EXPECT_TRUE(ptr1);
		EXPECT_EQ(1, pComp->GetCount());
	}

	EXPECT_EQ(0, pComp->GetCount());
}

TEST(ComPtr, TestGetCtorDtor1) {
	TestComp* pComp = new TestComp;
	ITestComp* pCmp = reinterpret_cast<ITestComp*>(pComp->QueryInterface(UIDTestComp));

	{
		ComPtr<ITestComp, UIDTestComp> ptr1(static_cast<IUnknown*>(pCmp));
		EXPECT_EQ(pCmp, ptr1.get());
		EXPECT_EQ(1, pComp->GetCount());
	}

	EXPECT_EQ(0, pComp->GetCount());
}

TEST(ComPtr, TestCtorDtor2) {
	TestComp* pComp = new TestComp;
	ITestComp* pCmp = reinterpret_cast<ITestComp*>(pComp->QueryInterface(UIDTestComp));

	{
		ComPtr<ITestComp, UIDTestComp> ptr1(pCmp);
		EXPECT_EQ(1, pComp->GetCount());
		ComPtr<ITestComp, UIDTestComp> ptr2(ptr1);
		EXPECT_EQ(2, pComp->GetCount());
	}

	EXPECT_EQ(0, pComp->GetCount());
}

TEST(ComPtr, TestMoveCtorDtor) {
	TestComp* pComp = new TestComp;
	ITestComp* pCmp = reinterpret_cast<ITestComp*>(pComp->QueryInterface(UIDTestComp));

	{
		ComPtr<ITestComp, UIDTestComp> ptr1(pCmp);
		EXPECT_EQ(1, pComp->GetCount());
		ComPtr<ITestComp, UIDTestComp> ptr2(std::move(ptr1));
		EXPECT_EQ(1, pComp->GetCount());
	}

	EXPECT_EQ(0, pComp->GetCount());
}

TEST(ComPtr, TestEqualOperator1) {
	TestComp* pComp = new TestComp;
	ITestComp* pCmp = reinterpret_cast<ITestComp*>(pComp->QueryInterface(UIDTestComp));

	{
		ComPtr<ITestComp, UIDTestComp> ptr1 = pCmp;
		EXPECT_EQ(1, pComp->GetCount());
		ComPtr<ITestComp, UIDTestComp> ptr2 = ptr1;
		EXPECT_EQ(2, pComp->GetCount());
	}

	EXPECT_EQ(0, pComp->GetCount());
}

TEST(ComPtr, TestStarOperator) {
	TestComp* pComp = new TestComp;
	ComPtr<ITestComp, UIDTestComp> ptr1(pComp->QueryInterface(UIDTestComp));

	const int val = 2;
	EXPECT_EQ(val * val, ptr1->Calculate(val));
	EXPECT_EQ(val * val, (*ptr1).Calculate(val));
}

TEST(ComPtr, TestAssignChangeType) {
	TestComp* pComp = new TestComp;
	const int val = 2;
	
	{
		ComPtr<ITestComp, UIDTestComp> ptr1(pComp->QueryInterface(UIDTestComp));
		EXPECT_EQ(1, pComp->GetCount());
		ComPtr<ITestComp1, UIDTestComp1> ptr2(ptr1);
		EXPECT_EQ(2, pComp->GetCount());
		EXPECT_EQ(val, ptr2->DoReturn(val));
		
		ComPtr<ITestComp1, UIDTestComp1> ptr3;
		ptr3 = ptr1;
		EXPECT_EQ(3, pComp->GetCount());
		EXPECT_EQ(val, ptr3->DoReturn(val));
	}
	EXPECT_EQ(0, pComp->GetCount());
}





