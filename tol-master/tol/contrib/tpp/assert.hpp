
namespace tpp {

/*! \file assert.hpp
        \brief Implements a better 'Assert'
 */

#ifndef REVIVER_ASSERT_HPP
#define REVIVER_ASSERT_HPP


/*! \def MyAssertFunction
    \brief Function used by 'Assert' function in _DEBUG mode.
   
    Details.
*/
bool MyAssertFunction( bool b, const char* desc, int line, const char* file);

#if defined( _DEBUG )
#define Assert( exp, description ) tpp::MyAssertFunction( (bool)(exp), description, __LINE__, __FILE__ )
#else
#define Assert( exp, description )
#endif


#endif

}
