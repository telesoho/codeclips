#include "stdafx.h"

#include "dna.h"
#include "variable.h"
#include "Table.h"
#include "MemAccess.h"
#include "Serialize.h"
#include "Serialize.hpp"
#include "log_archive.hpp"

using namespace boost::serialization;


#define OPEN_FILE(v)                                            \
    std::ofstream ofs;                                          \
    std::ofstream ofslog;                                       \
    CString filename = Serialize::getFile(p_dir, #v).c_str();   \
    _SLOG(filename);                                            \
    CString logfile = Serialize::getLogFile(p_dir, #v).c_str(); \
    _SLOG(logfile);                                             \
    ofs.open(filename);                                         \
    ofslog.open(logfile);                                       \
    if(ofs.fail()) throw std::exception(filename);              \
    if(ofslog.fail()) throw std::exception(logfile);            \
    boost::archive::xml_oarchive oa(ofs);                       \
    log_archive oalog(ofslog)


#define SAVE_VALUABLE(v)                                        \
{                                                               \
    oa & _S(v);                                                 \
    oalog & _S(v);                                              \
}


#define SAVE_TABLE(_v)                                          \
{                                                               \
    OPEN_FILE(_v);                                              \
    oa & _S(_v);                                                \
    oalog & _S(_v);                                             \
}

#define SAVE_TABLE_MAX(_t,_v,_n)                                \
{                                                               \
    OPEN_FILE(_v);                                              \
    oa & _S(_n);                                                \
    oalog & _S(_n);                                             \
    if ( _n > 0) {                                              \
        if( _v != NULL ) {                                      \
            bool is_null = false;                               \
            oa & _S(is_null);                                   \
            oa & make_nvp(#_v, make_array<_t>(_v,_n));          \
            oalog & make_nvp(#_v, make_array<_t>(_v,_n));       \
        } else {                                                \
            bool is_null = true;                                \
            oa & _S(is_null);                                   \
            oalog & _S(is_null);                                \
            oa & _S(_v);                                        \
            oalog & _S(_v);                                     \
        }                                                       \
    }                                                           \
}

#define SAVE_TABLE_MAX_1(_t,_v,_n)                              \
{                                                               \
    OPEN_FILE(_v);                                              \
    oa & _S(_n);                                                \
    oalog & _S(_n);                                             \
    if ( _n >= 0) {                                             \
        if( _v != NULL ) {                                      \
            bool is_null = false;                               \
            oa & _S(is_null);                                   \
            oa & make_nvp(#_v, make_array<_t>(_v,_n+1));        \
            oalog & make_nvp(#_v, make_array<_t>(_v,_n+1));     \
        } else {                                                \
            bool is_null = true;                                \
            oa & _S(is_null);                                   \
            oalog & _S(is_null);                                \
            oa & _S(_v);                                        \
            oalog & _S(_v);                                     \
        }                                                       \
    }                                                           \
}


#define SAVE_RESULT_TABLE(_t, _v, _n)                           \
{                                                               \
    OPEN_FILE(_v);                                              \
    int count = sizeof(_v) / sizeof(_t*);                       \
    oa & _S(count);                                             \
    oa & _S(_n);                                                \
    oalog & _S(count);                                          \
    oalog & _S(_n);                                             \
    for( int i=0; i<count; i++) {                               \
        if (_v[i] != NULL) {                                    \
            bool is_null = false;                               \
            oa & _S(is_null);                                   \
            _t* p = _v[i];                                      \
            oa & make_nvp(#_v, make_array<_t>(p,_n));           \
            oalog & make_nvp(#_v, make_array<_t>(p,_n));        \
        } else {                                                \
            bool is_null = true;                                \
            oa & _S(is_null);                                   \
            oalog & _S(is_null);                                \
            oa & _S(_v);                                        \
            oalog & _S(_v);                                     \
        }                                                       \
    }                                                           \
}

namespace c3 {
void Serialize::saveTables(const char * p_dir)
{

    SAVE_TABLE_MAX_1(NODE, node_t, nmax);

    SAVE_TABLE(ArrayDevice);

    /* CalEndStep[3] */
    SAVE_TABLE(CalEndStep);

    SAVE_TABLE_MAX_1(DK_T0, DK_t, dk_max);

    /* DefLowVol */
    SAVE_TABLE(DefLowVol);

    /* DefRikirituL */
    SAVE_TABLE(DefRikirituL);

    /* GenCap */
    SAVE_TABLE(GenCap);

    /* PcsSeitei */
    SAVE_TABLE(PcsSeitei);

    SAVE_TABLE_MAX_1(SSC, SSC_t, sscmax);

    SAVE_TABLE_MAX_1(SSR, SSR_t, ssrmax);

    SAVE_TABLE_MAX_1(SVR, svr_t, svrmax);

    /* SVR_Impedance[4] */
    SAVE_TABLE(SVR_Impedance);

    /* SeiteiCap */
    SAVE_TABLE(SeiteiCap);

    /* TermsGen */
    SAVE_TABLE(theApp.TermsGen);

    /* TermsLoad */
    SAVE_TABLE(theApp.TermsLoad);

    SAVE_TABLE_MAX_1(BANK_T, bank_t, bank_max);

    SAVE_TABLE_MAX_1(BRANCH, branch_t, bmax);

    SAVE_TABLE_MAX(CABLE_DB, cable_DB_t, cdb_max);

    SAVE_TABLE_MAX_1(FEEDER_T, feeder_t, feeder_max);

    SAVE_TABLE(flicker);

    SAVE_RESULT_TABLE(structResLfacBranch, g_rstAC_Branch, num_rstLfacBranch);

    SAVE_RESULT_TABLE(structResLfacNode, g_rstAC_Node, num_rstLfacNode);

    /* g_rstAC_SVC[3] */
    SAVE_RESULT_TABLE(structResLfacSVC, g_rstAC_SVC, num_rstLfacSVC);

    /* g_rstAC_SVR[3] */
    SAVE_RESULT_TABLE(structResLfacSVR, g_rstAC_SVR, num_rstLfacSVR);

    /* g_rstAC_TVR[3] */
    SAVE_RESULT_TABLE(structResLfacTVR, g_rstAC_TVR, num_rstLfacTVR);

    /* g_rstFlicNode */
    SAVE_TABLE_MAX(structResFlicNode, g_rstFlicNode, num_rstLfacNode);

    SAVE_TABLE_MAX(structResLfscBranch, g_rstLfscBranch, num_rstLfscBranch);

    SAVE_TABLE_MAX(structResLfscNode, g_rstLfscNode, num_rstLfscNode);

    SAVE_TABLE_MAX_1(GEN, gen_t, gmax);

    SAVE_TABLE(hogo);

    /* structActSVR  *g_actSVR */
    SAVE_TABLE_MAX(structActSVR, g_actSVR, num_actSVR);

    SAVE_TABLE_MAX(structActTVR, g_actTVR, num_actTVR);

    SAVE_TABLE_MAX(structWorkBranch, g_wkBranch, num_wkBranch);

    SAVE_TABLE_MAX(structWorkGen, g_wkGen, num_wkGen);

    SAVE_TABLE_MAX(structWorkLoad, g_wkLoad, num_wkLoad);

    SAVE_TABLE_MAX(structWorkNode, g_wkNode, num_wkNode);

    SAVE_TABLE_MAX(structWorkSSC, g_wkSSC, num_wkSSC);

    SAVE_TABLE_MAX(structWorkSSR, g_wkSSR, num_wkSSR);

    SAVE_TABLE_MAX(structWorkSVC, g_wkSVC, num_wkSVC);

    SAVE_TABLE_MAX(structWorkSVR, g_wkSVR, num_wkSVR);

    SAVE_TABLE_MAX(structWorkTVR, g_wkTVR,num_wkTVR);

    SAVE_TABLE(theApp.ksDen);

    SAVE_TABLE(theApp.ksKou);

    SAVE_TABLE(theApp.ksSVR);

    SAVE_TABLE(theApp.ksTVR);

    SAVE_TABLE_MAX_1(LOAD, load_t, lmax);

    SAVE_TABLE(luminous);

    /* m_wkBranch[65536*2] */
    SAVE_TABLE_MAX(BOOL, theApp.m_wkBranch, num_wkBranch);

    /* m_wkNode[65536*2] */
    SAVE_TABLE_MAX(BOOL, theApp.m_wkNode, num_wkNode);

    /* m_wkSvr[512] */
    SAVE_TABLE_MAX(BOOL, theApp.m_wkSvr, num_wkSVR);

    /* m_wkTvr[512] */
    SAVE_TABLE_MAX(BOOL, theApp.m_wkTvr, num_wkTVR);

    /* rectwave */
    SAVE_TABLE(rectwave);

    SAVE_TABLE(rstBankSC);

    SAVE_TABLE_MAX_1(SVC, svc_t, svcmax);

    SAVE_TABLE_MAX(SVR_DB, svr_DB_t, svrdb_max);

    /* svrtap_DB_t[SVRTAPDB_MAX] */
    SAVE_TABLE_MAX(SVRTAP_DB, svrtap_DB_t, svrtapdb_max);

    SAVE_TABLE(t_SelectNode);

    SAVE_TABLE_MAX(TVR_DB, tvr_DB_t, tvrdb_max);

    SAVE_TABLE_MAX_1(TVR, tvr_t, tvrmax);

    SAVE_TABLE_MAX(TVRTAP_DB, tvrtap_DB_t, tvrtapdb_max);

    SAVE_TABLE_MAX_1(VECTOR, vector_t, vmax);

    SAVE_TABLE_MAX_1(short, wkBranchDir, bmax);

    SAVE_TABLE(theApp.m_DevPattern);

    SAVE_TABLE(theApp.m_Route);

    SAVE_TABLE(theApp.m_RouteFCB);

}

/*
template<T>
save_result_table(int c, T * v, n)
{
OPEN_FILE(g_rstAC_Branch);
CString nvp;
int count = c;
oa << _S(n);
oa << _S(count);
for( int i=0; i<count; i++) {
nvp.Format("%s_%d", "g_rstAC_Branch", i);
if (v[i] != NULL) {
T* p = g_rstAC_Branch[i];
oa << make_nvp(nvp, make_array<T>(p,num_rstLfacBranch));
} else {
bool is_null = false;
oa << make_nvp(nvp, is_null);
}
}

}
*/
void Serialize::saveValues(const char * p_dir)
{

    OPEN_FILE(variables);

    /* Base */
    SAVE_VALUABLE(Base);

    /* CalEndFlicker */
    SAVE_VALUABLE(CalEndFlicker);

    /* CalEndGen */
    SAVE_VALUABLE(CalEndGen);

    /* CalEndGenryuX */
    SAVE_VALUABLE(CalEndGenryuX);

    /* CalEndPcsSeitei */
    SAVE_VALUABLE(CalEndPcsSeitei);

    /* CalEndSC */
    SAVE_VALUABLE(CalEndSC);

    /* CalEndStepJJ */
    SAVE_VALUABLE(CalEndStepJJ);

    /* CalEndStepSJ */
    SAVE_VALUABLE(CalEndStepSJ);

    /* CalFile */
    SAVE_VALUABLE(CalFile);

    /* CalNumFlicker */
    SAVE_VALUABLE(CalNumFlicker);

    /* CalNumFlickerOwnLoad */
    SAVE_VALUABLE(CalNumFlickerOwnLoad);

    /* CalNumJyoji */
    SAVE_VALUABLE(CalNumJyoji);

    /* CalNumSC */
    SAVE_VALUABLE(CalNumSC);

    /* CalNumSyunji */
    SAVE_VALUABLE(CalNumSyunji);

    /* CalSoFlickerAther */
    SAVE_VALUABLE(CalSoFlickerAther);

    /* CalSoFlickerOwn */
    SAVE_VALUABLE(CalSoFlickerOwn);

    /* Cal_EPC */
    SAVE_VALUABLE(Cal_EPC);

    /* Cal_ITR */
    SAVE_VALUABLE(Cal_ITR);

    /* DefRikirituG */
    SAVE_VALUABLE(DefRikirituG);

    /* FileVersion */
    SAVE_VALUABLE(FileVersion);

    /* GenryuXBranch */
    SAVE_VALUABLE(GenryuXBranch);

    /* LfSC_Gen */
    SAVE_VALUABLE(LfSC_Gen);

    /* LoadMode */
    SAVE_VALUABLE(LoadMode);

    /* OperationMode */
    SAVE_VALUABLE(OperationMode);

    /* ParentOperationMode */
    SAVE_VALUABLE(ParentOperationMode);

    /* SetArea */
    SAVE_VALUABLE(SetArea);

    /* SyunjiTeigiSec */
    SAVE_VALUABLE(SyunjiTeigiSec);

    /* ViewReasonableRange */
    SAVE_VALUABLE(ViewReasonableRange);

    /* dGenryuX */
    SAVE_VALUABLE(dGenryuX);

    SAVE_VALUABLE(swingno);

    SAVE_VALUABLE(t_SetTapNo);

}


/*============================================================================
* PROCESS NAME   : Serialize::SaveData
* DESCRIPTION    : 
* CALL INTERFACE : const char * dir
* RETRUN         : void 
*============================================================================*/
void Serialize::SaveData(const char * dir,               /* 出力フォルダ */
                         const char * className,
                         int id,
                         int count
                         )                              /* 共通変数をダンプする */
{
    try {
        CString folder = GetDataPath(dir, className, id, count).c_str();
        if ( MakeFolder(folder)) {
            saveValues(folder);
            saveTables(folder);
        }
    }catch(std::exception e) {
        AfxMessageBox(e.what());
    }
}

}