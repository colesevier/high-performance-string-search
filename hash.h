#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        // first compute the w values
        // i'm thinking of going in reverse order and then just having three cases
        // 1. equal to 6, below 6, and above 6
        // initialize w to all zero
        unsigned long long w[5] = {0};
        size_t len = k.size();
        if (len == 0)
        {
          return static_cast<HASH_INDEX_T>(0);
        }
        // fill w from the right to the left
        size_t wIndex = 4; // 0, 1, 2, 3, 4
        size_t end = len;
        // calculating w[]
        while (end > 0 && wIndex >=0)
        {
          size_t start = 0;
          if (end >= 6)
          {
            start = end - 6;
          }
          unsigned long long val = 0ULL;
          for (size_t i = start; i < end; i ++)
          {
            // base conversion
            val = val * 36ULL;
            // add value of the character
            val += static_cast<unsigned long long>(letterDigitToNumber(k[i]));
          }
          end = start;
          w[wIndex] = val;
          wIndex --;
        }

        // now calculate h(k)
        unsigned long long ret = 0ULL;
        // go through w and increment
        for (size_t i=0; i < 5; i ++)
        {
          ret += static_cast<unsigned long long>(rValues[i]) * w[i];
        }
        return ret;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // check for number first
        if (letter <= '9' && letter >= '0')
        {
          return letter - '0' + 26;
        }
        // Add code here or delete this helper function if you do not want it
        letter = static_cast<char>(std::tolower(static_cast<char>(letter)));
        return letter - 'a';
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
            
        }
    }
};

#endif
