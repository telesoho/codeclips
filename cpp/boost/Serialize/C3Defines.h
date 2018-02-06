#define		NODE_NAME_MAX	7	// ノード名称文字数
#define		LOAD_MODE_MAX	3	// 重負荷/軽負荷/その他負荷
#define		BANK_IN_FEEDER_MAX	14	// １バンクに登録できるフィーダデータの最大数
#define		Line_MAX	7		// 配電線折れ点最大数 
#define		ACT_MAX		100		// ＳＶＲ動作時間特性最大数 
#define		LUMINOUS_MAX	30	// ちらつき視感度曲線登録最大数
#define		RECTWAVE_MAX	20	// 矩型波用ちらつき視感度曲線登録最大数

namespace c3 {
    typedef struct tagPOINT
    {
        LONG  x;
        LONG  y;
    } POINT, *PPOINT, NEAR *NPPOINT, FAR *LPPOINT;

    typedef struct TNUM0{
        int  num;
        int  no[NODE_IN_BRANCH_MAX];
    } Tnum;


    //////////////////////////////////////
    // ノードテーブル枠定義
    typedef struct NODE_TABLE{
        int  kanri;   // 管理No.
        int  pnNum;   // ノード計算結果レコードNo  2004.04.20 Add
        char name[NODE_NAME_MAX];  // ノード名称 (潮流計算用)
        CString strName;  // ノード名称 (旧ncomm)
        POINT pos;   // ノード配置点(絶対座標)
        POINT dname;   // ノード名称作画位置 
        Tnum branch;   // 接続配電線
        struct ND_TEIATU {
            struct ND_LV_CABLE{
                CString strName3; // 線種名称(三相)
                CString strNameS; // 線種名称(単相)
                UINT len3;  // 線種長(三相)
                UINT lenS;  // 線種長(単相)
            } cable;
            float tap;  // 低圧換算タップ[V] 
            // ADAM2201 (Hyron) 2016/09/06 Start
            float bestTap;  // 最適タップ -1(空白)
            float ritu6750; // 最適　適正率（％） 6750タップ  -1(空白)
            float ritu6600; // 最適　適正率（％） 6600タップ  -1(空白)
            float ritu6450; // 最適　適正率（％） 6450タップ  -1(空白)
            float ritu6300; // 最適　適正率（％） 6300タップ  -1(空白)
            short  secnum[5]; /* 解析断面数 最大12ヶ月×2日×24時間 = 576断面 */
            /* 0:総解析断面数 */
            /* 適正範囲に入った解析断面数 1:6300タップ,2：6450タップ, 3：6600タップ, 4：6750タップ */
            float VolNight[16]; // 電圧分布（6300V~7050V）夜間(19～6時) -1(空白)
            float VolDay[16];   // 電圧分布（6300V~7050V）昼間(7～18時) -1(空白)
            float avgVol;       // 平均電圧(0～9999) -1(空白)
            float maxVol;       // 最大電圧(0～9999) -1(空白)
            float minVol;       // 最小電圧(0～9999) -1(空白)
            // ADAM2201 (Hyron) 2016/09/06 End
            float Gp3;  // 発電Ｐ(三相)
            float GpS;  // 発電Ｐ(単相)
            float Lp3;  // 負荷Ｐ(三相)
            float LpSu;  // 負荷Ｐ(単相/不平衡)
            float LpSb;  // 負荷Ｐ(単相/平衡)
            float rikiritu3G; // 力率(三相発電)
            float rikiritu3L; // 力率(三相負荷)
            float rikirituSG; // 力率(単相発電)
            float rikirituSL; // 力率(三相負荷)
        } teiatu ;  // 低圧系統

        struct ND_CB {
            float CAP;  // 定格容量:A 
            short pattern; // 遮断器が接続されている場合のパターン番号（1or2, 0:なし)
            short sw;   // 入／切状態 ON/OFF （現在状態）
            short sw2;  // 入／切 ON/OFF  （常時状態）  Add 2003.04.15 (R.T)
            short type;  // 開閉器種別 0～
            float Current; // 適正範囲逸脱個所表示用（通過電流）
            short Reasonable; // 逸脱判定OFF/ON Add 2003.03.17 J.S
            float OCR;  // OCR整定値（Ａ） Add 2003.10.27 J.S
            // ADAM No.0010-2 P95 Del start
            //  float SetCurrent; // 開閉器通過電流  Add 2006.01.07 S.S
            //  int  CkSetCUR; // 1:開閉器通過電流 1:設定する, 0:設定しない Add 2006.01.07 S.S
            short CkSetCUR; // 1:開閉器通過電流 1:設定する, 0:設定しない Conv 2006.05.18 J.S
            // ADAM No.0010-2 P95 Del end

            ////////////////////////////////////////////////////////
            // ADAM No.0010-1 P95 Add start
            struct _t_keisoku{
                // ADAM1203 (SinoCom) 2014/10/20 Start
                //int  dir; // 潮流方向 0:"順", 1:"逆", 2:"－", 3: " "   (デフォルトは－)
                int  dir; // 潮流方向 0:"順", 1:"逆", 2:"－"(使用しない), 3: " "
                // ADAM1203 (SinoCom) 2014/10/20 End
                int  cur; // 通過電流(A)【0～999999】 -1:空白(データ欠損または新規作成時)
                // ADAM1203 (SinoCom) 2014/10/20 Start
                float rikiritu; // 力率(%)【-100.00～100.00】マイナス値は進み力率
                int  V1; // A側電圧(V)
                int  V2; // B側電圧(V)
                // ADAM1203 (SinoCom) 2014/10/20 End
            }keisoku[LOAD_MODE_MAX]; // 計測値

            struct _t_settei{
                BOOL use; // 有効  0:OFF 1:ON(有効)
                // ADAM1203 (SinoCom) 2014/10/20 Start
                //int  dir; // 潮流方向 0:"順", 1:"逆", 2: " "
                int  dir; // 潮流方向 0:"順", 1:"逆"
                // ADAM1203 (SinoCom) 2014/10/20 End
                int  cur; // 通過電流(A)【0～999999】データ欠損または新規作成時は「0」
                // ADAM1203 (SinoCom) 2014/10/20 Start
                float rikiritu; // 力率(%)【-100.00～100.00】 マイナス値は進み力率
                // ADAM1203 (SinoCom) 2014/10/20 End
            }settei[LOAD_MODE_MAX]; // 設定値  (FCB通過電流の伸び率を考慮した開閉器の通過電流)
            // ADAM No.0010-1 P95 Add end
            ////////////////////////////////////////////////////////
        } CB ;

        struct ND_DEVICE{  // 接続機器 管理No. 
            int  gen;  // 接続電源 管理No.
            int  load;  // 接続需要家 管理No.
            int  SSR;  // 調相設備:シャントリアクトル(SSR) 管理No.
            int  SSC;  // 調相設備:スタティックコンデンサ(SSC) 管理No.
            int  SL;   // 接続特殊負荷 管理No. 
            int  svc;  // SVC 管理No.
        } kiki;

        // Add 2003.11.03 J.S
        struct ND_FL{    // データ 
            BOOL checkFL;  // 既設フリッカ設定
            float dV10;   // ΔV10
        } flicker;    // フリッカ

        short Reasonable; // 逸脱判定OFF/ON
        short ReasonableSJ; // 逸脱判定OFF/ON 瞬時時の10％で電圧差
        BOOL dummy;
    } NODE;


    typedef struct NRET0{
        int id;
        int no;
    } NRET;

    // 系統基準テーブル枠定義
    typedef struct BASE0{
        float CAP;  // 系統基準容量(MVA) 
        float VOLT;  // 系統基準電圧(V) 
        float FREQ;  // 系統周波数(Hz)
        float EPC;  // 収斂定数 
        short ITR;  // 最大反復回数 
    } BASE;

    // 計算ファイル定義
    typedef struct CALFILE0{
        char LFdat[512]; // 潮流計算用入力データ
        char LFlog[512]; // 潮流計算結果(.LOG).....テーブル反映ファイル
        char LFlst[512]; // 潮流計算結果(.LST).....判定ファイル
    } CALFILE;

    // 変電所テーブル枠定義
    typedef struct DK_T0{
        short no;   // 変電所No
        CString strName; // 名称
        short BNK[4];  // 所属バンク
    } DK_T;

    //////////////////////////////////////
    // 低圧系統電圧上下限値／電圧降下想定値(初期値)エリア
    typedef struct DEF_LOW_VOL0{
        float   LimitV200[2];   // 低圧系統電圧上下限値200[V]Base 0:Min, 1:Max Add 2003.10.28 J.S
        float   LimitV100[2];   // 低圧系統電圧上下限値100[V]Base 0:Min, 1:Max Add 2003.10.28 J.S
        // Conv 2006.01.26 S.S
        // float        dropVol;                // 低圧系統電圧降下相定値[V]
        // Conv 2006.02.27 J.S
        //      float   dropVol[3];             // 低圧系統電圧降下相定値[V]・・・[重負荷/軽負荷/その他負荷]
        float   dropVol[2][3];          // 低圧系統電圧降下相定値[V]・・・[直下/末端][重負荷/軽負荷/その他負荷]
    } DEF_LOW_VOL;

    // 分散型電源連系可能容量解析条件テーブル枠定義
    typedef struct GEN_CAP0{
        int     MODE;    // Add 2006.02.17 S.S 電圧逸脱判定範囲モード（通常解析、逸脱範囲指定）
        int  node;    // 選択ノードNo.
        int  gen;    // ダミー発電機No.
        float CAP;    // 申し入れ容量(kVA)
        float dCAP;    // 容量刻み(kVA)
        float rikiritu;   // 力率(%)
        float W;     // (kVA)
        BOOL    check;    // 按分計算　1:する、0:しない
        int     cal_mode;           // Add 2006.01.31 S.S 
        struct KEKKA {
            // Conv 2006.02.02 S.S
            // BOOL bFlag;   // 解析結果  True:成功, False：失敗
            short bFlag;   // 解析結果  1:連系可能、2:連系不可能、3:検討不可
            CString hantei;   // Add 2006.02.03 S.S 画面上の解析結果文字列 "連系可能", "連系不可能", "検討不可"
            short Reasonable;  // 逸脱判定OFF/ON
            float CAP;   // 連系可能容量(kVA)
            CString comment;  // 画面下の結果理由：電圧逸脱、潮流計算エラーなど
            CString comment2;  // Add 2006.02.03 S.S 画面最下部の結果理由:過負荷など 
            CString bank_comment; // Add 2006.02.13 S.S バンク過負荷エラー

        }kekka;    // 解析結果 
    } GENCAP;

    // PCS整定値自動算出
    typedef struct{
        int  gno;  // 選択発電機No.
        struct KEKKA {
            int  saiteki; // 0:連系ノード最適 1:フィーダ最適
            int  NrikirituBf; // 連系ノード最適力率(前)
            int  NrikirituAf; // 連系ノード最適力率(後)
            int  FrikirituBf; // フィーダ最適力率(前)
            int  FrikirituAf; // フィーダ最適力率(後)
            int  ErrFlag;  // 自動算出不可時の情報
            // ERR内容
            // 0:ERR無し
            // 1:出力が０(定格容量または発電率が０）
            // ADAM0126 (SinoCom) 2014/01/07 Start
            // 2:PCS制御方式が力率一定制御 // Del
            // 2:PCS制御方式が電圧一定制御 // ADD
            // ADAM0126 (SinoCom) 2014/01/07 End
            // 3:潮流計算実施不可
            // 4:その他
        }result; // 算出結果
    } PCS_SEITEI;

    //////////////////////////////////////
    // 調相設備テーブル(スタティックコンデンサ:SSC)テーブル枠定義
    typedef struct SC_T0{
        int  kanri;   // 管理No.
        int  node;   // 接続ノード管理No. 
        int  psNum;   // SSC計算結果レコードNo  2004.05.27 Add
        POINT pos;   // 接続ノード相対座標
        //////////////////////////////////////////////////////////////////////////
        // Add 2006.01.30 S.S
        BOOL unuse;  // 運用除外モード　False:除外しない、True:除外する
        //////////////////////////////////////////////////////////////////////////
        struct SC_T1{
            // ADAM No.0005-1 P80 Chg start
            //  float CAP;  // 容量(kVA/KVar)
            float CAP;  // 容量(kVA)
            // ADAM No.0005-1 P80 Chg end

            // Comm 2003.05.06 J.S
            //  float dCAP;  // 投入調整容量(kVA/KVar)
            float V[2];  // 基準整定電圧(V) [SetArea]
            float CAPmax;  // 最大投入容量(kVar)
            float ActTime; // 動作時限(秒･%) 
            float fukantai; // 不感帯整定値(±%)
            float FixCAP;  // 固定投入容量(KVar)
            int  CkFixCAP; // 1:固定投入量量を使用する, 0:使用しない
            struct SC_T2{
                float V;  // 電圧設定値（V)
                float dTime; // 検出時限(秒)
            } RyOver; // 過電圧リレー
            struct SC_T3{
                float V;  // 電圧設定値（V)
                float dTime[2]; // [0]:検出時限(秒), [1]:不検出時限(秒)
                float CAP;  // 投入容量(kVar)
            } RyShort; // 不足電圧リレー

        } data;
    } SSC;

    //////////////////////////////////////
    // 調相設備テーブル(シャントリアクトル:SSR)テーブル枠定義
    typedef struct SHR_T0{
        int  kanri;   // 管理No. 
        int  node;   // 接続ノード管理No. 
        int  psNum;   // SSR計算結果レコードNo  2004.05.27 Add
        POINT pos;   // 接続ノード相対座標
        //////////////////////////////////////////////////////////////////////////
        // Add 2006.01.30 S.S
        BOOL unuse;  // 運用除外モード　False:除外しない、True:除外する
        //////////////////////////////////////////////////////////////////////////
        struct SHR_T1{
            float CAP;  // 容量(kVA)
            float dCAP;  // 投入調整容量(kVar)
            float V[2];  // 基準整定電圧(V) [SetArea]
            float CAPmax;  // 最大投入容量(kVar)
            float ActTime; // 動作時限(秒･%) 
            float fukantai; // 不感帯整定値(±%)
            float FixCAP;  // 固定投入容量(KVar)
            int  CkFixCAP; // 1:固定投入量量を使用する, 0:使用しない
            struct SHR_T2{
                float V;  // 電圧設定値（V)
                float dTime[2]; // [0]:検出時限(秒), [1]:不検出時限(秒)
                float CAP;  // 投入容量(kVar)
            } RyOver; // 過電圧リレー
            struct SHR_T3{
                float V;  // 電圧設定値（V)
                float dTime; // 検出時限(秒)
            } RyShort; // 不足電圧リレー
        } data;
    } SSR;

    // Add 2007.02.06 S.S SVR整定
    typedef struct{
        int node;   // 選択ノードNo.
        int updown_vol;  // 上下限制約値
    } SEITEICAP;

    //////////////////////////////////////
    // バンクテーブル枠定義
    typedef struct BANK_T0{
        short no;   // バンクNo
        short DK;   // 所属変電所No
        short Feeder[BANK_IN_FEEDER_MAX]; // 所属フィーダーNo（FCB管理No＝gen_t[].kanri）
        CString strName; // 名称
        float CAP;  // バンク容量[MVA]
        float Bimp;  // バンクインピーダンス[％]
        float Xdd;  // 背後インピーダンス[%]
        float futouritu; // 不等[%]
        float Cur;  // 許容電流値[A]
        // ADAM No.0017-2 P124 Del start
        float V[3];  // 送出電圧[V] 重負荷、軽負荷、その他負荷
        // ADAM No.0017-2 P124 Del end
        float Current; // 適正範囲逸脱個所表示用（バンク通過電流）
        short Reasonable; // 逸脱判定OFF/ON
        float MinCurrent; // バンク最低負荷[A] // Add 2006.01.26 J.S
    } BANK_T;

    //////////////////////////////////////
    // 配電線管理テーブル枠定義
    typedef struct BRANCH_T0{
        int  kanri;   // 管理No. 
        int  pbNum;   // ブランチ計算結果レコードNo  2004.04.20 Add
        // ノード管理No. 
        struct BRANCH_T1{    // ノード管理No. 
            int  from;  // 始点 
            int  to;   // 終点 
        } node;

        struct BRANCH_T2{
            int  num;
            int  no[Line_MAX];
        } vector ;    // 配電線を構成する線分 

        // ノード管理No. 
        struct BRANCH_T3{    // 変圧器情報 
            int  no;   // 接続SVR 管理No. 
        } svr;

        //////////////////////////////////////////////////////////////////////////
        // Add 2006.01.06 S.S
        struct BRANCH_T4{    // 変圧器情報 
            int  no;   // 接続TVR 管理No. 
        } tvr;
        //////////////////////////////////////////////////////////////////////////

        struct BRANCH_T5{
            short check;  // チェックフラグ   : ON or OFF
            short flag;  // ブランチ活線状態 : ON_ALL,ON_FROM,ON_TO,OFF_ALL
            short CB;   // ＣＢ状態   : ON_ALL,ON_FROM,ON_TO,OFF_ALL
        } kassen;    // 活線状況管理
        struct BRN_1{
            CString strName; // 線種名称
            short inputMode; // 入力モード（ID_Z_INPUT or ID_Z_DB）
            short line;  // 架空電線路(ID_LINE_OVER)・地中電線路(ID_LINE_UNDER)
            UINT len;  // 線種長
            double zR;   // 直接入力時のインピーダンス:R
            double zX;   // 直接入力時のインピーダンス:X
            double zC;   // 直接入力時のインピーダンス:C
            float OverCurr; // 通過電流許容値
            float OverCurr2; // Add 2006.02.01 S.S 事故時許容電流
            // ADAM2203 (Hyron) 2016/10/18 Start
            CString sensyu;//線種（材質）
            int size;//配電線の太さ
            // ADAM2203 (Hyron) 2016/10/18 End
        } cable;
        float permit;   // 通過電流許容値
        float Current;  // 適正範囲逸脱個所表示用（配電線通過電流）
        short Reasonable;  // 逸脱判定OFF/ON

        short  modeLV;  // 解析対象フラグ
        struct BRN_LV_1{
            CString strName; // 線種名称
            short inputMode; // 入力モード（ID_Z_INPUT or ID_Z_DB）
            UINT len;  // 線種長
            double zR;   // 直接入力時のインピーダンス:R
            double zX;   // 直接入力時のインピーダンス:X
        } cableW;  // 低圧系統
        BOOL dummy;
    } BRANCH;

    //////////////////////////////////////
    // 線種ＤＢテーブル枠定義
    typedef struct CABLE_DB0{
        short no;   // 管理No
        CString strName; // 線種名称
        short size;  // サイズ
        double r,x,c;  // R,X,C
        float permit;  // 許容値
        float jiko;  // 事故時許容値 // Add 2006.01.26 J.S
        short type;  // 電線種別
        // ADAM2203 (Hyron) 2016/10/18 Start
        CString senyu; //電線(材質)
        int bra_size;//配電線の太さ
        // ADAM2203 (Hyron) 2016/10/18 End
    } CABLE_DB;

    //////////////////////////////////////
    // フィーダーテーブル枠定義
    typedef struct FEEDER_T0{
        short no;   // フィーダーNo（FCB管理No＝gen_t[].kanri）
        short BNK;  // 所属バンクNo
        int  node;  // 配電線名
        short Conv;  // 電線データ補正有無
        short Reasonable; // 逸脱判定OFF/ON

        // ADAM No.0002-1 P63 Add start
        struct _t_keisoku{
            // ADAM1203 (SinoCom) 2014/10/20 Start
            //int  dir; // 潮流方向 0:"順", 1:"逆", 2:"－", 3: " "   (デフォルトは－)
            int  dir; // 潮流方向 0:"順", 1:"逆", 2:"－"(使用しない, 3: " "(欠測)
            // ADAM1203 (SinoCom) 2014/10/20 End
            int  cur; // 通過電流(A)【0～999999】 -1:空白(データ欠損または新規作成時)
            // ADAM1203 (SinoCom) 2014/10/20 Start
            float rikiritu;  // 力率(%)【-100.00～100.00】 マイナス値は進み力率
            // ADAM1203 (SinoCom) 2014/10/20 End
        }keisoku[LOAD_MODE_MAX]; // 計測値

        struct _t_settei{
            // ADAM1203 (SinoCom) 2014/10/20 Del Start
            //float nobi; // 伸び率(%)【-99.9～999.9】10000:空白(データ欠損または新規作成時)
            // ADAM1203 (SinoCom) 2014/10/20 Del End
            int  dir; // 潮流方向 0:"順", 1:"逆"
            int  cur; // 通過電流(A)【0～999999】データ欠損または新規作成時は「0」
            // ADAM1203 (SinoCom) 2014/10/20 Start
            float rikiritu;  // 力率(%)【-100.00～100.00】 マイナス値は進み力率
            // ADAM1203 (SinoCom) 2014/10/20 End
        }settei[LOAD_MODE_MAX]; // 設定値

        struct _t_date{
            int  yy; // 年
            int  mm; // 月
            int  dd; // 日
            int  hh; // 時
        }date[LOAD_MODE_MAX]; // 日時

        struct _t_V{
            int  bf; // 工事対象設備連系前(V)【5800～7000】
            int  af; // 工事対象設備連系後(V)【5800～7000】
        }V[LOAD_MODE_MAX]; // 送出電圧
        // ADAM No.0002-1 P63 Add end
        // ADAM2201 (Hyron) 2016/10/19 Start
        float upVol;       // 最適タップ 上限電圧（V）
        float downVol;     // 最適タップ 下限電圧（V）
        // ADAM2201 (Hyron) 2016/10/19 End

    } FEEDER_T;

    //////////////////////////////////////
    // フリッカ解析条件テーブル枠定義
    typedef struct FLICKER0{
        struct FLICKER1{
            int  id;  // 解析対象連系機器(発電機/負荷)Id
            int  no;  // 解析対象連系機器管理No 
        } device;   // 解析対象連系機器(発電機/負荷)
        struct FLICKER2{
            int  flag;  // 0:OFF(反映しない),1:ON(反映する)
            double P;   // 出力(負荷)変動量(Hz)
            double rikiritu; // 変動出力(負荷)の力率(％)
            int  r_flag;  // 力率フラグ 0:遅れ,1:進み
            double freq;  // 変動周波数(Hz)
        } data[3];  // 解析データ
        struct FLICKER3{
            int  so;   // 結果表示相
            double Vol[3];  // フリッカ発生設備連系前のノード電圧結果　[重負荷/軽負荷/その他負荷](V)
            double dVol[3][3]; // フリッカ発生設備連系後のノード電圧差　　[重負荷/軽負荷/その他負荷](V)
        } kekka;
    } FLICKER;

    ////////////////////////////////////////////////////////////////////////////
    // 潮流計算結果テーブル枠定義（配電線）
    ////////////////////////////////////////////////////////////////////////////
    typedef struct {
        int  no;   // 配電線管理Ｎｏ
        double P[3];  // 有効電力 
        double Q[3];  // 無効電力 
        double I[3];  // 電流位相 Add rsc
        double Ideg[3];  // 電流
        double  bfI[3];  // ループ投入前電流  2003.12.9 S.Mura
        // POINT pos1;  // 結果表示位置 
        // POINT pos2;  // 結果表示位置 
        int  visual;  // ﾋﾞｼﾞｭｱﾙ表示時のFrom側かTo側表示場所
        int  dir;  // 潮流方向
        int     bfdir;  // ループ投入前潮流方向  2003.12.9 S.Mura
        int  fcb;  // 所属ＦＣＢ 1:自系統, 2:他系統  2004.1.15 S.Mura
        double svr_impd; // SVRインピーダンス補正値
        int  svr_rev; // SVRインピーダンス補正要否フラグ
    } structResLfacBranch;

    ////////////////////////////////////////////////////////////////////////////
    // 潮流計算結果テーブル枠定義（ノード）
    ////////////////////////////////////////////////////////////////////////////
    typedef struct {
        int  no;  // ノード管理Ｎｏ
        float kV;   // ノード電圧(活線電圧チェック結果) 
        float lVol[3]; // 負荷電圧特性でのノード電圧(潮流計算結果)
        double P;  // 有効電力 
        double Q;  // 無効電力 
        double I;  // 電流
        double bfI; // ループ投入前電流  2004.01.20 S.Mura
        double vol; // ノード電圧 
        double deg; // ノード位相角 
        double per; // 一番大きい計算結果を１とした時の比率(ﾋﾞｼﾞｭｱﾙ表示)
        int  dir; // 潮流方向
        // ADAM1602 (Hyron) 2015/09/11 Start
        short   dirChangeFlag;    // 潮流方向変更点フラグ 0:潮流方向変更点ではない 1:潮流方向変更点
        // ADAM1602 (Hyron) 2015/09/11 End
        double Pp;  // 有効電力(Power:負荷分) 
        double Qp;  // 無効電力(Power:負荷分) 
        double Ip;  // 電流(Power:負荷分)  // ADAM 147 Add　→ ADAM 161 Del →ADAM169 add
        double Pz;  // 有効電力(Z分) 
        double Qz;  // 無効電力(Z分) 
        struct _t_Vgraph{   
            int  Root_Tno; // ルートテーブル管理№
            int  Root_Nno; // ルートテーブルのノード管理№保管場所
            float Vol;  // 母線電圧(kV)          // 瞬時電圧変動解析（特殊負荷）の変動前結果
            float VolAV;  // 母線電圧(kV)（瞬低解析専用） 平均値
            float Vdrop;  // 電圧降下値(V)（瞬低解析専用） (重負荷/軽負荷) // 瞬時電圧変動解析（特殊負荷）の変動後結果
            POINT pos;  // 母線電圧ベクトルポジション加工用 
        } Vgraph;    // [LoadMode][SVR動作回数]分容易

    } structResLfacNode;

    // フリッカ計算テーブル枠定義（ノード）
    typedef struct R_FLIC_0{
        int  no;   // ノード管理Ｎｏ
        double V1;   // フリッカ接続前電圧 (V)
        double dVso;  // 総合ΔV10
    } structResFlicNode;

    typedef struct {
        int  no;  // SVR管理Ｎｏ
        double Q; // 無効電力 
        // 到達電圧はノード結果テーブルより参照
    } structResLfacSVC;

    ///////////////////////////////////////////////////////////////////////
    // 潮流解析結果テーブル枠定義
    ///////////////////////////////////////////////////////////////////////
    typedef struct {
        int  no;  // SVR管理Ｎｏ
        double P[3]; // 有効電力 
        double Q[3]; // 無効電力 
        double I[3]; // 電流 
        POINT pos1; // 結果表示位置 
        POINT pos2; // 結果表示位置
        // Conv 2006.09.07 J.S
        // UINT dir; // 潮流方向 
        short dir; // 潮流方向 

        // Add 2006.12.13 J.S
        // 一次二次タップ電圧
        float tapV1, tapV2; 
        //  基準整定電圧
        float KVol;
        //  目標点電圧
        float Vr;
        // 通過電流
        double cur;
        // LDC整定値
        complex LDC;
        // 到達電圧はノード結果テーブルより参照
    } structResLfacSVR;

    typedef struct {
        int  no;  // SVR管理Ｎｏ
        double P[3]; // 有効電力 
        double Q[3]; // 無効電力 
        double I[3]; // 電流 
        POINT pos1; // 結果表示位置 
        POINT pos2; // 結果表示位置 
        // Conv 2006.09.07 J.S
        // UINT dir; // 潮流方向 
        short dir; // 潮流方向 

        // Add 2006.12.13 J.S
        // 一次二次タップ電圧
        float tapV1, tapV2; 
        //  基準整定電圧
        float KVol;
        //  目標点電圧
        float Vr;
        // 通過電流
        double cur;
        // ADAM1605 (Hyron) 2015/11/16 Start
        // LDC整定値
        complex LDC; // ADAM 1605 Add
        // ADAM1605 (Hyron) 2015/11/16 End
        // 到達電圧はノード結果テーブルより参照
    } structResLfacTVR;

    class complex {
    public:
        double re;
        double im;
        complex(double a,double b=0.0){re=a; im=b;}
        complex(){ re=0; im=0;}
        complex  operator -();
        complex& operator =(complex& a);
        complex& operator +=(complex& a);
        complex& operator -=(complex& a);
        complex& operator *=(complex& a);
        complex& operator /=(complex& a);
        double abs();
        complex compl();
        double getRe();
        double getIm();
        void setRe(double r);
        void setIm(double i);
        friend complex operator +(complex&,complex&);
        friend complex operator -(complex&,complex&);
        friend complex operator *(complex&,complex&);
        friend complex operator /(complex&,complex&);
        friend int operator ==(complex&,complex&);
        //   friend ostream& operator <<(ostream&,complex&);
        //   friend istream& operator >>(istream&,complex&);
    };


    // ＯＣＴ付きＶＳ設置個所検討
    typedef struct {
        int  no;   // ランチ管理Ｎｏ
        double I[3][2]; // [短絡容量計算結果/結果編集][発電機連系前後の電流値]
        double Inv;  // 逆変換機能付き発電機からの短絡電流  2004.09.10 Add
        int  dir;  // 電流方向
        BOOL rFlag;  // 逆潮流フラグ
    } structResLfscBranch;

    ////////////////////////////////////////////////////////////////////////////
    // 短絡容量結果テーブル枠定義（ノード）
    ////////////////////////////////////////////////////////////////////////////
    typedef struct R_SC_0{
        int  no;   // ノード管理Ｎｏ
        double P[3][2]; // [短絡容量計算結果/結果編集] [発電機無し/有り]時における､短絡容量 P 
        double I[3][2]; // [短絡容量計算結果/結果編集] [発電機無し/有り]時における､短絡容量 I 
        // double per[5];  // 一番大きい計算結果を１とした時の比率(ﾋﾞｼﾞｭｱﾙ表示)
        double Inv;  // 逆変換機能付き発電機からの短絡電流  2004.09.10 Add
        complex Z[2];  // スイングからの合成インピーダンス
        BOOL check[2]; // [発電機無し/有り]時における､このノードが判定領域に入るか(TRUE)入らないか(FALSE)のフラグ
        int  bnum;  // ブランチ接続最終（0～10）
        struct R_SC_1{
            BOOL check;  // [短絡容量計算結果/結果編集] データ設定時のチェックフラグ
            int  no;   // そのノード接続ブランチNo.
            int  node;  // branch[i] のノードNo.
            double Pb[2];  // [発電機無し/有り]時における､そのノード接続ブランチ短絡容量
            complex Z[2];  // [発電機無し/有り]時における､そのノード接続ブランチ(branch[i].node)までのインピーダンス（＝PbをZにした複素数）
            double Ib[2][2]; // [短絡容量計算結果/結果編集] [発電機無し/有り]時における､そのノード接続ブランチ短絡電流
            complex I[2][2]; // [短絡容量計算結果/結果編集] [発電機無し/有り]時における､そのノード接続ブランチ短絡電流（Ibの複素数）
        } gen;
        struct R_SC_2{
            BOOL check;  // [短絡容量計算結果/結果編集] データ設定時のチェックフラグ
            int  no;   // そのノード接続ブランチNo.
            int  node;  // branch[i] のノードNo.
            double Pb[2];  // [発電機無し/有り]時における､そのノード接続ブランチ短絡容量
            complex Z[2];  // [発電機無し/有り]時における､そのノード接続ブランチ(branch[i].node)までのインピーダンス（＝PbをZにした複素数）
            double Ib[2][2]; // [短絡容量計算結果/結果編集] [発電機無し/有り]時における､そのノード接続ブランチ短絡電流
            complex I[2][2]; // [短絡容量計算結果/結果編集] [発電機無し/有り]時における､そのノード接続ブランチ短絡電流（Ibの複素数）
        } branch[NODE_IN_BRANCH_MAX];
        BOOL rFlag;   // 逆潮流時に判定外とする柱状リクローザ（TRUE=判定しない）
        int  dir;   // 電流方向
    } structResLfscNode; // [0]:保護協調/整定計算用/フリッカ用｡[1]:保護協調/整定計算用｡[2],[3]:整定計算専用｡[4]：分流効果専用

    //////////////////////////////////////
    // 電源パターン管理テーブル枠定義
    typedef struct GEN_T0{
        int  kanri;   // 管理No. 
        int  node;   // 接続ノード管理No.
        short pattern;  // パターンＩＤ 1:FCB,2～発電機
        short dir;   // 方向 
        POINT pos;   // 接続ノード相対座標
        // Add 2003.10.27 J.S
        short type;   // 発電機種別 0:同期発電機、1:誘導発電機、2:逆変換装置付
        //////////////////////////////////////////////////////////////////////////
        // Add 2006.01.30 S.S
        BOOL unuse;  // 運用除外モード　False:除外しない、True:除外する
        //////////////////////////////////////////////////////////////////////////
        struct G_DATA1{    // データ 
            short kousoku[2];  // 拘束条件  V or Q  [SetArea]

            // ADAM No.0007-1 P82 Chg start
            float CAP[2];   // 電源定格容量(kVA) [SetArea] 
            //float CAP[2];   // 定格容量(kVA) [SetArea] 【0～999999】
            // ADAM No.0007-1 P82 Chg end

            // Conv 2006.02.28 S.S
            /*
            float P[2][3];  // 有効電力(kW)   [SetArea][重負荷/軽負荷/その他負荷]
            float Q[2][3];  // 無効電力(kVAR)  [SetArea][重負荷/軽負荷/その他負荷]
            float V[2][3];  // 端子電圧(V)   [SetArea][重負荷/軽負荷/その他負荷]
            */
            float P[2][2][LOAD_MODE_MAX];  // 有効電力(kW)   [常時/瞬時][SetArea][重負荷/軽負荷/その他負荷]
            float Q[2][2][LOAD_MODE_MAX];  // 無効電力(kVAR)  [常時/瞬時][SetArea][重負荷/軽負荷/その他負荷]
            float V[2][2][LOAD_MODE_MAX];  // 端子電圧(V)   [常時/瞬時][SetArea][重負荷/軽負荷/その他負荷]
            float Xdd;   // 発電機リアクタンス
            //  float Is;    // 短絡電流供給能力
            short SS;    // 変電所
            short Bank;   // バンク
            float OCR;   // OCR整定値（Ａ）
            float KyoAmp;   // 許容電流値（Ａ） // Add (R.T) 2003.03.20

            // ADAM No.0002-2 P63 Del start  (FCB)
            float dLoad[2];  // 按分用負荷   [SetArea]
            // ADAM No.0002-2 P63 Del end

            // Conv 2006.02.28 S.S
            // float rikiritu[2][3]; // 力率(%)・・・正数 [SetArea][重負荷/軽負荷/その他負荷]
            float rikiritu[2][2][LOAD_MODE_MAX]; // 力率(%)・・・正数 [常時/瞬時][SetArea][重負荷/軽負荷/その他負荷]

            // ADAM No.0007-2 P82 Del start
            float riyou[LOAD_MODE_MAX];  // 利用率（％）[重負荷/軽負荷/その他負荷]
            // ADAM No.0007-2 P82 Del end

            // Add 2003.10.27 J.S
            float CurLimit;  // 通過電流制限値(A)
            float X;    // SG:初期過渡ﾘｱｸﾀﾝｽ、IG:拘束ﾘｱｸﾀﾝｽ
            float TrCAP;   // 分散型電源構内Tr容量(kVA) // Add 2005.03.01 J.S
            float TrX;   // 分散型電源構内Trｲﾝﾋﾟｰﾀﾞﾝｽ(マシンベース)
            float CT[2];   // ＣＴ比
            float TapIns[2];  // 定時限要素タップ
            float TapDim[2];  // 瞬時要素タップ
            float DeltaIns;  // 定時限要素タップ刻み幅
            float DeltaDim;  // 瞬時要素タップ刻み幅

            //////////////////////////////////////////////
            // ADAM No.0007-1 P82 Add start
            short housiki;  // 発電方式  0:太陽光，1:風力，2:燃料電池，3:ディーゼル，4:低圧集約
            CString strGenPower; // 発電率定義ファイル名
            float Pritsu[LOAD_MODE_MAX];  // 発電率（％）[重負荷/軽負荷/その他負荷]

            struct _t_syunji{
                short bf; // 変動前(%)
                short af; // 変動後(%)
            }syunji;  // 瞬時電圧変動  瞬時電圧変動における｛常時，瞬時｝の出力比率

            struct _t_pcs
            {
                // ADAM 39 Add start
                BOOL CntlEnd; // PCS制御終了フラグ TRUE:制御終了
                // ADAM 39 Add end
                short type; // 0:力率一定制御, 1:電圧一定制御
                float Vref; // 電圧一定制御 基準電圧(V)
                float Cref; // 力率一定制御 運転力率(%)
            } pcs; // PCS制御方式

            // ADAM No.0007-1 P82 Add end
            //////////////////////////////////////////////
        } data;

        // Add 2003.11.03 J.S
        struct G_DATA3{    // データ 
            BOOL checkFL;  // 既設フリッカ設定
            float P;    // 変動発電量（kW）
            float rikiritu;  // 力率(%)
            float cycle;   // 変動頻度（回／分）
        } flicker;

        // Comm 2004.01.17 J.S
        /*
        // float C_LimitX;  // 限流リアクタンス(％) 系統ベース
        // [0]:保護協調解析､[1]:整定値解析､[2]:瞬低解析 時の専用インピーダンス（％) 系統ベース
        struct {
        float EtcImp[3]; // ＳＧ　[0]:連系用Tr等のｲﾝﾋﾟｰﾀﾞﾝｽ,[1]:連系用Trのｲﾝﾋﾟｰﾀﾞﾝｽ,   [2]:未使用
        // ＩＧ　[0]:連系用Tr等のｲﾝﾋﾟｰﾀﾞﾝｽ,[1]:限流ﾘｱｸﾄﾙ等のｲﾝﾋﾟｰﾀﾞﾝｽ,[2]:[1]とリンク
        float GenCAP;  // 整定計算(SG)用､電力容量[kW]
        float TrCAP;  // 受電点変圧器定格容量合計値[kVA]
        short G_reverse; // 発電機連系条件（ON:逆潮有り　OFF:逆潮無し）
        float IGcos;  // 瞬時電圧変動時の力率％（誘導発電機専用）
        } terms;
        */
        float Current;  // 適正範囲逸脱個所表示用（ＦＣＢ通過電流）
        short Reasonable;  // 逸脱判定OFF/ON
        int  dummy;
    } GEN;


    typedef struct {
        int  no;    // SVR管理No.
        float TotalTime;  // 各SVRの動作時間合計値[sec]
        struct _t_count {
            short lf;   // 潮流計算動作有無 実行した:ON　実行しなかった:OFF
            short reset;  // 潮流計算により不感帯にはいった場合の状態動作有無 ﾘｾｯﾄ状態:ON　動作状態:OFF
            float tap;  // SVRタップ[V]
            float time;  // SVRタップ調整動作時間(sec)
            float dVOL;  // 偏差電圧(%)
            float sekibun; // 残りの積分時間（前回の積分時間-SVR動作時間[sec]*偏差電圧[%]）
        } count[ACT_MAX];
    } structActSVR;

    //////////////////////////////////////
    // 短絡保護協調解析条件テーブル枠定義
    typedef struct HOGO0{
        int  CalMode;  // 解析種別  0:短絡電流(ID_CUR),1:もらい事故(ID_MORAI),2:分流効果(ID_BUNRYU);
        int  ScNode;   // 事故ノードNo.
        int  TermsGen;  // 連系発電機No.
        int  TermsNode;  // 連系点ノードNo.
        struct HOGO1{
            int  node;  // 短絡電流解析結果表示ﾉｰﾄﾞ管理No
            double cur[2];  // 短絡電流値
        }kekka;    // 解析結果 
    } HOGO;

    typedef struct {
        int  no;    // TVR管理No.
        float TotalTime;  // 各TVRの動作時間合計値[sec]
        struct _t_count{
            short lf;   // 潮流計算動作有無 実行した:ON　実行しなかった:OFF
            short reset;  // 潮流計算により不感帯にはいった場合の状態動作有無 ﾘｾｯﾄ状態:ON　動作状態:OFF
            float tap;  // TVRタップ[V]
            float time;  // TVRタップ調整動作時間(sec)
            float dVOL;  // 偏差電圧(%)
            float sekibun; // 残りの積分時間（前回の積分時間-TVR動作時間[sec]*偏差電圧[%]）
        } count[ACT_MAX];
    } structActTVR;

    typedef struct {
        int  no;
        BOOL wCheck; // ワークチェックフラグ   : TRUE or FALSE
        struct _t_Root{
            int  rno; // ルートNo
            short check; // ルートチェックフラグ   : ON or OFF
        } Root[2]; // (old=rootB_t.check/rootB2_t.check)
        int  dummyBranch;
        int  csflg;   // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
    } structWorkBranch;

    typedef struct {
        int  no;
        float P[3][2]; // 重負荷､軽負荷
        float Q[3][2]; // 重負荷､軽負荷
        float I[3][2]; // 重負荷､軽負荷 Add 1996.12.27 J.S
        // POINT pos;  // 結果表示位置 
        struct _t_kassen{
            int  check; // チェックフラグ   : ON or OFF
            int  flag; // ブランチ活線状態 : ON_ALL,ON_FROM,ON_TO,OFF_ALL
        } kassen;   // 活線状況管理
        int  dummyGen;
    } structWorkGen;

    typedef struct {
        int  no;
        float P[3][3];
        float Q[3][3];
        float I[3][3];
        // POINT pos[2];  // 結果表示位置 
        //int  csflg;  // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
    } structWorkLoad;

    typedef struct {
        int  no;
        // float Rl[3];   // 三相不平衡解析時の合成インピーダンス負荷:R
        // float Xl[3];   // 三相不平衡解析時の合成インピーダンス負荷:X
        BOOL wCheck;   // ワークチェックフラグ   : TRUE or FALSE
        int  dummyNode;
        int  csflg;   // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
        /*
        struct {   
        float dV;   // 電圧偏差
        POINT pos;  // 母線電圧ベクトルポジション加工用 (node_ub[i].cure.vol[x]を加工)
        } VgraphUB[3];
        struct {
        BOOL set;  // 解析対象チェック・・不平衡解消地点設定,配電用変電所設定ダイアログボックス（選択）
        double V1[3];  // 相間電圧計測値・・・不平衡解消地点設定,配電用変電所設定ダイアログボックス
        double V2[3];  // 相間電圧計測値・・・(計算用、ファイル出力なし)
        BOOL cAlimit; // 電圧不平衡率使用フラグ・・不平衡解消地点設定ダイアログボックス
        BOOL cBlimit; // 電圧不平衡係数使用フラグ・・不平衡解消地点設定ダイアログボックス
        double Alimit;  // 電圧不平衡率・・不平衡解消地点設定ダイアログボックス
        int  fAlimit; // 電圧不平衡率判定結果(計算用、ファイル出力なし)　OK：制約範囲内、ERR：制約を満たさない
        double Blimit;  // 電圧不平衡係数 ±・・不平衡解消地点設定ダイアログボックス
        double wBlimit; // 電圧不平衡係数(計算用、ファイル出力なし) 　不平衡解析実行時に上記の値をコピー。Ｂ行列更新時に２分探索にてデータを更新する
        int  nBlimit; // 電圧不平衡係数更新回数(計算用、ファイル出力なし)　0～n
        } Unbalance;
        */
    } structWorkNode;

    typedef struct {
        int  no;
        float P;
        float Q;
        float I;
        // float vol;
        short err;
        short Vflag;
        short fukantai; // 計算結果が不感帯に入っているかのフラグ -1:ERR 0:OK 
        struct _t_act {
            short reset;  // 潮流計算により不感帯にはいった場合の状態動作有無 ﾘｾｯﾄ状態:ON　動作状態:OFF
            float time;  // SSR出力調整動作時間(sec)
            float dVOL;  // 偏差電圧(%)
        } act;
        // POINT pos;  // 結果表示位置
        int  csflg;   // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
    } structWorkSSC;

    typedef struct {
        int  no;
        float P;
        float Q;
        float I;
        // float vol;
        short err;
        short Vflag;
        short fukantai; // 計算結果が不感帯に入っているかのフラグ -1:ERR 0:OK 
        struct _t_act {
            short reset;  // 潮流計算により不感帯にはいった場合の状態動作有無 ﾘｾｯﾄ状態:ON　動作状態:OFF
            float time;  // SSC出力調整動作時間(sec)
            float dVOL;  // 偏差電圧(%)
        } act;
        // POINT pos;  // 結果表示位置 
        int  csflg;   // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
    } structWorkSSR;

    typedef struct {
        int  no;
        double Qsvc;   // SVC無効出力（潮流計算反映値:P=0.0､Q=-Qsvcで指定）
        double Qsvc_B;   // SVC無効出力:積分値
        double QsvcOld;  // SVC無効出力（潮流計算反映値:前回の値）
        double k;    // 係数
        double Xsvc;  // 配変からＳＶＣ連系点までのイピーダンス(%)
        double Vsvc;  // SVC端電圧計測値
        double VsvcOld; // SVC端電圧計測値：Ｑ（潮流計算結果:前回の値）
        double Pl;   // SVC設置点より上流側の線路潮流：Ｐ
        double Ql;   // SVC設置点より上流側の線路潮流：Ｑ
        double QlOld;  // SVC設置点より上流側の線路潮流：Ｑ（潮流計算結果:前回の値）
        short fukantai; // 計算結果が不感帯に入っているかのフラグ -1:ERR 0:OK 
        short err;  // エラーNo　Add 2004.04.05
        int  csflg;   // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
    } structWorkSVC;

    typedef struct {
        int  no;
        float cur[3];    // 通過電流値(A)
        float vol[3];    // 目標点電圧計算値(V)
        int  err[3];    // エラーコード　0:無し,1:ハンチング,2:上限超過,3:下限超過
        short ponping[3];   // ハンチング回数
        short TapId[3];   // ハンチング回数をﾁｪｯｸするためのタップ上下動作ＩＤ
        short fukantai[3];  // 計算結果が不感帯に入っているかのフラグ -1:ERR 0:OK 
        long ActTapNum;   // 風力発電機解析　SVRタップ動作回数解析における1日のタップ動作回数
        short ActTapLDC;   // SVR整定値判定（SVR動作頻度解析結果）OK or ERR
        float tap_old[2][3];  // 一次,二次 前回のタップ電圧(V)
        float TapHistory[3][3]; // 重/軽のタップ収束における履歴（前回のタップ電圧）･･･タップ初期値(定常状態の把握)に使用
        struct _t_root {
            //  int  sno; // ＳＶＲ管理No
            int  rno; // ルートNo
            int  node[2];// ＳＶＲ接続ﾉｰﾄﾞがroot_t[no].node[?]に設定されている場所　0:一次側,1:二次側
        } root;
        int  csflg;   // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
        int  fcbdir;   // FCB設置方向 0: FCBがSVRの左側に設置 1: FCBがSVRの右側に設置
        // Conv 2006.10.16 J.S
        // fcbdirは、当初、SVRの一次側がFCBに近い方のノードであれば、"0"、遠い方であれば、"1"をセットしていた。
        // しかし、下記の値のセット内容(BRANCH_FROM/BRANCH_TO)から、ブランチのFrom or To側がセットされている物として、
        // 当該変数を各所で使用している。このため接続SVRブランチのFrom or To側をセットするようにする。

        int  dir;   // 潮流方向 1:順方向（一次から二次） -1:逆方向（二次から一次）
    } structWorkSVR;

    typedef struct {
        int  no;
        float cur[3];    // 通過電流値(A)
        float vol[3];    // 目標点電圧計算値(V)
        int  err[3];    // エラーコード　0:無し,1:ハンチング,2:上限超過,3:下限超過
        short ponping[3];   // ハンチング回数
        short TapId[3];   // ハンチング回数をﾁｪｯｸするためのタップ上下動作ＩＤ
        short fukantai[3];  // 計算結果が不感帯に入っているかのフラグ -1:ERR 0:OK 
        long ActTapNum;   // 風力発電機解析　SVRタップ動作回数解析における1日のタップ動作回数
        short ActTapLDC;   // SVR整定値判定（SVR動作頻度解析結果）OK or ERR
        float tap_old[2][3];  // 一次,二次 前回のタップ電圧(V)
        float TapHistory[3][3]; // 重/軽のタップ収束における履歴（前回のタップ電圧）･･･タップ初期値(定常状態の把握)に使用
        struct _t_root {
            int  rno; // ルートNo
            int  node[2];// ＳＶＲ接続ﾉｰﾄﾞがroot_t[no].node[?]に設定されている場所　0:一次側,1:二次側
        } root;
        int  csflg;   // CSV編集済フラグ 0:未編集 1:編集済  2004.04.20  Add
        int  fcbdir;   // FCB設置方向 0: FCBがSVRの左側に設置 1: FCBがSVRの右側に設置
        int  dir;   // 潮流方向 1:順方向（一次から二次） -1:逆方向（二次から一次）
    } structWorkTVR;


    //////////////////////////////////////
    // 負荷管理テーブル枠定義
    typedef struct LOAD_0{
        int  kanri;   // 管理No. 
        int  node;   // 接続ノード管理No.
        short pattern;  // パターンＩＤ 1:単一需要家　(2:特殊負荷)
        short dir;   // 方向 
        POINT pos;   // 接続ノード相対座標 
        //////////////////////////////////////////////////////////////////////////
        // Add 2006.01.30 S.S
        BOOL unuse;  // 運用除外モード　False:除外しない、True:除外する
        //////////////////////////////////////////////////////////////////////////
        struct LOAD_1{
            struct LOAD_1_1{
                float P;  // KW設定値

                // ADAM No.0009-2 P90 Del start
                float Cur; // A設定値
                float Cur_a; // A設定値（電圧変動解析按分結果）
                // ADAM No.0009-2 P90 Del end

            } high;  // 高圧お客様
            struct LOAD_1_2{
                float P;  // KW設定値

                // ADAM No.0009-2 P90 Del start
                float Cur; // A設定値
                float Cur_a; // A設定値（電圧変動解析按分結果）
                // ADAM No.0009-2 P90 Del end

            } Tr;  // Trお客様
            struct LOAD_1_3{
                float P;  // KW設定値

                // ADAM No.0009-2 P90 Del start
                float Cur; // A設定値
                // ADAM No.0009-2 P90 Del end
                // ADAM1203 (SinoCom) 2014/10/20 Start
                float rikiritu; // 力率(%)【-100.00～100.00】 マイナス値は進み力率
                // ADAM1203 (SinoCom) 2014/10/20 End
            } spot;  // スポット負荷
            short target;   // 計算対象種別

            // 常時データ ↓
            float P[2][LOAD_MODE_MAX];  // 高圧お客様(kW) [SetArea][重負荷/軽負荷/その他負荷]【0.00～999999.99】
            float Q[2][LOAD_MODE_MAX];  // 無効電力(kVAR) [SetArea][重負荷/軽負荷/その他負荷]【0.00～999999.99】
            // 常時データ ↑

            // ADAM No.0009-1 P90 Add start
            struct _t_syunji {
                short bf;  // 変動前(%)【0～999】
                short af;  // 変動後(%)【0～999】
                float Pbf[LOAD_MODE_MAX]; // 変動前 有効電力：常時電圧変動の有効電力×変動前(%)
                float Qbf[LOAD_MODE_MAX]; // 変動前 無効電力：常時電圧変動の無効電力×変動前(%)
                float Paf[LOAD_MODE_MAX]; // 変動後 有効電力：常時電圧変動の有効電力×変動後(%)
                float Qaf[LOAD_MODE_MAX]; // 変動後 無効電力：常時電圧変動の無効電力×変動後(%)
            }syunji;  // 瞬時電圧変動  瞬時電圧変動における｛常時，瞬時｝の出力比率
            // ADAM No.0009-1 P90 Add end

            // ADAM1203 (SinoCom) 2014/10/20 Del Start
            //float rikiritu[2][LOAD_MODE_MAX]; // 力率(%)      [SetArea][重負荷/軽負荷/その他負荷] 
            // ADAM1203 (SinoCom) 2014/10/20 Del End

            // ADAM No.0009-2 P90 Del start
            float riyou[2][LOAD_MODE_MAX]; // 利用率（％）  [SetArea][重負荷/軽負荷/その他負荷] 
            // ADAM No.0009-2 P90 Del end

        } data;
        struct LOAD_2{
            CString strName;  // お客様名称
            CString strCom;   // コメント
            float P;    // KW
        }memo[5];   // お客様メモ
        // Comm 2002.11.27 J.S Rev.3
        /*
        struct LOAD_3{
        BOOL set;  // 調整対象チェック・・・調整負荷設定ダイアログボックス（選択）
        double Ps[3];  // 短相負荷容量(kW)・・・調整負荷設定ダイアログボックス（単相負荷接続量）
        double Pa[3];  // 実負荷調整量(kW)・・・検証計算結果ダイアログボックス
        } Unbalance;
        */

        // Comm 2002.12.05 J.S 中国電システムは負荷の連系がありえない
        /*
        struct LOAD_4{
        float EtcImp[3]; // [0]:連系用Tr等のｲﾝﾋﾟｰﾀﾞﾝｽ,[1]:連系用Trのｲﾝﾋﾟｰﾀﾞﾝｽ,   [2]:未使用
        } terms;
        */
        // Add 2003.11.03 J.S
        struct LOAD_3{    // データ 
            short checkFL;  // 既設フリッカ設定
            short type;
            struct LOAD_3_1{
                float cap;   // 定格容量（kVA）
                float rikiritu;  // 力率(%)
                float cycle;   // 変動頻度（回／分）
            } type1;  // 電気炉
            struct LOAD_3_2{
                struct LOAD_3_3{
                    short num;    // 接続抵抗器数
                    float cap[5];    // 定格容量（kVA）
                    float rikiritu[5];  // 最大入力時力率（％）
                    float siyouritu[5];  // 使用率（％）
                    float cycle[5];   // 変動頻度（回／分）
                } so[3];
            } type2;  // 抵抗溶接機
            struct LOAD_3_4{
                float cur;   // 変動電流（Ａ）
                float rikiritu;  // 力率(%)
                float cycle;   // 変動頻度（回／秒）
            } type3;  // 電動機応用機器

        } flicker;
        short Reasonable; // 逸脱判定OFF/ON
    } LOAD;

    //////////////////////////////////////
    // ちらつき視感度曲線 ＤＢ
    typedef struct LUMINOUS0{
        int  d_num;  // データ数
        struct LUMINOUS1{
            double freq; // 変動周波数(Hz)
            double factor; // ちらつき視感度係数
        } data[LUMINOUS_MAX];
    } LUMINOUS;

    //////////////////////////////////////
    // 矩型波用ちらつき視感度曲線 ＤＢ
    typedef struct RECTWAVE0{
        int  d_num;  // データ数
        struct RECTWAVE1{
            double freq; // 変動周波数(Hz)
            double factor; // ちらつき視感度係数
        } data[RECTWAVE_MAX];
    } RECTWAVE;

    //////////////////////////////////////
    // フィーダー解析結果（短絡電流）解析対象の１バンク分：BANK_IN_FEEDER_MAX
    typedef struct RST_BANK_SC_0{
        BOOL bFlag;   // 計算結果取得済みフラグ
        int  no;    // バンクNo（Bank_t[].kanri）
        int  CurMinFeederNo; // 最小末端短絡電流フィーダのバンクテーブル内登録番号（Bank_t[].Feeder[i]のi）
        int  CurMinFeeder; // 最小末端短絡電流フィーダ（FCB管理No＝gen_t[].kanri）
        int  CurMinNode;  // 最小末端短絡電流ノード（node_t[].kanri）
        double CurMin;   // 最小末端短絡電流
        complex CurMinZ;  // バンク最小末端短絡電流ノードまでのインピーダンス（％）ADAM 1235 add
        int  CurMinLen;  // 配変から最小末端短絡電流ノードまでの線路超（m）ADAM 1235 add
        //float Xdd;   // 他フィーダ合成インピーダンス（自フィーダ含まず）
        struct FEEDER_0{
            int  no;   // フィーダーNo（FCB管理No＝gen_t[].kanri）
            BOOL bFlag;  // 計算結果取得済みフラグ
            // 選択した分散電源の連系前後の結果を記憶(CalNumSCと同期）
            complex Z;   // 短絡インピーダンス(配変結果＝生の短絡電流計算結果)
            complex Znet;  // フィーダ自体の系統のみの短絡インピーダンス(生の短絡電流計算結果-（バンクインピーダンス＋上位系インピーダンス))
            complex AtherFeederZ;// 他フィーダ系統インピーダンスの合計
            int  CurMinNode; // 最小末端短絡電流ノード
            double CurMin;  // 最小末端短絡電流
            complex CurMinZ; // 配変から最小末端短絡電流ノードまでのインピーダンス（％）ADAM 1235 add
            int  CurMinLen; // 配変から最小末端短絡電流ノードまでの線路超（m）ADAM 1235 add
            double Cur;  // 変電所短絡電流
            // Add 2007.03.11 J.S
            double CurFromNet; // 変電所短絡電流(系統側からの合計値)
        } Feeder[BANK_IN_FEEDER_MAX]; // フィーダ単位の結果
    } RST_BANK_SC; // バンク内結果

    //////////////////////////////////////
    // ＳＶＣ管理テーブル枠定義
    typedef struct SVC_T0{
        int  kanri;   // 管理No. 
        int  node;   // 接続ノード管理No. 
        int  psNum;   // SVC計算結果レコードNo  2004.04.20 Add
        POINT pos;   // 接続ノード相対座標
        //////////////////////////////////////////////////////////////////////////
        // Add 2006.01.30 S.S
        BOOL unuse;  // 運用除外モード　False:除外しない、True:除外する
        //////////////////////////////////////////////////////////////////////////
        struct SVC_T1{    // データ 
            short type;  // SVC動作種別　0:電圧一定制御,1:力率一定制御
            short LimitFlag; // Ｑリミッター有り:1/なし:0------------------------------------> 2003.01.28 J.S 後で削除
            double Qlimit[2]; // SVC-Qゲイン（現状[0]のみ使用､±Qlimit[0]）------------------------------------> 2003.01.28 J.S 後で削除
            double Vref[2]; // 電圧指令値 [SetArea]
            double Cref[2]; // 力率指令値 [SetArea]
            double fukantai; // 不感帯整定値(%) 

            // ADAM No.0004-1 P76 Chg start
            //  float CAP;  // 定格容量(kVar)
            float CAP;  // 定格容量(kVA)
            // ADAM No.0004-1 P76 Chg end

            float ActTime; // 動作時限(秒･%) 
        } data;
    } SVC;

    // SVRＤＢテーブル枠定義
    typedef struct SVR_DB{
        short no;   // 管理No
        CString strMaker; // メーカー
        CString strType; // 型式
        double CAP;  // 容量(kVA)
        short R67;  // 67リレー 0:なし、1:あり
        // ADAM1208 (SinoCom) 2014/10/20 Start
        float PT;     // PT比 60.0または61.8
        // ADAM1208 (SinoCom) 2014/10/20 End
        short ActTime; // 動作時間(秒）
        // Conv 2006.02.17 S.S
        // short Svrtype; // 逆送タイプ　1:完全逆送、2:逆送あり、3:逆送なし
        short Svrtype; // 逆送タイプ　1:逆送あり、0:逆送なし
        // Comm 2006.03.25 J.S
        // ADAM1613 (Hyron) 2015/09/11 Start
        short  DeviceType;  // 機器種別　0:Ⅰ型,1:Ⅱ型
        // ADAM1613 (Hyron) 2015/09/11 End
        /*
        double vol[2];  // 基準電圧(V)[一次/二次]
        double fukantai[2];// 不感帯(%)[一次/二次]
        double LDC_R[2]; // LDC(R)[一次/二次]
        double LDC_X[2]; // LDC(X)[一次/二次]
        */
    } SVR_DB;

    // SVRTAPＤＢテーブル枠定義
    typedef struct SVRTAP_DB0{
        short no;   // 管理No
        short tapno;  // タップ番号　1～9
        double vol;  // 電圧(V)[一次]
    } SVRTAP_DB;

    // TVRＤＢテーブル枠定義
    typedef struct TVR_DB{
        short no;   // 管理No
        CString strMaker; // メーカー
        CString strType; // 型式
        double CAP;  // 容量(kVA)
        double ActTime; // 動作時間(秒）
        short Tvrtype; // 逆送タイプ　1:逆送、0:なし
        // Comm 2006.03.25 J.S
        /*
        double vol[2];  // 基準電圧(V)[一次/二次]
        double fukantai[2];// 不感帯(%)[一次/二次]
        */
        // ADAM No.0003-1 P75 add start
        short R67;  // 67リレー (0:なし、1:あり)
        // ADAM No.0003-1 P75 add End
    } TVR_DB;

    // ＴＶＲ管理テーブル枠定義
    typedef struct TVR_T0{
        int  kanri;   // 管理No. 
        int  node[2];  // １－二次側ノード管理No. 
        int  branch;   // 接続ブランチ管理No.
        int  psNum;   // TVR計算結果レコードNo 
        struct TVR_1{    // データ 
            CString strMaker;  // 製造メーカー  // Add 2006.01.28 J.S
            CString strType;  // 型式    // Add 2006.01.28 J.S
            short phase1;  // 一次側ノード 0:from,1:to 
            short GyakusouKotei;  // 0:逆送時も自動運転を継続する。1:逆送時固定する
            short type;  // TVR種別　1:完全逆送,2:逆送あり,3:逆送なし
            BOOL TapFixed; // タップ固定　0:しない, 1:する
            float CAP;  // 容量(kVA)
            float tap[3][3]; // タップ(V)　[一次/二次/逆送時指定タップ][重負荷/軽負荷/その他負荷]
            float vol[2][2]; // 基準電圧整定値(V)[SetArea][一次/二次]
            float fukantai[2];// 不感帯整定値(%) [一次/二次]
            float LDC_R[2]; // LDC整定値 R(%) [一次/二次]
            float LDC_X[2]; // LDC整定値 X(%) [一次/二次]
            float ActTime; // 動作時間特性(秒･%) 
            float haba;     // 昇圧幅(V)
            //////////////////////////////////////////////////////////////////////////
            // Add 2006.01.24 S.S
            // Comm 2006.02.02 S.S
            // int     no;   // メーカ番号と型式番号なる主キー 1～
            // Comm 2006.02.02 S.S
            // int     TapNo;  // タップ番号
            //////////////////////////////////////////////////////////////////////////

            //////////////////////////////////////////////
            // ADAM No.0003-1 P75 Add start
            short   R67;  // 67リレー 0:未使用, 1:使用
            // ADAM No.0003-1 P75 Add end
        } data;
        struct TVR_T2{
            int  no;   // ルートNo
            int  node[2]; // ＴＶＲ接続ﾉｰﾄﾞがroot_t[no].node[?]に設定されている場所　0:一次側,1:二次側
        } root;
        // ADAM1606 (Hyron) 2015/09/11 Start
        float  Current;    // 適正範囲逸脱個所表示用（通過電流）
        float  permit;     // 通過電流許容値
        short  Reasonable; // 逸脱判定OFF/ON
        // ADAM1606 (Hyron) 2015/09/11 End
    } TVR;

    // TVRTAPＤＢテーブル枠定義
    typedef struct TVRTAP_DB0{
        short no;   // 管理No
        short tapno;  // タップ番号　1～9
        double vol;  // 電圧(V)[一次]
    } TVRTAP_DB;

    //////////////////////////////////////
    // 線分管理テーブル枠定義
    typedef struct VECTOR_T0{
        int  kanri;   // 管理No. 
        int  branch;   // 配電線管理No. 
        POINT s;    // 始点 絶対座標 
        POINT e;    // 終点 絶対座標
        BOOL dummy;
    } VECTOR;

    class CListPattern  
    {
    public:
        // 負荷/発電機パターンデータテーブル枠定義
        class CListInfo{
        public:
            //  long type;   // 31:発電機 32:負荷
            short ErrFlag;  // エラーフラグ　正常:0 ファイルが存在しない/オープンエラー:-1 データ不良:-2
            CString strFileName; // パターンファイル名称
            double pData[24]; // 時間別データ
            CListInfo() {
                ErrFlag = 0;
                strFileName = _T("");
            }
        };

    public:
        void RemoveAll();
        void RemoveAt(long index);
        CListInfo* GetList(long index);
        CListInfo* AddList();
        long GetCount()   { return m_ListInfo.GetCount(); };
        CListInfo* GetHead() { return m_ListInfo.GetHead(); };
        CListInfo* GetTail() { return m_ListInfo.GetTail(); };
        CListPattern();
        virtual ~CListPattern();

    private:
        CList<CListInfo*,CListInfo*>  m_ListInfo;

    };

    class CListRoute  
    {
    public:
        // 系統経路テーブル枠定義
        class CListInfo{
        public:
            int  start;     // ルート開始母線
            int  end;     // ルート終了母線
            int  max;     // ルート内母線数
            CList<int,int>  node;  // ノード管理No.
            CList<UINT,UINT> totalLen; // 総電線長
            CList<int,int>  branch;  // ブランチ管理No.

            CListInfo() {
                start = end = max = 0;
            }
            int GetNode(int index)  { return node.GetAt( node.FindIndex( index ) ); };
            int GetTotalLen(int index) { return totalLen.GetAt( totalLen.FindIndex( index ) ); };
            int GetBranch(int index) { return branch.GetAt( branch.FindIndex( index ) ); };
            void SetNode( int index, int nodeNo );
            void SetTotalLen( int index, UINT len )   { totalLen.SetAt( totalLen.FindIndex( index ), len ); };
            void SetBranch( int index, int branchNo ) { branch.SetAt( branch.FindIndex( index ), branchNo );};
        };

    public:
        UINT GetTotalLength(int nodeNo );
        int Route_Longest_Get(void);
        int GetNode(int index, int nodeIndx);
        void RemoveAll();
        CListInfo* GetList(int index);
        CListInfo* AddList();
        int GetCount()   { return m_ListInfo.GetCount(); };
        CListInfo* GetHead() { return m_ListInfo.GetHead(); };
        CListInfo* GetTail() { return m_ListInfo.GetTail(); };
        CListRoute();
        virtual ~CListRoute();

    private:
        CList<CListInfo*,CListInfo*>  m_ListInfo;

    };

    //////////////////////////////////////
    // ＳＶＲ管理テーブル枠定義
    typedef struct SVR_T0{
        int  kanri;   // 管理No. 
        int  node[2];  // １－二次側ノード管理No. 
        int  branch;   // 接続ブランチ管理No.
        int  psNum;   // SVR計算結果レコードNo  2004.04.20 Add
        struct SVR_1{    // データ 
            CString strMaker;  // 製造メーカー  // Add 2006.01.28 J.S
            CString strType;  // 型式    // Add 2006.01.28 J.S
            // ADAM1608 (Hyron) 2015/09/11 Start
            short DeviceType;   // 種別　0:SVR,1:NSVRⅠ型,2:NSVRⅡ型
            // ADAM1608 (Hyron) 2015/09/11 End
            short phase1;  // 一次側ノード 0:from,1:to 
            short type;  // SVR種別　1:完全逆送,2:逆送あり,3:逆送なし
            BOOL TapFixed; // タップ固定　0:しない, 1:する
            float CAP;  // 容量(kVA)
            float tap[3][3]; // タップ(V)　[一次/二次/逆送時指定タップ][重負荷/軽負荷/その他負荷]
            float vol[2][2]; // 基準電圧整定値(V)[SetArea][一次/二次]
            float fukantai[2];// 不感帯整定値(%) [一次/二次]
            float LDC_R[2]; // LDC整定値 R(%) [一次/二次]
            float LDC_X[2]; // LDC整定値 X(%) [一次/二次]
            float ActTime; // 動作時間特性(秒･%) 
            float haba;     // 昇圧幅(V) Add 2003.04.15 (R.T)
            //////////////////////////////////////////////////////////////////////////
            // Add 2006.01.23 S.S
            // Comm 2006.02.02 S.S 
            // int     no;   // メーカ番号と型式番号なる主キー 1～
            short   R67;  // 67リレー 0:なし、1:あり
            // Comm 2006.02.02 S.S 
            // int     TapNo;  // タップ番号
            //////////////////////////////////////////////////////////////////////////
            // ADAM1610 (Hyron) 2015/09/11 Start
            struct _t_keisoku{
                int    dir;  // 潮流方向 0:"順", 1:"逆", 2:"－"(使用しない), 3: " "
                int    cur;  // 通過電流(A)【0～999999】 -1:空白(データ欠損または新規作成時)
                float  rikiritu; // 力率(%)【-100.00～100.00】マイナス値は進み力率
                int    V1;  // A側電圧(V)
                int    V2;  // B側電圧(V)
            }keisoku[LOAD_MODE_MAX]; // 計測値 [重負荷/軽負荷/その他負荷]

            struct _t_settei{
                BOOL   use;  // 有効  0:OFF 1:ON(有効)
                int    dir;  // 潮流方向 0:"順", 1:"逆"
                int    cur;  // 通過電流(A)【0～999999】データ欠損または新規作成時は「0」
                float  rikiritu; // 力率(%)【-100.00～100.00】 マイナス値は進み力率
            }settei[LOAD_MODE_MAX];  // 設定値 [重負荷/軽負荷/その他負荷]
            // ADAM1610 (Hyron) 2015/09/11 End
        } data;  

        struct SVR_T2{
            int  no;   // ルートNo
            int  node[2]; // ＳＶＲ接続ﾉｰﾄﾞがroot_t[no].node[?]に設定されている場所　0:一次側,1:二次側
        } root;
        // ADAM1606 (Hyron) 2015/09/11 Start
        float  Current;    // 適正範囲逸脱個所表示用（通過電流）
        float  permit;     // 通過電流許容値
        short  Reasonable; // 逸脱判定OFF/ON
        // ADAM1606 (Hyron) 2015/09/11 End
    } SVR;

}