#pragma once

template<class Archive>
void serialize(Archive & ar, CString& s, const unsigned int version)
{
    std::string cstring(s);
    ar & _S(cstring);
    s = cstring.c_str();
}

template<class Archive>
void serialize(Archive & ar, POINT& point, const unsigned int version)
{
    ar & _S(point.x);
    ar & _S(point.y);
}

template<class Archive>
void serialize(Archive & ar, NODE::ND_DEVICE & nd_device, const unsigned int version)
{
    ar & _S(nd_device.gen);
    ar & _S(nd_device.load);
    ar & _S(nd_device.SSR);
    ar & _S(nd_device.SSC);
    ar & _S(nd_device.SL);
    ar & _S(nd_device.svc);
}

template<class Archive>
void serialize(Archive & ar, Tnum & tnum, const unsigned int version)
{
    ar & _S(tnum.num);
    ar & _S(tnum.no);
}

template<class Archive>
void serialize(Archive & ar, NODE::ND_TEIATU::ND_LV_CABLE & nd_lv_cable, const unsigned int version)
{
    ar & _S(nd_lv_cable.strName3);
    ar & _S(nd_lv_cable.strNameS);
    ar & _S(nd_lv_cable.len3);
    ar & _S(nd_lv_cable.lenS);
}

template<class Archive>
void serialize(Archive & ar, NODE::ND_TEIATU & nd_teiatu, const unsigned int version)
{

    ar & _S(nd_teiatu.cable);

    ar & _S(nd_teiatu.tap);

    ar & _S(nd_teiatu.bestTap);
    ar & _S(nd_teiatu.ritu6750);
    ar & _S(nd_teiatu.ritu6600);
    ar & _S(nd_teiatu.ritu6450);
    ar & _S(nd_teiatu.ritu6300);
    ar & _S(nd_teiatu.secnum);
    ar & _S(nd_teiatu.VolNight);
    ar & _S(nd_teiatu.VolDay);
    ar & _S(nd_teiatu.avgVol);
    ar & _S(nd_teiatu.maxVol);
    ar & _S(nd_teiatu.minVol);

    ar & _S(nd_teiatu.Gp3);
    ar & _S(nd_teiatu.GpS);
    ar & _S(nd_teiatu.Lp3);
    ar & _S(nd_teiatu.LpSu);
    ar & _S(nd_teiatu.LpSb);
    ar & _S(nd_teiatu.rikiritu3G);
    ar & _S(nd_teiatu.rikiritu3L);
    ar & _S(nd_teiatu.rikirituSG);
    ar & _S(nd_teiatu.rikirituSL);
}

template<class Archive>
void serialize(Archive & ar, NODE::ND_CB::_t_keisoku& keisoku, const unsigned int version)
{
    ar & _S(keisoku.dir);
    ar & _S(keisoku.cur);
    ar & _S(keisoku.rikiritu);
    ar & _S(keisoku.V1);
    ar & _S(keisoku.V2);
}

template<class Archive>
void serialize(Archive & ar, NODE::ND_CB::_t_settei& settei, const unsigned int version)
{
    ar & _S(settei.use);
    ar & _S(settei.dir);
    ar & _S(settei.cur);
    ar & _S(settei.rikiritu);
}

template<class Archive>
void serialize(Archive & ar, NODE::ND_CB& nd_cb, const unsigned int version)
{
    ar & _S(nd_cb.CAP);
    ar & _S(nd_cb.pattern);
    ar & _S(nd_cb.sw);
    ar & _S(nd_cb.sw2);
    ar & _S(nd_cb.type);
    ar & _S(nd_cb.Current);
    ar & _S(nd_cb.Reasonable);
    ar & _S(nd_cb.OCR);
    ar & _S(nd_cb.CkSetCUR);
    ar & _S(nd_cb.keisoku);
    ar & _S(nd_cb.settei);

}


template<class Archive>
void serialize(Archive & ar, NODE::ND_FL& nd_fl, const unsigned int version){
    ar & _S(nd_fl.checkFL);
    ar & _S(nd_fl.dV10);
}

template<class Archive>
void serialize(Archive & ar, NODE& node, const unsigned int version)
{
    ar & _S(node.kanri);
    ar & _S(node.pnNum);


    if (Archive::is_loading::value) {
        std::string name;
        ar & make_nvp("node.name", name);
        strncpy(node.name, name.data(), sizeof(node.name));
    } else {
        std::string name(node.name);
        ar & make_nvp("node.name", name);
    }


    ar & _S(node.strName);
    ar & _S(node.pos);
    ar & _S(node.dname);
    ar & _S(node.branch);
    ar & _S(node.teiatu);

    ar & _S(node.CB) ;

    ar & _S(node.kiki);

    ar & _S(node.flicker);

    ar & _S(node.Reasonable);
    ar & _S(node.ReasonableSJ);
    ar & _S(node.dummy);
}

/* ArrayDevice */
template<class Archive>
void serialize(Archive & ar, NRET& nret, const unsigned int version)
{
   ar & _S(nret.id);
   ar & _S(nret.no);
}

template<class Archive>
void serialize(Archive & ar, CArray<NRET, NRET&>& carray, const unsigned int version)
{
    if (Archive::is_loading::value) {
        int count;
        ar & _S(count);
        carray.SetSize(count);
        ar & make_nvp("CArray.NRET", make_array<NRET>((NRET*)carray.GetData(), count));
    } else {
        int count = carray.GetCount();
        ar & _S(count);
        ar & make_nvp("CArray.NRET", make_array<NRET>((NRET*)carray.GetData(), count));
    }
}


template<class Archive>
void serialize(Archive & ar, BASE& base, const unsigned int version)
{
    ar & _S(base.CAP);
    ar & _S(base.VOLT);
    ar & _S(base.FREQ);
    ar & _S(base.EPC);
    ar & _S(base.ITR);
}

template<class Archive>
void serialize(Archive & ar, CALFILE& calfile, const unsigned int version)
{
    if (Archive::is_loading::value) {
        std::string LFdat(calfile.LFdat);
        std::string LFlog(calfile.LFlog);
        std::string LFlst(calfile.LFlst);

        ar & _S(LFdat);
        ar & _S(LFlog);
        ar & _S(LFlst);

        strncpy(calfile.LFdat , LFdat.data(), sizeof(calfile.LFdat));
        strncpy(calfile.LFlog , LFlog.data(), sizeof(calfile.LFlog));
        strncpy(calfile.LFlst , LFlst.data(), sizeof(calfile.LFlst));
    } else {
        std::string LFdat(calfile.LFdat);
        std::string LFlog(calfile.LFlog);
        std::string LFlst(calfile.LFlst);

        ar & _S(LFdat);
        ar & _S(LFlog);
        ar & _S(LFlst);
    }
}

template<class Archive>
void serialize(Archive & ar, DK_T0& dk_to, const unsigned int version)
{
    ar & _S(dk_to.no);
    ar & _S(dk_to.strName);
    ar & _S(dk_to.BNK);
}


template<class Archive>
void serialize(Archive & ar, DEF_LOW_VOL& def_low_vol, const unsigned int version)
{
    ar & _S(def_low_vol.LimitV200);
    ar & _S(def_low_vol.LimitV100);
    ar & _S(def_low_vol.dropVol);
}

template<class Archive>
void serialize(Archive & ar, GENCAP::KEKKA& kekka, const unsigned int version)
{
    ar & _S(kekka.bFlag);
    ar & _S(kekka.hantei);
    ar & _S(kekka.Reasonable);
    ar & _S(kekka.CAP);
    ar & _S(kekka.comment);
    ar & _S(kekka.comment2);
    ar & _S(kekka.bank_comment);
}

template<class Archive>
void serialize(Archive & ar, GENCAP& gencap, const unsigned int version)
{
    ar & _S(gencap.MODE);
    ar & _S(gencap.node);
    ar & _S(gencap.gen);
    ar & _S(gencap.CAP);
    ar & _S(gencap.dCAP);
    ar & _S(gencap.rikiritu);
    ar & _S(gencap.W);
    ar & _S(gencap.check);
    ar & _S(gencap.cal_mode);
    ar & _S(gencap.kekka);
}

template<class Archive>
void serialize(Archive & ar, PCS_SEITEI::KEKKA& kekka, const unsigned int version)
{
    ar & _S(kekka.saiteki);
    ar & _S(kekka.NrikirituBf);
    ar & _S(kekka.NrikirituAf);
    ar & _S(kekka.FrikirituBf);
    ar & _S(kekka.FrikirituAf);
    ar & _S(kekka.ErrFlag);
}

template<class Archive>
void serialize(Archive & ar, PCS_SEITEI& pcs_seitei, const unsigned int version)
{
    ar & _S(pcs_seitei.gno);
    ar & _S(pcs_seitei.result);
}

template<class Archive>
void serialize(Archive & ar, SSC::SC_T1::SC_T2& RyOver, const unsigned int version)
{
    ar & _S(RyOver.V);
    ar & _S(RyOver.dTime);
}

template<class Archive>
void serialize(Archive & ar, SSC::SC_T1::SC_T3& RyShort, const unsigned int version)
{
    ar & _S(RyShort.V);
    ar & _S(RyShort.dTime);
    ar & _S(RyShort.CAP);
}

template<class Archive>
void serialize(Archive & ar, SSC::SC_T1& data, const unsigned int version)
{
    ar & _S(data.CAP);
    ar & _S(data.V);
    ar & _S(data.CAPmax);
    ar & _S(data.ActTime);
    ar & _S(data.fukantai);
    ar & _S(data.FixCAP);
    ar & _S(data.CkFixCAP);
    ar & _S(data.RyOver);
    ar & _S(data.RyShort);
}

template<class Archive>
void serialize(Archive & ar, SSC& ssc, const unsigned int version)
{

    ar & _S(ssc.kanri);
    ar & _S(ssc.node);
    ar & _S(ssc.psNum);
    ar & _S(ssc.pos);
    ar & _S(ssc.unuse);

    ar & _S(ssc.data);
}

template<class Archive>
void serialize(Archive & ar, SSR::SHR_T1::SHR_T2& RyOver, const unsigned int version)
{
    ar & _S(RyOver.V);
    ar & _S(RyOver.dTime);
    ar & _S(RyOver.CAP);
}

template<class Archive>
void serialize(Archive & ar, SSR::SHR_T1::SHR_T3& RyShort, const unsigned int version)
{
    ar & _S(RyShort.V);
    ar & _S(RyShort.dTime);
}

template<class Archive>
void serialize(Archive & ar, SSR::SHR_T1& data, const unsigned int version)
{
    ar & _S(data.CAP);
    ar & _S(data.dCAP);
    ar & _S(data.V);
    ar & _S(data.CAPmax);
    ar & _S(data.ActTime);
    ar & _S(data.fukantai);
    ar & _S(data.FixCAP);
    ar & _S(data.CkFixCAP);
    ar & _S(data.RyOver);
    ar & _S(data.RyShort);
}

template<class Archive>
void serialize(Archive & ar, SSR& ssr, const unsigned int version)
{

    ar & _S(ssr.kanri);
    ar & _S(ssr.node);
    ar & _S(ssr.psNum);
    ar & _S(ssr.pos);
    ar & _S(ssr.unuse);
    ar & _S(ssr.data);
}

template<class Archive>
void serialize(Archive & ar, SEITEICAP& seiteicap, const unsigned int version)
{
    ar & _S(seiteicap.node);
    ar & _S(seiteicap.updown_vol);
}

template<class Archive,typename T>
void serialize(Archive & ar, CList<T,T>& lst, const unsigned int version)
{
    if (Archive::is_loading::value) {
        lst.RemoveAll();
        int count;
        ar & _S(count);
        T value ;
        for(int i=0; i<count; i++) {
            ar & make_nvp("CList.item", value);
            lst.AddTail(value);
        }
    } else {
        int count = lst.GetCount();
        ar & _S(count);
        for( POSITION pos = lst.GetHeadPosition(); pos != NULL; ) {
            ar & make_nvp("CList.item", lst.GetNext( pos ));

        }
    }
}


template<class Archive>
void serialize(Archive & ar, BANK_T& bank, const unsigned int version)
{
    ar & _S(bank.no);
    ar & _S(bank.DK);
    ar & _S(bank.Feeder);
    ar & _S(bank.strName);
    ar & _S(bank.CAP);
    ar & _S(bank.Bimp);
    ar & _S(bank.Xdd);
    ar & _S(bank.futouritu);
    ar & _S(bank.Cur);
    ar & _S(bank.V);
    ar & _S(bank.Current);
    ar & _S(bank.Reasonable);
    ar & _S(bank.MinCurrent);
}

template<class Archive>
void serialize(Archive & ar, BRANCH::BRANCH_T1& node, const unsigned int version)
{
    ar & _S(node.from);
    ar & _S(node.to);
}

template<class Archive>
void serialize(Archive & ar, BRANCH::BRANCH_T2& vector, const unsigned int version)
{
    ar & _S(vector.num);
    ar & _S(vector.no);
}

template<class Archive>
void serialize(Archive & ar, BRANCH::BRANCH_T3& svr, const unsigned int version)
{
    ar & _S(svr.no);
}

template<class Archive>
void serialize(Archive & ar, BRANCH::BRANCH_T4& tvr, const unsigned int version)
{
    ar & _S(tvr.no);
}

template<class Archive>
void serialize(Archive & ar, BRANCH::BRANCH_T5& kassen, const unsigned int version)
{
    ar & _S(kassen.check);
    ar & _S(kassen.flag);
    ar & _S(kassen.CB);
}

template<class Archive>
void serialize(Archive & ar, BRANCH::BRN_1& modeLV, const unsigned int version)
{

    ar & _S(modeLV.strName);
    ar & _S(modeLV.inputMode);
    ar & _S(modeLV.line);
    ar & _S(modeLV.len);
    ar & _S(modeLV.zR);
    ar & _S(modeLV.zX);
    ar & _S(modeLV.zC);
    ar & _S(modeLV.OverCurr);
    ar & _S(modeLV.OverCurr2);
    ar & _S(modeLV.sensyu);
    ar & _S(modeLV.size);
}

template<class Archive>
void serialize(Archive & ar, BRANCH::BRN_LV_1& cableW, const unsigned int version)
{
    ar & _S(cableW.strName);
    ar & _S(cableW.inputMode);
    ar & _S(cableW.len);
    ar & _S(cableW.zR);
    ar & _S(cableW.zX);
}

template<class Archive>
void serialize(Archive & ar, BRANCH& branch, const unsigned int version)
{

    ar & _S(branch.kanri);
    ar & _S(branch.pbNum);
    ar & _S(branch.node);

    ar & _S(branch.vector) ;

    ar & _S(branch.svr);

    ar & _S(branch.tvr);

    ar & _S(branch.kassen);
    ar & _S(branch.cable);
    ar & _S(branch.permit);
    ar & _S(branch.Current);
    ar & _S(branch.Reasonable);

    ar & _S(branch.modeLV);

    ar & _S(branch.cableW);
    ar & _S(branch.dummy);

}

template<class Archive>
void serialize(Archive & ar, CABLE_DB& cable_db, const unsigned int version)
{

    ar & _S(cable_db.no);
    ar & _S(cable_db.strName);
    ar & _S(cable_db.size);
    ar & _S(cable_db.r);
    ar & _S(cable_db.x);
    ar & _S(cable_db.c);
    ar & _S(cable_db.permit);
    ar & _S(cable_db.jiko);
    ar & _S(cable_db.type);
    ar & _S(cable_db.senyu);
    ar & _S(cable_db.bra_size);
}

template<class Archive>
void serialize(Archive & ar, FEEDER_T::_t_keisoku& keisoku, const unsigned int version)
{
    ar & _S(keisoku.dir);
    ar & _S(keisoku.cur);
    ar & _S(keisoku.rikiritu);
}

template<class Archive>
void serialize(Archive & ar, FEEDER_T::_t_settei& settei, const unsigned int version)
{
    ar & _S(settei.dir);
    ar & _S(settei.cur);
    ar & _S(settei.rikiritu);
}

template<class Archive>
void serialize(Archive & ar, FEEDER_T::_t_date& date, const unsigned int version)
{
    ar & _S(date.yy);
    ar & _S(date.mm);
    ar & _S(date.dd);
    ar & _S(date.hh);
}

template<class Archive>
void serialize(Archive & ar, FEEDER_T::_t_V& V, const unsigned int version)
{
    ar & _S(V.bf);
    ar & _S(V.af);
}

template<class Archive>
void serialize(Archive & ar, FEEDER_T& feeder, const unsigned int version)
{

    ar & _S(feeder.no);
    ar & _S(feeder.BNK);
    ar & _S(feeder.node);
    ar & _S(feeder.Conv);
    ar & _S(feeder.Reasonable);

    ar & _S(feeder.keisoku);

    ar & _S(feeder.settei);

    ar & _S(feeder.date);

    ar & _S(feeder.V);
    ar & _S(feeder.upVol);
    ar & _S(feeder.downVol);

}

template<class Archive>
void serialize(Archive & ar, FLICKER::FLICKER1& device, const unsigned int version)
{

    ar & _S(device.id);
    ar & _S(device.no);
}

template<class Archive>
void serialize(Archive & ar, FLICKER::FLICKER2& data, const unsigned int version)
{

    ar & _S(data.flag);
    ar & _S(data.P);
    ar & _S(data.rikiritu);
    ar & _S(data.r_flag);
    ar & _S(data.freq);
}

template<class Archive>
void serialize(Archive & ar, FLICKER::FLICKER3& kekka, const unsigned int version)
{
    ar & _S(kekka.so);
    ar & _S(kekka.Vol);
    ar & _S(kekka.dVol);
}

template<class Archive>
void serialize(Archive & ar, FLICKER& flicker, const unsigned int version)
{
    ar & _S(flicker.device);
    ar & _S(flicker.data);
        ar & _S(flicker.kekka);
}

template<class Archive>
void serialize(Archive & ar, structResLfacBranch& ResLfacBranch, const unsigned int version)
{
    ar & _S(ResLfacBranch.no);
    ar & _S(ResLfacBranch.P);
    ar & _S(ResLfacBranch.Q);
    ar & _S(ResLfacBranch.I);
    ar & _S(ResLfacBranch.Ideg);
    ar & _S(ResLfacBranch.bfI);
    ar & _S(ResLfacBranch.visual);
    ar & _S(ResLfacBranch.dir);
    ar & _S(ResLfacBranch.bfdir);
    ar & _S(ResLfacBranch.fcb);
    ar & _S(ResLfacBranch.svr_impd);
    ar & _S(ResLfacBranch.svr_rev);
}

template<class Archive>
void serialize(Archive & ar, structResLfacNode::_t_Vgraph& Vgraph, const unsigned int version)
{
    ar & _S(Vgraph.Root_Tno);
    ar & _S(Vgraph.Root_Nno);
    ar & _S(Vgraph.Vol);
    ar & _S(Vgraph.VolAV);
    ar & _S(Vgraph.Vdrop);
    ar & _S(Vgraph.pos);
}

template<class Archive>
void serialize(Archive & ar, structResLfacNode& ResLfacNode, const unsigned int version)
{
    ar & _S(ResLfacNode.no);
    ar & _S(ResLfacNode.kV);
    ar & _S(ResLfacNode.lVol);
    ar & _S(ResLfacNode.P);
    ar & _S(ResLfacNode.Q);
    ar & _S(ResLfacNode.I);
    ar & _S(ResLfacNode.bfI);
    ar & _S(ResLfacNode.vol);
    ar & _S(ResLfacNode.deg);
    ar & _S(ResLfacNode.per);
    ar & _S(ResLfacNode.dir);
    ar & _S(ResLfacNode.dirChangeFlag);
    ar & _S(ResLfacNode.Pp);
    ar & _S(ResLfacNode.Qp);
    ar & _S(ResLfacNode.Ip);
    ar & _S(ResLfacNode.Pz);
    ar & _S(ResLfacNode.Qz);
    ar & _S(ResLfacNode.Vgraph);
}


template<class Archive>
void serialize(Archive & ar, structResFlicNode& ResFlicNode, const unsigned int version)
{

    ar & _S(ResFlicNode.no);
    ar & _S(ResFlicNode.V1);
    ar & _S(ResFlicNode.dVso);
}

template<class Archive>
void serialize(Archive & ar, structResLfacSVC& ResLfacSVC, const unsigned int version)
{
    ar & _S(ResLfacSVC.no);
    ar & _S(ResLfacSVC.Q);
}

template<class Archive>
void serialize(Archive & ar, structResLfacSVR& ResLfacSVR, const unsigned int version)
{
    ar & _S(ResLfacSVR.no);
    ar & _S(ResLfacSVR.P);
    ar & _S(ResLfacSVR.Q);
    ar & _S(ResLfacSVR.I);
    ar & _S(ResLfacSVR.pos1);
    ar & _S(ResLfacSVR.pos2);
    ar & _S(ResLfacSVR.dir);

    ar & _S(ResLfacSVR.tapV1);
    ar & _S(ResLfacSVR.tapV2);

    ar & _S(ResLfacSVR.KVol);

    ar & _S(ResLfacSVR.Vr);

    ar & _S(ResLfacSVR.cur);

    ar & _S(ResLfacSVR.LDC);
}

template<class Archive>
void serialize(Archive & ar, structResLfacTVR& ResLfacTVR, const unsigned int version)
{

    ar & _S(ResLfacTVR.no);
    ar & _S(ResLfacTVR.P);
    ar & _S(ResLfacTVR.Q);
    ar & _S(ResLfacTVR.I);
    ar & _S(ResLfacTVR.pos1);
    ar & _S(ResLfacTVR.pos2);
    ar & _S(ResLfacTVR.dir);

    ar & _S(ResLfacTVR.tapV1);
    ar & _S(ResLfacTVR.tapV2);

    ar & _S(ResLfacTVR.KVol);

    ar & _S(ResLfacTVR.Vr);

    ar & _S(ResLfacTVR.cur);

    ar & _S(ResLfacTVR.LDC);
}

template<class Archive>
void serialize(Archive & ar, complex& Complex, const unsigned int version)
{
    ar & _S(Complex.re);
    ar & _S(Complex.im);
}

template<class Archive>
void serialize(Archive & ar, structResLfscBranch& ResLfscBranch, const unsigned int version)
{
    ar & _S(ResLfscBranch.no);
    ar & _S(ResLfscBranch.I);
    ar & _S(ResLfscBranch.Inv);
    ar & _S(ResLfscBranch.dir);
    ar & _S(ResLfscBranch.rFlag);
}

template<class Archive>
void serialize(Archive & ar, structResLfscNode::R_SC_1& gen, const unsigned int version)
{
    ar & _S(gen.check);
    ar & _S(gen.no);
    ar & _S(gen.node);
    ar & _S(gen.Pb);
    ar & _S(gen.Z);
    ar & _S(gen.Ib);
    ar & _S(gen.I);
}

template<class Archive>
void serialize(Archive & ar, structResLfscNode::R_SC_2& branch, const unsigned int version)
{
    ar & _S(branch.check);
    ar & _S(branch.no);
    ar & _S(branch.node);
    ar & _S(branch.Pb);
    ar & _S(branch.Z);
    ar & _S(branch.Ib);
    ar & _S(branch.I);
}

template<class Archive>
void serialize(Archive & ar, structResLfscNode& ResLfscNode, const unsigned int version)
{
    ar & _S(ResLfscNode.no);
    ar & _S(ResLfscNode.P);
    ar & _S(ResLfscNode.I);

    ar & _S(ResLfscNode.Inv);
    ar & _S(ResLfscNode.Z);
    ar & _S(ResLfscNode.check);
    ar & _S(ResLfscNode.bnum);
    ar & _S(ResLfscNode.gen);
    ar & _S(ResLfscNode.branch);
    ar & _S(ResLfscNode.rFlag);
    ar & _S(ResLfscNode.dir);
}


template<class Archive>
void serialize(Archive & ar, GEN::G_DATA1::_t_syunji& syunji, const unsigned int version)
{
    ar & _S(syunji.bf);
    ar & _S(syunji.af);
}

template<class Archive>
void serialize(Archive & ar, GEN::G_DATA1::_t_pcs& pcs, const unsigned int version)
{
    ar & _S(pcs.CntlEnd);
    ar & _S(pcs.type);
    ar & _S(pcs.Vref);
    ar & _S(pcs.Cref);
}

template<class Archive>
void serialize(Archive & ar, GEN::G_DATA1& data, const unsigned int version)
{
    ar & _S(data.kousoku);

    ar & _S(data.CAP);

    ar & _S(data.P);
    ar & _S(data.Q);
    ar & _S(data.V);
    ar & _S(data.Xdd);

    ar & _S(data.SS);
    ar & _S(data.Bank);
    ar & _S(data.OCR);
    ar & _S(data.KyoAmp);

    ar & _S(data.dLoad);

    ar & _S(data.rikiritu);

    ar & _S(data.riyou);

    ar & _S(data.CurLimit);
    ar & _S(data.X);
    ar & _S(data.TrCAP);
    ar & _S(data.TrX);
    ar & _S(data.CT);
    ar & _S(data.TapIns);
    ar & _S(data.TapDim);
    ar & _S(data.DeltaIns);
    ar & _S(data.DeltaDim);

    ar & _S(data.housiki);
    ar & _S(data.strGenPower);
    ar & _S(data.Pritsu);

    ar & _S(data.syunji);

    ar & _S(data.pcs);

}

template<class Archive>
void serialize(Archive & ar, GEN::G_DATA3& flicker, const unsigned int version)
{
    ar & _S(flicker.checkFL);
    ar & _S(flicker.P);
    ar & _S(flicker.rikiritu);
    ar & _S(flicker.cycle);
}

template<class Archive>
void serialize(Archive & ar, GEN& gen, const unsigned int version)
{
    ar & _S(gen.kanri);
    ar & _S(gen.node);
    ar & _S(gen.pattern);
    ar & _S(gen.dir);
    ar & _S(gen.pos);

    ar & _S(gen.type);
    ar & _S(gen.unuse);
    ar & _S(gen.data);

    ar & _S(gen.flicker);

    ar & _S(gen.Current);
    ar & _S(gen.Reasonable);
    ar & _S(gen.dummy);
}

template<class Archive>
void serialize(Archive & ar, structActSVR::_t_count& count, const unsigned int version)
{
    ar & _S(count.lf);
    ar & _S(count.reset);
    ar & _S(count.tap);
    ar & _S(count.time);
    ar & _S(count.dVOL);
    ar & _S(count.sekibun);
}

template<class Archive>
void serialize(Archive & ar, structActSVR& ActSVR, const unsigned int version)
{
    ar & _S(ActSVR.no);
    ar & _S(ActSVR.TotalTime);
    ar & _S(ActSVR.count);
}

template<class Archive>
void serialize(Archive & ar, HOGO::HOGO1& kekka, const unsigned int version)
{
    ar & _S(kekka.node);
    ar & _S(kekka.cur);
}

template<class Archive>
void serialize(Archive & ar, HOGO& hogo, const unsigned int version)
{
    ar & _S(hogo.CalMode);
    ar & _S(hogo.ScNode);
    ar & _S(hogo.TermsGen);
    ar & _S(hogo.TermsNode);
    ar & _S(hogo.kekka);
}


template<class Archive>
void serialize(Archive & ar, structActTVR::_t_count& count, const unsigned int version)
{
    ar & _S(count.lf);
    ar & _S(count.reset);
    ar & _S(count.tap);
    ar & _S(count.time);
    ar & _S(count.dVOL);
    ar & _S(count.sekibun);
}

template<class Archive>
void serialize(Archive & ar, structActTVR& ActTVR, const unsigned int version)
{
    ar & _S(ActTVR.no);
    ar & _S(ActTVR.TotalTime);
    ar & _S(ActTVR.count);
}
template<class Archive>
void serialize(Archive & ar, structWorkBranch::_t_Root& Root, const unsigned int version)
{
    ar & _S(Root.rno);
    ar & _S(Root.check);
}

template<class Archive>
void serialize(Archive & ar, structWorkBranch& WorkBranch, const unsigned int version)
{
    ar & _S(WorkBranch.no);
    ar & _S(WorkBranch.wCheck);
    ar & _S(WorkBranch.Root);
    ar & _S(WorkBranch.dummyBranch);
    ar & _S(WorkBranch.csflg);
}

template<class Archive>
void serialize(Archive & ar, structWorkGen::_t_kassen& kassen, const unsigned int version)
{
    ar & _S(kassen.check);
    ar & _S(kassen.flag);
}

template<class Archive>
void serialize(Archive & ar, structWorkGen& WorkGen, const unsigned int version)
{
    ar & _S(WorkGen.no);
    ar & _S(WorkGen.P);
    ar & _S(WorkGen.Q);
    ar & _S(WorkGen.I);

    ar & _S(WorkGen.kassen);
    ar & _S(WorkGen.dummyGen);
}

template<class Archive>
void serialize(Archive & ar, structWorkLoad& WorkLoad, const unsigned int version)
{
    ar & _S(WorkLoad.no);
    ar & _S(WorkLoad.P);
    ar & _S(WorkLoad.Q);
    ar & _S(WorkLoad.I);
}

template<class Archive>
void serialize(Archive & ar, structWorkNode& WorkNode, const unsigned int version)
{
    ar & _S(WorkNode.no);
    ar & _S(WorkNode.wCheck);
    ar & _S(WorkNode.dummyNode);
    ar & _S(WorkNode.csflg);
}

template<class Archive>
void serialize(Archive & ar, structWorkSSC::_t_act& act, const unsigned int version)
{
    ar & _S(act.reset);
    ar & _S(act.time);
    ar & _S(act.dVOL);
}

template<class Archive>
void serialize(Archive & ar, structWorkSSC& WorkSSC, const unsigned int version)
{

    ar & _S(WorkSSC.no);
    ar & _S(WorkSSC.P);
    ar & _S(WorkSSC.Q);
    ar & _S(WorkSSC.I);

    ar & _S(WorkSSC.err);
    ar & _S(WorkSSC.Vflag);
    ar & _S(WorkSSC.fukantai);
    ar & _S(WorkSSC.act);

    ar & _S(WorkSSC.csflg);

}


template<class Archive>
void serialize(Archive & ar,  structWorkSSR::_t_act&  act, const unsigned int version)
{
    ar & _S(act.reset);
    ar & _S(act.time);
    ar & _S(act.dVOL);
}

template<class Archive>
void serialize(Archive & ar,  structWorkSSR&  WorkSSR, const unsigned int version)
{

    ar & _S(WorkSSR.no);
    ar & _S(WorkSSR.P);
    ar & _S(WorkSSR.Q);
    ar & _S(WorkSSR.I);

    ar & _S(WorkSSR.err);
    ar & _S(WorkSSR.Vflag);
    ar & _S(WorkSSR.fukantai);
    ar & _S(WorkSSR.act);

    ar & _S(WorkSSR.csflg);

}


template<class Archive>
void serialize(Archive & ar, structWorkSVC& WorkSVC, const unsigned int version)
{
    ar & _S(WorkSVC.no);
    ar & _S(WorkSVC.Qsvc);
    ar & _S(WorkSVC.Qsvc_B);
    ar & _S(WorkSVC.QsvcOld);
    ar & _S(WorkSVC.k);
    ar & _S(WorkSVC.Xsvc);
    ar & _S(WorkSVC.Vsvc);
    ar & _S(WorkSVC.VsvcOld);
    ar & _S(WorkSVC.Pl);
    ar & _S(WorkSVC.Ql);
    ar & _S(WorkSVC.QlOld);
    ar & _S(WorkSVC.fukantai);
    ar & _S(WorkSVC.err);
    ar & _S(WorkSVC.csflg);
}

template<class Archive>
void serialize(Archive & ar, structWorkSVR::_t_root& WorkSVR, const unsigned int version)
{
    ar & _S(WorkSVR.rno);
    ar & _S(WorkSVR.node);
}

template<class Archive>
void serialize(Archive & ar, structWorkSVR& WorkSVR, const unsigned int version)
{
    ar & _S(WorkSVR.no);
    ar & _S(WorkSVR.cur);
    ar & _S(WorkSVR.vol);
    ar & _S(WorkSVR.err);
    ar & _S(WorkSVR.ponping);
    ar & _S(WorkSVR.TapId);
    ar & _S(WorkSVR.fukantai);
    ar & _S(WorkSVR.ActTapNum);
    ar & _S(WorkSVR.ActTapLDC);
    ar & _S(WorkSVR.tap_old);
    ar & _S(WorkSVR.TapHistory);
    ar & _S(WorkSVR.root);
    ar & _S(WorkSVR.csflg);
    ar & _S(WorkSVR.fcbdir);
    ar & _S(WorkSVR.dir);

}

template<class Archive>
void serialize(Archive & ar, structWorkTVR::_t_root& root, const unsigned int version)
{
    ar & _S(root.rno);
    ar & _S(root.node);
}

template<class Archive>
void serialize(Archive & ar, structWorkTVR& WorkTVR, const unsigned int version)
{

    ar & _S(WorkTVR.no);
    ar & _S(WorkTVR.cur);
    ar & _S(WorkTVR.vol);
    ar & _S(WorkTVR.err);
    ar & _S(WorkTVR.ponping);
    ar & _S(WorkTVR.TapId);
    ar & _S(WorkTVR.fukantai);
    ar & _S(WorkTVR.ActTapNum);
    ar & _S(WorkTVR.ActTapLDC);
    ar & _S(WorkTVR.tap_old);
    ar & _S(WorkTVR.TapHistory);
    ar & _S(WorkTVR.root);
    ar & _S(WorkTVR.csflg);
    ar & _S(WorkTVR.fcbdir);
    ar & _S(WorkTVR.dir);
}


template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_1::LOAD_1_1& high, const unsigned int version)
{
    ar & _S(high.P);

    ar & _S(high.Cur);
    ar & _S(high.Cur_a);

}

template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_1::LOAD_1_2& Tr, const unsigned int version)
{
    ar & _S(Tr.P);
    ar & _S(Tr.Cur);
    ar & _S(Tr.Cur_a);

}

template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_1::LOAD_1_3& spot, const unsigned int version)
{
    ar & _S(spot.P);
    ar & _S(spot.Cur);
    ar & _S(spot.rikiritu);
}


template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_1::_t_syunji& syunji, const unsigned int version)
{
    ar & _S(syunji.bf);
    ar & _S(syunji.af);
    ar & _S(syunji.Pbf);
    ar & _S(syunji.Qbf);
    ar & _S(syunji.Paf);
    ar & _S(syunji.Qaf);
}

template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_1& data, const unsigned int version)
{
    ar & _S(data.high);
    ar & _S(data.Tr);
    ar & _S(data.spot);
    ar & _S(data.target);
    ar & _S(data.P);
    ar & _S(data.Q);
    ar & _S(data.syunji);
    ar & _S(data.riyou);
}

template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_2& memo, const unsigned int version)
{
    ar & _S(memo.strName);
    ar & _S(memo.strCom);
    ar & _S(memo.P);
}

template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_3::LOAD_3_1& type1, const unsigned int version)
{
    ar & _S(type1.cap);
    ar & _S(type1.rikiritu);
    ar & _S(type1.cycle);
}


template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_3::LOAD_3_2::LOAD_3_3& so, const unsigned int version)
{
    ar & _S(so.num);
    ar & _S(so.cap);
    ar & _S(so.rikiritu);
    ar & _S(so.siyouritu);
    ar & _S(so.cycle);
}

template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_3::LOAD_3_2& type2, const unsigned int version)
{
    ar & _S(type2.so);
}

template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_3::LOAD_3_4& type3, const unsigned int version)
{
    ar & _S(type3.cur);
    ar & _S(type3.rikiritu);
    ar & _S(type3.cycle);
}
template<class Archive>
void serialize(Archive & ar, LOAD::LOAD_3& flicker, const unsigned int version)
{
    ar & _S(flicker.checkFL);
    ar & _S(flicker.type);
    ar & _S(flicker.type1);
    ar & _S(flicker.type2);
    ar & _S(flicker.type3);

}

template<class Archive>
void serialize(Archive & ar, LOAD& load, const unsigned int version)
{
    ar & _S(load.kanri);
    ar & _S(load.node);
    ar & _S(load.pattern);
    ar & _S(load.dir);
    ar & _S(load.pos);
    ar & _S(load.unuse);

    ar & _S(load.data);
    ar & _S(load.memo);

    ar & _S(load.flicker);
    ar & _S(load.Reasonable);
}
template<class Archive>
void serialize(Archive & ar, LUMINOUS::LUMINOUS1& data, const unsigned int version)
{
    ar & _S(data.freq);
    ar & _S(data.factor);
}

template<class Archive>
void serialize(Archive & ar, LUMINOUS& luminous, const unsigned int version)
{
    ar & _S(luminous.d_num);
    ar & _S(luminous.data);
}

template<class Archive>
void serialize(Archive & ar, RECTWAVE::RECTWAVE1& data, const unsigned int version)
{
    ar & _S(data.freq);
    ar & _S(data.factor);
}

template<class Archive>
void serialize(Archive & ar, RECTWAVE& rectwave, const unsigned int version)
{

    ar & _S(rectwave.d_num);
    ar & _S(rectwave.data);
}

template<class Archive>
void serialize(Archive & ar, RST_BANK_SC::FEEDER_0& Feeder, const unsigned int version)
{
    ar & _S(Feeder.no);
    ar & _S(Feeder.bFlag);

    ar & _S(Feeder.Z);
    ar & _S(Feeder.Znet);
    ar & _S(Feeder.AtherFeederZ);
    ar & _S(Feeder.CurMinNode);
    ar & _S(Feeder.CurMin);
    ar & _S(Feeder.CurMinZ);
    ar & _S(Feeder.CurMinLen);
    ar & _S(Feeder.Cur);
    ar & _S(Feeder.CurFromNet);
}

template<class Archive>
void serialize(Archive & ar, RST_BANK_SC& rst_bank_sc, const unsigned int version)
{
    ar & _S(rst_bank_sc.bFlag);
    ar & _S(rst_bank_sc.no);
    ar & _S(rst_bank_sc.CurMinFeederNo);
    ar & _S(rst_bank_sc.CurMinFeeder);
    ar & _S(rst_bank_sc.CurMinNode);
    ar & _S(rst_bank_sc.CurMin);
    ar & _S(rst_bank_sc.CurMinZ);
    ar & _S(rst_bank_sc.CurMinLen);
    ar & _S(rst_bank_sc.Feeder);
}

template<class Archive>
void serialize(Archive & ar, SVC::SVC_T1& data, const unsigned int version)
{

    ar & _S(data.type);
    ar & _S(data.LimitFlag);
    ar & _S(data.Qlimit);
    ar & _S(data.Vref);
    ar & _S(data.Cref);
    ar & _S(data.fukantai);
    ar & _S(data.CAP);
    ar & _S(data.ActTime);
}

template<class Archive>
void serialize(Archive & ar, SVC& svc, const unsigned int version)
{

    ar & _S(svc.kanri);
    ar & _S(svc.node);
    ar & _S(svc.psNum);
    ar & _S(svc.pos);
    ar & _S(svc.unuse);
    ar & _S(svc.data);
}

template<class Archive>
void serialize(Archive & ar, SVR_DB& svr_db, const unsigned int version)
{
    ar & _S(svr_db.no);
    ar & _S(svr_db.strMaker);
    ar & _S(svr_db.strType);
    ar & _S(svr_db.CAP);
    ar & _S(svr_db.R67);

    ar & _S(svr_db.PT);

    ar & _S(svr_db.ActTime);
    ar & _S(svr_db.Svrtype);
    ar & _S(svr_db.DeviceType);

}

template<class Archive>
void serialize(Archive & ar, SVRTAP_DB& svrtap_db, const unsigned int version)
{

    ar & _S(svrtap_db.no);
    ar & _S(svrtap_db.tapno);
    ar & _S(svrtap_db.vol);
}


template<class Archive>
void serialize(Archive & ar, TVR_DB& tvr_db, const unsigned int version)
{
    ar & _S(tvr_db.no);
    ar & _S(tvr_db.strMaker);
    ar & _S(tvr_db.strType);
    ar & _S(tvr_db.CAP);
    ar & _S(tvr_db.ActTime);
    ar & _S(tvr_db.Tvrtype);
    ar & _S(tvr_db.R67);
}

template<class Archive>
void serialize(Archive & ar, TVR::TVR_1& data, const unsigned int version)
{

    ar & _S(data.strMaker);
    ar & _S(data.strType);
    ar & _S(data.phase1);
    ar & _S(data.GyakusouKotei);
    ar & _S(data.type);
    ar & _S(data.TapFixed);
    ar & _S(data.CAP);
    ar & _S(data.tap);
    ar & _S(data.vol);
    ar & _S(data.fukantai);
    ar & _S(data.LDC_R);
    ar & _S(data.LDC_X);
    ar & _S(data.ActTime);
    ar & _S(data.haba);
    ar & _S(data.R67);
}

template<class Archive>
void serialize(Archive & ar, TVR::TVR_T2& root, const unsigned int version)
{
    ar & _S(root.no);
    ar & _S(root.node);
}

template<class Archive>
void serialize(Archive & ar, TVR& tvr, const unsigned int version)
{
    ar & _S(tvr.kanri);
    ar & _S(tvr.node);
    ar & _S(tvr.branch);
    ar & _S(tvr.psNum);
    ar & _S(tvr.data);
    ar & _S(tvr.root);

    ar & _S(tvr.Current);
    ar & _S(tvr.permit);
    ar & _S(tvr.Reasonable);
}

template<class Archive>
void serialize(Archive & ar, TVRTAP_DB& tvrtap_db, const unsigned int version)
{
    ar & _S(tvrtap_db.no);
    ar & _S(tvrtap_db.tapno);
    ar & _S(tvrtap_db.vol);
}

template<class Archive>
void serialize(Archive & ar, VECTOR& vector, const unsigned int version)
{

    ar & _S(vector.kanri);
    ar & _S(vector.branch);
    ar & _S(vector.s);
    ar & _S(vector.e);
    ar & _S(vector.dummy);
}

template<class Archive>
void serialize(Archive & ar, CListPattern::CListInfo& ListInfo, const unsigned int version)
{
    ar & _S(ListInfo.ErrFlag);
    ar & _S(ListInfo.strFileName);
    ar & _S(ListInfo.pData);
}

template<class Archive>
void serialize(Archive & ar, CListPattern& lst, const unsigned int version)
{
    if (Archive::is_loading::value) {
        lst.RemoveAll();
        int count;
        ar & _S(count);
        for(int i=0; i<count; i++) {
            ar & make_nvp("CListPattern.item", *lst.AddList());
        }
    } else {
        int count = (int)lst.GetCount();
        ar & _S(count);
        for( int i=0; i< count; i ++) {
            ar & make_nvp("CListPattern.item", *lst.GetList(i));
        }
    }

}

template<class Archive>
void serialize(Archive & ar, CListRoute::CListInfo& info, const unsigned int version)
{
    ar & _S(info.start);
    ar & _S(info.end);
    ar & _S(info.max);
    ar & _S(info.node);
    ar & _S(info.totalLen);
    ar & _S(info.branch);

}

template<class Archive>
void serialize(Archive & ar, CListRoute& lst, const unsigned int version)
{
    if (Archive::is_loading::value) {
        lst.RemoveAll();
        int count;
        ar & _S(count);
        for(int i=0; i<count; i++) {
            ar & make_nvp("CListRoute.item", *lst.AddList());
        }
    } else {
        int count = (int)lst.GetCount();
        ar & _S(count);
        for( int i=0; i< count; i ++) {
            ar & make_nvp("CListRoute.item", *lst.GetList(i));
        }
    }

}


template<class Archive>
void serialize(Archive & ar, SVR::SVR_1::_t_keisoku& keisoku, const unsigned int version)
{
    ar & _S(keisoku.dir);
    ar & _S(keisoku.cur);
    ar & _S(keisoku.rikiritu);
    ar & _S(keisoku.V1);
    ar & _S(keisoku.V2);
}

template<class Archive>
void serialize(Archive & ar, SVR::SVR_1::_t_settei& settei, const unsigned int version)
{
    ar & _S(settei.use);
    ar & _S(settei.dir);
    ar & _S(settei.cur);
    ar & _S(settei.rikiritu);
}

template<class Archive>
void serialize(Archive & ar, SVR::SVR_1& data, const unsigned int version)
{
    ar & _S(data.strMaker);
    ar & _S(data.strType);

    ar & _S(data.DeviceType);

    ar & _S(data.phase1);
    ar & _S(data.type);
    ar & _S(data.TapFixed);
    ar & _S(data.CAP);
    ar & _S(data.tap);
    ar & _S(data.vol);
    ar & _S(data.fukantai);
    ar & _S(data.LDC_R);
    ar & _S(data.LDC_X);
    ar & _S(data.ActTime);
    ar & _S(data.haba);
    ar & _S(data.R67);

    ar & _S(data.keisoku);
    ar & _S(data.settei);
}

template<class Archive>
void serialize(Archive & ar, SVR::SVR_T2& root, const unsigned int version)
{
    ar & _S(root.no);
    ar & _S(root.node);
}

template<class Archive>
void serialize(Archive & ar, SVR& svr, const unsigned int version)
{
    ar & _S(svr.kanri);
    ar & _S(svr.node);
    ar & _S(svr.branch);
    ar & _S(svr.psNum);
    ar & _S(svr.data);

    ar & _S(svr.root);

    ar & _S(svr.Current);
    ar & _S(svr.permit);
    ar & _S(svr.Reasonable);

}

/*TWH
template<class Archive>
void serialize(Archive & ar, CALFILE& calfile, const unsigned int version)
{
}
*/

