/* tol_parser.h: Declare Parser class of GNU/TOL language.

   Copyright (C) 2003 - Bayes Decision, SL (Spain [EU])

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA.
 */

/*! \brief Declarations of Parser Class attributes and methods.<br>
 *         functionality has been implemented in bbasic/bparser/par.cpp
 */

#ifndef TOL_PARSER_H
#define TOL_PARSER_H 1

#include <tol/tol_tree.h>
#include <tol/tol_btoken.h>

class BText;
class BFilter;
class BScanner;

//--------------------------------------------------------------------
/*! BParser class used in TOL language to parsing all code.
 *  The main proccess begins in Parse and Parsing method, and continue
 *  in ParseSymbol, invoking Scanner to retrieve nextSymbol_ and
 *  nextArgument_ of source code. There's only one instance of this
 *  class in each running instance of TOL language. static attribute
 *  defaultParser_ represents that instance.
 *  BParser returns a List with analized expression. This List is used
 *  in semantic analyzer (BGrammar) to create each user defined object.
 */
class BParser {
 private:
    BText     expression_;          //!< Expression to analize
    BFilter*  filter_;	            //!< Pointer to the BFilter object
    BScanner* scan_;	              //!< Pointer to the BScanner object
    BInt      openNumber_;          //!< Number of non closed open symbols
    BBool     complete_;	          //!< Tree completation indicator
    BBool     classInheritage_;     //!< Class inheritage indicator
    BToken*   nextSymbol_ ;         //!< Symbol   found after last scanning
    BToken*   nextArgument_;        //!< Argument found after last scanning
    BText     messageError_;        //!< Store message error from parser
    List*     newSymbol_;           //!< Store name of Struct Data Type created
    BToken*   lastSymbol_;          //!< Context symbol of first level
    BToken*   lastSymbol_2_;        //!< Context symbol of second level
    BToken*   delayedSymbol_ ;      //!< Symbol delayed to be parsed after knowing the next one
    static BParser* defaultParser_; //!< only one parser
    
 public:
    BParser();
    ~BParser();
    
    Tree* Parsing (const BText& expression);
    BBool HasError();

    static Tree* parsing (const BText& expression);
    static void InitDefaultParser();
    static BParser* DefaultParser();
    static const BText& Unparsing(const Tree* tre,
				  const BText& indent="  ",
				  const BText& endLin="\n");
    static const BText& Unparse(const List* tre,
				const BText& indent="  ",
				const BText& endLin="\n");
    static BText treWrite(List* tree, BText indent, BBool last=BFALSE);
    static BToken* treToken(const List* tree);
    static BBool hasError();

    const BText& MessageError();
    BFilter* Filter() const;
    BScanner* Scanner() const;
    
 private:
    BBool ReadNextSymbol(BTokenType& symbolType); 
    BToken* NextSymbol() const;
    BToken* NextArgument() const;
    void PutNextSymbol(BToken*);
    void PutNextArgument(const BText&);

    friend BText tokWrite(const BToken*, const BText&);

    static const BText& tokOpen(const BToken* tok);
    static const BChar* tokClose(const BToken* tok);

    Tree* ParseNone(Tree*, BCloseToken*);
    Tree* ParseOpen(Tree*);
    Tree* ParseClose(Tree*, BCloseToken*);
    Tree* ParseType(Tree*);
    Tree* ParseMonary(Tree*);
    Tree* ParseBinary(Tree*);
    Tree* ParseSeparator(Tree*);
    Tree* ParseMacroEmbed (Tree* tre);
    Tree* ParseDelayed (Tree* tre);
    Tree* ParseSymbol(Tree*, BCloseToken*);
    
    BText ErrorPosition (BInt& row, BInt& col);
    bool InAComment(BText& txt, int& curIndex) const;
};

BText tokWrite(const BToken*, const BText&);

#endif // TOL_BPARSER_H
