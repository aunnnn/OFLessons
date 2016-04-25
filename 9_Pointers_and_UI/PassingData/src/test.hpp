//
//  test.hpp
//  PassingData
//
//  Created by Kris Meeusen on 22/04/16.
//
//

#ifndef test_hpp
#define test_hpp

#include <stdio.h>
#include "ofMain.h"


class test{
public:
    
    test();
    ~test();
    
    string& mName;
    
    void setName(string& name){
        mName = name;
    }
    
};

#endif /* test_hpp */
