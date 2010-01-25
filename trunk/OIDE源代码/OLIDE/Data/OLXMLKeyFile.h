
//定义O语言XML文件中所使用到的结点健名称

#ifndef _OL_XML_KEYFILE_H_
#define _OL_XML_KEYFILE_H_


//O语言文件类型
enum OLANGUAGE_FILE_TYPE
{
	OFT_UNKNOW,
	OFT_SOLUTION,
	OFT_PROJECT,
	OFT_SYSTEM_OPTION,        //系统选项
	OFT_BUILD_PROJECT_RECORD  //编译工程记录
};

static const char*  OLXMLKey_OLanguageHead                    = "<?xml version=\"1.0\" encoding=\"GB2312\"?>";
static const char*  OLXMLKey_OLanguageFile                    = "O语言文件";
static const char*  OLXMLKey_FileType                         = "TYPE";

//方案与工程
static const char*  OLXMLKey_SolutionName                     = "方案名称";
static const char*  OLXMLKey_ProjectFile                      = "工程文件";
static const char*  OLXMLKey_Project                          = "工程";
static const char*  OLXMLKey_ProjectName                      = "工程名称";
static const char*  OLXMLKey_ProjectPath                      = "工程路径";
static const char*  OLXMLKey_ProjectTreeNodeExpandState       = "工程树结点展开状态";
static const char*  OLXMLKey_ProjectIncludeFile               = "工程包含文件";
static const char*  OLXMLKey_ProjectChildFile                 = "工程子文件";
static const char*  OLXMLKey_ProjectChildFileType             = "工程子文件类型";
static const char*  OLXMLKey_ProjectChildFilePath             = "工程子文件路径";
static const char*  OLXMLKey_ProjectProperty                  = "工程属性";
static const char*  OLXMLKey_ProjectPropertyLinker            = "链接器";
static const char*  OLXMLKey_ProjectPropertyCodeDir           = "代码目录";
static const char*  OLXMLKey_ProjectPropertyResourceDir       = "资源目录";
static const char*  OLXMLKey_ProjectPropertyProgramType       = "程序类型";
static const char*  OLXMLKey_ProjectPropertySubSystem         = "子系统";
static const char*  OLXMLKey_ProjectPropertyOutPutPath        = "输出目录";
static const char*  OLXMLKey_ProjectPropertyDebugMiddleOutPutPath    = "调试中间文件输出目录";
static const char*  OLXMLKey_ProjectPropertyDebugOutPutFileName      = "调试执行文件路径";
static const char*  OLXMLKey_ProjectPropertyReleaseMiddleOutPutPath  = "纯净中间文件输出目录";
static const char*  OLXMLKey_ProjectPropertyReleaseOutPutFileName    = "纯净执行文件路径";
static const char*  OLXMLKey_ProjectPropertyBuildRecord            = "生成记录";
static const char*  OLXMLKey_ProjectPropertyBuildRecordItem        = "生成记录项";
static const char*  OLXMLKey_ProjectPropertyBuildFileName          = "生成文件名";
static const char*  OLXMLKey_ProjectPropertyBuildFileTime          = "生成文件时间";
static const char*  OLXMLKey_ProjectPropertyBuildObjFileTime       = "生成目标文件时间";
static const char*  OLXMLKey_TreeNodeExpandState              = "树结点展开状态";

//系统选项
static const char*  OLXMLKey_SystemOption                     = "系统选项";
static const char*  OLXMLKey_SystemOptionCommon               = "常规项";
static const char*  OLXMLKey_SystemOptionUpdate               = "升级";
static const char*  OLXMLKey_SystemOptionUpdateEveryTime      = "每次启动升级";
static const char*  OLXMLKey_SystemOptionAssembler            = "汇编器";
static const char*  OLXMLKey_SystemOptionAssemblerPath        = "汇编器路径";
static const char*  OLXMLKey_SystemOptionLanguagePath         = "语言路径";
static const char*  OLXMLKey_SystemOptionLinker               = "链接器";
static const char*  OLXMLKey_SystemOptionLinkerPath           = "链接器路径";
static const char*  OLXMLKey_SystemOptionOASMEditor               = "OASM编辑器";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxWordFileName = "OASM语法字文件名";
static const char*  OLXMLKey_SystemOptionOASMEditorSelectionListFileName = "OASM选择列表框文件名";
static const char*  OLXMLKey_SystemOptionOASMEditorTemplateDir = "OASM模板目录";
static const char*  OLXMLKey_SystemOptionOASMEditorAutoCompleteFileName = "OASM自动完成配置文件名";
static const char*  OLXMLKey_SystemOptionOASMEditorTipFileName    = "OASM提示配置文件名";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColor    = "OASM语法着色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorBackGround = "OASM背景颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorText = "OASM文本颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorCommentLine = "OASM注释行颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorCommentBlock = "OASM注释块颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorIncludeText = "OASM引用文颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorIncludeLib = "OASM引用库颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorSegmentData = "OASM数据段标记颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorSegmentRData = "OASM只读段标记颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorSegmentBSS = "OASM预留段标记颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorSegmentExtern = "OASM外部段标记颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorSegmentCode = "OASM代码段标记颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorDigital = "OASM数字颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorInstruction = "OASM指令颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorFInstruction = "OASM浮点指令颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorRegister = "OASM寄存器颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorChar = "OASM单字符颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorString = "OASM字符串颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorDefineWord = "OASM定义定颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorMacro = "OASM宏标识符颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorOperatorTxt = "OASM文本操作符颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorSyntaxColorOperator = "OASM操作符颜色";
static const char*  OLXMLKey_SystemOptionOASMEditorTextFont        = "OASM文本字体";
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfHeight = "OASMlfHeight"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfWidth = "OASMlfWidth" ;
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfEscapement = "OASMlfEscapement"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfOrientation = "OASMlfOrientation"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfWeight = "OASMlfWeight"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfItalic = "OASMItalic"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfUnderline = "OASMlfUnderline"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfStrikeOut = "OASMlfStrikeOut"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfCharSet = "OASMlfCharSet"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfOutPrecision = "OASMlfOutPrecision"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfClipPrecision = "OASMlfClipPrecision"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfQuality = "OASMlfQuality"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfPitchAndFamily = "OASMlfPitchAndFamily"; 
static const char*  OLXMLKey_SystemOptionOASMEditorTextFontlfFaceName = "OASMlfFaceName"; 
static const char*  OLXMLKey_SystemOptionOASMEditorExtraColumn        = "OASM附加栏";
static const char*  OLXMLKey_SystemOptionOASMEditorExtraColumnLineNumber  = "OASM行号";
static const char*  OLXMLKey_SystemOptionOASMEditorExtraColumnBookMarker  = "OASM书签";
static const char*  OLXMLKey_SystemOptionOASMEditorExtraColumnFold  = "OASM折叠";
static const char*  OLXMLKey_SystemOptionOASMSave  = "OASM保存";
static const char*  OLXMLKey_SystemOptionOASMAutoSave  = "OASM自动保存";

static const char*  OLXMLKey_SystemOptionOMLEditor               = "OML编辑器";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxWordFileName = "OML语法字文件名";
static const char*  OLXMLKey_SystemOptionOMLEditorSelectionListFileName = "OML选择列表框文件名";
static const char*  OLXMLKey_SystemOptionOMLEditorTemplateDir = "OML模板目录";
static const char*  OLXMLKey_SystemOptionOMLEditorAutoCompleteFileName = "OML自动完成配置文件名";
static const char*  OLXMLKey_SystemOptionOMLEditorTipFileName    = "OML提示配置文件名";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColor    = "OML语法着色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorBackGround = "OML背景颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorText = "OML文本颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorCommentLine = "OML注释行颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorCommentBlock = "OML注释块颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorDigital = "OML数字颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorChar = "OML单字符颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorString = "OML字符串颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorKeyWord = "OML关键字颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorMacro = "OML宏标识符颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorSyntaxColorOperator = "OML操作符颜色";
static const char*  OLXMLKey_SystemOptionOMLEditorTextFont        = "OML文本字体";
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfHeight = "OMLlfHeight"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfWidth = "OMLlfWidth" ;
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfEscapement = "OMLlfEscapement"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfOrientation = "OMLlfOrientation"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfWeight = "OMLlfWeight"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfItalic = "OMLItalic"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfUnderline = "OMLlfUnderline"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfStrikeOut = "OMLlfStrikeOut"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfCharSet = "OMLlfCharSet"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfOutPrecision = "OMLlfOutPrecision"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfClipPrecision = "OMLlfClipPrecision"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfQuality = "OMLlfQuality"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfPitchAndFamily = "OMLlfPitchAndFamily"; 
static const char*  OLXMLKey_SystemOptionOMLEditorTextFontlfFaceName = "OMLlfFaceName"; 
static const char*  OLXMLKey_SystemOptionOMLEditorExtraColumn        = "OML附加栏";
static const char*  OLXMLKey_SystemOptionOMLEditorExtraColumnLineNumber  = "OML行号";
static const char*  OLXMLKey_SystemOptionOMLEditorExtraColumnBookMarker  = "OML书签";
static const char*  OLXMLKey_SystemOptionOMLEditorExtraColumnFold  = "OML折叠";
static const char*  OLXMLKey_SystemOptionOMLSave  = "OML保存";
static const char*  OLXMLKey_SystemOptionOMLAutoSave  = "OML自动保存";

static const char*  OLXMLKey_SystemOptionDisassembler            = "反汇编";
static const char*  OLXMLKey_SystemOptionDiaassemblerPath        = "反汇编器路径";
static const char*  OLXMLKey_SystemOptionDosmLanguagePath        = "反汇编语言路径";

//中间语言
static const char*  OLXMLKey_SystemOptionOMLCompiler             = "中间语言编译器";
static const char*  OLXMLKey_SystemOptionOMLCompilerPath         = "中间语言编译器路径";
static const char*  OLXMLKey_SystemOptionOMLLanguagePath         = "中间语言内码文件路径";


#endif //_OL_XML_KEYFILE_H_