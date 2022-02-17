// Author: Omer Mustel (om2349)
// COMS W4995 - Design Using C++
// Date: 16 Feb 2022
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <string.h>
#include <cstdlib>
#include <chrono>

const int SIZE = 1'000'000;

auto compare( void const*, void const*) -> int;
auto compare_rev( void const*, void const*) -> int;
//template< size_t n >
void sort( std::vector<std::string>&, int flag );
char *convert(const std::string &);
int cmpstr(const void*, const void*);
int cmpstr_rev(const void*, const void*);


int main()
{
    std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    /******************
     < std::strings >
    ******************/

    std::vector<std::string> strings;
//    std::vector<std::string> cp_qs; //std::string qsort
//    std::vector<std::string> rev_qs; // reverse

//    std::vector<std::string> cp_s; // sts::string std::sort
//    std::vector<std::string>rev_s; // reverse

    /***********************
     <   c-style strings  >
    ***********************/
    std::vector<std::string> vs;

    int d = static_cast<int>(str.size()-1);
    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_int_distribution<> dist(0, d);

    for(int i=0; i < SIZE; ++i) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(4, 32);
        int size = distr(gen);
        std::string string = "";

        for(int j = 0; j < size; ++j) {
            int random_index = dist(engine); //get index between 0 and str.size()-1
            string += str[random_index];
        }
//        strings[i] = string;
        strings.push_back(string);
        vs.push_back(string);
    }


//    std::copy(std::begin(strings), std::end(strings), std::begin(cp_qs));
//    std::copy(std::begin(strings), std::end(strings), std::begin(rev_qs));
    /*********************************************/
    /*            std::strings                  */
    /********************************************/
    std::cout << "\nstd::strings\n\n";
    std::vector<std::string> cp_qs = strings; //std::string qsort
    std::vector<std::string> rev_qs = strings; // reverse
    std::vector<std::string> cp_s = strings; // sts::string std::sort
    std::vector<std::string>rev_s = strings; // reverse

    auto start = std::chrono::steady_clock::now();
    sort( cp_qs, 1 );
    auto now = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = now - start;
    std::cout << "qsort for std::strings time: " << elapsed_seconds.count() << "'s\n";


    start = std::chrono::steady_clock::now();
    sort( rev_qs, 0);
    now = std::chrono::steady_clock::now();
    elapsed_seconds = now - start;
    std::cout << "qsort reverse for std::strings time: " << elapsed_seconds.count() << "'s\n";



//    std::copy(std::begin(strings), std::end(strings), std::begin(cp_s));
//    std::copy(std::begin(strings), std::end(strings), std::begin(rev_s));

//    int n = sizeof(cp_s) / sizeof(cp_s[0]);
    start = std::chrono::steady_clock::now();
    std::sort(cp_s.begin(), cp_s.end());
    now = std::chrono::steady_clock::now();
    elapsed_seconds = now - start;
    std::cout << "std::sort for std::strings time: " << elapsed_seconds.count() << "'s\n";

    start = std::chrono::steady_clock::now();
    std::sort(rev_s.begin(), rev_s.end(), std::greater<>());
    now = std::chrono::steady_clock::now();
    elapsed_seconds = now - start;
    std::cout << "std::sort reversed for std::strings time: " << elapsed_seconds.count() << "'s\n";
//     for(int i=0; i < 4; ++i)
//       std::cout << strings[i] << " " << cp_s[i] << " " << rev_s[i] << "\n";


    /******************************************************/
    /*        <sort & qosrt for c-style strings>          */
    /******************************************************/
    std::cout << "\n C-style strings \n\n";
    // convert to c style
    std::vector<char*> c_style, c_cp, rev_c, c_qs, rev_c_qs; //create copies for all sorting calls
    std::transform(vs.begin(), vs.end(), std::back_inserter(c_style), convert);
    std::transform(vs.begin(), vs.end(), std::back_inserter(c_cp), convert);
    std::transform(vs.begin(), vs.end(), std::back_inserter(rev_c), convert);
    std::transform(vs.begin(), vs.end(), std::back_inserter(c_qs), convert);
    std::transform(vs.begin(), vs.end(), std::back_inserter(rev_c_qs), convert);


    // lambdas for std::sort asc and desc c-style strings
    auto cstr_compare_rev = [](const char* s1, const char* s2) {
        return (strcmp(s1,s2) > 0);
    };
    auto cstr_compare = [](const char* s1, const char* s2) {
        return strcmp(s1,s2) < 0;
    };

    start = std::chrono::steady_clock::now();
    qsort( c_qs.data(), c_qs.size(), sizeof( c_qs[0] ), cmpstr );
    now = std::chrono::steady_clock::now();
    elapsed_seconds = now - start;
    std::cout << "qsort for c-style strings time: " << elapsed_seconds.count() << "'s\n";

    start = std::chrono::steady_clock::now();
    qsort( rev_c_qs.data(), rev_c_qs.size(), sizeof( rev_c_qs[0] ), cmpstr_rev);
    now = std::chrono::steady_clock::now();
    elapsed_seconds = now - start;
    std::cout << "qsort reversed for c-style strings time: " << elapsed_seconds.count() << "'s\n";

    start = std::chrono::steady_clock::now();
    std::sort(c_cp.begin(), c_cp.end(), cstr_compare);
    now = std::chrono::steady_clock::now();
    elapsed_seconds = now - start;
    std::cout << "std::sort for c-style strings time: " << elapsed_seconds.count() << "'s\n";

    start = std::chrono::steady_clock::now();
    std::sort(rev_c.begin(), rev_c.end(), cstr_compare_rev);
    now = std::chrono::steady_clock::now();
    elapsed_seconds = now - start;
    std::cout << "std::sort reversed for c-style strings time: " << elapsed_seconds.count() << "'s\n";
//    for(int i = 0; i < 4; ++i)
//        std::cout << c_style[i] << " " << rev_c[i] << "\n";
    // delete all memory allocated in the function 'convert'
    for(int i=0; i < c_style.size(); ++i) {
        delete [] c_style[i];
        delete [] c_cp[i];
        delete [] rev_c[i];
        delete [] c_qs[i];
        delete [] rev_c_qs[i];
    }
    return 0;

}


/**************** qsort c-style strings ****************/
int cmpstr(const void *one, const void *two) {
    return (strcmp(*(char **)one, *(char **)two));
}

/************ Reverse qsort c-style strings **************/
int cmpstr_rev(const void *one, const void *two) {
    return -(strcmp(*(char **)one, *(char **)two));
}


/**************** qsort std::strings ****************/
auto compare( void const* e1, void const* e2 ) -> int
{
    std::string const* const p1 = *static_cast<std::string* const*>( e1 );
    std::string const* const p2 = *static_cast<std::string* const*>( e2 );
    return (p1->compare( *p2 ));
}

/************ Reverse qsort std::strings **************/
auto compare_rev( void const* e1, void const* e2 ) -> int
{
    std::string const* const p1 = *static_cast<std::string* const*>( e1 );
    std::string const* const p2 = *static_cast<std::string* const*>( e2 );
    return -(p1->compare( *p2 ));
}

/************ sort call qsort for std::strings **************/
void sort( std::vector<std::string> &a, int flag )
{
    std::vector<std::string const*> pointers;
    pointers.reserve( a.size() );
    for( std::string& item : a ){ pointers.push_back( &item ); }
    if (flag)
        qsort( pointers.data(), a.size(), sizeof( pointers[0] ), compare );
    else
        qsort( pointers.data(), a.size(), sizeof( pointers[0] ), compare_rev );
    std::vector<std::string> result;
    result.reserve( a.size() );
    for( std::string const* p : pointers ) { result.push_back( move( *p ) ); }
    for( int i = 0; i < int( a.size() ); ++i ) { a[i] = move( result[i] ); }
}

/******** convers std::strings to c_style strings *********/
char *convert(const std::string & s)
{
    char *pc = new char[s.size()+1];
    strcpy(pc, s.c_str());
    return pc;
}