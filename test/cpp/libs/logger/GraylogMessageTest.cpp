#include "logger/GraylogMessage.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(GraylogMessage, ExpectBarIsBaz)
{
    logger::GraylogMessage uut(1, "Foo");
    uut.addField("bar", "baz");
    uut.addField("blah", 1.0);
    uut.addField("blam", 42);

    EXPECT_EQ("baz", uut.getField("bar")->getAsSting());
    EXPECT_EQ(1.0, uut.getField("blah")->getAsDouble());
    EXPECT_EQ(42, uut.getField("blam")->getAsInt16());
}
