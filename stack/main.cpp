//
//  main.cpp
//  stack
//
//  Created by Эльдар Дамиров on 11.10.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <functional>
#include <unordered_map>

#include <time.h>

#include "fileIO.h"
#include "logsConstants.h"


//// ------------------------------------------------------------------------------------------------
const int poisonInt = 12345678;
const double poisonDouble = NAN;
const float poisonFloat = NAN;
const char poisonChar = '~';
//// ------------------------------------------------------------------------------------------------


template <typename typeOfData> struct stackElement
    {
    typeOfData element;
    std::string hashOfElement = "";
    };


template <typename typeOfData> class stack
    {
    public:
    
        stack ( size_t newStackCapacity )
            {
            stackCapacity = newStackCapacity;
            init();
            }
        
        ~stack()
            {
            free ( beginningOfStack );
            }
            
        
        //// ------------------------------------------------------------------------------------------------
        int selfTest()
            {
            srand ( time ( NULL ) );
            
            for ( stackElement <typeOfData>* i = beginningOfStack; i < currentFreeElement; i++ )
                {
                if ( rand() % 4 == 1 )
                    {
                    i->element = poisonValue;
                    }
                }
                
            return 0;
            }
        //// ------------------------------------------------------------------------------------------------
        
        
        
        
        
        stackElement <typeOfData>* getBeginningOfStack() // returns pointer to beginning of stack;
            {
            if ( beginningOfStack == nullptr )
                { 
                
                listOfErrors = listOfErrors + "In getBeginningOfStack: " + stackInitError;
                return nullptr;
                }
            return beginningOfStack;
            }
        
        
        typeOfData* getCurrentFreeElement() // returns pointer to next element in stack that is currently free;
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement < beginningOfStack ) )
                {
         
                listOfErrors = listOfErrors + "In getCurrentFreeElement: " + stackCurrentFreeElementError;
                return nullptr;
                }
                
            return currentFreeElement;
            }
        
        size_t getStackCapacity() // returns stack capacity;
            {
            if ( stackCapacity == 0 )
                {
                listOfErrors = listOfErrors + "In getStackCapacity: " + stackStorageError;
                
                throw;
                }
                
            return stackCapacity;
            }
        
        int setBeginningOfStack ( typeOfData* newBeginningOfStack ) // sets new stack beginning;
            {
            if ( newBeginningOfStack == nullptr )
                {
                
                listOfErrors = listOfErrors + "In setBeginningOfStack: " + stackBeginningError;

                throw;
                }
            
            beginningOfStack = newBeginningOfStack;
            
            return 0;
            }
        
        int setCurrentFreeElement ( typeOfData* newCurrentFreeElement ) // sets new pointer to new free element;
            {
            if ( newCurrentFreeElement == nullptr )
                {
                
                listOfErrors = listOfErrors + "In setCurrentFreeElement: " + stackCurrentFreeElementError;

                throw;
                }
                
            currentFreeElement = newCurrentFreeElement;
            
            return 0;
            }
        
        int setStackCapacity ( size_t newStackCapacity ) // sets new stack capacity;
            {
            if ( newStackCapacity == 0 )
                {
                listOfErrors = listOfErrors + "In setStackCapacity: " + stackStorageError;
                
                throw;
                }
                
            stackCapacity = newStackCapacity;
                
            return 0;
            }
        
        int push ( typeOfData elementToPush )
            {
            if ( currentFreeElement > ( beginningOfStack + ( stackCapacity - 1 ) ) )
                {
                listOfErrors = listOfErrors + "In PUSH: " + stackCurrentFreeElementError;
                
                throw;
                }
            
                
            currentFreeElement->element = elementToPush;
            currentFreeElement->hashOfElement = std::to_string ( std::hash <std::string> {} ( std::to_string ( currentFreeElement->element ) ) );
            
            currentFreeElement++;
            
            
            if ( ( currentFreeElement ) == ( beginningOfStack + ( stackCapacity - 1 ) ) )
                {
                enlargeStack();
                }
                
            return 0;
            }
        
        int clear()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement == nullptr ) )
                {
                listOfErrors = listOfErrors + "In CLEAR: " + stackInitError;
                
                throw;
                }
                
            currentFreeElement = beginningOfStack;
            
            return 0;
            }
        
        typeOfData* top()
            {
            if ( ( ( currentFreeElement - 1 ) == nullptr ) || ( beginningOfStack == nullptr ) )
                {
                
                listOfErrors = listOfErrors + "In TOP: " + stackCurrentFreeElementError;

                return nullptr;
                }
            
//            if ( ( currentFreeElement - 1 ) < beginningOfStack )
//                {
//                return ( typeOfData* ) beginningOfStack->element;
//                }
//            else
//                {
//                return ( typeOfData* ) ( currentFreeElement - 1 )->element;
//                }

            return ( typeOfData* ) ( currentFreeElement - 1 )->element;
            }
        
        int pop()
            {
            if ( ( currentFreeElement - 1 ) <  beginningOfStack )
                {
                
                listOfErrors = listOfErrors + "In POP: " + stackCurrentFreeElementError;

                throw;
                }
                
            currentFreeElement--;
            
            return 0;
            }
        
        bool empty()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement == nullptr ) )
                {
                listOfErrors = listOfErrors + "In EMPTY: " + stackInitError;

                return false;
                }
            
            if ( currentFreeElement == beginningOfStack )
                {
                return true;
                }
            else
                {
                return false;
                }
            }
        
        int size()
            {
            if ( ( beginningOfStack == nullptr ) || ( currentFreeElement < beginningOfStack ) || ( currentFreeElement == nullptr ) )
                {
                listOfErrors = listOfErrors + "In SIZE: " + stackInitError;

                throw;
                }
                
            int currentSize = ( currentFreeElement - beginningOfStack ) + 1;
            
            return currentSize;
            }
        
        int swap ( stack stackToSwapWith )
            {
            typeOfData* tempBeginningOfStack = stackToSwapWith.getBeginningOfStack();
            typeOfData* tempCurrentFreeElement = stackToSwapWith.getCurrentFreeElement();
            size_t tempStackCapacity = stackToSwapWith.getStackCapacity();
            
            if ( ( tempBeginningOfStack == nullptr ) || ( tempCurrentFreeElement == nullptr ) || ( tempStackCapacity == 0 ) )
                {
                printf ( stackStorageError );
                listOfErrors = listOfErrors + "In SWAP: " + stackStorageError;
                
                return -1;
                }
                
            stackToSwapWith.setBeginningOfStack ( beginningOfStack );
            stackToSwapWith.setCurrentFreeElement ( currentFreeElement );
            stackToSwapWith.setStackCapacity ( stackCapacity );
            
            beginningOfStack = tempBeginningOfStack;
            currentFreeElement = tempCurrentFreeElement;
            stackCapacity = tempStackCapacity;
            
            return 0;
            }
        
        
        int dump()
            {
            writeToFile dumpOutput ( "dump.txt", 10000 );
            
            std::string firstLine = "Errors: ";
            if ( listOfErrors.size() == 0 )
                {
                firstLine = firstLine + "none of them. \n";
                }
            else
                {
                firstLine = firstLine + "\n";
                }
            
            for ( int i = 0; i < firstLine.size(); i++ )
                {
                dumpOutput.writeNextChar ( firstLine [ i ] );
                }
            
            for ( int i = 0; i < listOfErrors.size(); i++ )
                {
                dumpOutput.writeNextChar ( listOfErrors [ i ] );
                }
                
            
            dumpOutput.writeString ( "\n Stack is" );
            if ( ok() == true )
                {
                dumpOutput.writeString ( " ok.\n" );
                }
            else
                {
                dumpOutput.writeString ( "n't ok.\n" );
                }
            
            
            for ( int i = 0; i < getStackCapacity(); i++ )
                {
                dumpOutput.writeString ( "\n[ " );
                
                if ( ( beginningOfStack + i )->element != poisonValue )
                    {
                    dumpOutput.writeNextChar ( ( typeOfData ) ( beginningOfStack + i )->element );
                    }
                else
                    {
                    dumpOutput.writeString ( " Here is poison value " );
                    }
                    
                dumpOutput.writeString ( " ]" );
                }
                
            for ( int i = 0; i < ( getStackCapacity() - 1 ); i++ )
                {
                std::cout << ( typeOfData ) ( beginningOfStack + i )->element << " hash: " << ( beginningOfStack + i )->hashOfElement << std::endl;
                }

            return 0;
            }
            
        bool ok()
            {
            return checkHashes();
            }
            
        
    
    private:
    
        //// ------------------------------------------------------------------------------------------------
        stackElement <typeOfData>* beginningOfStack;
        stackElement <typeOfData>* currentFreeElement;
        size_t stackCapacity = 0;
        //// ------------------------------------------------------------------------------------------------
        typeOfData poisonValue = NULL;
        std::string listOfErrors = "";
        //// ------------------------------------------------------------------------------------------------
        
        long long hashSum = 0;
        
        int init()
            {
            beginningOfStack = ( stackElement <typeOfData>* ) calloc ( stackCapacity, sizeof ( stackElement <typeOfData> ) );
            
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
                poisonValue = NAN;
                }
                
            for ( int i = 0; i < getStackCapacity(); i++ )
                {
                ( beginningOfStack + i )->element = poisonValue;
                }
            
            if ( beginningOfStack == nullptr )
                {
                printf ( "%s", stackBeginningError );
                
                throw;
                }
            
            currentFreeElement = beginningOfStack;
            
            
            return 0;
            }
            
            
        int enlargeStack()
            {
            if ( beginningOfStack == nullptr )
                {
                printf ( "%s", stackBeginningError );
                
                throw;
                }
                
                
            int tempCurrentFreeElement = ( currentFreeElement - beginningOfStack );
            
//            beginningOfStack = ( stackElement <typeOfData>* ) realloc ( beginningOfStack, ( ( stackCapacity * 2 ) * sizeof ( stackElement <typeOfData> ) ) );
            reinitStack ( tempCurrentFreeElement );
            stackCapacity = stackCapacity * 2;
        
            
            currentFreeElement = ( beginningOfStack + tempCurrentFreeElement );
        
            for ( stackElement <typeOfData>* i = currentFreeElement; i < ( beginningOfStack + stackCapacity ); i++ )
                {
                i->element = poisonValue;
                }
            
            return 0;
            }
            
        stackElement <typeOfData>* reinitStack ( int tempCurrentFreeElement )
            {
            stackElement <typeOfData>* tempBeginningOfStack = ( stackElement <typeOfData>* ) calloc ( ( stackCapacity * 2 ), sizeof ( stackElement <typeOfData> ) );
            
            for ( int i = 0; i < tempCurrentFreeElement; i++ )
                {
                ( tempBeginningOfStack + i )->element = ( beginningOfStack + i )->element;
                ( tempBeginningOfStack + i )->hashOfElement = ( beginningOfStack + i )->hashOfElement;
                }
                
            return tempBeginningOfStack;
            }
            
            
            
            bool checkHashes()
                {
                for ( stackElement <typeOfData>* currentElement = beginningOfStack; currentElement < currentFreeElement; currentElement++ )
                    {
                    if ( currentElement->hashOfElement != std::to_string ( std::hash <std::string> {} ( std::to_string ( currentElement->element ) ) ) )
                        {
                        return false;
                        }
                    }
                
                return true;
                }
                
        
    };




int main ( int argc, const char * argv[] )
    {
    stack <int> myStack ( 2 );
    myStack.push ( 445321 );
    myStack.push ( 6 );
    myStack.push ( 1 );
    myStack.push ( 17 );
    myStack.push ( 0 );
    myStack.push ( 63 );
    myStack.push ( 74 );
    myStack.push ( 831 );
    myStack.push ( 628 );
    myStack.pop();
    
    myStack.selfTest();

    printf ( "AAAA: %d\n", myStack.top() );
    
    //stackElement <int>* pointer = myStack.getBeginningOfStack();

    //myStack.selfTest();
    
    //( myStack.getBeginningOfStack() + 2 )->element = 5;
    
    
    myStack.dump();
    std::cout << "\nHEEEEEEEEEEY   " << myStack.ok() << "ENDL" << std::endl;
//    ( myStack.getBeginningOfStack() + 2 )->element = 5;
    //std::cout << "STATUS: " << myStack.ok() << std::endl;
    
    
    //size_t hash1 = std::hash <std::string> {} ( "6" );
    //std::cout << "HASH: " << hash1 << std::endl;

    
    
    return 0;
    }


/*
контрольная сумма
привести this к (char*) и до sizeof записать хеш
канарейки - в начале и конце, пострадают первым



*/
