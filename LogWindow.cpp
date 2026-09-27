#include "stdafx.h"

#include "LogWindow.h"

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
	size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
	std::unique_ptr<char[]> buf(new char[size]);
	snprintf(buf.get(), size, format.c_str(), args ...);
	return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

int     filter_ztxt_files(std::string offset, std::vector<std::string>& vec_res)
{
	boost::system::error_code ec;
	boost::filesystem::path offset_path(offset);

	for (boost::filesystem::directory_iterator it(offset_path, ec), eit;
		it != eit;
		it.increment(ec)
		)
	{
		if (ec)
			continue;

		if (boost::filesystem::is_regular_file(it->path()))
		{
			string ext = it->path().extension().string();
			if (ext  == ".ztxt")
				vec_res.push_back(it->path().filename().string());
		}
		// if you need recursion
		else if (boost::filesystem::is_directory(it->path()))
		{
			filter_ztxt_files(it->path().string(), vec_res);
		}
	}
	return ((int)vec_res.size());
}

string intToHexString(DWORD intValue) {

	string hexStr;

	/// integer value to hex-string
	std::stringstream sstream;
	sstream << "0x"
		<< std::setfill('0') << std::setw(2)
		<< std::hex << (DWORD)intValue;

	hexStr = sstream.str();
	sstream.clear();    //clears out the stream-string

	return hexStr;
}
string ztxtDirPathStr = "";

QStandardItemModel* LogWindow::model = new QStandardItemModel();
enum  { RED, ORANGE, YELLOW, GREEN, BLUE, INDIGO, VIOLET };
enum  { OUTPUT_CALL, OUTPUT_ALL,LOG, LOG_INSTANCE, LOG_CALL, LOG_CALL_VIRT, LOG_STRING, LOG_PATTERN, LOG_CALL_INSIDE, LOG_POINTER, MODULE, OUTPUT , OUTPUT_SELECTED
};
LogWindow::LogWindow(QWidget* parent): QWidget(parent)
{
	ui.setupUi(this);
	Sleep(2000);
	TCHAR dllFilePath[512 + 1] = { 0 };
	GetModuleFileNameW(MainCore::hModule, dllFilePath, 512);
	////MessageBox(NULL, L"BP", L"Main BreakePoint", 0);
	string dllDirPathStr = FileExtension::GetDirectoryPathFromFilePatch(StringExtension::StringFromWChar(dllFilePath));
	ztxtDirPathStr = dllDirPathStr + "\\";
	vector<std::string> vec_res;
	filter_ztxt_files(dllDirPathStr, vec_res);
	for (vector<std::string>::iterator it = vec_res.begin(); it != vec_res.end(); ++it) {
		string cut = *it;
		cut = StringExtension::ReplaceString(cut, ".ztxt", "");
		ui.comboBoxServer->addItem(QString::fromStdString(cut));
	}


	
		ui.treeViewModules->setModel(model);
		
		
		AppendTextBoxModules();
		
		
		AppendTreeViewModules();

}

LogWindow::~LogWindow()
{
}
template<typename ... Args>
void LogWindow::AppendLogFormat(int window,int color,bool newLine,const std::string& format, Args ... args)
{
	
	
	AppendLog( window,  color, newLine , string_format(format, args...).c_str());
}
void  LogWindow::AppendLog(int window, int color,bool newLine,QString  msg )
{
	
	
	string line = "";
	switch (color)
	{
	case RED:
		line = "<font color=\"red\">" + msg.toStdString() + "</font>";
		break;
	case ORANGE:
		line = "<font color=\"orange\">" + msg.toStdString() + "</font>";
		break;
	case YELLOW:
		line = "<font color=\"yellow\">" + msg.toStdString() + "</font>";
		break;
	case GREEN:
		line = "<font color=\"green\">" + msg.toStdString() + "</font>";
		break;
	case BLUE:
		line = "<font color=\"blue\">" + msg.toStdString() + "</font>";
		break;
	case INDIGO:
		line = "<font color=\"indigo\">" + msg.toStdString() + "</font>";
		break;
	case VIOLET:
		line = "<font color=\"violet\">" + msg.toStdString() + "</font>";
		break;
	default:

	;}
	
	
	switch (window)
	{
	case OUTPUT_CALL:
		this->ui.plainTextEditOutputCall->appendHtml(QString::fromStdString(line));
		break;
	case OUTPUT_ALL:
		this->ui.plainTextEditOutputAll->appendHtml(QString::fromStdString(line));
		break;

	case LOG:
		this->ui.plainTextEditLog->appendHtml(QString::fromStdString(line));
		break;
	case LOG_INSTANCE:
		this->ui.plainTextEditLogInstance->appendHtml(QString::fromStdString(line));
		break;
		
	case LOG_CALL:
		this->ui.plainTextEditLogCall->appendHtml(QString::fromStdString(line));
		break;
	case LOG_CALL_VIRT:
		this->ui.plainTextEditLogCallVirt->appendHtml(QString::fromStdString(line));
		break;
	case LOG_STRING:
		this->ui.plainTextEditLogString->appendHtml(QString::fromStdString(line));
		break;
	case LOG_PATTERN:
		this->ui.plainTextEditLogPattern->appendHtml(QString::fromStdString(line));
		break;

	case LOG_CALL_INSIDE:
		this->ui.plainTextEditLogCallInside->appendHtml(QString::fromStdString(line));
		break;
	case LOG_POINTER:
		this->ui.plainTextEditLogPointer->appendHtml(QString::fromStdString(line));
		break;


	case MODULE:
		this->ui.plainTextEditOutputModules->appendHtml(QString::fromStdString(line));
		break;
	case OUTPUT:
		this->ui.plainTextEditOutput->appendHtml(QString::fromStdString(line));
		break;
	case OUTPUT_SELECTED:
		this->ui.plainTextEditOutputSelected->appendHtml(QString::fromStdString(line));
		break;
	default:

	;}
	

}





bool LogWindow::CheckTextFile(const char* fileName)
{
	
	std::ifstream infile(fileName);

	if (infile.good() == false)
	{
		AppendLogFormat(OUTPUT, RED, true, "FILE NOT EXIST: %s", fileName);
		return false;
	}
	std::string line;
	int lineCounter = 1;
	bool isError = false;

	while (std::getline(infile, line))
	{
		vector<string> sett = StringExtension::Split(line, "\t");
		if (sett.size() == 0)
		{
			AppendLogFormat(LOG, RED, true, "LINE NULL  %s", line.c_str(), lineCounter);
			continue;
		}
		if (StringExtension::Equals("//", sett[0].c_str()))
		{
			continue;
		}
		if (StringExtension::Equals("CALL-UPDOWN", sett[0].c_str()))
		{

			if (sett.size() != 5)
			{
				AppendLogFormat(LOG, RED, true, "CALL-UPDOWN SIZE Index: %s  ->  %s", line.c_str(), lineCounter);
				isError = true;
			}
		}
		if (StringExtension::Equals("CALL-UPDOWN-COUNT", sett[0].c_str()))
		{
			if (sett.size() != 6)
			{
				AppendLogFormat(LOG, RED, true, "CALL-UPDOWN-COUNT SIZE Index: %s  ->  %s", line.c_str(), lineCounter);
				isError = true;
			}
		}
		if (StringExtension::Equals("INSTANCE-UPDOWN", sett[0].c_str()))
		{
			if (sett.size() != 6)
			{
				AppendLogFormat(LOG, RED, true, "INSTANCE-UPDOWN SIZE Index: %s  ->  %s", line.c_str(), lineCounter);
				isError = true;
			}
		}
		if (StringExtension::Equals("INSTANCE-UPDOWN-COUNT", sett[0].c_str()))
		{
			if (sett.size() != 7)
			{
				AppendLogFormat(LOG, RED, true, "INSTANCE-UPDOWN-COUNT SIZE Index: %s  ->  %s", line.c_str(), lineCounter);
				isError = true;
			}
		}
		if (StringExtension::Equals("CALL-UPDOWN-VIRT", sett[0].c_str()))
		{

			if (sett.size() != 6)
			{
				AppendLogFormat(LOG, RED, true, "CALL-UPDOWN-VIRT SIZE Index: %s  ->  %s", line.c_str(), lineCounter);
				isError = true;
			}
		}
		if (StringExtension::Equals("CALL-UPDOWN-VIRT-COUNT", sett[0].c_str()))
		{

			if (sett.size() != 7)
			{
				AppendLogFormat(LOG, RED, true, "CALL-UPDOWN-VIRT-COUNT SIZE Index: %s  ->  %s", line.c_str(), lineCounter);
				isError = true;
			}
		}
		if (StringExtension::Equals("CALL-INSIDE-CALL", sett[0].c_str()))
		{

			if (sett.size() != 5)
			{
				AppendLogFormat(LOG, RED, true, "CALL-INSIDE-CALL SIZE Index: %s  ->  %s", line.c_str(), lineCounter);
				isError = true;
			}
		}
		lineCounter++;
	}
	return !isError;
}
vector<string> ReadDefaultList()
{
	vector<string> list;
	std::ifstream infile(ztxtDirPathStr+ "DefaultList.xtxt");
	std::string line;
	while (std::getline(infile, line))
	{
		list.push_back(line);
	}
	return list;
}
void LogWindow::FindOpcodeCalls(const char* filePath, map< DWORD, string> moduleFunctions)
{
	if (this->ui.checkBox->isChecked())
	{

	}
	else
	{
		MainCore::searchOutput.clear();
	}
	

	std::ifstream infile(filePath);
	std::string line;
	while (std::getline(infile, line))
	{
		if (StringExtension::Equals(line.c_str(),""))
		{
			continue;
		}
		vector<string> sett = StringExtension::Split(line, "\t");
		if (sett[0].size() == 0)
		{
		continue;
		}
		if (StringExtension::Equals("//", sett[0].c_str()))
		{
			continue;
		}
	
		map<DWORD, string>::iterator itor;
		const char* searchMethod = sett[0].c_str();


		//###################################################################################
		if (StringExtension::Equals("CALL-UPDOWN", searchMethod))
		{

			
			const char* searchMethodDir = sett[3].c_str();
			const char* pythonFunctionName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();
			int callNumber = atoi(sett[4].c_str());
			bool isModuleFounded = false;
			for (itor = moduleFunctions.begin(); itor != moduleFunctions.end(); itor++)
			{
				if (StringExtension::Equals(itor->second.c_str(), pythonFunctionName))
				{
					isModuleFounded = true;
					DWORD funcAddress = itor->first;



					DWORD sizeFuncByte = AsmOperations::GetModuleFunctionSize(pythonFunctionName, moduleFunctions);
					vector< _DecodedInst>functionsOpInstructions;
					if (StringExtension::Equals("UP", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);

					}
					else if (StringExtension::Equals("DOWN", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
					}
					else
					{
						AppendLogFormat(LOG_CALL, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
						
						break;
					}
					DWORD functionAddress = AsmOperations::GetCallStaticAddress(pythonFunctionName, functionsOpInstructions, callNumber);
					if (functionAddress != 0)
					{
						AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
						MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));

					}
					else
					{
						AppendLogFormat(LOG_CALL, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
						

					}


					break;

				}
			}

			if (!isModuleFounded)
			{
				AppendLogFormat(LOG_CALL, RED, true, "NOT FOUND MODULE NAME: %s FROM LINE:  %s", pythonFunctionName, line.c_str());
				
			}
			continue;
		}
		//###################################################################################

		if (StringExtension::Equals("CALL-UPDOWN-COUNT", searchMethod))
		{

			const char* searchMethodDir = sett[3].c_str();
			const char* pythonFunctionName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();
			int callCount = atoi(sett[4].c_str());
			int callNumber = atoi(sett[5].c_str());
			bool isModuleFounded = false;
			for (itor = moduleFunctions.begin(); itor != moduleFunctions.end(); itor++)
			{
				if (StringExtension::Equals(itor->second.c_str(), pythonFunctionName))
				{
					isModuleFounded = true;
					DWORD funcAddress = itor->first;



					DWORD sizeFuncByte = AsmOperations::GetModuleFunctionSize(pythonFunctionName, moduleFunctions);
					vector< _DecodedInst>functionsOpInstructions;



					if (StringExtension::Equals("UP", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);

					}
					else if (StringExtension::Equals("DOWN", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
					}
					else
					{
						AppendLogFormat(LOG_CALL, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
						
						break;
					}
					DWORD funcCallCount = AsmOperations::GetModuleFunctionsCallsCount(functionsOpInstructions);
					if (funcCallCount != callCount)
					{
						AppendLogFormat(LOG_CALL, RED, true, "INCORRECT CALL COUNT  IS [%d ]IN LINE: %s ", funcCallCount, line.c_str());
						
						break;
					}

					DWORD functionAddress = AsmOperations::GetCallStaticAddress(pythonFunctionName, functionsOpInstructions, callNumber);
					if (functionAddress != 0)
					{
						AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
						MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));

					}
					else
					{
						AppendLogFormat(LOG_CALL, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
						

					}
					break;
				}
			}
			if (!isModuleFounded)
			{
				AppendLogFormat(LOG_CALL, RED, true, "NOT FOUND MODULE NAME: %s FROM LINE:  %s", pythonFunctionName, line.c_str());
				
			}
			continue;
		}
		//################################################################################################################
		if (StringExtension::Equals("INSTANCE-UPDOWN", searchMethod))
		{

			const char* searchMethodLookFor = sett[5].c_str();
			const char* searchMethodDir = sett[3].c_str();
			const char* pythonFunctionName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();

			int callNumber = atoi(sett[4].c_str());
			bool isModuleFounded = false;
			for (itor = moduleFunctions.begin(); itor != moduleFunctions.end(); itor++)
			{
				if (StringExtension::Equals(itor->second.c_str(), pythonFunctionName))
				{
					isModuleFounded = true;
					DWORD funcAddress = itor->first;



					DWORD sizeFuncByte = AsmOperations::GetModuleFunctionSize(pythonFunctionName, moduleFunctions);
					vector< _DecodedInst>functionsOpInstructions;



					if (StringExtension::Equals("UP", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);

					}
					else if (StringExtension::Equals("DOWN", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
					}
					else
					{
						AppendLogFormat(LOG_INSTANCE, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
						
						break;
					}


					DWORD functionAddress = 0;


					if (StringExtension::Equals("DWORD", searchMethodLookFor))
					{
						functionAddress = AsmOperations::GetInstanceDwordAddress(pythonFunctionName, functionsOpInstructions, callNumber);

					}
					else if (StringExtension::Equals("CALL", searchMethodLookFor))
					{
						functionAddress = AsmOperations::GetInstanceCallDwordAddress(pythonFunctionName, functionsOpInstructions, callNumber);
					}
					else
					{
						AppendLogFormat(LOG_INSTANCE, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
						
						break;
					}


					if (functionAddress != 0)
					{
						AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
						MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));

					}
					else
					{
						AppendLogFormat(LOG_INSTANCE, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
						

					}
					break;
				}
			}
			if (!isModuleFounded)
			{
				AppendLogFormat(LOG_INSTANCE, RED, true, "NOT FOUND MODULE NAME: %s FROM LINE:  %s", pythonFunctionName, line.c_str());
				
			}
			continue;
		}
		//################################################################################################################

		if (StringExtension::Equals("INSTANCE-UPDOWN-COUNT", searchMethod))
		{

			const char* searchMethodLookFor = sett[6].c_str();
			const char* searchMethodDir = sett[3].c_str();
			const char* pythonFunctionName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();
			int callCount = atoi(sett[4].c_str());
			int callNumber = atoi(sett[5].c_str());
			bool isModuleFounded = false;
			for (itor = moduleFunctions.begin(); itor != moduleFunctions.end(); itor++)
			{
				if (StringExtension::Equals(itor->second.c_str(), pythonFunctionName))
				{
					isModuleFounded = true;
					DWORD funcAddress = itor->first;



					DWORD sizeFuncByte = AsmOperations::GetModuleFunctionSize(pythonFunctionName, moduleFunctions);
					vector< _DecodedInst>functionsOpInstructions;



					if (StringExtension::Equals("UP", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);

					}
					else if (StringExtension::Equals("DOWN", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
					}
					else
					{
						AppendLogFormat(LOG_INSTANCE, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
						
						break;
					}
					DWORD funcCallCount = AsmOperations::GetModuleFunctionsCallsCount(functionsOpInstructions);
					if (funcCallCount != callCount)
					{
						AppendLogFormat(LOG_INSTANCE, RED, true, "INCORRECT CALL COUNT  IS [%d ]IN LINE: %s ", funcCallCount,line.c_str() );
						
						break;
					}

					DWORD functionAddress = 0;


					if (StringExtension::Equals("DWORD", searchMethodLookFor))
					{
						functionAddress = functionAddress = AsmOperations::GetInstanceDwordAddress(pythonFunctionName, functionsOpInstructions, callNumber);

					}
					else if (StringExtension::Equals("CALL", searchMethodLookFor))
					{
						functionAddress = AsmOperations::GetInstanceCallDwordAddress(pythonFunctionName, functionsOpInstructions, callNumber);

					}
					else
					{
						AppendLogFormat(LOG_INSTANCE, RED, true, "MISSING LOOK FOR IN LINE: %s", line.c_str());
						
						break;
					}


					if (functionAddress != 0)
					{
						AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
						MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));

					}
					else
					{
						AppendLogFormat(LOG_INSTANCE, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
						

					}
					break;
				}
			}
			if (!isModuleFounded)
			{
				AppendLogFormat(LOG_INSTANCE, RED, true, "NOT FOUND MODULE NAME: %s FROM LINE:  %s", pythonFunctionName, line.c_str());
				
			}
			continue;
		}
		//################################################################################################################

		if (StringExtension::Equals("CALL-UPDOWN-VIRT", searchMethod))
		{


			const char* searchMethodDir = sett[3].c_str();
			const char* pythonFunctionName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();
			int callNumber = atoi(sett[4].c_str());

			const char* instanceLookInName = sett[5].c_str();
			bool isModuleFounded = false;
			for (itor = moduleFunctions.begin(); itor != moduleFunctions.end(); itor++)
			{
				if (StringExtension::Equals(itor->second.c_str(), pythonFunctionName))
				{
					isModuleFounded = true;
					DWORD funcAddress = itor->first;
					DWORD offset = 0;


					DWORD sizeFuncByte = AsmOperations::GetModuleFunctionSize(pythonFunctionName, moduleFunctions);
					vector< _DecodedInst>functionsOpInstructions;

					DWORD functionAddress = 0;

					if (StringExtension::Equals("UP", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);
						offset = AsmOperations::GetCallVirtualFunctionOffset(pythonFunctionName, functionsOpInstructions, callNumber, false);



					}
					else if (StringExtension::Equals("DOWN", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
						offset = AsmOperations::GetCallVirtualFunctionOffset(pythonFunctionName, functionsOpInstructions, callNumber, true);

					}
					else
					{
						AppendLogFormat(LOG_CALL_VIRT, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
						
						break;
					}
					if (offset == -1)
					{
						AppendLogFormat(LOG_CALL_VIRT, RED, true, "CANT FIND VIRT OFFSET BETWEEN CALLS: %s", line.c_str());
						
						break;
					}
					for (vector< std::pair<DWORD, string >>::iterator it = AsmOperations::offsetList.begin(); it != AsmOperations::offsetList.end(); ++it)
					{

						if (StringExtension::Equals(it->second.c_str(), instanceLookInName))
						{
							DWORD inst = *reinterpret_cast<DWORD *>(it->first);
							DWORD virtInst = *reinterpret_cast<DWORD *>(inst + 4);
							functionAddress = *reinterpret_cast<DWORD *>(virtInst + offset);
							break;

						}
					}



					if (functionAddress != 0)
					{
						AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
						MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));

					}
					else
					{
						AppendLogFormat(LOG_CALL_VIRT, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
						

					}
					break;
				}

			}
			if (!isModuleFounded)
			{
				AppendLogFormat(LOG_CALL_VIRT, RED, true, "NOT FOUND MODULE NAME: %s FROM LINE:  %s", pythonFunctionName, line.c_str());
				
			}
			continue;
		}

		//################################################################################################################
		if (StringExtension::Equals("CALL-UPDOWN-VIRT-COUNT", searchMethod))
		{

			const char* searchMethodDir = sett[3].c_str();
			const char* pythonFunctionName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();
			int callCount = atoi(sett[4].c_str());
			int callNumber = atoi(sett[5].c_str());

			const char* instanceLookInName = sett[6].c_str();
			bool isModuleFounded = false;
			for (itor = moduleFunctions.begin(); itor != moduleFunctions.end(); itor++)
			{
				if (StringExtension::Equals(itor->second.c_str(), pythonFunctionName))
				{
					isModuleFounded = true;
					DWORD funcAddress = itor->first;


					DWORD sizeFuncByte = AsmOperations::GetModuleFunctionSize(pythonFunctionName, moduleFunctions);
					vector< _DecodedInst>functionsOpInstructions;

					DWORD functionAddress = 0;
					DWORD offset = 0;
					if (StringExtension::Equals("UP", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);
						offset = AsmOperations::GetCallVirtualFunctionOffset(pythonFunctionName, functionsOpInstructions, callNumber, true);



					}
					else if (StringExtension::Equals("DOWN", searchMethodDir))
					{
						functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
						offset = AsmOperations::GetCallVirtualFunctionOffset(pythonFunctionName, functionsOpInstructions, callNumber, true);
					
					}
					else
					{
						AppendLogFormat(LOG_CALL_VIRT, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
						
						break;
					}
					if (offset == -1)
					{
						AppendLogFormat(LOG_CALL_VIRT, RED, true, "CANT FIND VIRT OFFSET BETWEEN CALLS: %s", line.c_str());
						
						break;
					}
					DWORD funcCallCount = AsmOperations::GetModuleFunctionsCallsCount(functionsOpInstructions);
					if (funcCallCount != callCount)
					{
						AppendLogFormat(LOG_CALL_VIRT, RED, true, "INCORRECT CALL COUNT  IS [%d ]IN LINE: %s ", funcCallCount, line.c_str());
						
						continue;
					}

					for (vector< std::pair<DWORD, string >>::iterator it = AsmOperations::offsetList.begin(); it != AsmOperations::offsetList.end(); ++it)
					{

						if (StringExtension::Equals(it->second.c_str(), instanceLookInName))
						{
							DWORD inst = *reinterpret_cast<DWORD *>(it->first);
							DWORD virtInst = *reinterpret_cast<DWORD *>(inst + 4);
							functionAddress = *reinterpret_cast<DWORD *>(virtInst + offset);

							break;


						}
					}


					if (functionAddress != 0)
					{
						AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
						MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));
						break;
					}
					else
					{
						AppendLogFormat(LOG_CALL_VIRT, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
						
						break;
					}

				}
			}
			if (!isModuleFounded)
			{
				AppendLogFormat(LOG_CALL_VIRT, RED, true, "NOT FOUND MODULE NAME: %s FROM LINE:  %s", pythonFunctionName, line.c_str());
				
			}
			
			continue;
		}
		//#############################################################






		if (StringExtension::Equals("CALL-INSIDE-CALL-COUNT", searchMethod))
		{


			const char* searchMethodDir = sett[3].c_str();
			const char* callLookInName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();


			int callCount = atoi(sett[4].c_str());
			int callNumber = atoi(sett[5].c_str());
			



			DWORD funcAddress = 0;

			funcAddress = AsmOperations::GetAddressFromVectorOffsetList(callLookInName);

			if (funcAddress == 0)
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "ADDRESS FROM NATIVE LIST ZERO LINE: %s", line.c_str());
				
				continue;

			}
			if (funcAddress <= MainCore::hEntryBaseAddress)
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "ADDRESS OUTSIDE BOUND : %s", line.c_str());
				continue;
			}

			DWORD sizeFuncByte = AsmOperations::GetNativeFunctionSize(funcAddress);
			vector< _DecodedInst>functionsOpInstructions;





			if (StringExtension::Equals("UP", searchMethodDir))
			{
				functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);

			}
			else if (StringExtension::Equals("DOWN", searchMethodDir))
			{
				functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
			}
			else
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
				
				continue;
			}

			DWORD funcCallCount = AsmOperations::GetModuleFunctionsCallsCount(functionsOpInstructions);
			if (funcCallCount != callCount)
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "INCORRECT CALL COUNT  IS [%d ]IN LINE: %s ", funcCallCount, line.c_str());
				
				continue;
			}
			DWORD functionAddress = AsmOperations::GetCallStaticAddress(callLookInName, functionsOpInstructions, callNumber);
			if (functionAddress != 0)
			{
				AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
				MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));
				AppendLogFormat(LOG_CALL_INSIDE, GREEN, true, "SUCCES: %s", line.c_str());
			}
			else
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
				
				continue;
			}

		}
		//#############################################################






		if (StringExtension::Equals("CALL-INSIDE-CALL", searchMethod))
		{


			const char* searchMethodDir = sett[3].c_str();
			const char* callLookInName = sett[2].c_str();

			const char* functionNativeName = sett[1].c_str();
			int callNumber = atoi(sett[4].c_str());



			DWORD funcAddress = 0;

			funcAddress = AsmOperations::GetAddressFromVectorOffsetList(callLookInName);

			if (funcAddress == 0)
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "ADDRESS FROM NATIVE LIST ZERO LINE: %s", line.c_str());
				
				continue;

			}

			if (funcAddress <= MainCore::hEntryBaseAddress)
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "ADDRESS OUTSIDE BOUND : %s", line.c_str());
				continue;
			}
			DWORD sizeFuncByte = AsmOperations::GetNativeFunctionSize(funcAddress);
			vector< _DecodedInst>functionsOpInstructions;





			if (StringExtension::Equals("UP", searchMethodDir))
			{
				functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, true);

			}
			else if (StringExtension::Equals("DOWN", searchMethodDir))
			{
				functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(funcAddress, sizeFuncByte, false);
			}
			else
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "MISSING DIR IN LINE: %s", line.c_str());
				continue;
			}
			DWORD functionAddress = AsmOperations::GetCallStaticAddress(callLookInName, functionsOpInstructions, callNumber);
			if (functionAddress != 0)
			{
				AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
				MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));
			}
			else
			{
				AppendLogFormat(LOG_CALL_INSIDE, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
				
				continue;
			}

		}
		if (StringExtension::Equals("PATTERN", searchMethod))
		{

			const char* functionNativeName = sett[1].c_str();
			const char* functionPattern = sett[2].c_str();
			vector<DWORD> functionAddress = PatternScanFast::FindPatternList(functionPattern,"text");
			if (functionAddress.size() == 1)
			{
				AsmOperations::offsetList.push_back(make_pair(functionAddress[0], functionNativeName));
				MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress[0] - MainCore::hEntryBaseAddress,line));
			}
			else if(functionAddress.size() > 1)
			{
				AppendLogFormat(LOG_PATTERN, RED, true, "PATTERN MULTIPLE XREF: %s", line.c_str());

				continue;
			}
			else
			{
				AppendLogFormat(LOG_PATTERN, RED, true, "PATTERN ZERO XREF: %s", line.c_str());
				
				continue;
			}
		}
		if (StringExtension::Equals("STRING", searchMethod))
		{
			const char* functionNativeName = sett[1].c_str();
			const char* functionString = sett[2].c_str();
			string hexString = StringExtension::MakeHexString((BYTE *)functionString, strlen(functionString), true, true);
			vector<DWORD> addressString = PatternScanFast::FindPatternList(hexString.c_str(),"rdata");
			if (addressString.size() == 0)
			{
				AppendLogFormat(LOG_STRING, RED, true, "ADDRESS STRING DATA ZERO XREF: %s", line.c_str());
				
				continue;
			}
			else if (addressString.size() > 1)
			{
				AppendLogFormat(LOG_STRING, RED, true, "ADDRESS STRING DATA MULTIPLE: %s", line.c_str());

				continue;
			}
			else 
			{
				
			}

			BYTE first = (addressString[0] >> 24) & 0xff;
			BYTE second = (addressString[0] >> 16) & 0xff;
			BYTE third = (addressString[0] >> 8) & 0xff;
			BYTE fourth = addressString[0] & 0xff;



			string pushAddressString = "68 ";

			pushAddressString += StringExtension::ByteToHex(fourth) + " ";
			pushAddressString += StringExtension::ByteToHex(third) + " ";
			pushAddressString += StringExtension::ByteToHex(second) + " ";
			pushAddressString += StringExtension::ByteToHex(first);



			transform(pushAddressString.begin(), pushAddressString.end(), pushAddressString.begin(), toupper);
			vector<DWORD> addressXref = PatternScanFast::FindPatternList(pushAddressString.c_str(),"text");
			if (addressXref.size() == 0)
			{
				AppendLogFormat(LOG_STRING, RED, true, "ADDRESS STRING XREFF ZERO TO DATA: %s", line.c_str());
				
				continue;
			}
			else if (addressXref.size() >1)
			{
				AppendLogFormat(LOG_STRING, RED, true, "ADDRESS STRING XREFF MULTIPLE TO DATA: %s", line.c_str());

				continue;
			}
			else
			{
				
			}
			DWORD functionAddress = AsmOperations::GetNativeFunctionStart(addressXref[0]);

			if (functionAddress != 0)
			{
				AsmOperations::offsetList.push_back(make_pair(functionAddress, functionNativeName));
				
				MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, functionAddress - MainCore::hEntryBaseAddress,line));
				continue;
			}
			else
			{
				AppendLogFormat(LOG_STRING, RED, true, "ADDRESS ZERO LINE: %s", line.c_str());
				

				
				
			}
			continue;
		}

		if (StringExtension::Equals("POINTER", searchMethod))
		{
			const char* functionNativeName = sett[1].c_str();
			/*const char* searchMethodDir = sett[2].c_str();*/
			int searchOffset = atoi(sett[2].c_str());
			const char* functionPattern = sett[3].c_str();
			vector<DWORD> functionAddress = PatternScanFast::FindPatternList(functionPattern,"text");
			if (functionAddress.size() == 1)
			{
				DWORD add = *(DWORD*)(functionAddress[0] + searchOffset);
				AsmOperations::offsetList.push_back(make_pair(add, functionNativeName));
				MainCore::searchOutput.push_back(MainCore::FuncStruct(functionNativeName, add - MainCore::hEntryBaseAddress, line));
			}
			else if (functionAddress.size() > 1)
			{
				AppendLogFormat(LOG_POINTER, RED, true, "POINTER PATTERN MULTIPLE XREF: %s", line.c_str());

				continue;
			}
			else
			{
				AppendLogFormat(LOG_POINTER, RED, true, "PATTERN ZERO XREF: %s", line.c_str());

				continue;
			}
		}
	}
	  

	

	/*	for (vector<MainCore::FuncStruct>::iterator itor = MainCore::searchOutput.begin(); itor != MainCore::searchOutput.end(); itor++)
		{
			
		}*/
	vector<string> AppendList;
	vector<string> addressGroupNames;
	sort(MainCore::searchOutput.begin(), MainCore::searchOutput.end()); 
	for (vector<MainCore::FuncStruct>::iterator itor = MainCore::searchOutput.begin(); itor != MainCore::searchOutput.end(); itor++)
	{
		if (StringExtension::Contains(itor->searchLine.c_str(), "INSTANCE-"))
		{
			if (std::count(addressGroupNames.begin(), addressGroupNames.end(), itor->functionName))
			{

			}
			else
			{
				addressGroupNames.push_back(itor->functionName);
			}
		}
		

	}
	for (vector<MainCore::FuncStruct>::iterator itor = MainCore::searchOutput.begin(); itor != MainCore::searchOutput.end(); itor++)
	{
		if (StringExtension::Contains(itor->searchLine.c_str(), "INSTANCE-"))
		{
			
		}
		else
		{
			if (std::count(addressGroupNames.begin(), addressGroupNames.end(), itor->functionName))
			{

			}
			else
			{
				addressGroupNames.push_back(itor->functionName);
			}
		}
		
	}
	
	for (vector<string>::iterator it = addressGroupNames.begin(); it != addressGroupNames.end(); ++it)
	{
		map<DWORD, DWORD> addressGroupList;
		DWORD addressGroupListCount = 0;
		for (vector<MainCore::FuncStruct>::iterator itor = MainCore::searchOutput.begin(); itor != MainCore::searchOutput.end(); itor++)
		{
			if  (itor->functionName == *it)
			{
				if (addressGroupList.count(itor->functionAddress))
				{
					addressGroupList[itor->functionAddress] ++;
					addressGroupListCount++;
				}
				else
				{
					addressGroupList.insert(map<  DWORD, DWORD>::value_type(itor->functionAddress, 1));
					addressGroupListCount++;
				}
			}
		}
		
		if (addressGroupList.size() == 1)
		{
			for (map<DWORD, DWORD>::iterator itor = addressGroupList.begin(); itor != addressGroupList.end(); itor++)
			{
				AppendLogFormat(OUTPUT, GREEN, true, "Globals::%s = Globals::hEntryBaseAddress + %s;              // [%u %%]    [%u / %u]", it->c_str(), intToHexString(itor->first).c_str(), ((itor->second * 100) / addressGroupListCount), itor->second, addressGroupListCount);
				string buffer = string(400, '\0');;
				
				sprintf(&buffer[0], "Globals::%s = Globals::hEntryBaseAddress + %s;              // [%u %%]    [%u / %u]", it->c_str(), intToHexString(itor->first).c_str(), ((itor->second * 100) / addressGroupListCount), itor->second, addressGroupListCount);
				AppendList.push_back(buffer);
				

			}
		}
		else
		{
			for (map<DWORD, DWORD>::iterator itor = addressGroupList.begin(); itor != addressGroupList.end(); itor++)
			{
				AppendLogFormat(OUTPUT, RED, true, "Globals::%s = Globals::hEntryBaseAddress + %s;              // [%u %%]    [%u / %u]", it->c_str(), intToHexString(itor->first).c_str(), ((itor->second * 100) / addressGroupListCount), itor->second, addressGroupListCount);
				string buffer = string(400, '\0');;

				sprintf(&buffer[0], "Globals::%s = Globals::hEntryBaseAddress + %s;              // [%u %%]    [%u / %u]", it->c_str(), intToHexString(itor->first).c_str(), ((itor->second * 100) / addressGroupListCount), itor->second, addressGroupListCount);
				AppendList.push_back(buffer);
			}
		}
		
		//ReadDefaultList()
	}
	vector<string> list = ReadDefaultList();
	for (vector<string>::iterator it = list.begin(); it != list.end(); ++it)
	{
		int counter = 0;
		bool isContain = false;
		for (vector<string>::iterator it2 = AppendList.begin(); it2 != AppendList.end(); ++it2)
		{
			string con = *it + " ";
			if (StringExtension::Contains(it2->c_str(), con.c_str()))
			{
				isContain = true;
				counter++;
			}

		}
		if (isContain)
		{
			for (vector<string>::iterator it2 = AppendList.begin(); it2 != AppendList.end(); ++it2)
			{
				string con = *it + " ";
				if (StringExtension::Contains(it2->c_str(), con.c_str()))
				{
					if (counter > 1)
					{
						AppendLogFormat(OUTPUT_SELECTED, RED, true, it2->c_str());
					}
					else
					{
						AppendLogFormat(OUTPUT_SELECTED, GREEN, true, it2->c_str());
					}
					
				}

			}
			
		}
		else
		{
			AppendLogFormat(OUTPUT_SELECTED, BLUE, true, "//Globals::%s = Globals::hEntryBaseAddress + %s; ", it->c_str(), 0);

		}
	}
	
	

}


DWORD CheckModuleFunctionNotJMP(DWORD address)
{

		//###################################################################################
		unsigned int decodedInstructionsCount = 0, i, next;
		_DecodeResult res;
		// Decoded instruction information.
		_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
		_DecodeType dt = Decode32Bits;
		_OffsetType offset = 0;
		res = distorm_decode(address, (const unsigned char*)address, 5, dt, decodedInstructions, 5, &decodedInstructionsCount);
		if (res == DECRES_INPUTERR) {

		}
		if (StringExtension::Equals((char*)decodedInstructions[0].mnemonic.p, "JMP"))
		{
			string s = "";
			s += (char*)decodedInstructions[0].operands.p;
			s = StringExtension::ReplaceString(s, "0x", "");
			char* p;
			DWORD n = strtol(s.c_str(), &p, 16);
			return n;
		}
		
	
	return address;
}


map< DWORD, string> CheckModuleFunctionNotJMP(map< DWORD, string> moduleFunctions)
{
	map< DWORD, string> moduleFunctions2;
	map<DWORD, string>::iterator itor = moduleFunctions.begin();
	for (; itor != moduleFunctions.end(); itor++)
	{
		//###################################################################################
				unsigned int decodedInstructionsCount = 0, i, next;
				_DecodeResult res;
				// Decoded instruction information.
				_DecodedInst decodedInstructions[MAX_INSTRUCTIONS];
				_DecodeType dt = Decode32Bits;
				_OffsetType offset = 0;
				res = distorm_decode(itor->first, (const unsigned char*)itor->first, 5, dt, decodedInstructions, 5, &decodedInstructionsCount);
				if (res == DECRES_INPUTERR) {

				}
				if (StringExtension::Equals((char*)decodedInstructions[0].mnemonic.p, "JMP"))
				{
					string s = "";
					s += (char*)decodedInstructions[0].operands.p;
					s = StringExtension::ReplaceString(s, "0x", "");
					char * p;
					DWORD n = strtol(s.c_str(), &p, 16);
					moduleFunctions2.insert(map< DWORD, string>::value_type((n), itor->second));
				}
				else
				{
					moduleFunctions2.insert(map< DWORD, string>::value_type((itor->first), itor->second));
				}
	}
	return moduleFunctions2;
}



void LogWindow::on_pushButtonDo_clicked()
{

	/*AppendTextBoxModules();*/
	

	/*AppendTreeViewModules();*/


	ui.plainTextEditLog->clear();
	ui.plainTextEditLogInstance->clear();
	ui.plainTextEditLogCall->clear();
	ui.plainTextEditLogCallVirt->clear();
	ui.plainTextEditLogString->clear();
	ui.plainTextEditLogPattern->clear();
	ui.plainTextEditLogCallInside->clear();
	ui.plainTextEditLogPointer->clear();




	ui.plainTextEditOutput->clear();
	ui.plainTextEditOutputSelected->clear();
	AsmOperations::offsetList.clear();
	
	MainCore::SetBaseAddress(true);

	string filePath = ztxtDirPathStr + ui.comboBoxServer->currentText().toStdString() + ".ztxt";
	if (!CheckTextFile(filePath.c_str()))
	{
		AppendLogFormat(LOG, RED, true, "SCANNING STOPED CHECK FILE ERRORS: %s", filePath.c_str());
	}
	else
	{
		AppendLogFormat(LOG, GREEN, true, "CHECK FILE : %s  OK", filePath.c_str());
		AppendLogFormat(LOG, GREEN, true, "BASEADDRESS  %s", intToHexString(MainCore::hEntryBaseAddress).c_str());
	}

	map< DWORD, string> moduleFunctions = CheckModuleFunctionNotJMP(MainCore::CreateModuleFunctionMap());
	
	FindOpcodeCalls(filePath.c_str(), moduleFunctions);
}
void LogWindow::AppendTreeViewModules()
{
	for (map<string, PyMethodDef*>::iterator itor = MainCore::initModulesMap.begin(); itor != MainCore::initModulesMap.end(); itor++)
	{
		if (itor->first == "zipimport")
		{
			continue;
		}		
		QStandardItem* module = new QStandardItem();
		module->setText(itor->first.c_str());		
		if (itor->second == NULL)
		{
			continue;
		}
		for (int i = 0;; i++)
		{
			if (itor->second[i].ml_name == NULL)
			{
				break;
			}
			QStandardItem* function = new QStandardItem();
			function->setText(itor->second[i].ml_name);
			module->appendRow(function);
		}

		model->appendRow(module);
	}
}
void LogWindow::AppendTextBoxModules()
{
	for (map<string, PyMethodDef*>::iterator itor = MainCore::initModulesMap.begin(); itor != MainCore::initModulesMap.end(); itor++)
	{
		if (itor->first == "zipimport")
		{
			continue;
		}
		string head = "#[  Module :  " + itor->first + " ]#";		
		AppendLog(MODULE, GREEN, true, QString::fromStdString(head));

		if (itor->second == NULL)
		{
			continue;
		}
		for (int i = 0;; i++)
		{
			if (itor->second[i].ml_name == NULL)
			{
				break;
			}
			string func = "" + string(itor->second[i].ml_name) + "		                                        " + intToHexString((DWORD)itor->second[i].ml_meth - MainCore::hEntryBaseAddress) + "";
			AppendLog(MODULE, RED, true, QString::fromStdString(func));
		}
	}
}

void LogWindow::on_pushButtonMakerMake_clicked(bool checked)
{

}

void LogWindow::on_pushButtonMakerModuleRefresh_clicked(bool checked)
{
	
}

void LogWindow::on_comboBoxMakerMethod_currentIndexChanged(const QString &arg1)
{
	
}

void LogWindow::on_treeViewModules_activated( QModelIndex &index)
{
	
}
//DWORD CheckJMP(DWORD address)
//{
//
//	BYTE byt = 0x00;
//	MemoryExtension::GetByte((void*)address, &byt);
//	if (byt == 0xE9)
//	{
//		DWORD dwr = *reinterpret_cast<DWORD*>((void*)(address+1));
//		return dwr;
//	}
//	else
//	{
//		return address;
//	}
//}
void LogWindow::on_treeViewModules_clicked(const QModelIndex &index)
{
	
	this->ui.plainTextEditOutputCall->clear();
	this->ui.plainTextEditOutputAll->clear();

	QStandardItem* column = model->itemFromIndex(index);
	
	for (map<string, PyMethodDef*>::iterator itor = MainCore::initModulesMap.begin(); itor != MainCore::initModulesMap.end(); itor++)
	{
		if ("zipimport"==  itor->first)
		{
			continue;
		}
		if(column->parent() == NULL)
		{
			continue;
		}
		string columnRoot = column->parent()->text().toStdString();

		if (columnRoot != itor->first)
		{
			continue;
		}
		

		for (int i = 0;; i++)
		{
			if (itor->second[i].ml_name == NULL)
			{
				break;
			}
			if (StringExtension::Equals(column->text().toStdString().c_str(), itor->second[i].ml_name))
			{



				vector< _DecodedInst>functionsOpInstructions;
				string importMethodName = "" + itor->first + itor->second[i].ml_name;
				DWORD sizeFuncByte = AsmOperations::GetModuleFunctionSize(importMethodName.c_str(), CheckModuleFunctionNotJMP( MainCore::CreateModuleFunctionMap()));
				functionsOpInstructions = AsmOperations::GetModuleFunctionsOpInstructions(CheckModuleFunctionNotJMP((DWORD)itor->second[i].ml_meth), sizeFuncByte, false);
				int counter = 1;
				for (vector< _DecodedInst>::iterator it = functionsOpInstructions.begin(); it != functionsOpInstructions.end(); ++it)
				{
					string functionLine = "";
					functionLine += (char*)it->mnemonic.p;

					functionLine += "  ";
					functionLine += (char*)it->operands.p;
					if (StringExtension::Equals((char*)it->mnemonic.p, "CALL"))
					{
						AppendLog(OUTPUT_ALL,GREEN,true,QString::fromStdString(functionLine));
					}
					else if (StringExtension::Equals((char*)it->mnemonic.p, "PUSH"))
					{
						AppendLog(OUTPUT_ALL, RED, true, QString::fromStdString(functionLine));
					}
					else
					{
						AppendLog(OUTPUT_ALL, BLUE, true, QString::fromStdString(functionLine));
					}
					
					if (StringExtension::Equals((char*)it->mnemonic.p, "CALL"))
					{
						string line = to_string(counter) + " CALL ";


						
						map<string, string>::iterator itor;
						string functionFoundName = "";
						if (StringExtension::Contains((char*)it->operands.p, "0x"))
						{
							for (itor = MainCore::pythonPatternFunctionsList.begin(); itor != MainCore::pythonPatternFunctionsList.end(); itor++)
							{
								string strAddress = "";
								strAddress += (char*)it->operands.p;
								strAddress = StringExtension::ReplaceString(strAddress, "0x", "");
								char* p;
								DWORD address = strtol(strAddress.c_str(), &p, 16);
								bool isContain = MemoryExtension::AddressStartWithPattern(itor->first, address );
								if (isContain)
								{
									functionFoundName = itor->second;
									break;
								}
							}
						}
						
						

						line += (char*)it->operands.p;
						line += " " + functionFoundName;
						AppendLog(OUTPUT_CALL, BLUE, true, QString::fromStdString(line));
						counter++;
					}
				}


			}
		}
	}
}

//void LogWindow::on_pushButtonDumpExecute_clicked()
//{
//	typedef bool(__thiscall* tCEterPackManagerGet)(DWORD This, void* rMappedFile, const char* c_szFileName, LPCVOID* pData);/////
//	typedef DWORD(__thiscall* tCMappedFileSize)(void* This);
//	typedef DWORD* (__thiscall* tCMappedFile)(void* This);
//	tCMappedFile CMappedFile = NULL;
//	tCMappedFileSize CMappedFileSize = NULL;
//	tCEterPackManagerGet CEterPackManagerGet = NULL;
//	
//		int* pointer;
//	pointer = (int*)malloc(1990720 * sizeof(int));
//
//	const VOID* pvData;
//	CMappedFile = (tCMappedFile)(MainCore::hEntryBaseAddress + 0x20C320);;
//	CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x20C9E0);;
//
//	DWORD h   = (*reinterpret_cast<DWORD*>(MainCore::hEntryBaseAddress + 0x1992988));
//
//
//	
//
//
//	DWORD obj = 0;
//
//	CMappedFile((void*)pointer);
//	/*DWORD k = (*reinterpret_cast<DWORD*>(obj));*/
//	CEterPackManagerGet = (tCEterPackManagerGet)(MainCore::hEntryBaseAddress + 0x131D200);
//	
//	
//		QStringList lines = ui.plainTextEditDumpImput->toPlainText().split('\n', QString::SkipEmptyParts);
//		for (int i = 0; i < lines.size(); ++i)
//		{
//			string g = lines.at(i).toStdString();
//			const char* line = g.c_str();
//			CEterPackManagerGet(h, (void*)pointer, line, &pvData);
//		}
//		
//}
void LogWindow::on_pushButtonDumpExecute_clicked()
{
	typedef bool(__thiscall* tCEterPackManagerGet2)(DWORD This, const char* c_szFileName, int a1, int a2, int a3, int a4, int a5, LPCVOID* pData, void* rMappedFile);/////
	typedef DWORD(__thiscall* tCMappedFileSize)(void* This);
	typedef DWORD* (__thiscall* tCMappedFile)(void* This);
	tCMappedFile CMappedFile = NULL;
	tCMappedFileSize CMappedFileSize = NULL;
	tCEterPackManagerGet2 CEterPackManagerGet2 = NULL;

	int* rMappedFile;
	rMappedFile = (int*)malloc(51990720 * sizeof(int));

	const VOID* pvData;
	CMappedFile = (tCMappedFile)(MainCore::hEntryBaseAddress + 0x1DCAF);;
	//CMappedFileSize = (tCMappedFileSize)(MainCore::hEntryBaseAddress + 0x20C9E0);;

	DWORD h = (*reinterpret_cast<DWORD*>(MainCore::hEntryBaseAddress + 0x1BBECB4));





	DWORD obj = 0;

	CMappedFile((void*)rMappedFile);
	/*DWORD k = (*reinterpret_cast<DWORD*>(obj));*/
	CEterPackManagerGet2 = (tCEterPackManagerGet2)(MainCore::hEntryBaseAddress + 0x22061);


	QStringList lines = ui.plainTextEditDumpImput->toPlainText().split('\n', QString::SkipEmptyParts);
	for (int i = 0; i < lines.size(); ++i)
	{
		string g = lines.at(i).toStdString();
		const char* line = g.c_str();
	

		CEterPackManagerGet2(h, line, 1, 63754643, 1, 1, 1, &pvData, (void*)rMappedFile);
	}

}

void LogWindow::on_pushButton_clicked()
{
	ui.plainTextEditOutputModules->clear();

	model->clear();
	AppendTextBoxModules();
	
	AppendTreeViewModules();
}
