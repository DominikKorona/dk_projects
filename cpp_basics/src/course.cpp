#include "course.hpp"

std::list<int> sweets(int childrens, int amount) {
    std::list<int> candies;
    int onepupil = (int) amount / (childrens - 1);
    int rest = amount % (childrens - 1);

    candies.push_back(onepupil);
    candies.push_back(rest);
    return candies;
}

void reversion(std::string &name) {
    int l = 7;
    for (int i = 0; i < l / 2; ++i) {
        std::swap(name[i], name[l - i - 1]);
    }
}

void capitalletters(std::string &str) {
    for (char &c: str) {
        if (std::islower(c) && (c >= 'a' && c <= 'z')) {
            c = (char) (c - 'a' + 'A'); // (char) lub static_cast<char>
        }
    }
}

bool is_prime(int number) {
    if (number < 2)
        return false;
    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0)
            return false;
    }
    return true;
}

int **primenumbers(int rows) {
    const int cols = 2;
    int **prime_tab = new int *[rows];
    for (int i = 0; i < rows; ++i) {
        prime_tab[i] = new int[cols];
        prime_tab[i][0] = i + 1;
        prime_tab[i][1] = 0;
    }

    int i = 2;
    int j = 0;
    while (j < rows) {
        if (is_prime(i)) {
            prime_tab[j][1] = i;
            j++;
        }
        i++;
    }
    return prime_tab;
}

std::vector<std::vector<int>> primenumbers_vec(int number) {
    std::vector<std::vector<int>> vec(number, std::vector<int>(2));
    for (int i = 0; i < number; ++i) {
        vec[i][0] = i + 1;
    }
    int counter = 0;
    int numb = 2;
    while (counter<number){
        if (is_prime(numb)) {
            vec[counter][1] = numb;
            counter++;
        }numb++;
    }
    return vec;
}

float avg(float *values, int ile) {
    float aver = 0;
    for (int i = 0; i < ile; ++i) {
        aver += *values;
        values++;
    }

    return aver / (float) (ile);
}