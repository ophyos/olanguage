// Scintilla source code edit control
/** @file LexOASM.cxx
 ** Lexer for Assembler, just for the OASM syntax
 ** Written by The victor_yjg <victor_yjg@soh.com>
 **/
// Copyright 1998-2003 by Neil Hodgson <neilh@scintilla.org>
// The License.txt file describes the conditions under which this software may be distributed.

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

#include "Platform.h"

#include "PropSet.h"
#include "Accessor.h"
#include "StyleContext.h"
#include "KeyWords.h"
#include "Scintilla.h"
#include "SciLexer.h"
#include "CharacterSet.h"

#ifdef SCI_NAMESPACE
using namespace Scintilla;
#endif

static bool MatchWord(StyleContext& sc,char* pchWord,int& nSize,int nRelativePos){

	nSize = (int)strlen(pchWord);
	for(int i=0;i<nSize;++i){
		if((char)sc.GetRelative(nRelativePos+i) != pchWord[i])
			return false;
	}

	return true;
}

static bool MatchWordAtList(StyleContext& sc,WordList &keywords,int nIndex,int& nSize,int nRelativePos = 0){

	if(nIndex>=0 && nIndex<keywords.len){
		return MatchWord(sc,keywords.words[nIndex],nSize,nRelativePos);
	}

	return false;
}

static bool IsSeparatorChar(int nChar){

	switch(nChar){
		case ' ':	case '\t':
		case '\r':	case '\n':		
			return true;
	}

	return false;
}

static bool IsDigitChar(int ch){

	if(IsADigit(ch,16))
		return true;

	switch(ch){
		case '.':
		case '+':
		case '-':
		case 'e':
		case 'x':
			return true;
	}

	return false;
}

static bool MatchKeyWordInList(StyleContext& sc,WordList &keywords,int& nSize,int nRelativePos = 0){

	nSize = 0;
	int nSizeTemp = 0;
	for(int i=0;i<keywords.len;++i){
		if(MatchWord(sc,keywords.words[i],nSizeTemp,nRelativePos)){
			if(nSizeTemp > nSize){
				nSize = nSizeTemp;
			}
		}
	}

	return (nSize>0);
}

static bool IsSeparatorWord(StyleContext& sc,int nRelativePos,WordList* pKeywords = 0){

	if(IsSeparatorChar(sc.GetRelative(nRelativePos)))
		return true;

	if(pKeywords){
		int nSize;
		if(MatchKeyWordInList(sc,*pKeywords,nSize,nRelativePos))
			return true;
	}	

	return false;
}

enum OML_KEYWORDS_SYMBOL{
	OKS_COMMENT_LINE,	
	OKS_COMMENT_BLOCK_BEGIN,
	OKS_COMMENT_BLOCK_END,	
};

static void ColouriseOMLDoc(unsigned int startPos, int length, int initStyle, WordList *keywordlists[],
Accessor &styler){	

	WordList &keywords_comment_symbol      = *keywordlists[0];
	WordList &keywords_keyword             = *keywordlists[1];
	WordList &keywords_operator            = *keywordlists[2];
	WordList &keywords_macro_txt           = *keywordlists[3];
				
	
	/*bool stylingWithinPreprocessor = styler.GetPropertyInt("styling.within.preprocessor") != 0;

	CharacterSet setWordStart(CharacterSet::setAlpha, "_", 0x80, true);
	CharacterSet setWord(CharacterSet::setAlphaNum, "._", 0x80, true);
	if (styler.GetPropertyInt("lexer.cpp.allow.dollars", 1) != 0) {
		setWordStart.Add('$');
		setWord.Add('$');
	}

	int visibleChars = 0;
	bool lastWordWasUUID = false;	
	bool continuationLine = false;*/

	//if (initStyle == SCE_OML_PREPROCESSOR) {
	//	// Set continuationLine if last character of previous line is '\'
	//	int lineCurrent = styler.GetLine(startPos);
	//	if (lineCurrent > 0) {
	//		int chBack = styler.SafeGetCharAt(startPos-1, 0);
	//		int chBack2 = styler.SafeGetCharAt(startPos-2, 0);
	//		int lineEndChar = '!';
	//		if (chBack2 == '\r' && chBack == '\n') {
	//			lineEndChar = styler.SafeGetCharAt(startPos-3, 0);
	//		} else if (chBack == '\n' || chBack == '\r') {
	//			lineEndChar = chBack2;
	//		}
	//		continuationLine = lineEndChar == '\\';
	//	}
	//}

	StyleContext sc(startPos, length, initStyle, styler);

	int nWordSize;
	bool bIsElementEnd = false;

	for (; sc.More(); sc.Forward()) {		

		if (sc.atLineStart) {
			//if (sc.state == SCE_OML_STRING) {
			//	// Prevent SCE_OML_STRINGEOL from leaking back to previous line which
			//	// ends with a line continuation by locking in the state upto this position.
			//	sc.SetState(SCE_OML_STRING);
			//}
			//// Reset states to begining of colourise so no surprises
			//// if different sets of lines lexed.
			//visibleChars = 0;
			//lastWordWasUUID = false;	

			bIsElementEnd = true;
		}		
		
		//// Handle line continuation generically.
		//if (sc.ch == '\\') {
		//	if (sc.chNext == '\n' || sc.chNext == '\r') {
		//		sc.Forward();
		//		if (sc.ch == '\r' && sc.chNext == '\n') {
		//			sc.Forward();
		//		}
		//		continuationLine = true;
		//		continue;
		//	}
		//}

		// Determine if the current state should terminate.
		switch (sc.state) {			
			case SCE_OML_NUMBER:
				// We accept almost anything because of hex. and number suffixes
				if (!IsDigitChar(sc.ch)) {
					sc.SetState(SCE_OML_DEFAULT);
				}
				break;			
			case SCE_OML_COMMENT:
				if( MatchWordAtList(sc,keywords_comment_symbol,OKS_COMMENT_BLOCK_END,nWordSize)){  // */
					sc.Forward(nWordSize-1);
					sc.ForwardSetState(SCE_OML_DEFAULT);
					bIsElementEnd = true;				
				}
				break;			
			case SCE_OML_COMMENTLINE:
				if (sc.atLineStart) {
					sc.SetState(SCE_OML_DEFAULT);
				}
				break;			
			case SCE_OML_STRING:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_OML_STRINGEOL);
				} else if (sc.ch == '\\') {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
						sc.Forward();
					}
				} else if (sc.ch == '\"') {
					sc.ForwardSetState(SCE_OML_DEFAULT);
					bIsElementEnd = true;
				}
				break;
			case SCE_OML_CHARACTER:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_OML_STRINGEOL);
				} else if (sc.ch == '\\') {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
						sc.Forward();
					}
				} else if (sc.ch == '\'') {
					sc.ForwardSetState(SCE_OML_DEFAULT);
					bIsElementEnd = true;
				}
				break;			
			case SCE_OML_STRINGEOL:
				if (sc.atLineStart) {
					sc.SetState(SCE_OML_DEFAULT);
				}
				break;
			}
			
			// Determine if a new state should be entered.
			if (sc.state == SCE_OML_DEFAULT) {
				
				//Platform::DebugPrintf("%X %X %X",pchCommentLine[0],pchCommentLine[1],pchCommentLine[2]);

				bool bWhile = false;
				do 
				{
					bWhile = false;

					if(MatchWordAtList(sc,keywords_comment_symbol,OKS_COMMENT_LINE,nWordSize)) { //  //
						sc.SetState(SCE_OML_COMMENTLINE);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_comment_symbol,OKS_COMMENT_BLOCK_BEGIN,nWordSize)) { // /*
						sc.SetState(SCE_OML_COMMENT);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if (sc.ch == '\"') { //string
						sc.SetState(SCE_OML_STRING);
						bIsElementEnd = false;
					} else if (sc.ch == '\'') { //char
						sc.SetState(SCE_OML_CHARACTER);
						bIsElementEnd = false;
					}else if (bIsElementEnd && (IsADigit(sc.ch) || (sc.ch == '.' && IsADigit(sc.chNext)))) {//digit
						sc.SetState(SCE_OML_NUMBER);
						bIsElementEnd = false;
					}

					else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_keyword,nWordSize)){ //define word
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OML_KEYWORD);
							sc.Forward(nWordSize);
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}					
						sc.SetState(SCE_OML_DEFAULT);
					}else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_macro_txt,nWordSize)){ //macro
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OML_MACRO_TXT);
							sc.Forward(nWordSize);
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}					
						sc.SetState(SCE_OML_DEFAULT);
					}else if(MatchKeyWordInList(sc,keywords_operator,nWordSize)){ //Operator
						sc.SetState(SCE_OML_SYMBOL_OPERATOR);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OML_DEFAULT);
					}
					else{
						bIsElementEnd = false;
					}					

				} while (bWhile);				
				
				//else if (setWordStart.Contains(sc.ch) || (sc.ch == '@')) {
				//	if (lastWordWasUUID) {
				//		sc.SetState(SCE_OML_UUID);
				//		lastWordWasUUID = false;
				//	} else {
				//		sc.SetState(SCE_OML_IDENTIFIER);
				//	}
				//} else if (sc.ch == '\"') {
				//	sc.SetState(SCE_OML_STRING);
				//} else if (sc.ch == '\'') {
				//	sc.SetState(SCE_OML_CHARACTER);
				//} else if (sc.ch == '#' && visibleChars == 0) {
				//	// Preprocessor commands are alone on their line
				//	sc.SetState(SCE_OML_PREPROCESSOR);
				//	// Skip whitespace between # and preprocessor word
				//	do {
				//		sc.Forward();
				//	} while ((sc.ch == ' ' || sc.ch == '\t') && sc.More());
				//	if (sc.atLineEnd) {
				//		sc.SetState(SCE_OML_DEFAULT);
				//	}
				//} else if (isoperator(static_cast<char>(sc.ch))) {
				//	sc.SetState(SCE_OML_OPERATOR);
				//}
			}			

			/*if (!IsASpace(sc.ch) ) {
				visibleChars++;
			}
			continuationLine = false;*/

			if(!bIsElementEnd && IsSeparatorChar(sc.ch))
			{
				bIsElementEnd = true;
			}
		}
		sc.Complete();
}

static bool IsStreamCommentStyle(int style) {
	return style == SCE_OML_COMMENT;
}

// Store both the current line's fold level and the next lines in the
// level store to make it easy to pick up with each increment
// and to make it possible to fiddle the current level for "} else {".
static void FoldOMLDoc(unsigned int startPos, int length, int initStyle,
   WordList *[], Accessor &styler) {

   bool foldComment = styler.GetPropertyInt("fold.comment") != 0;
   bool foldPreprocessor = styler.GetPropertyInt("fold.preprocessor") != 0;
   bool foldCompact = styler.GetPropertyInt("fold.compact", 1) != 0;
   bool foldAtElse = styler.GetPropertyInt("fold.at.else", 0) != 0;
   unsigned int endPos = startPos + length;
   int visibleChars = 0;
   int lineCurrent = styler.GetLine(startPos);
   int levelCurrent = SC_FOLDLEVELBASE;
   if (lineCurrent > 0)
	   levelCurrent = styler.LevelAt(lineCurrent-1) >> 16;
   int levelMinCurrent = levelCurrent;
   int levelNext = levelCurrent;
   char chNext = styler[startPos];
   int styleNext = styler.StyleAt(startPos);
   int style = initStyle;
   for (unsigned int i = startPos; i < endPos; i++) {
	   char ch = chNext;
	   chNext = styler.SafeGetCharAt(i + 1);		   
	   style = styleNext;
	   styleNext = styler.StyleAt(i + 1);
	   bool atEOL = (ch == '\r' && chNext != '\n') || (ch == '\n');
	   if (foldComment && IsStreamCommentStyle(style)) {
		   
	   }		   	   

	  /* if (foldPreprocessor && (style == SCE_OML_PREPROCESSOR)) {
		   if (ch == '#') {
			   unsigned int j = i + 1;
			   while ((j < endPos) && IsASpaceOrTab(styler.SafeGetCharAt(j))) {
				   j++;
			   }
			   if (styler.Match(j, "region") || styler.Match(j, "if")) {
				   levelNext++;
			   } else if (styler.Match(j, "end")) {
				   levelNext--;
			   }
		   }
	   }*/
	   if (style == SCE_OML_SYMBOL_OPERATOR) {
		   if (ch == '{') {
			   // Measure the minimum before a '{' to allow
			   // folding on "} else {"
			   if (levelMinCurrent > levelNext) {
				   levelMinCurrent = levelNext;
			   }
			   levelNext++;
		   } else if (ch == '}') {
			   levelNext--;
		   }
	   }
	   if (!IsASpace(ch))
		   visibleChars++;
	   if (atEOL || (i == endPos-1)) {
		   int levelUse = levelCurrent;
		   if (foldAtElse) {
			   levelUse = levelMinCurrent;
		   }
		   int lev = levelUse | levelNext << 16;
		   if (visibleChars == 0 && foldCompact)
			   lev |= SC_FOLDLEVELWHITEFLAG;
		   if (levelUse < levelNext)
			   lev |= SC_FOLDLEVELHEADERFLAG;
		   if (lev != styler.LevelAt(lineCurrent)) {
			   styler.SetLevel(lineCurrent, lev);
		   }
		   lineCurrent++;
		   levelCurrent = levelNext;
		   levelMinCurrent = levelCurrent;
		   visibleChars = 0;
	   }
   }
}

static const char * const oasmWordListDesc[] = {	
	"CommentSymbol"
	"Keyword",
	"Operator",
	"MacroTxt",
	0
};

LexerModule lmOML(SCLEX_OML, ColouriseOMLDoc, "omp", FoldOMLDoc, oasmWordListDesc);

