/* Vbbot_base.h - ViewBar Bot Base functions */

#include <fstream.h>
/*void getURLS (CStringArray & URLS, CString filename) { // filename includes path

	CFile file;
	CFileException exception;
	UINT BytesRead;
	UINT CompVal;
	CString tmpString;

	if (!file.Open (filename, CFile::modeReadWrite, &exception)) {
		// * pMessage = "File could not be opened.";
		::MessageBox (NULL, "Error while opening file", "Error", MB_OK);
	}

	char Buffer [65535];
	BytesRead = file.Read (Buffer, 65535);
	while (CompVal < BytesRead + 1) {

		while (!(Buffer[CompVal] == ',')) {

			tmpString += Buffer[CompVal];
			
		}
		URLS.Add(tmpString);
		CompVal++;
		tmpString = "";
	}
}*/

void getURLS (CStringArray & URLS, CString filename) {

	CString tmpString;
	ifstream in (filename);
	char Buffer [500];
	while (in.getline (Buffer, 500));
	int i = 0;
	if (!(Buffer[i] == '0')) {
		while (!(Buffer[i] == '0')) {
		
			while (!(Buffer[i] == ',' || Buffer[i] == '0')) {
					tmpString += Buffer[i];
					i++;
			}
			URLS.Add(tmpString);
			i++;
			tmpString = "";
		}
	}
	else
		::MessageBox (NULL, "File List is empty.","Error",MB_OK|MB_ICONEXCLAMATION);
}