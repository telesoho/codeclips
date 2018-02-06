#pragma once

#include <set>
#include <fstream>
#include <iomanip>
#include "log_archive.hpp"

#define _S(name)                                                \
    boost::serialization::make_nvp(BOOST_PP_STRINGIZE(name), name)

#define _SN(_t, _v, _n)                                                \
    boost::serialization::make_nvp(BOOST_PP_STRINGIZE(_v), boost::serialization::make_array<_t>(_v, _n))

#define _SLOG(msg)                                               \
{\
    std::ofstream ofs;\
    ofs.open ((boost::format("%s\\debug.log")%c3::GetExeDir()).str().c_str(), std::ofstream::out | std::ofstream::app);\
    ofs << msg << std::endl;\
}

#define INPUT_DIR       ("DNAData\\Input")
#define RESULT_DIR      ("DNAData\\Result")

#define DUMP_LEVEL (3)

#define DUMP(_v)        c3::dump(6, #_v, _v, __FILE__, __LINE__)
#define DUMP6(_v)        c3::dump(6, #_v, _v, __FILE__, __LINE__)
#define DUMP5(_v)        c3::dump(5, #_v, _v, __FILE__, __LINE__)
#define DUMP4(_v)        c3::dump(4, #_v, _v, __FILE__, __LINE__)
#define DUMP3(_v)        c3::dump(3, #_v, _v, __FILE__, __LINE__)
#define DUMP2(_v)        c3::dump(2, #_v, _v, __FILE__, __LINE__)
#define DUMP1(_v)        c3::dump(1, #_v, _v, __FILE__, __LINE__)

#define DUMP_XML(_v)     c3::Serialize::DumpXML(#_v, _v, __FILE__, __LINE__)
#define DUMP_TABLE_XML(_v, _n)     c3::Serialize::DumpXML(#_v, _v, _n, __FILE__, __LINE__)


#define DUMPX(_v)        c3::dumpX(3, #_v, _v, __FILE__, __LINE__)
#define DUMPX6(_v)        c3::dumpX(6, #_v, _v, __FILE__, __LINE__)
#define DUMPX5(_v)        c3::dumpX(5, #_v, _v, __FILE__, __LINE__)
#define DUMPX4(_v)        c3::dumpX(4, #_v, _v, __FILE__, __LINE__)
#define DUMPX3(_v)        c3::dumpX(3, #_v, _v, __FILE__, __LINE__)
#define DUMPX2(_v)        c3::dumpX(2, #_v, _v, __FILE__, __LINE__)
#define DUMPX1(_v)        c3::dumpX(1, #_v, _v, __FILE__, __LINE__)

namespace c3 {
    std::vector<std::string> splitpath(const std::string& str, const std::set<char> delimiters);

    template<typename T>
    static void dump(int level, const char * vName, const T& v, const char * fname, int lineNum) {
        if (level > DUMP_LEVEL) {
            return;
        }
        CString folder;
        folder.Format("%s\\DNAData", c3::GetExeDir());
        if ( c3::Serialize::MakeFolder(folder) ) {
            std::set<char> delims;
            delims.insert('\\');
            std::vector<std::string> path = splitpath(fname, delims);
            std::string logFileName = path.back();
            std::ofstream ofs;
            ofs.open ((boost::format ("%s\\%s.log") % folder%"unit_test").str ().c_str (), std::ofstream::out | std::ofstream::app);
            ofs << fname << "(" << lineNum << "):" << vName << "=" << std::setprecision(9) << v << std::endl;
        }
    }

    template<typename T, size_t n>
    static void dump (int level, const char * vName, const T (&v)[n], const char * fname, int lineNum) {
        if (level > DUMP_LEVEL) {
            return;
        }
        CString vArrayName;
        for (int i = 0; i < n; i++) {
            vArrayName.Format ("%s[%d]", vName, i);
            c3::dump (level, vArrayName, v[i], fname, lineNum);
        }
    }

    template<typename T>
    static void dumpX (int level, const char * vName, const T& v, const char * fname, int lineNum) {
        if (level > DUMP_LEVEL) {
            return;
        }
        CString folder;
        folder.Format ("%s\\DNAData", c3::GetExeDir ());
        if (c3::Serialize::MakeFolder (folder)) {
            std::set<char> delims;
            delims.insert ('\\');
            std::vector<std::string> path = splitpath (fname, delims);
            std::string logFileName = path.back ();
            std::ofstream ofs;
            ofs.open ((boost::format("%s\\%s.log")%folder%logFileName .c_str()).str().c_str(), std::ofstream::out | std::ofstream::app);
            ofs << fname << "(" << lineNum << "):" << vName << "=" << std::setprecision (9) << v << std::endl;
        }
    }

    template<typename T, size_t n>
    static void dumpX(int level, const char * vName, const T (&v)[n], const char * fname, int lineNum) {
        if (level > DUMP_LEVEL) {
            return;
        }
        CString vArrayName;
        for(int i = 0; i < n; i++) {
            vArrayName.Format("%s[%d]", vName, i);
            c3::dumpX(level, vArrayName, v[i], fname, lineNum);
        }
    }

    const char * GetExeDir();
    class Serialize {
        static std::string getFile(const char * dir, const char * filename);
        static std::string getLogFile(const char * dir, const char * filename);

        void saveTables(const char * p_dir);
        void saveValues(const char * p_dir);

        void loadTables(const char * p_dir);
        void loadValues(const char * p_dir);

        static std::string GetDataPath(const char * dir, const char * className, int id, int count);
        static CString m_strDumpFolder;
    public:
        static BOOL MakeFolder(const char * dir);

        template<typename T>
        static void DumpXML(const char * vName, T& v, const char * fname, int lineNum) 
        {
            std::ofstream ofs;
            std::ofstream ofslog;
            CString osfile = c3::Serialize::getFile(m_strDumpFolder, vName).c_str();
            CString logfile = c3::Serialize::getLogFile(m_strDumpFolder, vName).c_str();
            ofs.open(osfile);
            ofslog.open(logfile);

            if(ofs.fail()) throw std::exception(osfile);
            if(ofslog.fail()) throw std::exception(logfile);

            boost::archive::xml_oarchive oa(ofs);
            log_archive oalog(ofslog);
            oa & boost::serialization::make_nvp(vName, v);
            oalog & boost::serialization::make_nvp(vName, v);
        }

        template<typename T>
        static void DumpXML(const char * vName, T* v, int& size, const char * fname, int lineNum) 
        {
            std::ofstream ofs;
            std::ofstream ofslog;
            CString osfile = c3::Serialize::getFile(m_strDumpFolder, vName).c_str();
            CString logfile = c3::Serialize::getLogFile(m_strDumpFolder, vName).c_str();
            ofs.open(osfile);
            ofslog.open(logfile);

            if(ofs.fail()) throw std::exception(osfile);
            if(ofslog.fail()) throw std::exception(logfile);

            boost::archive::xml_oarchive oa(ofs);
            log_archive oalog(ofslog);
            oa & _S(size);
            oa & boost::serialization::make_nvp(vName, boost::serialization::make_array<T>(v, size));
            oalog & _S (size);
            oalog & boost::serialization::make_nvp(vName, boost::serialization::make_array<T>(v, size));
        }

        static BOOL SetDumpFolder(const char * dir,               /* 出力フォルダ */
                         const char * className,
                         int id,
                         int count)
        {
            m_strDumpFolder = GetDataPath(dir, className, id, count).c_str();
            return MakeFolder(m_strDumpFolder);
        }


        void SaveData(const char * dir,               /* 出力フォルダ */
                         const char * className,
                         int id,
                         int count
                         );                              /* 共通変数をダンプする */
    };

}