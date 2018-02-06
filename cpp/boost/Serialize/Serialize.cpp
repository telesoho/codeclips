#include "stdafx.h"
#include "dna.h"
#include "variable.h"
#include "Table.h"
#include "MemAccess.h"
#include "Serialize.h"
#include "Serialize.hpp"
#include <boost/format.hpp>

static char szDirectory[MAX_PATH];


namespace c3 {
    CString Serialize::m_strDumpFolder;

    std::vector<std::string> splitpath(const std::string& str, const std::set<char> delimiters)
    {
        std::vector<std::string> result;

        char const* pch = str.c_str();
        char const* start = pch;
        for(; *pch; ++pch)
        {
            if (delimiters.find(*pch) != delimiters.end())
            {
                if (start != pch)
                {
                    std::string str(start, pch);
                    result.push_back(str);
                }
                else
                {
                    result.push_back("");
                }
                start = pch + 1;
            }
        }
        result.push_back(start);

        return result;
    }

    const char* GetExeDir() {
        if ( szDirectory[0] == 0) {
            ::GetModuleFileName(AfxGetApp()->m_hInstance, szDirectory, MAX_PATH);
            for ( int i = strlen(szDirectory) - 1; i > 0; i--) {
                if (szDirectory[i] == '\\') {
                    szDirectory[i] = 0;
                    break;
                }
            }
        }
        return szDirectory;
    }

    std::string Serialize::GetDataPath(const char * dir, const char * className, int id, int count)
    {
        return (boost::format("%s\\%s_%s_%d_%d")%GetExeDir()%dir%className%id%count).str();
    }

    BOOL Serialize::MakeFolder(const char * dir)
    {
        int ret = SHCreateDirectoryEx(NULL, dir, NULL);
        if( ret == ERROR_SUCCESS || ERROR_ALREADY_EXISTS == ret ) {
            return TRUE;
        }
        return FALSE;
    }

    std::string Serialize::getFile(const char * dir, const char * filename) {
        return (boost::format("%s\\%s.xml")%dir%filename).str();
    }

    std::string Serialize::getLogFile(const char * dir, const char * filename)
    {
        return (boost::format("%s\\%s.log.xml")%dir%filename).str();
    }


}