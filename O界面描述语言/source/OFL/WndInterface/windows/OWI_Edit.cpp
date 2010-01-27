
#include "OWI_Edit.h"
#include "../../CreateWnd/windows/OFControl.h"

OFL_API void _stdcall Edit_SetText(void* pEdit,char* string)
{
	((WinEdit*)pEdit)->SetText(string);
}

OFL_API char* _stdcall Edit_GetText(void* pEdit)
{
	return (char*)((WinEdit*)pEdit)->GetText();
}

OFL_API void _stdcall Edit_SetTextColor(void* pEdit,unsigned int color)
{
	((WinEdit*)pEdit)->SetTextColor(color);
}

OFL_API unsigned int _stdcall Edit_GetTextColor(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetTextColor();
}

OFL_API int _stdcall Edit_GetCharCount(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetCharCount();
}

OFL_API int _stdcall Edit_GetLineCount(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetLineCount();
}

OFL_API int _stdcall Edit_GetTopLine(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetTopLine();
}

OFL_API void _stdcall Edit_SetLimitText(void* pEdit,int limit)
{
	((WinEdit*)pEdit)->SetLimitText(limit);
}

OFL_API int _stdcall Edit_GetLimitText(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetLimitText();
}

OFL_API void _stdcall Edit_SetLeftMargin(void* pEdit,int margin)
{
	((WinEdit*)pEdit)->SetLeftMargin(margin);
}

OFL_API int _stdcall Edit_GetLeftMargin(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetLeftMargin();
}

OFL_API void _stdcall Edit_SetRightMargin(void* pEdit,int margin)
{
	((WinEdit*)pEdit)->SetRightMargin(margin);
}

OFL_API int _stdcall Edit_GetRightMargin(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetRightMargin();
}

OFL_API void _stdcall Edit_SetModifyFlag(void* pEdit,bool modify)
{
	((WinEdit*)pEdit)->SetModifyFlag(modify);
}

OFL_API bool _stdcall Edit_GetModifyFlag(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetModifyFlag();
}

OFL_API void _stdcall Edit_SetPassword(void* pEdit,char pw)
{
	((WinEdit*)pEdit)->SetPassword(pw);
}

OFL_API char _stdcall Edit_GetPassword(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetPassword();
}

OFL_API void _stdcall Edit_SetSelectStart(void* pEdit,int start)
{
	((WinEdit*)pEdit)->SetSelectStart(start);
}

OFL_API int _stdcall Edit_GetSelectStart(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetSelectStart();
}

OFL_API void _stdcall Edit_SetSelectEnd(void* pEdit,int end)
{
	((WinEdit*)pEdit)->SetSelectEnd(end);
}

OFL_API int _stdcall Edit_GetSelectEnd(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetSelectEnd();
}

OFL_API void _stdcall Edit_SetReadOnly(void* pEdit,bool readonly)
{
	((WinEdit*)pEdit)->SetReadOnly(readonly);
}

OFL_API bool _stdcall Edit_GetReadOnly(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetReadOnly();
}

OFL_API void _stdcall Edit_SetFormatRect(void* pEdit,const RECT& rc)
{
	Rect rect;
	rect.mLeft = rc.left;
	rect.mRight = rc.right;
	rect.mTop = rc.top;
	rect.mBottom = rc.bottom;
	((WinEdit*)pEdit)->SetFormatRect(rect);
}

OFL_API void _stdcall Edit_GetFormatRect(void* pEdit,RECT& rc)
{
	Rect rect;
	rect = ((WinEdit*)pEdit)->GetFormatRect();
	rc.left = rect.mLeft;
	rc.top = rect.mTop;
	rc.right = rect.mRight;
	rc.bottom = rect.mBottom;	
}


//检索操作队列中是否存在可以撤销的动作，返回值指明撤销队列中是否存在可以撤销的动作
OFL_API bool _stdcall Edit_CanUndo(void* pEdit)
{
	return ((WinEdit*)pEdit)->CanUndo();
}

//撤销上一次操作
OFL_API bool _stdcall Edit_Undo(void* pEdit)
{
	return ((WinEdit*)pEdit)->Undo();
}

//清空撤销队列(当用户调用SetCaption()和SetMemHandle()也会自动清除撤销队列)
OFL_API void _stdcall Edit_ResetUndoBuffer(void* pEdit)
{
	((WinEdit*)pEdit)->ResetUndoBuffer();
}

//拷贝当前被选择的文本到剪贴板
OFL_API void _stdcall Edit_Copy(void* pEdit)
{
	((WinEdit*)pEdit)->Copy();
}

//剪切当前被选择的文本到剪贴板
OFL_API void _stdcall Edit_Cut(void* pEdit)
{
	((WinEdit*)pEdit)->Cut();
}

//清除当前被选择的文本，但并不把内容复制到剪贴板中
OFL_API void _stdcall Edit_Clear(void* pEdit)
{
	((WinEdit*)pEdit)->Clear();
}

//粘贴剪贴板中的内容到控件的当前光标位置
OFL_API void _stdcall Edit_Paste(void* pEdit)
{
	((WinEdit*)pEdit)->Paste();
}

//获取最接近指定坐标(相对于控件客户区)的字符索引, line保存返回字符索引所在的行索引
OFL_API int _stdcall Edit_GetCharFromPoint(void* pEdit,const POINT& p, /*Out*/int* line)
{
	Point point;
	point.x = p.x;
	point.y = p.y;
	return ((WinEdit*)pEdit)->GetCharFromPoint(point,line);
}

//获取指定字符索引在控件客户区的位置坐标(如果要获取的字符为分界符，则返回此行尾字符之后的"虚字符"坐标)
OFL_API void _stdcall Edit_GetPointFromChar(void* pEdit,int index,POINT& p)
{
	Point point;
	point = ((WinEdit*)pEdit)->GetPointFromChar(index);
	p.x = point.x;
	p.y = point.y;
}

//检索指定行第一个字符索引，如果行编号超出了有效范围则函数返回-1；如果传入-1，则获取当前行的首字符索引
OFL_API int _stdcall Edit_GetFirstCharFromLine(void* pEdit,int index)
{
	return ((WinEdit*)pEdit)->GetFirstCharFromLine(index);
}

//检索指定的字符索引所在的行
OFL_API int _stdcall Edit_GetLineFromChar(void* pEdit,int index)
{
	return ((WinEdit*)pEdit)->GetLineFromChar(index);
}

//获取当前行(当没有选择文本，当前行指光标所在行，否则是指选择文本一个字符所在行)
OFL_API int _stdcall Edit_GetCurrentLine(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetCurrentLine();
}

//检索指定字符索引所在行的字符数(注意：不包含回车符和行尾符;如果传入索引超出有效范围，函数返回0)
OFL_API int _stdcall Edit_GetLineLengthFromChar(void* pEdit,int index)
{
	return ((WinEdit*)pEdit)->GetLineLengthFromChar(index);
}

//把指定的某一个行拷贝到buffer所指定的缓冲中(不包含空终止符)，bufferSize指明了buffer的大小，返回实际拷贝的字节数
OFL_API int _stdcall Edit_CopyLine(void* pEdit,int line, char* buffer, unsigned short bufferSize)
{
	return ((WinEdit*)pEdit)->CopyLine(line,buffer,bufferSize);
}

//选择指定范围的文本，两个参数分别指定选择位置的起始点与结束点
OFL_API void _stdcall Edit_SelectText(void* pEdit,int start,int end)
{
	((WinEdit*)pEdit)->SelectText(start,end);
}

//获取当前被选择文本的起止范围(两参数都可为NULL),start保存被选文本首字符索引，end保存被选文本尾字符之后第一个字符的索引
OFL_API void _stdcall Edit_GetSelectRange(void* pEdit,int* start, int* end)
{
	((WinEdit*)pEdit)->GetSelectRange(start,end);
}

//选择所有文本
OFL_API void _stdcall Edit_SelectAllText(void* pEdit)
{
	((WinEdit*)pEdit)->SelectAllText();
}

//取消选择
OFL_API void _stdcall Edit_CancelSelect(void* pEdit)
{
	((WinEdit*)pEdit)->CancelSelect();
}

//用指定的文本替换高亮选择的文本,undo指明是否以后可以撤销(如果不存在被选择的文本，函数返回false)
OFL_API bool _stdcall Edit_ReplaceText(void* pEdit,char* string, bool undo)
{
	return ((WinEdit*)pEdit)->ReplaceText(string,undo);
}

//删除被选择的文本
OFL_API bool _stdcall Edit_DeleteSelect(void* pEdit,bool undo)
{
	return ((WinEdit*)pEdit)->DeleteSelect(undo);
}

//如果控件没有文本被选择，执行此函数在光标处插入指定的文本
OFL_API bool _stdcall Edit_InsertText(void* pEdit,char* string, bool undo)
{
	return ((WinEdit*)pEdit)->InsertText(string,undo);
}

//对于多行编辑控件，获取垂直滚动条的抓取器(Thumb)在滚动条中的位置
OFL_API int _stdcall Edit_GetVertThumb(void* pEdit)
{
	return ((WinEdit*)pEdit)->GetVertThumb();
}

//滚动控件，使得闪烁Caret光标可见
OFL_API void _stdcall Edit_ScrollCaret(void* pEdit)
{
	((WinEdit*)pEdit)->ScrollCaret();
}

//对于多行编辑控件，在水平方向和垂直方向分别滚动horz和vert
OFL_API void _stdcall Edit_ScrollText(void* pEdit,int horz,int vert)
{
	((WinEdit*)pEdit)->ScrollText(horz,vert);
}

//对于多行编辑控件，在垂直方向滚动文本
OFL_API void _stdcall Edit_VertScroll(void* pEdit,int param)
{
	((WinEdit*)pEdit)->VertScroll((EditScrollType)param);
}

//对于多行编辑控件，设置Tab字符在控件中占据的字符间距(默认8字符宽),redraw表明此操作是否使控件重新显示文本(默认不更新显示)
OFL_API void _stdcall Edit_SetTabSpace(void* pEdit,unsigned int space, bool redraw)
{
	((WinEdit*)pEdit)->SetTabSpace(space,redraw);
}


OFL_API void _stdcall Edit_DestroyControl(void* pEdit)
{
	((WinEdit*)pEdit)->DestroyControl();
}

OFL_API char* _stdcall Edit_GetClass(void* pEdit)
{
	return (char*)((WinEdit*)pEdit)->GetClass();
}

OFL_API void _stdcall Edit_SetCaption(void* pEdit,char* string)
{
	((WinEdit*)pEdit)->SetCaption(string);
}

OFL_API char* _stdcall Edit_GetCaption(void* pEdit)
{
	return (char*)((WinEdit*)pEdit)->GetCaption();
}

