# AdvAlgo-Assgn2
In the Text file ( AESOP TALES.txt ) provided as data
Develop implementations  for the interface spec below:

    Find_Length_of _Text( txtfile )   // normalize multiple blank chars to
                                     // single blank char and remove(store)
                                    // website URLS that have infected
                                    // text file using FSA based RegEx
                                   //  matcher

    Find_Pattern ( ​ pattern , InTextRange,  algo)   // Find the number of occurrences of
                                                     // pattern  using any one of the
                                                    //  following  algo rithms (2nd parameter)
                                                    //  Rabin­Karp,  Knuth_Morris_Pratt
                                                    //  Suffix Tree (with Suffix arrays & LCP)
                                                  //   InTextRange :  can be  indices or
                                                 //    two patterns (e.g two story titles)

    Build_Cross_Index(txtfile, algo )//  Build an Index (Lex sorted)
                                     // (​ Word​ , Number of occurrences,   
                                    //   List of Story Titles & # of
                                    //   occurrences of ​ Word)

    Find_Maximal,Palindromes​ (PalindromeSize,  InTextRange ) // List maximal palindromes of size
                                                             // greater than or equal to
                                                             //  PalindromeSize,  with occurrences   (Story titles and  indices )

    Print_Stats ( ) // Text Size used,  URL infection  list    found,   
                     //  Algo Used, Preprocessing time, Search time
                     // (Vary  the parameters ​ pattern ,
                    //  InTextRange )

    for ​ timing plot //  and Self Test & Verification outcome



///USAGE
KMP
    kmp(char* text, char* pattern); //the function itself prints all the occurrences (location) of the pattern

Search using suffix arrays
    create_suff_arr();
    linear_search(char* text_to_be_searched);

Palindrome
    find_palindrome(int length);
