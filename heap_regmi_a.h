#ifndef HEAP_REGMI_A
#define HEAP_REGMI_A

#include <climits>
#include <vector>
#include <cassert>
#include <iostream>
#include <sstream>
using namespace std;

typedef unsigned int uint;

/**
 * a generic heap class for use in analyzing build_heap and heap_sort
 * algorithms
 * @author Jon Beck
 * @author modified by Arjan Regmi
 * @version 6th April, 2017
 */
template< typename Comparable >
class Heap
{
 public:
  /**
   * The constructor for an empty heap
   */
  Heap( )
    : build_count{ 0 }, sort_count{ 0 } {}

  /**
   * The constructor that takes in an array and builds them into a heap
   * @param items a vector of items to go into the heap
   */
  explicit Heap( const vector<Comparable> & items )
    : build_count{ 0 }, sort_count{ 0 }, array{ items }
  {
    build_heap( );
  }

  /* since there are no dynamically allocated fields, all the rest of
     the big six do not need to be implemented */

  /**
   * accessor to determine whether there are any elements on the heap
   * @return true if the heap is empty; false otherwise
   */
  bool is_empty( ) const
  {
    return array.empty(); 
  }

  /**
   * accessor to determine how many basic operations were performed the
   * last time heap_sort was called. this would not be in a production
   * heap class
   * @return the count of the basic operations
   */
  uint heap_sort_count() const
  {
    return sort_count;
  }

  /**
   * accessor to determine how many basic operations were performed
   * the last time build_heap was called. this would not be in a
   * production heap class
   * @return the count of the basic operations
   */
  uint build_heap_count() const
  {
    return build_count;
  }

  /**
   * insert an element into the heap
   * @param value the value to be inserted
   */
  void insert( const Comparable & value )
  {
    array.push_back( value ); 
    bubble_up( array.size() - 1 ); 
  }

  /**
   * delete the maximum element from the heap. should be called
   * "delete" but that's a reserved word in C++
   * @return the element with the largest value in the heap
   */
  Comparable delete_max( )
  {
    assert( !is_empty() );
    uint temp = array.front(); 
    array.front() = array.at( array.size() - 1 ); 
    array.pop_back(); 
    percolate_down( 0 ); 
    return temp; 
  }

  /**
   * uses the heap_sort algorithm as described in Levitin 3rd pp 231
   * et seq sets the sort_count field. fills result vector with the
   * elements in order
   * @param result a vector that will be filled with the items in
   * ascending order
   */
  void heap_sort( vector< Comparable > & result )
  {
    build_heap( );
    result = array; 
    uint n = result.size();
    for( uint i = n - 1; i != 0; i-- )
    { 
      sort_count++;
      swap( result.at( 0 ), result.at( i ) ); 
      n--; 
      sort_count++; 
      percolate_down( 0, result, n ); 
    }
  }

  /**
   * generate a string representation of the array in its current
   * state requires the heap elements to implement the << operator
   * this is for debugging purposes; it would not be included in a
   * production class
   * @return string representation of the heap value in their current order
   */
  string to_string( ) const
  {
    if( is_empty() )
    {
      return "";
    }
    stringstream buffer;
    for( auto value : array )
    {
      buffer << value << ' ';
    }
    return buffer.str();
  }

 private:
  uint build_count;
  uint sort_count;
  vector<Comparable> array;

  /**
   * establish a valid heap from an arbitrary arrangement of items
   */
  void build_heap( )
  {
    for( uint i = array.size() / 2; i != UINT_MAX; i-- )
    {
      build_count++;
      sort_count++; 
      percolate_down( i ); // Basic Operation Candidate
    }
  }

  void bubble_up( uint index )
  {
    uint parent = ( index - 1 ) / 2; 
    while( index > 0 && array.at( index ) > array.at( parent ) )
    {
      swap( array.at( index ), array.at( parent ) ); 
      index = parent; 
      parent = ( index - 1 ) / 2; 
    }
  }

  void percolate_down( uint index )
  {
    while( (2 * index + 1) < array.size() )
    {
      uint child1 = 2 * index + 1; 
      uint child2 = child1 + 1; 

      uint big_child = child1; 
      if( child2 < array.size() && array.at( child2 ) > array.at( child1 ) )
      {
        big_child = child2; 
      }
      if( array.at( big_child ) > array.at( index ) )
      {
        swap( array.at( index ), array.at( big_child ) );
        index = big_child; 
      }
      else
      {
        index = array.size(); 
      }
    }
  }

  void percolate_down( uint index, vector<Comparable> & array, uint current_size )
  {
    while( (2 * index + 1) < current_size )
    {
      uint child1 = 2 * index + 1; 
      uint child2 = child1 + 1; 

      uint big_child = child1; 
      if( child2 < current_size && array.at( child2 ) > array.at( child1 ) )
      {
        big_child = child2; 
      }
      if( array.at( big_child ) > array.at( index ) )
      {
        swap( array.at( index ), array.at( big_child ) );
        index = big_child; 
      }
      else
      {
        index = current_size; 
      }
    }
  }
};

#endif