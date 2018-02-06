#pragma once


template<class Archive>
void serialize(Archive & ar, ND_PCSDATA& nd_pcsdata, const unsigned int version)
{
    ar & _S(nd_pcsdata.no);          // ノードNo
    ar & _S(nd_pcsdata.vol);
    ar & _S(nd_pcsdata.P);
    ar & _S(nd_pcsdata.Q);
}


template<class Archive>
void serialize(Archive & ar, BR_PCSDATA& br_pcsdata, const unsigned int version)
{
    ar & _S(br_pcsdata.no);   // ブランチNo
    ar & _S(br_pcsdata.cur);
    ar & _S(br_pcsdata.pir);
}


template<class Archive>
void serialize(Archive & ar, SVR_PCSDATA& svr_pcsdata, const unsigned int version)
{
    ar & _S(svr_pcsdata.no);   // SVRNo
    ar & _S(svr_pcsdata.cur);
    ar & _S(svr_pcsdata.pir);
}


template<class Archive>
void serialize(Archive & ar, TVR_PCSDATA& tvr_pcsdata, const unsigned int version)
{
    ar & _S(tvr_pcsdata.no);   // TVRNo
    ar & _S(tvr_pcsdata.cur);
    ar & _S(tvr_pcsdata.pir);
}

template<class Archive>
void serialize(Archive & ar, PCSDATA_EXL& pcsdata_exl, const unsigned int version)
{
    ar & _S(pcsdata_exl.max_node_no);
    ar & _S(pcsdata_exl.max_bf);
    ar & _S(pcsdata_exl.max_af);
    ar & _S(pcsdata_exl.max_riki);
    ar & _S(pcsdata_exl.node_bf);
    ar & _S(pcsdata_exl.node_af);
    ar & _S(pcsdata_exl.node_riki);
    ar & _S(pcsdata_exl.use);
}

template<class Archive>
void serialize(Archive & ar, NODEN& noden, const unsigned int version)
{
    ar & _S(noden.id);// DNA node_tのNo.
    ar & _S(noden.name);
    ar & _S(noden.use_flg); // 対象であれば1, 
    ar & _S(noden.tap); // 変圧器タップ比
    ar & _S(noden.vol_pu); // [2]→整定前、後、[LOOP_NUM]→重負荷分散電源あり、なし、軽負荷　あり、なし 100V系
}


template<class Archive>
void serialize(Archive & ar, SEITEI& seitei, const unsigned int version)
{
    ar & _S(seitei.max_node);   // 対象ノード数
    ar & _SN(NODEN,seitei.node,seitei.max_node);

    ar & _S(seitei.max_vol); // 集約した最大電圧 100V系
    ar & _S(seitei.max_id);
    ar & _S(seitei.min_vol); // 集約した最小電圧 100V系
    ar & _S(seitei.min_id);
    // 整定結果
    ar & _S(seitei.irc);
    ar & _S(seitei.min_jiko_ohm_r);
    ar & _S(seitei.min_jiko_ohm_x);
    ar & _S(seitei.max_jiko_ohm_r);
    ar & _S(seitei.max_jiko_ohm_x);
    ar & _S(seitei.min_kijyun_vol);
    ar & _S(seitei.max_kijyun_vol);

    ar & _S(seitei.err_node_id); // エラー対象ノードID
    ar & _S(seitei.err_node_name); // エラー対象ノード名称
    ar & _S(seitei.err_vol); //エラー電圧値
    ar & _S(seitei.err_type); // 重負荷、軽負荷、発電機あり、なしの番号
    ar & _S(seitei.err_type_info1);
    ar & _S(seitei.err_type_info2);
    ar & _S(seitei.err_type_info3); // エラー時期
    ar & _S(seitei.err_type_info4); // Add 20070312 S.S エラーの上限、下限情報 

}

template<class Archive>
void serialize(Archive & ar, CString& s, const unsigned int version)
{
    std::string cstring(s);
    ar & _S(cstring);
    s = cstring.c_str();
}

