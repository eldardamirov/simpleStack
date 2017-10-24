//
//  main.cpp
//  stack
//
//  Created by Эльдар Дамиров on 11.10.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#include<bits/stdc++.h>


#include "fileIO.h"




const int poisonInt = 12345678;
const double poisonDouble = NAN;
const float poisonFloat = NAN;
const char poisonChar = '~';


template <typename typeOfData> struct stackElement
    {
    typeOfData element;
//    std::string previousHash;
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
            
            }
            
        
        //////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////
        
        void selfTest()
            {
            ( beginningOfStack + 1 )->element = 7865;
            }
        
        
        
        //////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////
        
        
        
        
        stackElement <typeOfData>* getBeginningOfStack() // returns pointer to beginning of stack;
            {
            if ( beginningOfStack == nullptr )
                { 
                
                listOfErrors = listOfErrors + "In getBeginningOfStack: " + "Stack isn't initialized, or some error during init has occured. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";
                return nullptr;
                }
            return beginningOfStack;
            }
        
        
        typeOfData* getCurrentFreeElement() // returns pointer to next element in stack that is currently free;
            {
            if ( ( currentFreeElement == nullptr ) || ( currentFreeElement < beginningOfStack ) )
                {
         
                listOfErrors = listOfErrors + "In getCurrentFreeElement: " + "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";
                return nullptr;
                }
                
            return currentFreeElement;
            }
        
        size_t getStackCapacity() // returns stack capacity;
            {
            if ( stackCapacity == 0 )
                {
                
                listOfErrors = listOfErrors + "In getStackCapacity: " + "Something is wrong with stack storage or stack capacity value hasn't been updated. ¯|_(ツ)_/¯ \n";
                return -1;
                }
                
            return stackCapacity;
            }
        
        int setBeginningOfStack ( typeOfData* newBeginningOfStack ) // sets new stack beginning;
            {
            if ( newBeginningOfStack == nullptr )
                {
                
                listOfErrors = listOfErrors + "In setBeginningOfStack: " + "New beginning of stack is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
            
            beginningOfStack = newBeginningOfStack;
            
            return 0;
            }
        
        int setCurrentFreeElement ( typeOfData* newCurrentFreeElement ) // sets new pointer to new free element;
            {
            if ( newCurrentFreeElement == nullptr )
                {
                
                listOfErrors = listOfErrors + "In setCurrentFreeElement: " + "New current free element is incorrect. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return -1;
                }
                
            currentFreeElement = newCurrentFreeElement;
            
            return 0;
            }
        
        int setStackCapacity ( size_t newStackCapacity ) // sets new stack capacity;
            {
            if ( newStackCapacity == 0 )
                {
                
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
                
                listOfErrors = listOfErrors + "In PUSH: " + "Bad access, trying to access element out of range. ¯|_(ツ)_/¯ \n";
                return -1;
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
                
                listOfErrors = listOfErrors + "In TOP: " + "Current free element is out of range or even hasn't been initialized, maybe something is wrong with stack pointer. (Note that returning value in this case isn't prorep one) ¯|_(ツ)_/¯ \n";

                return nullptr;
                }
            
            if ( ( currentFreeElement - 1 ) < beginningOfStack )
                {
                return ( typeOfData* ) beginningOfStack->element;
                }
            else
                {
                return ( typeOfData* ) ( currentFreeElement - 1 )->element;
                }
                
            }
        
        int pop()
            {
            if ( ( currentFreeElement - 1 ) <  beginningOfStack )
                {
                
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
//                    dumpOutput.writeString ( "%" );
                    }
                dumpOutput.writeString ( " ]" );
                }
                
                
            for ( int i = 0; i < ( getStackCapacity() - 1 ); i++ )
                {
                std::cout << ( typeOfData ) ( beginningOfStack + i )->element << " hash: " << ( beginningOfStack + i )->hashOfElement << std::endl;
                }
            // make POISON_INT, POISON_DOUBLE

            return 0;
            }
            
        bool ok()
            {
            return checkHashes();
            }
            
        
    
    private:
    

        stackElement <typeOfData>* beginningOfStack ;
        size_t stackCapacity = 0;
        stackElement <typeOfData>* currentFreeElement;
        typeOfData poisonValue = NULL;
        std::string listOfErrors = "";
        
        
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
                printf ( "Beginning pointer isn't correct. ¯|_(ツ)_/¯ \n" );
                return -1;
                }
            
            currentFreeElement = beginningOfStack;
            
            
            
            return 0;
            }
            
            
        int enlargeStack()
            {
            if ( beginningOfStack == nullptr )
                {
                printf ( "Beginning pointer isn't correct. ¯|_(ツ)_/¯ \n" );
                return -1;
                }
                
                
            int tempCurrentFreeElement = ( currentFreeElement - beginningOfStack );
            
            beginningOfStack = ( stackElement <typeOfData>* ) realloc ( beginningOfStack, ( ( stackCapacity * 2 ) * sizeof ( stackElement <typeOfData> ) ) );
            stackCapacity = stackCapacity * 2;
        
            
            currentFreeElement = ( beginningOfStack + tempCurrentFreeElement );
        
            for ( stackElement <typeOfData>* i = currentFreeElement; i < ( beginningOfStack + stackCapacity ); i++ )
                {
                i->element = poisonValue;
                }
            
            return 0;
            }
            
        bool checkHashes()
            {
            for ( int indexMove = 1; indexMove < size(); indexMove++ )
                {
                //if (  ( ( beginningOfStack + indexMove )->previousHash ) != std::hash <std::string> {} ( std::to_string ( ( beginningOfStack + indexMove )->element ) ) )
                if ( ( ( beginningOfStack + indexMove )->hashOfElement ) !=  std::to_string ( std::hash <std::string> {} ( std::to_string ( ( currentFreeElement + indexMove )->element ) ) ) ) 
                    {
                    std::cout << "COMPARING VALUES: " << ( ( beginningOfStack + indexMove )->hashOfElement ) << "   " << std::to_string ( ( std::hash <std::string> {} ( std::to_string ( ( beginningOfStack + indexMove )->element ) ) ) ) << std::endl;
                    
//                    printf ( "\n !!!! \n" );
//                    return false;
//                    printf ( "\n !!!! \n" );

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

    printf ( "AAAA: %d\n", myStack.top() );
    
    stackElement <int>* pointer = myStack.getBeginningOfStack();

    //myStack.selfTest();
    
    //( myStack.getBeginningOfStack() + 2 )->element = 5;
    
    
    myStack.dump();
    ( myStack.getBeginningOfStack() + 2 )->element = 5;
    std::cout << "STATUS: " << myStack.ok() << std::endl;
    
    
    size_t hash1 = std::hash <std::string> {} ( "6" );
    std::cout << "HASH: " << hash1 << std::endl;

    
    
    return 0;
    }


/*
контрольная сумма
привести this к (char*) и до sizeof записать хеш
канарейки - в начале и конце, пострадают первым



*/
