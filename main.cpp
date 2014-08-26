//
//  main.cpp
//
//  Created by Duncan Cunningham on 5/17/13.
//  Copyright (c) 2013 Duncan Cunningham. All rights reserved.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//----------------------------------------------------------------------------------
//! Paritions elements around the supplied pivot element.  Elements less than the pivot
//! element will be to the left of pivot and elements to the right of the pivot will be
//! to the right.  Function operates on the range of aLeft to aRight on the list.
//! @return The new index of the pivot element
//----------------------------------------------------------------------------------
unsigned int parition
    (
    std::vector<int>& aList,    //!< List to parition
    unsigned int aLeft,         //!< Start index in list
    unsigned int aRight,        //!< End index in list
    unsigned int aPivot         //!< Pivot index
    )
{
    int pivot = aList[aPivot];
    unsigned int store = aLeft;
    
    std::swap( aList[aPivot], aList[aRight] );
    
    for( unsigned int i = aLeft; i < aRight; ++i )
    {
        if( aList[i] < pivot )
        {
            std::swap( aList[i], aList[store] );
            store++;
        }
    }
    
    std::swap( aList[store], aList[aRight] );
    
    return store;
}

//----------------------------------------------------------------------------------
//! Finds the kth largest element in the list when the list is in decending order.
//! Uses the median of medians algorithm to find the kth largest element.  The list
//! elements will be reordered.  Function operates on the range of left index to right
//! index on the list.
//! @return Index of the kth largest element
//----------------------------------------------------------------------------------
int findKthLargest
    (
    std::vector<int>& aList,    //!< List to search through
    unsigned int aLeft,         //!< Start index in list
    unsigned int aRight,        //!< End index in list
    unsigned int aKth           //!< Kth largest element
    )
{
    unsigned int listLength = ( aRight + 1 ) - aLeft;
    unsigned int medianAdvance = 5 / 2;
    unsigned int medianCount = ( listLength ) / 5;
    unsigned int remainder = ( listLength ) % 5;
    
    // Account for remainder
    if( remainder )
    {
        medianCount++;
    }

    // Find all the median and place them at the start
    for( unsigned int i = 0; i < medianCount; ++i )
    {
        unsigned int subLeft = aLeft + i * 5;
        unsigned int subRight = subLeft + 4;
        
        if( subRight > aRight )
        {
            medianAdvance = (remainder - 1) / 2;
        }
        
        std::swap( aList[aLeft + i], aList[subLeft + medianAdvance] );
    }
    
    // Parition the list around the median of the medians
    unsigned int medianIdx = parition( aList, aLeft, aRight, aLeft + medianCount / 2 );
    
    // Length of elements greater than the median
    unsigned int greaterHalfLength = aRight - medianIdx;
    
    if( aKth <= greaterHalfLength )
    {
        return findKthLargest( aList, medianIdx + 1, aRight, aKth );
    }
    else if( aKth - 1 == greaterHalfLength )
    {
        return aLeft + medianCount / 2;
    }
    // Case where aKth >= greaterHalfLength + 1
    else
    {
        return findKthLargest( aList, aLeft, medianIdx - 1, aKth - greaterHalfLength - 1 );
    }
}

//----------------------------------------------------------------------------------
//! Finds the kth largest elements in a list
//----------------------------------------------------------------------------------
void findKthLargestElements
    (
    std::vector<int>& aList,        //!< List to search through         (in)
    std::vector<int>& aLargest,     //!< List of kth largest elements   (out)
    unsigned int aKth               //!< Kth largest to search for      (in)
    )

{
    if( !aList.empty() && aKth <= aList.size() )
    {
        // Find the kth largest element, with the list paritioned with the kth largest
        // element as the pivot
        unsigned int kthLargest = findKthLargest( aList, 0, aList.size() - 1, aKth );
        
        // Add the kth largest elements.  The kth largest elements are from
        // the pivot to the end of the list.
        for( unsigned int i = kthLargest; i < aList.size(); ++i )
        {
            aLargest.push_back( aList[i] );
        }
    }
}

//----------------------------------------------------------------------------------
//! Main entry point
//! @return Return code
//----------------------------------------------------------------------------------
int main
    (
    int aArgc,              //!< Command line argument count
    const char* aArgv[]     //!< Command line arguments
    )
{
    int kth = 0;
    std::vector<int> numbers;

    if( aArgc > 2 )
    {
        std::ifstream file( aArgv[1] );
        
        if( file.is_open() )
        {
            std::string line;

            while( file.good() )
            {
                std::getline( file, line );
                std::istringstream stream( line );

                int number;
                if( stream >> number )
                {
                    numbers.push_back( number );
                }
            }

            file.close();

        }
        else
        {
            std::cout << "Unable to open file " << aArgv[1] << std::endl;
        }

        std::istringstream stream( aArgv[2] );

        if( !( stream >> kth ) )
        {
            std::cout << "Error, invalid kth number specified" << std::endl;
        }
    }
    else if( aArgc == 2 )
    {
        std::cout << "Error, no kth number specified" << std::endl;
    }
    else if( aArgc == 1 )
    {
        std::cout << "Error, no data file or kth number specified" << std::endl;
    }
        
    if( !numbers.empty()  and kth > 0 )
    {
        std::vector<int> largest;
        findKthLargestElements( numbers, largest, kth );
    
        for( unsigned int i = 0; i < largest.size(); ++i )
        {
            std::cout << largest[i] << std::endl;
        }
    }
    
    return 0;
}

