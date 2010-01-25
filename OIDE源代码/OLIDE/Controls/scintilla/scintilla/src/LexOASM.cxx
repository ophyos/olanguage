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

#include "OASM.h"

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

enum OASM_KEYWORDS_SYMBOL{
	OKS_COMMENT_LINE,
	OKS_COMMENT_LINE2,
	OKS_COMMENT_BLOCK_BEGIN,
	OKS_COMMENT_BLOCK_END,
	OKS_COMMENT_BLOCK_BEGIN2,
	OKS_COMMENT_BLOCK_END2,
	OKS_INCLUDE_TEXT_BEGIN,
	OKS_INCLUDE_TEXT_END,
	OKS_INCLUDE_LIB_BEGIN,
	OKS_INCLUDE_LIB_END,
	OKS_INCLUDE_BIN_BEGIN,
	OKS_INCLUDE_BIN_END,
	OKS_WCHAR_BEGIN,
	OKS_WCHAR_END,
	OKS_WSTRING_BEGIN,
	OKS_WSTRING_END,
	OKS_SEGMENT_BEGIN,
	OKS_SEGMENT_END,
	OKS_SEGMENT_DATA_BEGIN,
	OKS_SEGMENT_DATA_END,
	OKS_SEGMENT_RDATA_BEGIN,
	OKS_SEGMENT_RDATA_END,
	OKS_SEGMENT_BSS_BEGIN,
	OKS_SEGMENT_BSS_END,
	OKS_SEGMENT_EXTRA_BEGIN,
	OKS_SEGMENT_EXTRA_END,
	OKS_SEGMENT_STACK_BEGIN,
	OKS_SEGMENT_STACK_END,
	OKS_SEGMENT_EXTERN_BEGIN,
	OKS_SEGMENT_EXTERN_END,
	OKS_SEGMENT_CODE_BEGIN,
	OKS_SEGMENT_CODE_END,
};

static void ColouriseOASMDoc(unsigned int startPos, int length, int initStyle, WordList *keywordlists[],
Accessor &styler) {

	WordList &keywords_symbol       = *keywordlists[0];
	WordList &keywords_cpu_insns    = *keywordlists[1];
	WordList &keywords_fpu_insns    = *keywordlists[2];
	WordList &keywords_register     = *keywordlists[3];	
	WordList &keywords_define_word  = *keywordlists[4];
	WordList &keywords_macro        = *keywordlists[5];	
	WordList &keywords_operator_txt = *keywordlists[6];
	WordList &keywords_operator     = *keywordlists[7];
	
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

	//if (initStyle == SCE_OASM_PREPROCESSOR) {
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
			//if (sc.state == SCE_OASM_STRING) {
			//	// Prevent SCE_OASM_STRINGEOL from leaking back to previous line which
			//	// ends with a line continuation by locking in the state upto this position.
			//	sc.SetState(SCE_OASM_STRING);
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
			case SCE_OASM_NUMBER:
				// We accept almost anything because of hex. and number suffixes
				if (!IsDigitChar(sc.ch)) {
					sc.SetState(SCE_OASM_DEFAULT);
				}
				break;			
			case SCE_OASM_COMMENT:
				if( MatchWordAtList(sc,keywords_symbol,OKS_COMMENT_BLOCK_END,nWordSize) ||  // ¡¹
					MatchWordAtList(sc,keywords_symbol,OKS_COMMENT_BLOCK_END2,nWordSize)){  // */
					sc.Forward(nWordSize-1);
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;				
				}
				break;			
			case SCE_OASM_COMMENTLINE:
				if (sc.atLineStart) {
					sc.SetState(SCE_OASM_DEFAULT);
				}
				break;		
			case SCE_OASM_INCLUDE_TEXT:
				if(MatchWordAtList(sc,keywords_symbol,OKS_INCLUDE_TEXT_END,nWordSize)){ //¡·
					sc.Forward(nWordSize-1);
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;
				}
				break;
			case SCE_OASM_INCLUDE_LIB:
				if(MatchWordAtList(sc,keywords_symbol,OKS_INCLUDE_LIB_END,nWordSize)){ //¡µ
					sc.Forward(nWordSize-1);
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;
				}
				break;
			case SCE_OASM_INCLUDE_BIN:
				if(MatchWordAtList(sc,keywords_symbol,OKS_INCLUDE_BIN_END,nWordSize)){ //¡¿
					sc.Forward(nWordSize-1);
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;
				}
				break;
			case SCE_OASM_WCHARACTER:
				if(MatchWordAtList(sc,keywords_symbol,OKS_WCHAR_END,nWordSize)){ //¡¯
					sc.Forward(nWordSize-1);
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;
				}
				break;
			case SCE_OASM_WSTRING:
				if(MatchWordAtList(sc,keywords_symbol,OKS_WSTRING_END,nWordSize)){ //¡±
					sc.Forward(nWordSize-1);
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;
				}
				break;
			case SCE_OASM_STRING:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_OASM_STRINGEOL);
				} else if (sc.ch == '\\') {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
						sc.Forward();
					}
				} else if (sc.ch == '\"') {
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;
				}
				break;
			case SCE_OASM_CHARACTER:
				if (sc.atLineEnd) {
					sc.ChangeState(SCE_OASM_STRINGEOL);
				} else if (sc.ch == '\\') {
					if (sc.chNext == '\"' || sc.chNext == '\'' || sc.chNext == '\\') {
						sc.Forward();
					}
				} else if (sc.ch == '\'') {
					sc.ForwardSetState(SCE_OASM_DEFAULT);
					bIsElementEnd = true;
				}
				break;			
			case SCE_OASM_STRINGEOL:
				if (sc.atLineStart) {
					sc.SetState(SCE_OASM_DEFAULT);
				}
				break;
			}
			
			// Determine if a new state should be entered.
			if (sc.state == SCE_OASM_DEFAULT) {
				
				//Platform::DebugPrintf("%X %X %X",pchCommentLine[0],pchCommentLine[1],pchCommentLine[2]);

				bool bWhile = false;
				do 
				{
					bWhile = false;

					if(MatchWordAtList(sc,keywords_symbol,OKS_COMMENT_LINE,nWordSize)) { //¡Î
						sc.SetState(SCE_OASM_COMMENTLINE);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_COMMENT_LINE2,nWordSize)) { //  //
						sc.SetState(SCE_OASM_COMMENTLINE);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_COMMENT_BLOCK_BEGIN,nWordSize)) { //¡¸
						sc.SetState(SCE_OASM_COMMENT);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_COMMENT_BLOCK_BEGIN2,nWordSize)) { // /*
						sc.SetState(SCE_OASM_COMMENT);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_INCLUDE_TEXT_BEGIN,nWordSize)){ //¡¶
						sc.SetState(SCE_OASM_INCLUDE_TEXT);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_INCLUDE_LIB_BEGIN,nWordSize)){ //¡´
						sc.SetState(SCE_OASM_INCLUDE_LIB);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_INCLUDE_BIN_BEGIN,nWordSize)){ //¡¾
						sc.SetState(SCE_OASM_INCLUDE_BIN);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_WCHAR_BEGIN,nWordSize)){ //¡®
						sc.SetState(SCE_OASM_WCHARACTER);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_WSTRING_BEGIN,nWordSize)){ //¡°
						sc.SetState(SCE_OASM_WSTRING);
						sc.Forward(nWordSize-1);
						bIsElementEnd = false;
					}else if (sc.ch == '\"') { //string
						sc.SetState(SCE_OASM_STRING);
						bIsElementEnd = false;
					} else if (sc.ch == '\'') { //char
						sc.SetState(SCE_OASM_CHARACTER);
						bIsElementEnd = false;
					}else if (bIsElementEnd && (IsADigit(sc.ch) || (sc.ch == '.' && IsADigit(sc.chNext)))) {//digit
						sc.SetState(SCE_OASM_NUMBER);
						bIsElementEnd = false;
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_BEGIN,nWordSize) ||
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_END,nWordSize)){ //¦à ¦á
						sc.SetState(SCE_OASM_SEGMENT_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_DATA_BEGIN,nWordSize) || 
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_DATA_END,nWordSize)){ //¦î ¦ï
						sc.SetState(SCE_OASM_SEGMENT_DATA_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_RDATA_BEGIN,nWordSize) || 
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_RDATA_END,nWordSize)){ //¦ê ¦ë
						sc.SetState(SCE_OASM_SEGMENT_RDATA_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_BSS_BEGIN,nWordSize) ||
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_BSS_END,nWordSize)){ //¦è ¦é
						sc.SetState(SCE_OASM_SEGMENT_BSS_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_EXTRA_BEGIN,nWordSize) || 
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_EXTRA_END,nWordSize)){ //¦â ¦ã
						sc.SetState(SCE_OASM_SEGMENT_EXTRA_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_STACK_BEGIN,nWordSize) ||
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_STACK_END,nWordSize)){ //¦ä ¦å
						sc.SetState(SCE_OASM_SEGMENT_STACK_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_EXTERN_BEGIN,nWordSize) || 
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_EXTERN_END,nWordSize)){ //¦æ ¦ç
						sc.SetState(SCE_OASM_SEGMENT_EXTERN_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_CODE_BEGIN,nWordSize) ||
						     MatchWordAtList(sc,keywords_symbol,OKS_SEGMENT_CODE_END,nWordSize)){ //¦ð ¦ñ
						sc.SetState(SCE_OASM_SEGMENT_CODE_FLAG);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}

					else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_cpu_insns,nWordSize)){ //CPU instructions
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OASM_CPU_INSTRUCTIONS);
							sc.Forward(nWordSize);
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_fpu_insns,nWordSize)){ //FPU instructions
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OASM_FPU_INSTRUCTIONS);
							sc.Forward(nWordSize);	
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}					
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_register,nWordSize)){ //Register
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OASM_REGISTER);
							sc.Forward(nWordSize);
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}					
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_define_word,nWordSize)){ //define word
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OASM_DEFINE_WORD);
							sc.Forward(nWordSize);
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}					
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_macro,nWordSize)){ //macro
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OASM_MACRO);
							sc.Forward(nWordSize);
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}					
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(bIsElementEnd && MatchKeyWordInList(sc,keywords_operator_txt,nWordSize)){ //Operator text
						if(IsSeparatorWord(sc,nWordSize,&keywords_operator)){
							sc.SetState(SCE_OASM_OPERATOR_TXT);
							sc.Forward(nWordSize);
							bWhile = true;
							bIsElementEnd = true;
						}else{
							bIsElementEnd = false;
						}					
						sc.SetState(SCE_OASM_DEFAULT);
					}else if(MatchKeyWordInList(sc,keywords_operator,nWordSize)){ //Operator
						sc.SetState(SCE_OASM_OPERATOR);
						sc.Forward(nWordSize);
						bWhile = true;
						bIsElementEnd = true;
						sc.SetState(SCE_OASM_DEFAULT);
					}
					else{
						bIsElementEnd = false;
					}					

				} while (bWhile);				
				
				//else if (setWordStart.Contains(sc.ch) || (sc.ch == '@')) {
				//	if (lastWordWasUUID) {
				//		sc.SetState(SCE_OASM_UUID);
				//		lastWordWasUUID = false;
				//	} else {
				//		sc.SetState(SCE_OASM_IDENTIFIER);
				//	}
				//} else if (sc.ch == '\"') {
				//	sc.SetState(SCE_OASM_STRING);
				//} else if (sc.ch == '\'') {
				//	sc.SetState(SCE_OASM_CHARACTER);
				//} else if (sc.ch == '#' && visibleChars == 0) {
				//	// Preprocessor commands are alone on their line
				//	sc.SetState(SCE_OASM_PREPROCESSOR);
				//	// Skip whitespace between # and preprocessor word
				//	do {
				//		sc.Forward();
				//	} while ((sc.ch == ' ' || sc.ch == '\t') && sc.More());
				//	if (sc.atLineEnd) {
				//		sc.SetState(SCE_OASM_DEFAULT);
				//	}
				//} else if (isoperator(static_cast<char>(sc.ch))) {
				//	sc.SetState(SCE_OASM_OPERATOR);
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
	return style == SCE_OASM_COMMENT;
}

// Store both the current line's fold level and the next lines in the
// level store to make it easy to pick up with each increment
// and to make it possible to fiddle the current level for "} else {".
static void FoldOASMDoc(unsigned int startPos, int length, int initStyle,
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

	  /* if (foldPreprocessor && (style == SCE_OASM_PREPROCESSOR)) {
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
	   if (style == SCE_OASM_OPERATOR) {
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
	"Symbol",
	"CPU instructions",
	"FPU instructions",
	"Registers",
	"Operator",
	"Directive operands",
	"Extended instructions",
	0
};

LexerModule lmOASM(SCLEX_OASM, ColouriseOASMDoc, "osm", FoldOASMDoc, oasmWordListDesc);

