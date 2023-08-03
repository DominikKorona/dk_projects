#ifndef CPP_BASICS_COURSE_HPP
#define CPP_BASICS_COURSE_HPP

#include <list>
#include <string>
#include <vector>

std::list<int> sweets(int childrens, int amount);

void reversion(std::string &name);

void capitalletters(std::string &str);

bool is_prime(int number);

int **primenumbers(int rows);

std::vector<std::vector<int>> primenumbers_vec(int number);

float avg(float *values, int ile);
#endif //CPP_BASICS_COURSE_HPP
