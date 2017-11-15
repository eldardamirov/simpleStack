//
//  main.cpp
//  Stack
//
//  Created by Эльдар Дамиров on 11.10.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#define stackUnit stackElement <typeOfData>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <functional>
#include <unordered_map>

#include <time.h>

#include "fileIO.h"
#include "logsConstants.h"


enum { NONE, LOW, MEDIUM, FULL };

/*
 NONE - no secure features at all;
 LOW - canaries checker;
 MEDIUM - elements sum, canaries checker;
 FULL - hash, elements sum, class sum, canaries checker;
*/


//// ------------------------------------------------------------------------------------------------
const int poisonInt = 12345678;
const double poisonDouble = NAN;
const float poisonFloat = NAN;
const char poisonChar = '~';
//// ------------------------------------------------------------------------------------------------


template <typename typeOfData> struct stackElement
    {
    typeOfData elementValue;
    size_t elementHashValue = 0;
    };
    

template <typename typeOfData> class Stack 
    {
    public:
        Stack ( int tempStackCapacity, int tempStackSecurutyMode )
            {
            stackCapacity = tempStackCapacity;
            init();
            }
            
        ~Stack()
            {
            
//            for ( int i = 0; i < stackCapacity; i++ )
//                {
//                printf ( "%d\n", ( stackBeginning + i )->elementValue );
//                }
            
            delete[] stackBeginning;
            }
            
            
        int push ( typeOfData pushingValue )
            {                
            if ( ( stackCurrentSize + 1 ) == stackCapacity )
                {
                reinitStack ( stackCapacity * 2 );
                stackCapacity = stackCapacity * 2;
                }
                
            ( stackBeginning + stackCurrentElement )->elementValue = pushingValue;
            stackCurrentElement++; 
            
            if ( stackSecurityMode > MEDIUM )
                {
                // here hash should happen;
                }
            
            return 0;
            }
            
        typeOfData pop()
            {
            stackCurrentElement--;
            return ( stackBeginning + stackCurrentElement )->elementValue;
            }
            
        typeOfData* top()
            {
            return ( typeOfData* ) &( stackBeginning + stackCurrentElement - 1 )->elementValue;
            }
        
        bool empty()
            {
            if ( stackCurrentSize == 0 )
                {
                return true;
                }
            else
                {
                return false;
                }
            }
            
        size_t size()
            {
            return stackCurrentSize;
            }
        
        
        
            
        
        
    private:

//// ------------------------------------------------------------------------------------------------
        stackElement <typeOfData>* stackBeginning = nullptr;
        int stackCurrentElement = 0, stackCapacity = 0;
        int stackCurrentSize = 0;
        int stackSecurityMode = FULL;
        bool isOk = true;
        std::string errorList = "";
        typeOfData poisonValue;
        
//// ------------------------------------------------------------------------------------------------
        int init()
            {
            stackBeginning = new stackUnit [ stackCapacity ];
            if ( stackBeginning == nullptr )
                {
                errorList = errorList + stackInitError;
                return 1;
                }
            
            if ( setPoisonValue() == 1 )
                {
                return 1;
                }
        
            for ( int i = 0; i < stackCapacity; i++ )
                {
                ( stackBeginning + i )->elementValue = poisonValue; 
                }
                
            return 0;
            }
            
            
        int setPoisonValue()
            {
            if ( typeid ( typeOfData ).name() == typeid ( int ).name() )
                {
                poisonValue = poisonInt;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( double ).name() )
                {
                poisonValue = poisonDouble;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( float ).name() )
                {
                poisonValue = poisonFloat;
                }
            else if ( typeid ( typeOfData ).name() == typeid ( char ).name() )
                {
                poisonValue = poisonChar;
                }
            else
                {
                errorList = errorList + detectVariableTypeError;
                return 1;
                }
                
            return 0;
            }
            
        int reinitStack ( int newStackCapacity )
            {
            stackUnit* tempStackBeginning = new stackUnit [ newStackCapacity ];
            if ( tempStackBeginning == nullptr )
                {
                errorList = errorList + stackBeginningError;
                return 1;
                }
            
            
            if ( stackSecurityMode < FULL )  
                {
                for ( int i = 0; i <= stackCurrentElement; i++ )
                    {
                    ( tempStackBeginning + i )->elementValue = ( stackBeginning + i )->elementValue;
                    }
                }
            else
                {
                for ( int i = 0; i <= stackCurrentElement; i++ )
                    {
                    ( tempStackBeginning + i )->elementValue = ( stackBeginning + i )->elementValue;
                    ( tempStackBeginning + i )->elementHashValue = ( stackBeginning + i )->elementHashValue;
                    }
                }
                
            stackCapacity = newStackCapacity;
                
    
            for ( int i = ( stackCurrentElement + 1 ); i < stackCapacity; i++ )
                {
                ( tempStackBeginning + i )->elementValue = poisonValue;
                }
             
            stackBeginning = tempStackBeginning;
             
            return 0;
            }
            
        
                
    
    };
    
    
int main()
    {
    Stack <double> tempClass ( 10000, FULL );
    
    //tempClass.reinitStack ( 100000000 );
    tempClass.push ( 5.758384 );
    tempClass.push ( 5.758384 );
    tempClass.push ( 5.758384 );
    tempClass.push ( 5.758384 );
    tempClass.push ( 5.758384 );
    tempClass.push ( 5.75832 );
    tempClass.pop();
    std::cout << *tempClass.top();
    
    

    return 0;
    }








