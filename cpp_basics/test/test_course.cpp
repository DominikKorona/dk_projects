#include "gtest/gtest.h"
#include "course.hpp"

TEST(SweetTest, amounttest) {
    std::list<int> result1 = sweets(31, 67);
    std::list<int> expected1{2, 7};
    EXPECT_EQ(result1, expected1);

    std::list<int> result2 = sweets(31, 90);
    std::list<int> expected2{3, 0};
    EXPECT_EQ(result2, expected2);

    std::list<int> result3 = sweets(31, 59);
    std::list<int> expected3{1, 29};
    EXPECT_EQ(result3, expected3);
}

TEST(ReverseTest, ReverseName){
    std::string revname= "Dracula";
    std::string expected="alucarD";
    reversion(revname);
    EXPECT_EQ(revname, expected);
}

TEST(StringTest, CapitalizeString){
    std::string str= "Dracula1";
    std::string expected="DRACULA1";
    capitalletters(str);
    EXPECT_EQ(str, expected);
}

TEST(PrimeTest, PrimeNumbers){
    const int rows=5;
    const int cols=2;
    int **tab= primenumbers(rows); // Better idea is to use std::vector

    int values[rows][cols]={{1,2},
                            {2,3},
                            {3,5},
                            {4,7},
                            {5,11}};

    for (int i = 0; i < rows; ++i) {
        EXPECT_EQ(tab[i][1],values[i][1]);
        ASSERT_TRUE(is_prime(values[i][1])); //that test is enough
    }
    for (int i = 0; i < rows; ++i) {
        delete [] tab[i];
    }
    delete [] tab;
}

TEST(PrimeTest, PrimeNumbersVector){
    int rows=5;
    std::vector<std::vector<int>> expected={{1,2},{2,3},{3,5},{4,7},{5,11}};
    std::vector<std::vector<int>> result = primenumbers_vec(5);
    for (int i = 0; i < rows; ++i) {
        EXPECT_EQ(expected[i][1],result[i][1]);
    }
}

TEST(AvgTest, Average){
    const int size_tab=5;
    float tablica[size_tab]={3,5,4,3,1};

    float expected = 3.2;
    float result = avg(tablica, size_tab);
    EXPECT_EQ(result, expected);
}