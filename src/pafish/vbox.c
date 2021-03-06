
#define _WIN32_WINNT 0x0501 /* _WIN32_WINNT_WINXP */

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <wbemidl.h>

#include "vbox.h"
#include "utils.h"
#include "types.h"

/**
* SCSI registry key check
**/
int vbox_reg_key1()
{
	return pafish_exists_regkey_value_str(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 0\\Target Id 0\\Logical Unit Id 0", "Identifier", "VBOX");
}

/**
* SystemBiosVersion registry key check
**/
int vbox_reg_key2()
{
	return pafish_exists_regkey_value_str(HKEY_LOCAL_MACHINE, "HARDWARE\\Description\\System", "SystemBiosVersion", "VBOX");
}

/**
* VirtualBox Guest Additions key check
**/
int vbox_reg_key3()
{
	return pafish_exists_regkey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Oracle\\VirtualBox Guest Additions");
}

/**
* VideoBiosVersion key check
**/
int vbox_reg_key4()
{
	return pafish_exists_regkey_value_str(HKEY_LOCAL_MACHINE, "HARDWARE\\Description\\System", "VideoBiosVersion", "VIRTUALBOX");
}

/**
* ACPI Regkey detection
**/
int vbox_reg_key5()
{
	return pafish_exists_regkey(HKEY_LOCAL_MACHINE, "HARDWARE\\ACPI\\DSDT\\VBOX__");
}

/**
* FADT ACPI Regkey detection
**/
int vbox_reg_key7()
{
	return pafish_exists_regkey(HKEY_LOCAL_MACHINE, "HARDWARE\\ACPI\\FADT\\VBOX__");
}

/**
* RSDT ACPI Regkey detection
**/
int vbox_reg_key8()
{
	return pafish_exists_regkey(HKEY_LOCAL_MACHINE, "HARDWARE\\ACPI\\RSDT\\VBOX__");
}

/**
* VirtualBox Services Regkey detection
**/
int vbox_reg_key9()
{
	int res = FALSE, i;

	string strs[5];
	strs[0] = "SYSTEM\\ControlSet001\\Services\\VBoxGuest";
	strs[1] = "SYSTEM\\ControlSet001\\Services\\VBoxMouse";
	strs[2] = "SYSTEM\\ControlSet001\\Services\\VBoxService";
	strs[3] = "SYSTEM\\ControlSet001\\Services\\VBoxSF";
	strs[4] = "SYSTEM\\ControlSet001\\Services\\VBoxVideo";
	for (i = 0; i < 5; i++)
	{
		if (pafish_exists_regkey(HKEY_LOCAL_MACHINE, strs[i]))
		{
			res = TRUE;
		}
	}
	return res;
}

/**
* HARDWARE\\DESCRIPTION\\System SystemBiosDate == 06/23/99
**/
int vbox_reg_key10()
{
	return pafish_exists_regkey_value_str(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System", "SystemBiosDate", "06/23/99");
}

/**
* VirtualBox driver files in \\WINDOWS\\system32\\drivers\\
**/
int vbox_sysfile1()
{
	string strs[4];
	int res = FALSE, i = 0;

	strs[0] = "C:\\WINDOWS\\system32\\drivers\\VBoxMouse.sys";
	strs[1] = "C:\\WINDOWS\\system32\\drivers\\VBoxGuest.sys";
	strs[2] = "C:\\WINDOWS\\system32\\drivers\\VBoxSF.sys";
	strs[3] = "C:\\WINDOWS\\system32\\drivers\\VBoxVideo.sys";
	for (i = 0; i < 4; i++)
	{
		if (pafish_exists_file(strs[i]))
		{
			res = TRUE;
		}
	}
	return res;
}

/**
* VirtualBox other system files
**/
int vbox_sysfile2()
{
	string strs[14];
	int res = FALSE, i = 0;

	strs[0] = "C:\\WINDOWS\\system32\\vboxdisp.dll";
	strs[1] = "C:\\WINDOWS\\system32\\vboxhook.dll";
	strs[2] = "C:\\WINDOWS\\system32\\vboxmrxnp.dll";
	strs[3] = "C:\\WINDOWS\\system32\\vboxogl.dll";
	strs[4] = "C:\\WINDOWS\\system32\\vboxoglarrayspu.dll";
	strs[5] = "C:\\WINDOWS\\system32\\vboxoglcrutil.dll";
	strs[6] = "C:\\WINDOWS\\system32\\vboxoglerrorspu.dll";
	strs[7] = "C:\\WINDOWS\\system32\\vboxoglfeedbackspu.dll";
	strs[8] = "C:\\WINDOWS\\system32\\vboxoglpackspu.dll";
	strs[9] = "C:\\WINDOWS\\system32\\vboxoglpassthroughspu.dll";
	strs[10] = "C:\\WINDOWS\\system32\\vboxservice.exe";
	strs[11] = "C:\\WINDOWS\\system32\\vboxtray.exe";
	strs[12] = "C:\\WINDOWS\\system32\\VBoxControl.exe";
	strs[13] = "C:\\program files\\oracle\\virtualbox guest additions\\";
	for (i = 0; i < 14; i++)
	{
		if (pafish_exists_file(strs[i]))
		{
			res = TRUE;
		}
	}
	return res;
}

/**
* NIC MAC check
**/
int vbox_mac()
{
	/* VirtualBox mac starts with 08:00:27 */
	return pafish_check_mac_vendor("\x08\x00\x27");
}

/**
* VirtualBox devices
**/
int vbox_devices()
{
	HANDLE h;
	string strs[4];
	int res = FALSE, i = 0;

	/* Got this list from https://github.com/cuckoobox/community/blob/master/modules/signatures/antivm_vbox_devices.py */
	strs[0] = "\\\\.\\VBoxMiniRdrDN";
	strs[1] = "\\\\.\\pipe\\VBoxMiniRdDN";
	strs[2] = "\\\\.\\VBoxTrayIPC";
	strs[3] = "\\\\.\\pipe\\VBoxTrayIPC";
	for (i = 0; i < 4; i++)
	{
		h = CreateFile(strs[i], GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (h != INVALID_HANDLE_VALUE)
		{
			res = TRUE;
		}
	}
	return res;
}

/**
* Checking for Tray window
* https://twitter.com/waleedassar
**/
int vbox_traywindow()
{
	HWND h1, h2;
	h1 = FindWindow("VBoxTrayToolWndClass", NULL);
	h2 = FindWindow(NULL, "VBoxTrayToolWnd");
	if (h1 || h2)
		return TRUE;
	else
		return FALSE;
}

/**
* Checking network shared
* https://twitter.com/waleedassar
**/
int vbox_network_share()
{
	unsigned long pnsize = 0x1000;
	char provider[0x1000];
	/* a0rtega : any reason for this to be in the heap :?, changed to stack */
	//char * provider = (char *)LocalAlloc(LMEM_ZEROINIT, pnsize);

	int retv = WNetGetProviderName(WNNC_NET_RDR2SAMPLE, provider, &pnsize);
	if (retv == NO_ERROR)
	{
		if (lstrcmpi(provider, "VirtualBox Shared Folders") == 0)
		{
			//LocalFree(provider);
			return TRUE;
		}
		else
		{
			//LocalFree(provider);
			return FALSE;
		}
	}
	return FALSE;
}

/**
* Checking for virtual box processes
**/
int vbox_processes()
{
	int res = FALSE;
	HANDLE hpSnap;
	PROCESSENTRY32 pentry;

	hpSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hpSnap != INVALID_HANDLE_VALUE)
	{
		pentry.dwSize = sizeof(PROCESSENTRY32);
	}
	else
	{
		return FALSE;
	}

	if (!Process32First(hpSnap, &pentry))
	{
		CloseHandle(hpSnap);
		return FALSE;
	}

	do
	{
		if (lstrcmpi(pentry.szExeFile, "vboxservice.exe") == 0)
		{
			res = TRUE;
		}
		if (lstrcmpi(pentry.szExeFile, "vboxtray.exe") == 0)
		{
			res = TRUE;
		}
	} while (Process32Next(hpSnap, &pentry));
	return res;
}

/**
 * Check if the device identifier ("PCI\\VEN_80EE&DEV_CAFE") in the returned rows.
 */
int vbox_wmi_check_row(IWbemClassObject *row)
{
	CIMTYPE type = CIM_ILLEGAL;
	VARIANT value;

	HRESULT hresult = row->lpVtbl->Get(row, L"DeviceId", 0, &value, &type, 0);

	if (FAILED(hresult) || V_VT(&value) == VT_NULL || type != CIM_STRING)
	{
		return FALSE;
	}

	return (wcsstr(V_BSTR(&value), L"PCI\\VEN_80EE&DEV_CAFE") != NULL) ? TRUE : FALSE;
}

/**
 * Check for devices VirtualBox devices using WMI.
 */
int vbox_wmi_devices()
{
	IWbemServices *services = NULL;

	if (wmi_initialize(L"root\\cimv2", &services) != TRUE)
	{
		return FALSE;
	}

	int result = wmi_check_query(services, L"WQL", L"SELECT DeviceId FROM Win32_PnPEntity",
								 &vbox_wmi_check_row);

	wmi_cleanup(services);

	return result;
}
