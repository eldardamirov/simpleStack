//
//  main.cpp
//  stack
//
//  Created by Эльдар Дамиров on 11.10.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

#include <time.h>


#include "fileIO.h"





class stack
    {
    public:
        
        typedef int typeOfData;
        
        
        stack ( size_t newStackCapacity )
            {
            stackCapacity = newStackCapacity;
            init();
            }
        
        ~stack()
            {
            
            }
        

        
        typeOfData* getBeginningOfStack()
            {
            if ( beginningOfStack == nullptr )
                {
                printf ( "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In getBeginningOfStack: " + "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";
                return nullptr;
                }
            return beginningOfStack;
            }
        
        typeOfData* getCurrentFreeElement()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement < beginningOfStack ) )
                {
                printf ( "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In getCurrentFreeElement: " + "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";
                return nullptr;
                }
                
            return currentFreeElement;
            }
        
        size_t getStackCapacity()
            {
            if ( stackCapacity == 0 )
                {
                printf ( "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In getStackCapacity: " + "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n";
                return -1;
                }
                
            return stackCapacity;
            }
        
        int setBeginningOfStack ( typeOfData* newBeginningOfStack )
            {
            if ( newBeginningOfStack == nullptr )
                {
                printf ( "New beginning of stack is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In setBeginningOfStack: " + "New beginning of stack is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
            
            beginningOfStack = newBeginningOfStack;
            
            return 0;
            }
        
        int setCurrentFreeElement ( typeOfData* newCurrentFreeElement )
            {
            if ( newCurrentFreeElement == nullptr )
                {
                printf ( "New current free element is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In setCurrentFreeElement: " + "New current free element is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
                
            currentFreeElement = newCurrentFreeElement;
            
            return 0;
            }
        
        int setStackCapacity ( size_t newStackCapacity )
            {
            if ( newStackCapacity == 0 )
                {
                printf ( "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In setStackCapacity: " + "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n";
                return -1;
                }
                
            stackCapacity = newStackCapacity;
                
            return 0;
            }
        
        int push ( typeOfData elementToPush )
            {
            if ( currentFreeElement > ( beginningOfStack + ( stackCapacity - 1 ) ) )
                {
                printf ( "Bad access, trying to access element out of range. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In PUSH: " + "Bad access, trying to access element out of range. ¯|_(ツ)_/¯ \n";
                return -1;
                }
            
            *currentFreeElement = elementToPush;
            currentFreeElement++;
            
            return 0;
            }
        
        int clear()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement == nullptr ) )
                {
                printf ( "Stack isn't initialized, or some error during init has occured. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In CLEAR: " + "Stack isn't initialized, or some error during init has occured. ¯|_(ツ)_/¯ \n";
                return -1;
                }
                
            currentFreeElement = beginningOfStack;
            
            return 0;
            }
        
        typeOfData* top()
            {
            if ( ( ( currentFreeElement - 1 ) == nullptr ) || ( beginningOfStack == nullptr ) )
                {
                printf ( "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In TOP: " + "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return nullptr;
                }
            
            if ( ( currentFreeElement - 1 ) < beginningOfStack )
                {
                return beginningOfStack;
                }
            else
                {
                return ( currentFreeElement - 1 );
                }
                
            }
        
        int pop()
            {
            if ( ( currentFreeElement - 1 ) <  beginningOfStack )
                {
                printf ( "Current top element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In POP: " + "Current top element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. ¯|_(ツ)_/¯ \n";

                return -1;
                }
                
            currentFreeElement--;
            
            return 0;
            }
        
        bool empty()
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement == nullptr ) )
                {
                printf ( "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In EMPTY: " + "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

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
                printf ( "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In SIZE: " + "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
                
            int currentSize = ( currentFreeElement - beginningOfStack );
            
            return currentSize;
            }
        
        int swap ( stack stackToSwapWith )
            {
            typeOfData* tempBeginningOfStack = stackToSwapWith.getBeginningOfStack();
            typeOfData* tempCurrentFreeElement = stackToSwapWith.getCurrentFreeElement();
            size_t tempStackCapacity = stackToSwapWith.getStackCapacity();
            
            if ( ( tempBeginningOfStack == nullptr ) || ( tempCurrentFreeElement == nullptr ) || ( tempStackCapacity == 0 ) )
                {
                printf ( "One of the swapping stacks isn't initialised or working wrong. ¯|_(ツ)_/¯ \n" );
                listOfErrors = listOfErrors + "In SWAP: " + "One of the swapping stacks isn't initialised or working wrong. ¯|_(ツ)_/¯ \n";
                
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
                dumpOutput.writeNextChar ( 'f' );
                }

            return 0;
            }
            
        
    
    private:
        typeOfData* beginningOfStack = nullptr;

        size_t stackCapacity = 0;
        typeOfData* currentFreeElement = nullptr;
        std::string listOfErrors = "";
        
        int init()
            {
            beginningOfStack = ( typeOfData* ) calloc ( stackCapacity, sizeof ( typeOfData ) );
            
            if ( beginningOfStack == nullptr )
                {
                printf ( "Beginning pointer isn't correct. ¯|_(ツ)_/¯ \n" );
                return -1;
                }
            
            currentFreeElement = beginningOfStack;
            
            return 0;
            }
        
        
    };



int main(int argc, const char * argv[])
    {
    

    
    stack myStack ( 2 );
    myStack.push ( 53 );
    myStack.push ( 46 );
    myStack.pop();
    myStack.push ( 5348 );
    
    stack myStack2 ( 1 );
    myStack2.push ( 28379 );
    myStack2.push ( 4727 );
    
    myStack.swap ( myStack2 );
    
    myStack.dump();
    
    printf ( "%d", myStack.size() );
    
    return 0;
    }
