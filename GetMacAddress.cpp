http://study.marearts.com/2017/01/get-mac-address-in-mfc.html
//https://docs.microsoft.com/en-us/windows/desktop/api/iphlpapi/nf-iphlpapi-getadaptersinfo
//Requirements 	 
//Header	iphlpapi.h
//Library	Iphlpapi.lib
//DLL		Iphlpapi.dll
CString GetMACAddress()
{
	CString strGateWay = _T("");
	CString strMACAddress = _T("");
	IP_ADAPTER_INFO ipAdapterInfo[5];
	DWORD dwBuflen = sizeof(ipAdapterInfo);

	DWORD dwStatus = GetAdaptersInfo(ipAdapterInfo, &dwBuflen);
	if (dwStatus != ERROR_SUCCESS)
	{
		strMACAddress.Format(_T("Error for GetAdaptersInfo : %d"), dwStatus);
		AfxMessageBox(strMACAddress);
		return _T("");
	}
	PIP_ADAPTER_INFO pIpAdapterInfo = ipAdapterInfo;
	do{
		strGateWay = (CString)pIpAdapterInfo->GatewayList.IpAddress.String;
		if (strGateWay[0] == '0')
		{
			pIpAdapterInfo = pIpAdapterInfo->Next;
		}
		else
		{
			strMACAddress.Format(_T("%02X-%02X-%02X-%02X-%02X-%02X"),
				pIpAdapterInfo->Address[0],
				pIpAdapterInfo->Address[1],
				pIpAdapterInfo->Address[2],
				pIpAdapterInfo->Address[3],
				pIpAdapterInfo->Address[4],
				pIpAdapterInfo->Address[5]
				);

			break;
		}
	} while (pIpAdapterInfo);

	return strMACAddress;
}