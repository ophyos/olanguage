function DoParameterTypesReplacement(sText)
{
  //replace string with const char*
  var sOutput = sText.replace(/string /g, "const char* ");
  
  //Replace position with long
  sOutput = sOutput.replace(/position /g, "long ");

  //Replace bool with BOOL
  sOutput = sOutput.replace(/bool /g, "BOOL ");
  
  //Replace textrange with textrange*
  sOutput = sOutput.replace(/textrange /g, "TextRange* ");
  
  //Replace cells with char*
  sOutput = sOutput.replace(/cells /g, "char* ");

  //Replace stringresult with char*
  sOutput = sOutput.replace(/stringresult /g, "char* ");

  //Replace colour with COLORREF
  sOutput = sOutput.replace(/colour /g, "COLORREF ");

  //Replace colour with TextToFind*
  sOutput = sOutput.replace(/findtext /g, "TextToFind* ");
  
  //Replace keymod with DWORD
  sOutput = sOutput.replace(/keymod /g, "DWORD ");
  
  //Replace formatrange with long
  sOutput = sOutput.replace(/formatrange /g, "RangeToFormat* ");

  return sOutput;
}

function FindBodyParameters(sLine)
{
  var nStartParameters = sLine.indexOf("(");
  var nEndParameters = sLine.indexOf(")");
  var sParameters = sLine.substr(nStartParameters+1, nEndParameters - nStartParameters - 1);

  //Change the parameter types to something which the C++ compiler understands
  sParameters = DoParameterTypesReplacement(sParameters);

  //No first parameter
  if (sParameters.charAt(0) == ",")
    sParameters = "0" + sParameters;
  else
    sParameters = "(WPARAM) " + sParameters;
  
  //No second parameter
  if (sParameters.charAt(sParameters.length-1) == ",")
    sParameters += " 0";
  else
  {
    var nComma = sParameters.indexOf(", ");
    var sTemp = sParameters.substr(0, nComma + 2);
    sTemp += "(LPARAM)";
    sTemp += sParameters.substr(nComma + 1, sParameters.length - nComma);
    sParameters = sTemp;
  }
    
  //Ensure we have a "," at the end of the parameters list
  if (sParameters.length && sParameters.charAt(sParameters.length - 1) != ",")
    sParameters += ", ";

  //Add the "bDirect" parameter
  sParameters += "bDirect";

  //Remove the parameter types from the parameter string
  sParameters = sParameters.replace(/const char\*\ /g, "");
  sParameters = sParameters.replace(/long\ /g, "");
  sParameters = sParameters.replace(/int\ /g, "");  
  sParameters = sParameters.replace(/BOOL\ /g, "");
  sParameters = sParameters.replace(/TextRange\*\ /g, "");
  sParameters = sParameters.replace(/char\*\ /g, "");
  sParameters = sParameters.replace(/COLORREF\ /g, "");
  sParameters = sParameters.replace(/TextToFind\*\ /g, "");
  sParameters = sParameters.replace(/DWORD\ /g, "");
  sParameters = sParameters.replace(/RangeToFormat\*\ /g, "");
  
  return sParameters;
}

function FindHeaderParameters(sLine, bDefault)
{
  //find the parameters
  var nStartParameters = sLine.indexOf("(");
  var nEndParameters = sLine.indexOf(")");
  var sParameters = sLine.substr(nStartParameters+1, nEndParameters - nStartParameters - 1);

  //Change the parameter types to something which the C++ compiler understands
  sParameters = DoParameterTypesReplacement(sParameters);

  //No first parameter
  if (sParameters.charAt(0) == ",")
    sParameters = sParameters.substr(2, sParameters.length - 2);
  
  //No second parameter
  if (sParameters.charAt(sParameters.length-1) == ",")
    sParameters = sParameters.substr(0, sParameters.length - 1);
    
  //Ensure we have a "," at the end of the parameters list
  if (sParameters.length && sParameters.charAt(sParameters.length - 1) != ",")
    sParameters += ", ";

  //Add the special "BOOL bDirect = TRUE" default parameter
  if (bDefault)
    sParameters += "BOOL bDirect = TRUE";
  else
    sParameters += "BOOL bDirect";

  return sParameters;
}

function FindFunctionNameAndReturn(sLine)
{
  //Find the name of the function
  var nFirstSpace = sLine.indexOf(" ");
  var sTemp = sLine.substr(nFirstSpace+1, sLine.length - nFirstSpace);
  var nEquals = sTemp.indexOf("=");
  var sFunction = sTemp.substr(0, nEquals);

  return sFunction;
}

function FindFunctionName(sLine)
{
  //Find the name of the function
  var nFirstSpace = sLine.indexOf(" ");
  var sTemp = sLine.substr(nFirstSpace+1, sLine.length - nFirstSpace);
  nFirstSpace = sTemp.indexOf(" ");
  sTemp = sTemp.substr(nFirstSpace+1, sTemp.length - nFirstSpace);
  var nEquals = sTemp.indexOf("=");
  var sFunction = sTemp.substr(0, nEquals);

  return sFunction;
}

function HandleFunctionHeader(sLine, bDefault)
{
  //parse out the parameters from the line
  var sParameters = FindHeaderParameters(sLine, bDefault);
  
  //Find the name of the function
  var sFunctionNameAndReturn = FindFunctionNameAndReturn(sLine);
  
  //Replace SetFocus with SCISetFocus (to avoid conflict with CWnd::SetFocus)
  sFunctionNameAndReturn = sFunctionNameAndReturn.replace(/SetFocus/g, "SCISetFocus");
  
  //Create the header output line
  var sOutput = sFunctionNameAndReturn + "(" + sParameters + ")" + ";";
  
  //Change the parameter types to something which the C++ compiler understands
  sOutput = DoParameterTypesReplacement(sOutput);

  return sOutput;
}

function HandleFunctionBody(sLine)
{
  //Get the basic function header from the other function
  var sHeader = HandleFunctionHeader(sLine, false);
  
  //Trim off the terminating ";"
  var sHeader = sHeader.substr(0, sHeader.length - 1);
  
  //Add the C++ class scoping
  var nFirstSpace = sHeader.indexOf(" ");
  var sBody = sHeader.substr(0, nFirstSpace + 1) + " CScintillaCtrl::" + sHeader.substr(nFirstSpace + 1, sHeader.length - nFirstSpace - 1);

  //Remove any padding between the scoping
  //sBody = sParameters.replace(/:: /g, "::");
  
  //Remove any padding before the class name
  sBody = sBody.replace(/\  CScintillaCtrl::/, " CScintillaCtrl::");

  //Work out the message type from the line
  var sMessage = "SCI_" + FindFunctionName(sLine).toUpperCase();

  //parse out the parameters from the line
  var sParameters = FindBodyParameters(sLine, false);
  
  //Add the start of the function
  sBody += "\r\n" + "{\r\n";
  
  //Have we a return value from this function
  if (FindFunctionNameAndReturn(sLine).indexOf("void") != 0)
  {
    sBody += "  return Call(";
  }
  else
  {
    //Add the "Call" function
    sBody += "  Call(";
  }
  
  //Complete the function body
  sBody += sMessage + ", " + sParameters + ");\r\n}\r\n";

  return sBody;
}



//The actual script implementation

//Ensure the number of arguments are correct
if (WScript.Arguments.length < 1)
{
  WScript.Echo("Usage: ConvertScintillaiface PathToScintillaiface [/CPP]");
  WScript.Quit(1);
}

//Create the file system object
var g_FSO = new ActiveXObject("Scripting.FileSystemObject");

//Open the file as text for parsing
var ifaceFile = g_FSO.OpenTextFile(WScript.Arguments(0), 1, false);

var bCreateHeader = true;
if (WScript.Arguments.length >= 2) 
{
  if (WScript.Arguments(1) == "/CPP")
    bCreateHeader = false;
}

//Read in all the text from the file
var bHandlingDeprecatedCategory = false;
var sLine;
while(!ifaceFile.AtEndOfStream)
{
  sLine = ifaceFile.ReadLine();
  if (sLine.length)
  {
    if (sLine.charAt(0) != "#")
    {
      if (sLine.indexOf("fun") == 0)
      {
        if (!bHandlingDeprecatedCategory)
        {
          if (bCreateHeader)
            WScript.Echo(HandleFunctionHeader(sLine, true));
          else
            WScript.Echo(HandleFunctionBody(sLine));
        }
      }
      else if (sLine.indexOf("get") == 0)
      {
        var sFunctionName = FindFunctionName(sLine);        

        if (!bHandlingDeprecatedCategory && sFunctionName != "GetDirectFunction" && sFunctionName != "GetDirectPointer")
        {
          if (bCreateHeader)
            WScript.Echo(HandleFunctionHeader(sLine, true));
          else
            WScript.Echo(HandleFunctionBody(sLine));
        }
      }
      else if (sLine.indexOf("set") == 0)
      {
        if (!bHandlingDeprecatedCategory)
        {
          if (bCreateHeader)
            WScript.Echo(HandleFunctionHeader(sLine, true));
          else
            WScript.Echo(HandleFunctionBody(sLine));
        }
      }
      else if (sLine.indexOf("cat") == 0)
      {
        if (sLine.indexOf("Deprecated") != -1)
          bHandlingDeprecatedCategory = true;
        else
          bHandlingDeprecatedCategory = false;
      }
    }
  }
}


