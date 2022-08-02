#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include “utils.h”

// include build configuration defines
#include “../config.h”

VIP_ENCSTRING target;

void soundex(VIP_ENCSTRING s, VIP_ENCINT pos, VIP_ENCBOOL f( char c ) )
{
// write your algorithm
#ifdef VIP_NA_MODE
if ( pos >= s.size() ) return s;                                  
   string::iterator end = remove_if( s.begin() + pos, s.end(), f );  
   return s.substr( 0, end - s.begin() ); 
// do native stuff
// write the soundex algorithm here
#else

// do oblivious stuff
#endif
}
VIP_ENCBOOL isIn( VIP_ENCCHAR c ) { return target.find( toupper( c ) ) != string::npos; }

VIP_ENCBOOL notAlpha( VIP_ENCCHAR c ) { return !isalpha( c ); }


VIP_ENCSTRING soundex( VIP_ENCSTRING word )
{
    // VIP_INIT;
    //FOR DECLARATION OF MAP
     map<VIPCHAR,VIPCHAR> cmap = { {'B','1'}, {'F','1'}, {'P','1'}, {'V','1'},
                           {'C','2'}, {'G','2'}, {'J','2'}, {'K','2'}, {'Q','2'}, {'S','2'}, {'X','2'}, {'Z','2'},
                           {'D','3'}, {'T','3'},
                           {'L','4'},
                           {'M','5'}, {'N','5'},
                           {'R','6'} };


   //REMOVECHARS
    VIP_ENCSTRING result = removeChars( word, 0, notAlpha );

   
   for ( char &c : result ) c = toupper( c );

   
   char firstLetter = result[0];

   
   target = "HW";   result = removeChars( result, 1, isIn );

   
   for ( char &c : result ) { if ( cmap.count( c ) ) c = cmap[c]; }

   for ( int i = 1; i < result.size(); i++ ) if ( result[i] == result[i-1] ) result[i-1] = '*';
   target = "*";   result = removeChars( result, 1, isIn );

   
   target = "AEIOUY";   result = removeChars( result, 1, isIn );

   
   result[0] = firstLetter;

   
   result += "000";
   return result.substr( 0, 4 );

    // generating input data
    // VIP_ENCINT data = 0;

    // {
    //     Stopwatch s(“VIP_Bench_Runtime”);
    //     soundex(data);
    // }

    return 0;

}
int main()
{
   VIP_ENCSTRING word;
   while ( true )
   {
      fprintf(stdout, "Enter a word (empty to end): ", word);
      // cout << "Enter a word (empty to end): ";   getline( cin, word );
      if ( word == "" ) exit( 0 );
       fprintf(stdout,"Soundex representation is " \n<< soundex( word ) << endl;);
      // cout << "Soundex representation is " << soundex( word ) << endl;
   }
}