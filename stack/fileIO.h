//
//  fileIO.h
//  stack
//
//  Created by Эльдар Дамиров on 12.10.2017.
//  Copyright © 2017 Эльдар Дамиров. All rights reserved.
//

#ifndef fileIO_h
#define fileIO_h

#include <sys/uio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <bitset>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <time.h>


#include <iostream>




struct fileMapping
    {
    int fileDescriptor;
    size_t fileSize;
    unsigned char* dataPointer;
    };


class readFromFile
    {
    public:

        readFromFile ( char* inputFileName )
            {
            inputFileName = "input.txt";

            init();
            }

        ~readFromFile()
            {
            munmap ( dataPointer, fileSize );
            close ( mapping->fileDescriptor );
            free ( mapping );
            }



        char getNextChar()
            {
            char tempBuffer =  *( ( mapping->dataPointer ) + currentChar );
            currentChar++;

            return tempBuffer;
            }


        size_t getFileSize()
            {
            return fileSize;
            }


        char* meGetDataPointer()
            {
            return ( char* ) ( mapping->dataPointer );
            }


        bool isEnd()
            {
            return ( currentChar + 1 ) >= fileSize;
            }

    private:
        
        //// ------------------------------------------------------------------------------------------------
        char* inputFileName = {};
        //// ------------------------------------------------------------------------------------------------
        struct stat st;
        int fileDescriptor = 0;
        unsigned char* dataPointer = {};
        fileMapping* mapping;
        size_t fileSize = 0;
        //// ------------------------------------------------------------------------------------------------
        int currentChar = 0;
        //// ------------------------------------------------------------------------------------------------

        void init()
            {
            fileDescriptor = open ( "input.txt", O_RDWR , 0 );
            if ( fileDescriptor < 0 )
                {
                printf ( "File descriptor error.\n" );
                
                throw;
                }


            if ( fstat ( fileDescriptor, &st ) < 0 )
                {
                printf ( "Fstat failed.\n" );
                close ( fileDescriptor );
                
                throw;
                }
            fileSize = ( size_t ) st.st_size;

            dataPointer = getDataPointer ( fileSize, fileDescriptor );
            mapping = createFileMapping ( fileDescriptor, dataPointer, fileSize );


            }

        unsigned char* getDataPointer ( size_t fileSize, int fileDescriptor )
            {
            unsigned char* tempDataPointer = ( unsigned char* ) mmap ( nullptr, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fileDescriptor, 0 );

            if ( tempDataPointer == MAP_FAILED )
                {
                printf ( "mmap failed\n" );
                close ( fileDescriptor );

                throw;
                }

            return tempDataPointer;
            }

        fileMapping* createFileMapping ( int fileDescriptor, unsigned char* dataPointer, size_t fileSize )
            {
            fileMapping* tempMapping = ( fileMapping* ) malloc ( sizeof ( fileMapping ) );

            if ( tempMapping == nullptr )
                {
                printf ( "mmap failed\n" );
                munmap ( dataPointer, fileSize );
                close ( fileDescriptor );
                
                throw;
                }

            tempMapping->fileDescriptor = fileDescriptor;
            tempMapping->fileSize = fileSize;
            tempMapping->dataPointer = dataPointer;

            return tempMapping;
            }


    };



//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////



class writeToFile
    {
    public:

        writeToFile ( char* fileName, size_t fileSize )
            {
            outputFileName = fileName;
            fileSizeMe = fileSize + 1;

            init();
            }

        void writeNextChar ( char inputChar )
            {
            map [ currentPosition ] = inputChar;
            currentPosition++;
            }
        
        void writeString ( std::string inputString )
            {
            for ( int i = 0; i < inputString.size(); i++ )
                {
                writeNextChar ( inputString [ i ] );
                }
            }
        
        ~writeToFile()
            {
            msync ( map, fileSizeMe, MS_SYNC );
            munmap ( map, fileSizeMe );
            close ( fileDescriptor );

            }
            
    private:
    
        //// ------------------------------------------------------------------------------------------------
        char* outputFileName = {};
        //// ------------------------------------------------------------------------------------------------
        struct stat st;
        int fileDescriptor = 0;
        int fileDescription = 0;
        char* map;
        size_t fileSizeMe = 0;
        //// ------------------------------------------------------------------------------------------------
        int currentPosition = 0;
        //// ------------------------------------------------------------------------------------------------


        void init()
            {
            fileDescriptor = open ( "dump.txt", O_RDWR | O_CREAT , ( mode_t ) 0600 );
            if ( fileDescriptor < 0 )
                {
                printf ( "File descriptor error.\n" );
                
                throw;
                }

            fileDescription = makeFileDescription ( fileDescriptor, fileSizeMe );
            updateFileSize ( fileDescriptor, fileDescription );
            map = mmapFile ( fileDescriptor, fileSizeMe );
            }

        int makeFileDescription ( int fileDescriptor, size_t fileSize )
            {
            int tempFileDescription = lseek ( fileDescriptor, int ( fileSizeMe ), SEEK_SET );
            if ( tempFileDescription < 0 )
                {
                close ( fileDescriptor );
                printf ( "lseek error." );
                
                throw;
                }

            return tempFileDescription;
            }

        void updateFileSize ( int fileDescriptor, int fileDescription )
            {
            if ( write ( fileDescriptor, "", 1 ) < 0 )
                {
                close ( fileDescriptor );
                printf ( "Writing null string to last file's byte failed." );
                
                throw;
                }
            }

        char* mmapFile ( int fileDescriptor, size_t fileSize )
            {
            char* tempMap = ( char* ) ( mmap ( 0, fileSize, PROT_WRITE | PROT_READ, MAP_SHARED, fileDescriptor, 0 ) );
            if ( tempMap == MAP_FAILED )
                {
                close ( fileDescriptor );
                printf ( "File mapping failed." );
                
                throw;
                }

            return tempMap;
            }




    };


#endif /* fileIO_h */
