#include <gtest/gtest.h>

#include "../src/ComPtr.h"
#include "component1.h"


TEST(ComPtr, TEST1) {

	Component1 cmp;
	IComponent1* pCmp = &cmp;
	cmp.AddRef();
	EXPECT_EQ(1, cmp.GetCount());

	{
		ComPtr<IComponent1, UIDComponent1> ptr;
		EXPECT_FALSE(ptr);
		//ComPtr<IComponent1, UIDComponent1> ptr1(pCmp);
		//EXPECT_TRUE(ptr1);
		EXPECT_EQ(1, cmp.GetCount());
	}

	EXPECT_EQ(0, cmp.GetCount());
	cmp.AddRef();
	EXPECT_EQ(1, cmp.GetCount());
	ComPtr<IComponent1, UIDComponent1> ptr2(ComPtr<IComponent1, UIDComponent1>(pCmp));
	EXPECT_EQ(1, cmp.GetCount());
}
