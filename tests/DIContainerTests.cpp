#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "../src/DIContainer.h"
#include "../src/ComPtr.h"

#include "component1.h"
#include "component2.h"
#include "component3.h"
#include "component4.h"

IComponent* CreateCmp1() {
    return new Component1;
}

TEST(DIContainer, ComPtr) {
    DIContainer cont;
    // Register components in the container
    cont.RegisterInterface(UIDComponent1, CreateCmp1, CreationPolicy::SharedInstance);
    cont.RegisterInterface(UIDComponent2, []()->IComponent* { return new Component2; });

    int val = 12;
    ComPtr<IComponent1, UIDComponent1> cmp1(cont.GetInterface(UIDComponent1));
    int res1 = cmp1->Calculate(val);
    EXPECT_EQ(res1, val * val);

    ComPtr<IComponent2, UIDComponent2> cmp2 = (IComponent2*)cont.GetInterface(UIDComponent2);
    int res2 = cmp2->Calculate(val);
    EXPECT_EQ(res2, val * val * 2);
}

TEST(DIContainer, ComPtrUsage) {
    DIContainer cont;
    cont.RegisterInterface(UIDComponent1, CreateCmp1, CreationPolicy::SharedInstance);
    cont.RegisterInterface(UIDComponent2, []()->IComponent* { return new Component2; });

    int val = 12;
    IComponent1* cmp1 = (IComponent1*)cont.GetInterface(UIDComponent1);
    int res1 = cmp1->Calculate(val);
    EXPECT_EQ(res1, val * val);

    IComponent2* cmp2 = (IComponent2*)cont.GetInterface(UIDComponent2);
    int res2 = cmp2->Calculate(val);
    EXPECT_EQ(res2, val * val * 2);
}

TEST(DIContainer, AddRefRelease) {
    DIContainer cont;
    cont.RegisterInterface(UIDComponent1, CreateCmp1, CreationPolicy::SharedInstance);
    cont.RegisterInterface(UIDComponent2, []()->IComponent* { return new Component2; });

    int val = 12;
    IComponent1* cmp1 = (IComponent1*)cont.GetInterface(UIDComponent1);
    int res1 = cmp1->Calculate(val);
    EXPECT_EQ(res1, val * val);

    IComponent2* cmp2 = (IComponent2*)cont.GetInterface(UIDComponent2);
    int res2 = cmp2->Calculate(val);
    EXPECT_EQ(res2, val * val * 2);

    //std::cout << cont;

    EXPECT_EQ(0, cmp2->Release());
    EXPECT_EQ(1, cmp1->Release()); // Shared instance, a reference stil exists
}

TEST(DIContainer, ComponentNotRegistered) {
    DIContainer cont;
    cont.RegisterInterface(UIDComponent1, CreateCmp1, CreationPolicy::SharedInstance);
    try {
        IComponent2* cmp2 = (IComponent2*)cont.GetInterface(UIDComponent2);
        FAIL();
    }
    catch (const DIContainerExeption& ex) {
        ASSERT_TRUE(std::string(ex.what()).find(std::to_string(UIDComponent2)) != std::string::npos);
    }
}

TEST(DIContainer, ComponentAlreadyRegistered) {
    DIContainer cont;
    cont.RegisterInterface(UIDComponent1, CreateCmp1, CreationPolicy::SharedInstance);
    try {
        cont.RegisterInterface(UIDComponent1, CreateCmp1, CreationPolicy::SharedInstance);
        FAIL();
    }
    catch (const DIContainerExeption& ex) {
        ASSERT_TRUE(std::string(ex.what()).find(std::to_string(UIDComponent1)) != std::string::npos);
    }
}

TEST(DIContainer, CyclicDependencies) {
    DIContainer cont;
    try {
        cont.RegisterInterface(UIDComponent3, []()->IComponent* { return new Component3; });
        cont.RegisterInterface(UIDComponent4, []()->IComponent* { return new Component4; });
        IComponent3* cmp3 = (IComponent3*)cont.GetInterface(UIDComponent3);
        FAIL();
    }
    catch (const DIContainerExeption& ex) {
        std::string err(ex.what());
        ASSERT_TRUE(std::string(ex.what()).find(std::to_string(UIDComponent3)) != std::string::npos);
        ASSERT_TRUE(std::string(ex.what()).find(std::to_string(UIDComponent4)) != std::string::npos);
    }
}
