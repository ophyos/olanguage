
#ifndef _SYNTAX_WORD_LIST_H_
#define _SYNTAX_WORD_LIST_H_

////下面的符号字符串是按顺序的，请不要变更字符位置
//static const TCHAR g_oasmWordListSymbol[] = 
//{
//	_T("∥ 「  」 ")                             //注释
//	_T("《 》 〈 〉 【 】 ")                     //包含 引用
//	_T("‘  ’ “ ”  ")                         //宽字符(串)
//	_T("︵ ︶ ︻ ︼ ﹃ ﹄ ﹁ ﹂ ︹ ︺ ︿ ﹀  ︽ ︾ ︷ ︸ ")   //段
//};
//
////CPU指令
//static const TCHAR g_oasmWordListCPUInsns[] = 
//{
//	_T("加后A调整 除后A调整 乘后A调整 减后A调整 ")
//	_T("调整优先级到 检查数组边界 位左扫描到 位右扫描到 ")
//	_T("字节交换 位测试 位测试求反 位测试清0 位测试置1 ")    
//	_T("缓存队列刷出 得到CPU标识 加后十调整 减后十调整 建立堆栈帧 ")
//	_T("无效内在缓存 TLB入口无效 装入访问权限 连接加载操作 ")
//	_T("循环 相等循环 为零循环 不等循环 非零循环 ")
//	_T("加载段界限 连接加载保存操作 监视 非暂时提示移动到 监视等待 ")
//	_T("预读NTA 预读NT0 预读NT1 预读NT2 ")
//	_T("读专用模式寄存器 读执行监视计数 ")
//	_T("读时间戳计数 读时间戳计数和CPU标识 ")
//	_T("恢复系统模式 串扫描 持续保存操作 交换全段 ")
//	_T("测试 异常CPU ")
//	_T("验证读 验证写 回写并无效内在缓存 写专用模式寄存器 定位表 ")	
//};
//
////FPU指令
//static const TCHAR g_oasmWordListFPUInsns[] = 
//{
//	_T("清空浮点寄存器标志 浮点检查清除异常 浮点不检查清除异常 ")
//	_T("比较加载标志 比较加载标志出栈 反比加载标志  反比加载标志出栈 ")
//	_T("浮点释放 浮点检查初始化 浮点不检查初始化 浮点加载控制器 ")
//	_T("浮点加载环境 浮点恢复状态 浮点检查保存状态 浮点不检查保存状态 ")
//	_T("浮点检查保存控制器 浮点不检查保存控制器 浮点检查保存环境 ")
//	_T("浮点不检查保存环境 浮点检查保存状态器 浮点不检查保存状态器 ")
//	_T("浮点检查 浮点X恢复 浮点X保存 浮点分解 ")
//};
//
////寄存器
//static const TCHAR g_oasmWordListRegister[] = 
//{
//	_T("累加低  累加高  累加16  累加32 ")
//	_T("基数低  基数高  基数16  基数32 ")
//	_T("计数低  计数高  计数16  计数32 ")
//	_T("数据低  数据高  数据16  数据32 ")
//	_T("基址16  基址32  栈址16  栈址32 ")
//	_T("源址16  源址32  的址16  的址32 ")
//	_T("附段  码段  栈段  数段  志段 全段 ")
//	_T("任0 任1 任2 任3 任4 任5 任6 任7 ")
//	_T("浮0 浮1 浮2 浮3 浮4 浮5 浮6 浮7 ")
//	_T("调0 调1 调2 调3 调4 调5 调6 调7 ")
//	_T("媒0 媒1 媒2 媒3 媒4 媒5 媒6 媒7 ")
//	_T("流0 流1 流2 流3 流4 流5 流6 流7 ")
//	_T("控0 控2 控3 控4 ")
//};
//
////操作符
//static const TCHAR g_oasmWordListOperator[] = 
//{
//	_T("+ - × ÷ ± =  !  ? & | ^ %  ~  ")
//	_T("[ ] < > { } ( ) ")
//	_T("＾ Ω  ω ∞ ∽ ≌ Φ φ ↘ ↖ ↑ ↓ → ← ↙ ↗ ≮ ≯ § ∠ ▽ △ ")
//	_T("∨ ∧ ≥ ≤ ♂ ♀ ◎ ≈ √ ∫ ∮ ∝ ‖ ∪ ∏ ∈ ° ′ ‥ ： ＆ ～ ")
//	_T("∵ ﹉ ﹍ … ")
//	_T("ˇ ˉ π ㏒ ㏑ ")
//	_T("∑ σ ξ ")
//};

class CSyntaxWordList
{
public:

	CSyntaxWordList();
	~CSyntaxWordList();

	CString m_strOasmWordListSymbol;
	CString m_strOasmWordListCPUInsns;
	CString m_strOasmWordListFPUInsns;
	CString m_strOasmWordListRegister;
	CString m_strOasmWordListDefineWord;
	CString m_strOasmWordListMacro;
	CString m_strOasmWordListOperatorTxt;
	CString m_strOasmWordListOperator;

	CString m_strOMLWordListCommentSymbol;
	CString m_strOMLWordListKeyword;
	CString m_strOMLWordListOperator;
	CString m_strOMLWordListMacroTxt;	

	BOOL LoadOASMSyntaxWord(const CString& strSyntaxWordFileName);
	BOOL LoadOMLSyntaxWord(const CString& strSyntaxWordFileName);
};

#endif //_SYNTAX_WORD_LIST_H_

            
         
