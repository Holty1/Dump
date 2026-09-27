#pragma once
//if (ImGui::Button("Logout", ImVec2(60, 0)))
//{
//	//GameFunctions::NetworkStreamSendChatPacket("/logout");
//	DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x198);
//	Globals::PyCallClassMemberFunc((PyObject*)h, "OnInsertItemIcon", Py_BuildValue("(sissii)", "item", 19, "huj", "huj", 0, 1));
//}
//if (ImGui::Button("zest3", ImVec2(60, 0)))
//{
//	DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x198);
//
//
//
//
//	Globals::PyCallClassMemberFunc((PyObject*)h, "SetLoadingPhase", Py_BuildValue("()"));
//}
//if (ImGui::Button("test0", ImVec2(60, 0)))
//{
//	std::stringstream stream;
//	stream <<
//
//		PyRun_SimpleString("exec(compile(open('test.py').read(), 'test.py', 'exec'))");
//}
//if (ImGui::Button("test1", ImVec2(60, 0)))
//{
//	std::stringstream stream;
//	stream <<
//
//		PyRun_SimpleString("exec(compile(open('test1.py').read(), 'test1.py', 'exec'))");
//}
//if (ImGui::Button("test2", ImVec2(60, 0)))
//{
//	std::stringstream stream;
//	stream <<
//
//		PyRun_SimpleString("exec(compile(open('test2.py').read(), 'test2.py', 'exec'))");
//}
//if (ImGui::Button("zest4", ImVec2(60, 0)))
//{
//	/*MainForm::orbital_log_uart(0, StringExtension::DWORDToHexString(Globals::iCPythonPlayerInstance).c_str());
//	DWORD j = *reinterpret_cast<DWORD*>(Globals::iCPythonPlayerInstance + 4);
//	MainForm::orbital_log_uart(0, StringExtension::DWORDToHexString(j).c_str());*/
//	//MainForm::orbital_log_uart(0, StringExtension::DWORDToHexString(j).c_str());
//
//
//	DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x1AC);
//	/*PyCallClassMemberFunc(m_poHandler, "SetLoginPhase", Py_BuildValue("()"));
//	PyCallClassMemberFunc(m_poHandler, "SetGamePhase", Py_BuildValue("()"));*/
//	/*DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x178);*/
//	Globals::PyCallClassMemberFunc((PyObject*)h, "LoadData", Py_BuildValue("(ii)", 0, 0));
//	//Globals::PyCallClassMemberFunc((PyObject*)h, "SetSelectCharacterPhase", Py_BuildValue("()"));
//	/*Globals::PyCallClassMemberFunc((PyObject*)h, "__StartGame", Py_BuildValue("()"));*/
//
//}
//if (ImGui::Button("zest5", ImVec2(60, 0)))
//{
//	//v2[108], "BINARY_AppendNotifyMessage", v3);
//
//	/// network stream 408‬ SetGamePhase 
//	//CAccountConnector:: 228
//		//GameFunctions::NetworkStreamSendChatPacket("/logout");
//	//Globals::PyCallClassMemberFunc((PyObject*)Globals::m_poHandler, "OnLoginFailure", Py_BuildValue("(s)", "BESAMEKEY"));
//	//Globals::PyCallClassMemberFunc((PyObject*)Globals::m_poHandler, "OnConnectFailure", Py_BuildValue("()"));
//	DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x198);
//
//
//	/*DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x178);*/
//
//	Globals::PyCallClassMemberFunc((PyObject*)h, "SetSelectCharacterPhase", Py_BuildValue("()"));
//
//}
//if (ImGui::Button("zest6", ImVec2(60, 0)))
//{
//
//	DWORD h = *reinterpret_cast<DWORD*>(Globals::iCPythonNetworkStreamInstance + 0x198);
//	//Globals::PyCallClassMemberFunc((PyObject*)h, "SetSelectCharacterPhase", Py_BuildValue("()"));SetGamePhase
//	//Globals::PyCallClassMemberFunc((PyObject*)h, "SetLoadingPhase", Py_BuildValue("()"));
//
//	Globals::PyCallClassMemberFunc((PyObject*)h, "SetGamePhase", Py_BuildValue("()"));
//
//	//'PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "AppendMaterialToRefineDialog", Py_BuildValue("(ii)", rkRefineTable.materials[i].vnum, rkRefineTable.materials[i].count));
//	//PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "BINARY_SetTipMessage", Py_BuildValue("(s)", buf));
//}