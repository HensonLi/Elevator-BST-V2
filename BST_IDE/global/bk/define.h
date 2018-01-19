#ifndef DEFINE_H
#define DEFINE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <assert.h>
#include <time.h>

#ifdef WINDOWS
#include <conio.h>
#include <windows.h>
#include <winver.h>
#include "tlhelp32.h"
#include <winbase.h>
#include <setupapi.h>
#include <commctrl.h>
#include <tchar.h>
#include <process.h>
#include <basetyps.h>
#include <initguid.h>
#include <devguid.h>
//>@ע������ú궨��
#include <RegStr.h>
#endif
#ifndef WINDOWS
# include <sys/stat.h>
# include <sys/mman.h>
# include <sys/soundcard.h>
# include <sys/ioctl.h>
# include <sys/fcntl.h>
# include <sys/types.h>
#include "wav.h"
#include "mad.h"
#endif

#include <QtGui>
#include <QtGui/QPixmap>
#include <QtGui/QSplashScreen>
#include <QtGui/QApplication>
#include <QHash>
#include <QDebug>
#include <QFile>
#include <QProcess>
#include <QTime>
#include <math.h>
#include <QPainter>
#include <QStyle>
#include <math.h>
#include <QTimeLine>
#include <QTimer>
#include <QImage>
#include <QFontMetrics>
#include <QPointF>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QToolBox>
#include <QDateTime>
#include <QMainWindow>
#include <QFontDialog>
#include <QTreeWidgetItem>
#include <QThread>
#include <QEvent>
#include <QReadWriteLock>
#include <QMessageBox>
#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QPixmap>
#include <QSpacerItem>
#include <QIODevice>

#ifdef SURRPORT_XML
#include <QDomDocument>
#endif

//>@Net
#ifdef SURRPORT_NETWORK
#include <QtNetwork>
#include <QNetworkInterface>
#include <QTcpServer>
#include <QTcpSocket>
#endif

#ifdef SURRPORT_WEBKIT
#include <QGraphicsWebView>
#endif

#ifdef  SURRPORT_SVG
#include <QSvgRenderer>
#endif

#ifdef SURRPORT_QML
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeItem>
#endif

#ifdef SURRPORT_SQL
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>
#endif

#ifdef SURRPORT_SCRIPT
#include <QtScript/QtScript>
#endif

#define QTASCII 0            //>@ �Ƿ�ʹ��QT�����ASCII���

#if(QT_VERSION >= QT_VERSION_CHECK(4, 7, 0))
#define VAR_CAST   qobject_cast
#else
#define VAR_CAST   static_cast
#endif

inline void QtSleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
}

#define _DEBUG_
//>@__PRETTY_FUNCTION__ ���ڴ�ӡ������
#ifdef _DEBUG_
#define IDE_DEBUG(x)         qDebug(QString("[%1,%2(),Line %3]-%4").arg(__FILE__).arg(__func__).arg(__LINE__).arg(QString(x)).toStdString().c_str())
#define IDE_TRACE()			 qDebug(QString("[%1,%2(),Line %3]-Trace").arg(__FILE__).arg(__func__).arg(__LINE__).toStdString().c_str())
#define IDE_TRACE_INT(x)	 qDebug(QString("[%1,%2(),Line %3]-%4=%5").arg(__FILE__).arg(__func__).arg(__LINE__).arg(#x).arg((int)x).toStdString().c_str())
#define IDE_TRACE_STR(x)	 qDebug(QString("[%1,%2(),Line %3]-%4=%5").arg(__FILE__).arg(__func__).arg(__LINE__).arg(#x).arg(x).toStdString().c_str())
#define IDE_PRINTF(fmt, ...) qDebug("[%s,%s(),Line %s]-"#fmt, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#else
#define IDE_DEBUG(x)
#define IDE_TRACE()
#define IDE_TRACE_INT(x)
#define IDE_TRACE_STR(x)
#define IDE_PRINTF(fmt, ...)
#endif

#define AUDIO_STARTUP       QString(":/SystemAudio/rc/SystemAudio/open.wav")   //>@��������
#define AUDIO_PLUGIN        QString(":/SystemAudio/rc/SystemAudio/plugin.wav") //>@���ƶ��豸����
#define AUDIO_PLUGOUT       QString(":/SystemAudio/rc/SystemAudio/plugout.wav")//>@���ƶ��豸����
#define AUDIO_ERROR         QString(":/SystemAudio/rc/SystemAudio/error.wav")  //>@������

#define CLEAR(x)            memset(&(x), 0, sizeof(x))

#define D_NMPORT        60001   //>@��������˿ں�
#define D_CMDPORT       60002   //>@���������ж˿ں�
#define D_SQLPORT       60003

#define D_VPVPORT       60006   //>@��Ƶ�Խ���Ƶ�˿�
#define D_VPAPORT       60007   //>@��Ƶ�Խ���Ƶ�˿�

#define D_SCANIPFREQ    2000

#define D_DaemonHBTime        20000

#define D_WAITTIME      4294967294

#ifdef WINDOWS
    #define D_FSRCPATH              QApplication::applicationDirPath() + QString("/RuntimeRc/FSRC/")    //>@FLASH�еĳ�����Դ·��
    #define D_BST_DISPLAY           QApplication::applicationDirPath() + QString("/BST_DISPLAY.exe")    //>@
    #define D_BST_DAEMON            QApplication::applicationDirPath() + QString("/BST_DAEMON.exe")     //>@FLASH�еĳ�����Դ·��
    #define D_MENCODER              D_FSRCPATH + QString("TOOL/Windows/mencoder.exe")
    #define D_FFMPEG_PATH           D_FSRCPATH + QString("TOOL/Windows/ffmpeg.exe")
    #define D_FFSERVER_PATH         D_FSRCPATH + QString("TOOL/Windows/ffserver.exe")
    #define D_MPLAYER_PATH          D_FSRCPATH + QString("TOOL/Windows/mplayer.exe")
    #define D_GSTREAMER_PATH        D_FSRCPATH + QString("TOOL/Windows/gst-launch.exe")
#endif
#ifdef UBUNTU
    #define D_FSRCPATH              QApplication::applicationDirPath() + QString("/RuntimeRc/FSRC/")    //>@FLASH�еĳ�����Դ·��
    #define D_BST_DISPLAY           QApplication::applicationDirPath() + QString("/BST_DISPLAY")        //>@
    #define D_BST_DAEMON            QApplication::applicationDirPath() + QString("/BST_DAEMON")         //>@FLASH�еĳ�����Դ·��
    #define D_MENCODER              D_FSRCPATH + QString("TOOL/Ubuntu/mencoder")
    #define D_FFMPEG_PATH           D_FSRCPATH + QString("TOOL/Ubuntu/ffmpeg")
    #define D_FFSERVER_PATH         D_FSRCPATH + QString("TOOL/Ubuntu/ffserver")
    #define D_MPLAYER_PATH          D_FSRCPATH + QString("TOOL/Ubuntu/mplayer")
    #define D_GSTREAMER_PATH        D_FSRCPATH + QString("TOOL/Ubuntu/gst-launch")
#endif
#ifdef LINUX
    #define D_FSRCPATH              QString("/FSRC/")         //>@FLASH�еĳ�����Դ·��
    #define D_BST_DISPLAY           QString("/FSRC/EXE/BST_DISPLAY.exe")    //>@
    #define D_BST_DAEMON            QString("/FSRC/EXE/BST_DAEMON.exe")
    #define D_MENCODER              QString("/FSRC/mencoder")
    #define D_FFMPEG_PATH           QString("/FSRC/ffmpeg")
    #define D_FFSERVER_PATH         QString("/FSRC/ffserver")
    #define D_MPLAYER_PATH          QString("/FSRC/mplayer")
    #define D_GSTREAMER_PATH        QString("/FSRC/gst-launch")
#endif

#define D_PCSCA_PATH        QString("pcsca")

#define OUTPUTDIR           QString("Output")
#define RESOURCESDIR        QString("Resources")
#define D_TEMP_PATH         QString("TEMP/")

#define D_GrabScreenPath    (D_FSRCPATH + D_TEMP_PATH)
#define D_GrabScreenName    QString("GrabScreen.JPG")

#define D_VideoPhoneName    QString("VP.sdp")
#define D_VideoPhonePath    (D_FSRCPATH + D_VideoPhoneName)

#define D_DHCPCONF          QString("udhcpd.conf")
#define D_FFSERVERCONF      QString("ffserver.conf")
#define D_WIFICONF          QString("/etc/Wireless/RT2870AP/RT2870AP.dat")
#define D_DNSCONF           QString("/etc/resolv.conf")
#define D_NETERROR          QString("no such device")
#define D_GATEWAYERROR      QString("Network is unreachable")

//>@Ĭ������
#define D_HTHEMEDIR         QString("HTHEME/")      //>@���Ĭ�Ϻ�������
#define D_VTHEMEDIR         QString("VTHEME/")      //>@���Ĭ����������

#define D_THEMEDIR          QString("THEME/")       //>@�����������
#define D_EXEDIR            QString("EXE/")         //>@�������Ӧ�ó���
#define D_LOGDIR            QString("LOG/")         //>@���Log�ļ�
#define D_TMPDIR            QString("TMP/")         //>@�����ʱ�ļ�
#define D_BOOTDIR           QString("BOOT/")        //>@��������ļ���U���豸�ļ���MDP��LOGCONF�ȣ�

#define D_UDISK_CMD         QString("BST.cmd")
#define D_UDISK_EXE         D_EXEDIR
#define D_UDISK_THEME       D_THEMEDIR
#define D_UDISK_RC_LOGO     QString("RC/LOGO/")
#define D_UDISK_RC_VIDEO    QString("RC/VIDEO/")
#define D_UDISK_RC_IMAGE    QString("RC/IMAGE/")
#define D_UDISK_RC_TEXT     QString("RC/TEXT/")
#define D_UDISK_BACKUP      QString("BACKUP/")

#define D_ENVIRONMENT       QString("Scene.env")

#define D_UINAME            QString("ThemeDevelop.ui")
#define D_MDPNAME           QString("BOOT.mdp")
#define D_MAPNAME           QString("Event.map")

#define D_BOOTFILE          D_MDPNAME
#define D_BKBOOTFILE        QString("BOOT.default")
#define D_SCHEDULEMAP       D_MAPNAME
#define D_TIPSXML           QString("TIPS.xml")
#define D_LOGBKCONF         QString("LOGBK.conf")
#define D_LOGCONF           QString("LOG.conf")
#define D_LOGFILE           QString("BST_%1.log")

#define D_UI_LOGO           QString("IntegratedInfo/Logo/Common/Image")
#define D_UI_VIDEO          QString("MultiMedia/VIDEO/Common/Film")
#define D_UI_IMAGE          QString("MultiMedia/Image/Common/Image")
#define D_UI_TEXT           QString("TextBulletin/Text/Common/Txt")

#define D_UPGRADELOGODIR    QString("THEME/LOGO/")   //>@U��Ŀ¼�е�Logo�ļ�Ŀ¼
#define D_UPGRADEVIDEODIR   QString("THEME/VIDEO/")  //>@U��Ŀ¼�е�Video�ļ�Ŀ¼
#define D_UPGRADEIMAGEDIR   QString("THEME/IMAGE/")  //>@U��Ŀ¼�е�Image�ļ�Ŀ¼
#define D_UPGRADETEXTDIR    QString("THEME/TEXT/")   //>@U��Ŀ¼�е�Text�ļ�Ŀ¼

/**
//>@BeepSound
*/
#define D_Error             QString("Error")
#define D_Warning           QString("Warning")
#define D_Success           QString("Success")
#define D_Failed            QString("Failed")

#define D_StartUI           QString("StartUi")
#define D_PauseUI           QString("PauseUi")
#define D_ResumeUI          QString("ResumeUi")
#define D_RebootUI          QString("RebootUi")

#define D_KeyPress          QString("KeyPress")
#define D_NFDConn           QString("NFDConn")
#define D_NFDDisconn        QString("NFDDisconn")
#define D_UdiskPush         QString("UdiskPush")
#define D_UdiskPull         QString("UdiskPull")
#define D_NFCBrushCard      QString("NFCBrushCard")

#define D_UpGradeFailed     QString("UpGradeFailed")
#define D_UpGradeSucess     QString("UpGradeSucess")

//#define D_NFCDevPluge       QString("UdiskPluge")
//#define D_NFCDevPull        QString("UdiskPull")
//#define D_CamPluge          QString("CamPluge")
//#define D_CamkPull          QString("CamPull")
//#define D_MousePluge        QString("MousePluge")
//#define D_MousePull         QString("MousePull")
//#define D_KeyboardPluge     QString("KeyboardPluge")
//#define D_KeyboardPull      QString("KeyboardPull")
//#define D_MousePluge        QString("MousePluge")
//#define D_MousePull         QString("MousePull")
//#define D_GprsPluge         QString("GprsPluge")
//#define D_GprsPull          QString("GprsPull")
//#define D_WifiPluge         QString("WifiPluge")
//#define D_WifiPull          QString("WifiPull")

#define StartPosX 20
#define StartPosY 20

#define PI 3.14159265358979323846264338327950288419717

#define MAX_TMPMCHARLEN			1024
#define MAX_TMPWCHARLEN			1024
#define MID_TMPMCHARLEN			256
#define MID_TMPWCHARLEN			256
#define MIN_TMPMCHARLEN			32
#define MIN_TMPWCHARLEN			32

#define ret_OK					 2
#define ret_ERROR 				-2

#define ret_INVALID				 255
#define ret_NULL				 0

#define ret_SUCCESS 			 1
#define ret_FAIL				-1

#define ret_FULL				 3
#define ret_EMPTY				-3

#define ret_BUSY				 4
#define ret_IDLE				-4

#define LineLen 8     //�߳�
#define LinePulse 10  //�߿�
#define RectPulse 5  //�ڿ�����ļ��

//���������������
#define MAX_SCANF_COUNT 10
typedef char			( *pInputCharFun )  ( void );
typedef unsigned char	( *pInputByteFun )  ( void );
typedef size_t			( *pInputStrFun )   (  char *, size_t  );
typedef size_t			( *pInputMbyteFun )	(  unsigned char *, size_t  );
typedef bool			( *pOutputCharFun ) ( char );
typedef bool			( *pOutputByteFun ) ( unsigned char );
typedef size_t			( *pOutputStrFun )  ( char *, size_t );
typedef size_t			( *pOutputMbyteFun )( unsigned char *, size_t );

typedef struct{
    QString         mCpumodel;
    QString         mCpuLoad;
    QString         mMemModel;
    QString         mMemLoad;

    QString         mFsrcpath;
    QString         mTFlashpath;
    QString         mCurUiname;
    QString         mTFlashspace;

    QString         mUdisk0path;
    QString         mUdisk0space;
}DevInfo;

typedef enum{
    Failed = 0,
    Success,
    Start
}TaskState;

typedef enum{
    PATH_TYPENONE = 0,
    PATH_TYPERC,
    PATH_TYPENETADDR,
    PATH_TYPEABS,
    PATH_TYPEQRC
} FILEPATH_TYPE;

typedef enum{
    e_TabNet=0,
    e_TabUsart=1,
    e_TabUsb=2
}CONNECT_TAB_TYPE;

typedef enum{
    Vertical=0,
    Horizontal = 1
} DIRECTION;        //>@���� ����

typedef enum{
    Positive=0,
    Negative=1
} ORIENTATION;      //>@���� ����

typedef struct{
    DIRECTION mDirection;
    ORIENTATION mOrientation;
} CONSTRAINT;

typedef enum{
    RCTEXT=0,
    RCIMAGE=1
}RCTYPE;

/*!
 * Enums for port settings.
 */
typedef enum
{
    WIN_NAMES,
    IRIX_NAMES,
    HPUX_NAMES,
    SUN_NAMES,
    DIGITAL_NAMES,
    FREEBSD_NAMES,
    LINUX_NAMES
}NamingConvention;

typedef enum
{
    BAUD50 = 50,                //POSIX ONLY
    BAUD75 = 75,                //POSIX ONLY
    BAUD110 = 110,
    BAUD134 = 134,               //POSIX ONLY
    BAUD150 = 150,               //POSIX ONLY
    BAUD200 = 200,               //POSIX ONLY
    BAUD300 = 300,
    BAUD600 = 600,
    BAUD1200 = 1200,
    BAUD1800 = 1800,              //POSIX ONLY
    BAUD2400 = 2400,
    BAUD4800 = 4800,
    BAUD9600 = 9600,
    BAUD14400 = 14400,             //WINDOWS ONLY
    BAUD19200 = 19200,
    BAUD38400 = 38400,
    BAUD56000 = 56000,             //WINDOWS ONLY
    BAUD57600 = 57600,
    BAUD76800 = 76800,             //POSIX ONLY
    BAUD115200 = 115200,
    BAUD128000 = 128000,            //WINDOWS ONLY
    BAUD256000 = 256000             //WINDOWS ONLY
}BaudRateType;

typedef enum
{
    DATA_5 = 5,
    DATA_6 = 6,
    DATA_7 = 7,
    DATA_8 = 8
}DataBitsType;

typedef enum
{
    PAR_NONE,
    PAR_ODD,
    PAR_EVEN,
    PAR_MARK,               //WINDOWS ONLY
    PAR_SPACE
}ParityType;

typedef enum
{
    START_1 = 1
}StartBitsType;

typedef enum
{
    STOP_1 = 1,
    STOP_1_5 = 3,               //WINDOWS ONLY
    STOP_2 = 2
}StopBitsType;

typedef enum
{
    FLOW_OFF,
    FLOW_HARDWARE,
    FLOW_XONXOFF
}FlowType;

typedef enum{
    LCDIF = 0,
    LVDSIF,
    VGAIF,
    HDMIIF
} OUTPUTDEVICE;

typedef enum{
    TYPE_CH = 0,
    TYPE_EN,
    TYPE_FR,
    TYPE_DE,
    TYPE_JP
} LANGUAGE;

typedef enum{
    TYPE_LOWER=0,
    TYPE_UPPER
} TEXTCASE;

enum _RC_INDEX{
    INVALIDRC   = 0x077f7f7f,
    SHOWRC      = 0x067f7f7f,
    HIDERC      = 0x057f7f7f,
    PREVRC      = 0x047f7f7f,
    NEXTRC      = 0x037f7f7f,
    REPEATONERC = 0x027f7f7f,
    REPEATALLRC = 0x017f7f7f,
    //>@
    BGRC        = 100,
    RCDISABILITY= 0x00000018
};

inline quint32 GetRcNum(QString pRc)
{
    bool ok=false;
    quint32 tmpNum = INVALIDRC;
    tmpNum = pRc.toUInt(&ok, 10);
    if(!ok)
    {
        if(pRc.compare("Next", Qt::CaseInsensitive) == 0)
            tmpNum = NEXTRC;
        else if(pRc.contains("Prev", Qt::CaseInsensitive))
            tmpNum =  PREVRC;
    }
    return tmpNum;
}

typedef enum{
    Image0=0,
    Image1=1,
    Image2=2,
    Image3=3,
    Image4=4,
    Image5=5,
    Image6=6,
    Image7=7,
    Image8=8,
    Image9=9,
    ImageA=10,
    ImageB=11,
    ImageC=12,
    ImageD=13,
    ImageE=14,
    ImageF=15,
    ImageG=16,
    ImageH=17,
    ImageI=18,
    ImageJ=19,
    ImageK=20,
    ImageL=21,
    ImageM=22,
    ImageN=23,
    ImageO=24,
    ImageP=25,
    ImageQ=26,
    ImageR=27,
    ImageS=28,
    ImageT=29,
    ImageU=30,
    ImageV=31,
    ImageW=32,
    ImageX=33,
    ImageY=34,
    ImageZ=35
}IMAGE_INDEX;

typedef enum{
    Text0=0,
    Text1=1,
    Text2=2,
    Text3=3,
    Text4=4,
    Text5=5,
    Text6=6,
    Text7=7,
    Text8=8,
    Text9=9,
    TextA=10,
    TextB=11,
    TextC=12,
    TextD=13,
    TextE=14,
    TextF=15,
    TextG=16,
    TextH=17,
    TextI=18,
    TextJ=19,
    TextK=20,
    TextL=21,
    TextM=22,
    TextN=23,
    TextO=24,
    TextP=25,
    TextQ=26,
    TextR=27,
    TextS=28,
    TextT=29,
    TextU=30,
    TextV=31,
    TextW=32,
    TextX=33,
    TextY=34,
    TextZ=35
}TEXT_INDEX;

//>@COM

#define SelectedZValueDiff    10000
#define ZValueDiff            500

#define VERTEXRADIUS    5                   //>@�򶥵㷽��뾶,ָ�߳���һ��
#define SIDERADIUS      4                    //>@��߷���뾶
#define COM_MINSIZE     2

#define FRAMEVALIDWIDTH 10.0                  //>@��ߺͶ������Ч���ȣ��������ñ߿��������

#define COMNAME         0
#define COMTYPE         1

typedef enum{
    DRAGLEFT,
    DRAGTOP,
    DRAGRIGHT,
    DRAGBOTTOM,
    DRAGLEFTTOP,
    DRAGRIGHTTOP,
    DRAGRIGHTBOTTOM,
    DRAGLEFTBOTTOM,
    DRAGALL,
    DRAGNONE
} COM_OPERTATE;

typedef enum{
    EffectTypeNone=0,
    EffectTypeRoll,
    EffectTypeMove,
    EffectTypeFireworks,//>@�̻�
    EffectTypeFlip,
    EffectTypeViewer,
    EffectTypeCube,
    EffectTypeCylinder,
    EffectTypeShake,    //>@��
    EffectTypeBlink,    //>@��˸
    EffectTypeBulge,    //>@͹��
    EffectTypeIndent,   //>@����
    EffectTypeRotate,
    EffectTypeGlide,
    EffectTypeTwirl,
    EffectTypeZoom,
    EffectTypeTransparent,
    EffectTypeSpectrum,
    EffectTypeSpread,
    EffectTypeWheel,
    EffectTypeSlipCycle,
    EffectTypeShine,
    EffectTypeSwipe
}EffectType;

typedef enum{
    Last=0,
    Current=1,
    Next=2
} ORDER;

typedef enum{
    Separator = 3,
    Hundred = 2,
    Ten = 1,
    Single = 0
} NumSite;

typedef enum{
    STEP0 = 0,
    STEP1 = 1
} OPERATE_STEP;

typedef struct{
    QPixmap  mLastPointer;       //>@ʹ�ù�����Դָ�루Ҳ����ǰ����ʹ�õģ�
    QPixmap  mCurPointer;        //>@��ʹ�õ���Դָ��
}PIXMAP_POINTER;

typedef struct{
    int       mLastPointer;       //>@ʹ�ù�����Դָ�루Ҳ����ǰ����ʹ�õģ�
    int       mCurPointer;        //>@��ʹ�õ���Դָ��
}RC_POINTER;

class AREA_ANIMATE
{
public:
    AREA_ANIMATE()
    {
        mEffectType = EffectTypeNone;
        mDirection = Horizontal;
        mOrientation = Positive;
        mFrameStart = 0;
        mFrameEnd = 10;
        mFrameCount = mFrameEnd - mFrameStart -1;
        mAnimateTime = 200;
        mLoopCount = 1;        //>@ѭ�����������Ϊ0�����ʾ����ѭ��
        mDutyRatio = 50;        //>@ռ�ձȣ�0~100
        mAnimateType = QTimeLine::LinearCurve;
    }
public:
    EffectType              mEffectType;   //>@��Ч���ͣ�Ĭ��Ϊ����Ч
    DIRECTION               mDirection;    //>@ͼƬ��Ч����
    ORIENTATION             mOrientation;  //>@��Ч������
    int                     mLoopCount;
    int                     mFrameStart, mFrameEnd, mFrameCount;
    int                     mAnimateTime;
    int                     mDutyRatio;
    QTimeLine::CurveShape   mAnimateType;
};
Q_DECLARE_METATYPE(AREA_ANIMATE)

//>@����TCP�ķ�������
typedef struct{
    QString         mMajorType;
    QString         mMinorType;
    QHostAddress    mIP;
    QString         mDescription;
} TCPSERVICE_TYPE;
Q_DECLARE_METATYPE(TCPSERVICE_TYPE)

inline uint qHash(TCPSERVICE_TYPE pType)
{
    return qHash(pType.mMajorType+pType.mMinorType+pType.mIP.toString());
}

typedef enum{
    OPERATE_NONE = 0,
    OPERATE_INIT,
    OPERATE_RELEASE,
    //>@��������
    OPERATE_CHANGE,
    OPERATE_SLIP,   //>@����
    OPERATE_TURN, //>@ת��
    OPERATE_ADD,
    OPERATE_MODIFY,
    OPERATE_DEL,
    OPERATE_SHOW,
    OPERATE_HIDE,
    //>@���Ų���
    OPERATE_RUN,
    OPERATE_HALT,
    OPERATE_PLAY,
    OPERATE_PAUSE,
    OPERATE_STOP,
    OPERATE_STEADY,
    OPERATE_VOCAL,  //>@����
    OPERATE_MUTE,   //>@����
    OPERATE_RESUME,
    OPERATE_REPEAT,
    //>@���ڲ���
    OPERATE_KEYPRESS,
    OPERATE_KEYLIGHT,
    OPERATE_KEYCANCEL,
    OPERATE_KEYMOVE,
    OPERATE_KEYRELEASE
} AREA_OPERATE;

Q_DECLARE_METATYPE(AREA_OPERATE)   //>@�Զ����źŲ���
Q_DECLARE_METATYPE(QProcess::ExitStatus)

inline AREA_OPERATE GetOperateType(QString pType)
{
    if(pType.compare("INIT", Qt::CaseInsensitive) == 0)
        return OPERATE_INIT;
    else if(pType.compare("RELEASE", Qt::CaseInsensitive) == 0)
        return OPERATE_RELEASE;
    else if(pType.compare("CHANGE", Qt::CaseInsensitive) == 0)
        return OPERATE_CHANGE;
    else if(pType.compare("SLIP", Qt::CaseInsensitive) == 0)
        return OPERATE_SLIP;
    else if(pType.compare("TURN", Qt::CaseInsensitive) == 0)
        return OPERATE_TURN;
    else if(pType.compare("ADD", Qt::CaseInsensitive) == 0)
        return OPERATE_ADD;
    else if(pType.compare("MODIFY", Qt::CaseInsensitive) == 0)
        return OPERATE_MODIFY;
    else if(pType.compare("DEL", Qt::CaseInsensitive) == 0)
        return OPERATE_DEL;
    else if(pType.compare("SHOW", Qt::CaseInsensitive) == 0)
        return OPERATE_SHOW;
    else if(pType.compare("HIDE", Qt::CaseInsensitive) == 0)
        return OPERATE_HIDE;
    else if(pType.compare("RUN", Qt::CaseInsensitive) == 0)
        return OPERATE_RUN;
    else if(pType.compare("HALT", Qt::CaseInsensitive) == 0)
        return OPERATE_HALT;
    else if(pType.compare("PLAY", Qt::CaseInsensitive) == 0)
        return OPERATE_PLAY;
    else if(pType.compare("PAUSE", Qt::CaseInsensitive) == 0)
        return OPERATE_PAUSE;
    else if(pType.compare("STOP", Qt::CaseInsensitive) == 0)
        return OPERATE_STOP;
    else if(pType.compare("STEADY", Qt::CaseInsensitive) == 0)
        return OPERATE_STEADY;
    else if(pType.compare("VOCAL", Qt::CaseInsensitive) == 0)
        return OPERATE_VOCAL;
    else if(pType.compare("MUTE", Qt::CaseInsensitive) == 0)
        return OPERATE_MUTE;
    else if(pType.compare("RESUME", Qt::CaseInsensitive) == 0)
        return OPERATE_RESUME;
    else if(pType.compare("REPEAT", Qt::CaseInsensitive) == 0)
        return OPERATE_REPEAT;
    else if(pType.compare("KEYPRESS", Qt::CaseInsensitive) == 0)
        return OPERATE_KEYPRESS;
    else if(pType.compare("KEYLIGHT", Qt::CaseInsensitive) == 0)
        return OPERATE_KEYLIGHT;
    else if(pType.compare("KEYCANCEL", Qt::CaseInsensitive) == 0)
        return OPERATE_KEYCANCEL;
    else if(pType.compare("KEYMOVE", Qt::CaseInsensitive) == 0)
        return OPERATE_KEYMOVE;
    else if(pType.compare("KEYRELEASE", Qt::CaseInsensitive) == 0)
        return OPERATE_KEYRELEASE;
    return OPERATE_NONE;
}

inline QString GetOperateString(AREA_OPERATE pType)
{
    switch(pType)
    {
        case OPERATE_INIT:
            return QString("INIT");
        case OPERATE_RELEASE:
            return QString("RELEASE");
        case OPERATE_CHANGE:
            return QString("CHANGE");
        case OPERATE_SLIP:
            return QString("SLIP");
        case OPERATE_TURN:
            return QString("TURN");
        case OPERATE_ADD:
            return QString("ADD");
        case OPERATE_MODIFY:
            return QString("MODIFY");
        case OPERATE_DEL:
            return QString("DEL");
        case OPERATE_SHOW:
            return QString("SHOW");
        case OPERATE_HIDE:
            return QString("HIDE");
        case OPERATE_RUN:
            return QString("RUN");
        case OPERATE_HALT:
            return QString("HALT");
        case OPERATE_PLAY:
            return QString("PLAY");
        case OPERATE_PAUSE:
            return QString("PAUSE");
        case OPERATE_STOP:
            return QString("STOP");
        case OPERATE_STEADY:
            return QString("STEADY");
        case OPERATE_VOCAL:
            return QString("VOCAL");
        case OPERATE_MUTE:
            return QString("MUTE");
        case OPERATE_RESUME:
            return QString("RESUME");
        case OPERATE_REPEAT:
            return QString("REPEAT");
        case OPERATE_KEYPRESS:
            return QString("KEYPRESS");
        case OPERATE_KEYLIGHT:
            return QString("KEYLIGHT");
        case OPERATE_KEYCANCEL:
            return QString("KEYCANCEL");
        case OPERATE_KEYMOVE:
            return QString("KEYMOVE");
        case OPERATE_KEYRELEASE:
            return QString("KEYRELEASE");
        default:
            break;
    }
    return QString("UNKNOW");
}

typedef enum{
    MODE_NOREPEAT = 0,
    MODE_REPEATONE,
    MODE_REPEATALL
} REPEAT_MODE;

inline REPEAT_MODE GetRepeatMode(QString pMode)
{
    if(pMode.compare("RepeatOne"), Qt::CaseInsensitive == 0)
        return MODE_REPEATONE;
    else if(pMode.compare("RepeatAll"), Qt::CaseInsensitive == 0)
        return MODE_REPEATALL;
    return MODE_NOREPEAT;
}

typedef enum{
    RC_BGIMG = 0,
    //>@arrow
    RC_ARROWUP,
    RC_ARROWDOWN,
    RC_ARROWUPDOWN
} AREA_RC;

typedef struct{
    bool            mValid;
    AREA_OPERATE    mOperate;
} OPERATE_INFO;

enum _UPDATE_PARA{
    PARA_START = 0,
    PARA_MANUAL = 1,
    PARA_LEFTBTN = 2,
    PARA_AUTO = 3
};

#define PARA_CURVESHAPE  QString("AnimateType")  //>@��Ч��������
#define PARA_FRAMERANGE  QString("FrameRange")   //>@��Ч֡Ƶ��
#define PARA_INTERVAL    QString("Interval")     //>@��Чʱ��
#define PARA_DIRECTION   QString("Direction")    //>@��Ч����
#define PARA_ORIENTATION QString("Orientation")  //>@��Ч������
#define PARA_AMOUNT      QString("Amount")       //>@����
#define PARA_DUTYRATIO   QString("DutyRatio")    //>@ռ�ձ�
#define PARA_AUTOPLAY    QString("AutoPlay")
#define PARA_RCTYPE      QString("RcType")       //>@��Դ���ͣ�Image/Text

#define PARA_LAYOUT      QString("Layout")       //>@����
#define PARA_ROW         QString("Row")          //>@������������
#define PARA_COLUMN      QString("Column")       //>@������������
#define PARA_RSPACE      QString("RowSpace")     //>@������Ԫ�غ�����
#define PARA_CSPACE      QString("ColumnSpace")  //>@������Ԫ��������

#define PARA_STYLE       QString("Style")        //>@������ʽ
#define PARA_ALIGN       QString("Align")
#define PARA_PATTERN     QString("Pattern")

//>@3D
#define PARA_ANGLEDIFF   QString("AngleDiff")       //>@һ����ת�Ƕ�

typedef enum{
    ANGEL_0 = 0,
    ANGEL_90 = 90,
    ANGEL_180 = 180,
    ANGEL_270 = 270
} ROTATE;

//>@�����ļ�������UI��������Ĳ�����
typedef enum{
    CodeNone=0,
    CodeInsert,
    CodeHide,
    CodeMap,
    CodePlay,
    CodeStop,
    CodeDelete,
    CodeUnActive,
    CodeActive,  //>@ʹ֮���ڻҳ��
    CodeMove,
    CodeZoom,
    CodeUpdate,
    CodeSelect,
    CodeRefresh,
    CodeSave,
    CodeSaveRC,
    CodeRegularRC
}ITEM_OPERATECODE;

//>@�ļ�����
typedef enum{
    TYPE_INVALID=0,
    TYPE_START,
    TYPE_PRO,
    TYPE_MANUFACTURE,
    TYPE_UPGRADE,
    TYPE_NETWORKMANAGER,
    TYPE_VIDEOEDITOR,
    TYPE_IMAGEEDITOR,
    TYPE_AUDIOEDITOR,
    TYPE_FONTEDITOR,
    TYPE_ASCIICODEC,
    TYPE_XML,
    TYPE_INI,
    TYPE_LOG,
    TYPE_FACEDETECT,
    TYPE_RC,
    TYPE_FTP,
    TYPE_SMS,
    TYPE_SQLSERVER,
    Type_MONITOR,
    TYPE_CHAT,
    TYPE_DEVINFO,
    TYPE_MAPS,
    TYPE_UI,
    TYPE_MDP,
    TYPE_MAP,
    TYPE_STC,
    TYPE_STO
}FILE_TYPE;

typedef enum{
    RC_INVALID=0,
    RC_BMP,
    RC_JPG,
    RC_PNG,
    RC_GIF,
    RC_SVG,
    RC_QML,
    RC_TXT,
    RC_MP3,
    RC_WAV,
    RC_MP4,
    RC_AVI,
    RC_RMVB,
    RC_FLV
}RC_TYPE;

typedef enum{
    CODEC_INVALID=0,
    CODEC_MPEG4,
    CODEC_H264
}CODEC_TYPE;

//>@�������
typedef enum{
    COM_INVALID=0,
    COM_FRAME=1,
    COM_LEFTFRAME=2,
    COM_TOPFRAME=3,
    COM_RIGHTFRAME=4,
    COM_BOTTOMFRAME=5,
    COM_NOTE,
    COM_LINE,
    //>@Sence
    COM_NULL,
    //>@����
    COM_DESKTOP,
    //>@���ô���
    COM_SETBAR,
    COM_MESSAGEBAR,
    COM_PROGRESSBAR,
    COM_ANIMAL,
    //>@Function Info Reginon
    COM_FUNCINFO,
    COM_FLOOR,
    COM_ARROW,
    COM_FUNCTION,
    //>@MultiMedia Reginon
    COM_MULTIMEDIA,
    COM_VIDEO,
    COM_IMAGE,
    COM_WEBVIEW,
    COM_QML,
    COM_OPENGL,
    COM_AUDIO,
    COM_PHONE,
    //>@Text Bulletin Reginon
    COM_TEXTBULLETIN,
    COM_TEXT,
    //>@Integrated Info Reginon
    COM_INTEGRATEDINFO,
    COM_LOGO,
    COM_WEATHER,
    COM_TIME,
    COM_NAMEPLATE,
    //>@Button Operate Reginon
    COM_BUTTONOPERATE,
    COM_FLOORBTN,
    COM_FLOORLCD,
    COM_KEYBOARDBTN,    //>@����
    COM_PHONEBTN,
    COM_EMERGENCYBTN,
    COM_OPENBTN,
    COM_CLOSEBTN,
    COM_SETBTN,
    COM_DISABILITYBTN
} COM_TYPE;

typedef enum{
    ROTATE_0 = 0,
    ROTATE_90 = 90,
    ROTATE_180 = 180,
    ROTATE_270 = 270
} ROTATE_ANGLE;

typedef enum{
    STAGE_IN = 0,
    STAGE_OUT
} ZOOM_STAGE;

typedef enum{
    BASICUI_UNKNOW=0,
    BASICUI_LABEL,
    BASICUI_ENUM,
    BASICUI_STACK,
    BASICUI_BOOL,
    BASICUI_STRING,
    BASICUI_ENETADDR,
    BASICUI_CHECK,
    BASICUI_BUTTON,
    BASICUI_SWITCH,
    BASICUI_NUM,
    BASICUI_FILE,
    BASICUI_MAP
}BASICUI_TYPE;

class FileTreeItem;
class TabPage;
class PAGE_INFO
{
public:
    PAGE_INFO()
    {
        PageDialogPtr = 0;
        TreeItem = 0;
    }
    FILE_TYPE               FileType;
    QString                 FileDir;
    QString                 FileName;
    QVariant                Parameter;
    FileTreeItem           *TreeItem;   //>@����Ŀ�б��е�����
    QString                 IconName;
    TabPage                *PageDialogPtr;
};

typedef struct{
    QString CategoryType;
    QString ItemType;
    QString FileDir;
    QString FileName;
    QString IconName;
    bool BusyFlag;  //>@������
} FILE_INFO;

typedef struct{
    QString Icon;
    QString Resolution;     //>@�ֱ���
    bool SupportVideo;      //>@�Ƿ�֧����Ƶ
    bool SupportOpenGL;     //>@�Ƿ�֧��OpenGL
    QStringList Protocol;   //>@֧�ֵĽӿ�Э��
    QString Description;    //>@��Ŀ�ļ�����
} SolutionCategory;

typedef struct{
    QString Icon;
    QString Suffix;         //>@�ļ���׺
    QString Description;    //>@��Ŀ�ļ�����
} FileCategory;

typedef struct{
    QString NickName;
    QString RcName;
    QStringList RcTypes;
}RESOURCE;

typedef struct{
    QString EffectName;
    QString EffectPara;
    QList<RESOURCE> Resources;
}EFFECT;

typedef struct{
    QString     StateName;
    QList<EFFECT> Effects;
}STATEMACHINE;

typedef struct{
    QString Icon;
    COM_TYPE CurType;
    COM_TYPE ParentType;
    QList<STATEMACHINE*> StateMachines;
} ComCategory;

typedef enum{
    ParaInvalid=0,
    ParaBool,
    ParaNum,
    ParaStr,
    ParaEnum,
    ParaCheck
} ParaType;

typedef struct{
    QString     mItemName;
    ParaType    mControlType;
    QVariant    mValues;
    QVariant    mCurValue;
} SubCfgItemInfo;

typedef struct{
    QString                 mPhysicsType;
    QList<SubCfgItemInfo*>  mSubItems;
} CfgItemInfo;

class RESOURCE_INFO
{
public:
    RESOURCE_INFO(){}
    ~RESOURCE_INFO(){}
public:
    QString RcName;
    QString RcFile;
public:
    bool operator==(const RESOURCE_INFO &s)
    {
        if(this->RcName.compare(s.RcName))
            return false;
        if(this->RcFile.compare(s.RcFile))
            return false;
        return true;
    }
    bool operator!=(const RESOURCE_INFO &s)  { return !operator==(s); }
};

class EFFECT_INFO
{
public:
    EFFECT_INFO(){RcFiles.clear();}
    ~EFFECT_INFO(){RcFiles.clear();}
    void clear()
    {
        EffectType.clear();
        EffectPara.clear();
        RcFiles.clear();
    }
public:
    QString EffectType;
    QString EffectPara;
    QList<RESOURCE_INFO> RcFiles;
public:
    bool operator==(const EFFECT_INFO &s)
    {
        if(this->EffectType.compare(s.EffectType))
            return false;
        if(this->EffectPara.compare(s.EffectPara))
            return false;
        if(RcFiles.count() != s.RcFiles.count())
            return false;
        for(int i=0;i<RcFiles.count();i++)
        {
            RESOURCE_INFO tmpSrc = RcFiles.at(i);
            RESOURCE_INFO tmpDst = s.RcFiles.at(i);
            if(tmpSrc != tmpDst)
                return false;
        }
        return true;
    }
    bool operator!=(const EFFECT_INFO &s)  { return !operator==(s); }
    EFFECT_INFO & operator=(EFFECT_INFO &s)
    {
        if(*this == s)
            return *this;
        EffectType = s.EffectType;
        EffectPara = s.EffectPara;
        RcFiles.clear();
        for(int i=0;i<s.RcFiles.count();i++)
        {
            RcFiles.insert(i, s.RcFiles.at(i));
        }
        return *this;
    }
};

class STATE_INFO
{
public:
    STATE_INFO(){}
    ~STATE_INFO(){}
public:
    QString      StateName;
    EFFECT_INFO  Effect;
public:
    bool operator==(const STATE_INFO &s)
    {
        if(this->StateName.compare(s.StateName))
            return false;
        if(Effect != s.Effect)
            return false;
        return true;
    }
    bool operator!=(const STATE_INFO &s)  { return !operator==(s); }
    STATE_INFO & operator=(STATE_INFO &s)
    {
        if(*this == s)
            return *this;
        StateName = s.StateName;
        Effect = s.Effect;
        return *this;
    }
};

typedef struct{
    QString level;
    QString content;
}LOGTIP_INFO;

typedef struct _Com_Struct{
    QGraphicsWidget      *ComponentPtr;
    QString               ComPath;        //>@/Function/Floor
    QRectF                ComRect;
    QList<STATE_INFO*>    StateMachine;       //>@״̬��
}COM_STRUCT;

typedef enum{
    MODE_INVALID = 0,
    MODE_AUTO,      //>@�Զ�����ģʽ
    MODE_MANUAL     //>@�ֶ�����ģʽ
} WORKMODE;

typedef enum{
    ITEM_BASE=65536,   //UserType=65536
    ITEM_LAY,
    ITEM_TEXT,
    ITEM_FRAME,
    ITEM_INVALD
} IMAGEITEM_TYPE;

typedef enum{
    S_UNPLUGGED =0,
    S_LOCK,
    S_ERROR,
    S_PLUGGED,
    S_OFFLINE,        //>@���ߣ�����Storage�γ������߶ϵ�
    S_ONLINE,         //>@���ߣ�ֻҪ��ɨ�赽�Ķ������ߣ�Ҫ��Netmanager�е�Ӳ/���������ֿ���
    S_DEVSYNC,        //>@ͬ��״̬��ֻҪ�ǽ����������Ӷ���ͬ��״̬
    S_ACK,            //>@�豸��Ӧ��
    S_ON,
    S_OFF,
    S_PWM
} DEVICESTATE;

#define D_PHYSICSINTERFACE  QString("PID")
#define D_STATECODE         QString("SC")

//>@��ȡ�豸״̬�������Ƿ�Plug
inline DEVICESTATE GetDevStatus(QDomElement pDevElement)
{
    DEVICESTATE tmpState = S_UNPLUGGED;
    if(pDevElement.isNull())
        return tmpState;
    QString tmpDevStatus = pDevElement.attribute(D_STATECODE);
    if(tmpDevStatus.compare("PLUGGED", Qt::CaseInsensitive) == 0)
        tmpState = S_PLUGGED;
    else if(tmpDevStatus.compare("UNPLUGGED", Qt::CaseInsensitive) == 0)
        tmpState = S_UNPLUGGED;
    else if(tmpDevStatus.compare("LOCK", Qt::CaseInsensitive) == 0)
        tmpState = S_LOCK;
    else if(tmpDevStatus.compare("ERROR", Qt::CaseInsensitive) == 0)
        tmpState = S_ERROR;
    else if(tmpDevStatus.compare("ACK", Qt::CaseInsensitive) == 0)
        tmpState = S_ACK;
    else if(tmpDevStatus.compare("ON", Qt::CaseInsensitive) == 0)
        tmpState = S_ON;
    else if(tmpDevStatus.compare("OFF", Qt::CaseInsensitive) == 0)
        tmpState = S_OFF;
    else if(tmpDevStatus.compare("PWM", Qt::CaseInsensitive) == 0)
        tmpState = S_PWM;
    else if(tmpDevStatus.compare("OFFLINE", Qt::CaseInsensitive) == 0)
        tmpState = S_OFFLINE;
    else if(tmpDevStatus.compare("ONLINE", Qt::CaseInsensitive) == 0)
        tmpState = S_ONLINE;
    else if(tmpDevStatus.compare("DEVSYNC", Qt::CaseInsensitive) == 0)
        tmpState = S_DEVSYNC;
    return tmpState;
}

inline DEVICESTATE GetDevStatus(QDomElement pDevElement, QString &pDevPath)
{
    if(pDevElement.isNull())
        pDevPath.clear();
    else
        pDevPath = pDevElement.text();
    return GetDevStatus(pDevElement);
}

typedef enum{
    P_INVALID = 0,  //>@0
    P_CPU,
    P_MEM,
    P_DISK,
    P_RTC,
    P_Audio,
    P_LED,
    P_LCD,
    P_MDISK,
    P_Camera,
    P_Mouse,
    P_Touch,
    P_Keyboard,
    P_LAN,
    P_WAN,
    P_RMII,
    P_GPRS,
    P_WIFI,
    P_Bluetooth,
    P_NFC,
    //>@���ݽӿ��豸
    P_SodimasSAF,
    P_SodimasCAN,
    P_BSTRS232,
    P_YungtayRS485
} PH_Type;

Q_DECLARE_METATYPE(PH_Type)
inline uint qHash(PH_Type pType) { return (uint)pType; }

typedef enum{
    L_INVALID = 0,
    L_DLNA,
    L_Bonjour,
    L_FTP,
    L_SSH,
    L_Monitor,
    L_VideoPhone,
    L_Elevator,
    L_CardReader,
    L_NFCP2P,
    L_ThemeManager,
    L_ContentUpdates,
    L_NetDiscovery,
    L_NetManager
} LG_Type;

Q_DECLARE_METATYPE(LG_Type)
inline uint qHash(LG_Type pType) { return (uint)pType; }

typedef enum {DEV_PHYSICAL=0, DEV_LOGIC, DEV_NONE} DEV_TYPE;

inline DEV_TYPE GetDevType(QString pDevName)
{
    if(pDevName.contains("Physical"))
        return DEV_PHYSICAL;
    else if(pDevName.contains("Logic"))
        return DEV_LOGIC;
    return DEV_NONE;
}

inline QString GetDevTypeString(DEV_TYPE pDevType)
{
    if(pDevType == DEV_PHYSICAL)
        return QString("Physical");
    else if(pDevType == DEV_LOGIC)
        return QString("Logic");
    return QString();
}

inline PH_Type GetPHType(QString pPara)
{
    PH_Type PHType = P_INVALID;
    if(pPara.isEmpty())
        return PHType;
    if(pPara.compare("CPU", Qt::CaseInsensitive) == 0)
        PHType = P_CPU;
    else if(pPara.compare("MEM", Qt::CaseInsensitive) == 0)
        PHType = P_MEM;
    else if(pPara.compare("Disk", Qt::CaseInsensitive) == 0)
        PHType = P_DISK;
    else if(pPara.compare("RTC", Qt::CaseInsensitive) == 0)
        PHType = P_RTC;
    else if(pPara.compare("Audio", Qt::CaseInsensitive) == 0)
        PHType = P_Audio;
    else if(pPara.compare("LAN", Qt::CaseInsensitive) == 0)
        PHType = P_LAN;
    else if(pPara.compare("WAN", Qt::CaseInsensitive) == 0)
        PHType = P_WAN;
    else if(pPara.compare("RMII", Qt::CaseInsensitive) == 0)
        PHType = P_RMII;
    else if(pPara.compare("LCD", Qt::CaseInsensitive) == 0)
        PHType = P_LCD;
    else if(pPara.compare("LED", Qt::CaseInsensitive) == 0)
        PHType = P_LED;
    else if(pPara.compare("Sodimas-SAF", Qt::CaseInsensitive) == 0)
        PHType = P_SodimasSAF;
    else if(pPara.compare("Sodimas-CAN", Qt::CaseInsensitive) == 0)
        PHType = P_SodimasCAN;
    else if(pPara.compare("BST-RS232", Qt::CaseInsensitive) == 0)
        PHType = P_BSTRS232;
    else if(pPara.compare("Yungtay-RS485", Qt::CaseInsensitive) == 0)
        PHType = P_YungtayRS485;
    else if(pPara.compare("Mouse", Qt::CaseInsensitive) == 0)
        PHType = P_Mouse;
    else if(pPara.compare("Keyboard", Qt::CaseInsensitive) == 0)
        PHType = P_Keyboard;
    else if(pPara.compare("Touch", Qt::CaseInsensitive) == 0)
        PHType = P_Touch;
    else if(pPara.compare("Camera", Qt::CaseInsensitive) == 0)
        PHType = P_Camera;
    else if(pPara.compare("MobileDisk", Qt::CaseInsensitive) == 0)
        PHType = P_MDISK;
    else if(pPara.compare("GPRS", Qt::CaseInsensitive) == 0)
        PHType = P_GPRS;
    else if(pPara.compare("WIFI", Qt::CaseInsensitive) == 0)
        PHType = P_WIFI;
    else if(pPara.compare("NFC", Qt::CaseInsensitive) == 0)
        PHType = P_NFC;
    else if(pPara.compare("Bluetooth", Qt::CaseInsensitive) == 0)
        PHType = P_Bluetooth;
    return PHType;
}
inline PH_Type GetElementPHType(QDomElement pDevElement)
{
    if(pDevElement.isNull())
        return P_INVALID;
    return GetPHType(pDevElement.tagName());
}

inline LG_Type GetLGType(QString pPara)
{
    LG_Type LGType = L_INVALID;
    if(pPara.isEmpty())
        return LGType;
    if(pPara.compare("DLNA", Qt::CaseInsensitive) == 0)
        LGType = L_DLNA;
    else if(pPara.compare("Bonjour", Qt::CaseInsensitive) == 0)
        LGType = L_Bonjour;
    else if(pPara.compare("FTP", Qt::CaseInsensitive) == 0)
        LGType = L_FTP;
    else if(pPara.compare("SSH", Qt::CaseInsensitive) == 0)
        LGType = L_SSH;
    else if(pPara.compare("Monitor", Qt::CaseInsensitive) == 0)
        LGType = L_Monitor;
    else if(pPara.compare("VideoPhone", Qt::CaseInsensitive) == 0)
        LGType = L_VideoPhone;
    else if(pPara.compare("Elevator", Qt::CaseInsensitive) == 0)
        LGType = L_Elevator;
    else if(pPara.compare("CardReader", Qt::CaseInsensitive) == 0)
        LGType = L_CardReader;
    else if(pPara.compare("NFCP2P", Qt::CaseInsensitive) == 0)
        LGType = L_NFCP2P;
    else if(pPara.compare("ThemeManager", Qt::CaseInsensitive) == 0)
        LGType = L_ThemeManager;
    else if(pPara.compare("ContentUpdates", Qt::CaseInsensitive) == 0)
        LGType = L_ContentUpdates;
    else if(pPara.compare("NetDiscovery", Qt::CaseInsensitive) == 0)
        LGType = L_NetDiscovery;
    else if(pPara.compare("NetManager", Qt::CaseInsensitive) == 0)
        LGType = L_NetManager;
    return LGType;
}

typedef struct{
    QString     mParLabel;
    QString     mTagName;
    QString     mAtPara;
    QString     mAtList;
    QString     mText;
}DomInfo;

typedef enum{
    Type_SERIAL = 0,
    Type_SOCKET = 1,
    Type_USB = 2,
    Type_UnknowDevice = 3
} COMM_TYPE;

#define D_TFLASH    QString("TFLASH")
#define D_UDISK     QString("UDISK")
#define D_GPRS      QString("GPRS")
#define D_WIFI      QString("WIFI")
#define D_NFC       QString("NFC")
#define D_CAMERA    QString("CAMERA")
#define D_TOUCH     QString("TOUCH")
#define D_ETHERNET  QString("ETHERNET")

//>@�洢���ķ�����ʽ�����ΪF_UNKNOW���ʾ����ԭ����������
typedef enum{
    F_UNKNOW,
    F_FAT,
    F_EXT
} FORMAT_TYPE;

/*************************************************************
//>@D_Global
**************************************************************/
#define D_INVALIDTIME               18446744073709551614    //0xFFFFFFFFFFFFFFFE
#define D_MAXSERIALBLOCKSIZE        3*1024
#define D_MAXSOCKETBLOCKSIZE        32*1024
#define D_MAXUSBBLOCKSIZE           32*1024
#define D_FRAMEHEADER               0x80
#define D_FRAMEFOOTER               0x81
#define D_FRAMEHEADER_ACK           0xc0
#define D_FRAMEFOOTER_ACK           0xc1
/*************************************************************
//>@D_IB
**************************************************************/
#define D_IBFRAMELEN                11
#define D_FloorAntiShakeNum         10
#define D_DoorAntiShakeNum          10
#define D_ArrowAntiShakeNum         10
#define D_ArriveAntiShakeNum        10
#define D_VoiceAntiShakeNum         10
#define D_ButtonAntiShakeNum        10
#define D_FunctionAntiShakeNum      10

#define D_DoorArea                  0x30
#define D_DoorOpen                  0x20
#define D_DoorClose                 0x10

#define D_ArrowArea                 0x07
#define D_ArrowUnknow               0x00
#define D_ArrowUp                   0x01
#define D_ArrowUpRun                0x05
#define D_ArrowDown                 0x02
#define D_ArrowDownRun              0x06
#define D_ArrowUpDown               0x03
#define D_ArrowUpDownRun            0x07

#define D_SignalArea                0x38
#define D_SignalArrive              0x08
#define D_SignalVoice               0x10
#define D_SignalLowPower            0x20

#define D_Fun1Area                  0x7f
#define D_Fun2Area                  0x7f00
#define D_Fun3Area                  0x7f0000

#define D_SignalFireControl         0x20
#define D_SignalMaintenance         0x10
#define D_SignalFullLoad            0x08
#define D_SignalOverLoad            0x04
#define D_SignalEarthquake          0x02
#define D_SignalNosmoke             0x01
#define D_SignalPrior               0x20
#define D_SignalFire                0x10
#define D_SignalDriver              0x08
#define D_SignalStop                0x04
#define D_SignalLock                0x02
#define D_SignalEmergencyCall       0x01
/*************************************************************
//>@D_NFD/HB
**************************************************************/
#define NOCRC   //(NOCRC|CRC)
#define NONFDHB   //(NONFDHB|NFDHB)
#define D_HBTime                    10000
#define D_LIFE                      5
#define D_DELAY                     10
/*************************************************************
//>@Global
**************************************************************/
typedef struct{
    int                 mLuminance;
    int                 mEnergySave;
    QString             mTheme;
    QStringList         mThemeList;
    QString             mRotate;
    QStringList         mRotateList;
} LCDSet;

#ifdef SURRPORT_NETWORK
typedef struct{
    QHostAddress        mIP;
    quint16             mPort;
    QString             mSubmask;
    QString             mGateway;
    QString             mDNS;
    QString             mDHCP;
    bool                mScan;
} EthernetSet;
#endif

typedef struct{
    QString             mPort;
    BaudRateType        mBuad;
    QStringList         mBuadList;
} Terminal;

typedef enum{
    Flag_Normal = 0,
    Flag_Ack = 1
} FRAME_FLAG;

typedef enum{
    State_Wait = 0,
    State_Header,
    State_DatalenH,
    State_DatalenL,
    State_Continus
} FRAME_STATE;

typedef enum{
    Type_FloorStatus = 0x00,
    Type_ButtonStatus = 0x01,
    Type_DisabilityBtnStatus = 0x02,

    Type_Debug = 0x7d,      //>@��Ҫ���ڵ���ģʽ�½�ȡ�����źŽӿڵ�����
    Type_FileTrans = 0x50,
    Type_SetCmd = 0x51,
    Type_NONE = 0xff
} FRAME_TYPE;
/*************************************************************
//>@IB
**************************************************************/
typedef enum{
    Type_Send = 0,
    Type_Rev = 1
}IBPORTEVENTTYPE;

typedef struct{
    FRAME_TYPE  mCmd;
    quint8      mData[7];
} IBFRAME_STRUCT;

typedef enum{
    MODE_NORMAL = 0,
    MODE_DEBUG,
    MODE_CONFIGURE,
    MODE_APPUPGRADE
} IBWORKMODE;

typedef enum{
    STATE_Start = 0,
    STATE_Run,
    STATE_Stop,
    STATE_Open
} IBRUNSTATE;

typedef enum{
    ArrowUnknow = 0x00,
    ArrowUp = 0x01,
    ArrowUproll = 0x05,
    ArrowUphalt = 0x09,
    ArrowDown = 0x02,
    ArrowDownroll = 0x06,
    ArrowDownhalt = 0x10,
    ArrowUpDown = 0x03,
    ArrowUpDownroll = 0x07,
    ArrowUpDownhalt = 0x11
} ARROWSTATE;

inline ARROWSTATE GetArrowState(QString pStateName)
{
    if(pStateName.isEmpty())
        return ArrowUnknow;
    if(pStateName.compare("UP") == 0)
    {
        return ArrowUp;
    }
    else if(pStateName.compare("UPROLL") == 0)
    {
        return ArrowUproll;
    }
    else if(pStateName.compare("UPHALT") == 0)
    {
        return ArrowUphalt;
    }
    else if(pStateName.compare("DOWN") == 0)
    {
        return ArrowDown;
    }
    else if(pStateName.compare("DOWNROLL") == 0)
    {
        return ArrowDownroll;
    }
    else if(pStateName.compare("DOWNHALT") == 0)
    {
        return ArrowDownhalt;
    }
    else if(pStateName.compare("UPDOWN") == 0)
    {
        return ArrowUpDown;
    }
    else if(pStateName.compare("UPDOWNROLL") == 0)
    {
        return ArrowUpDownroll;
    }
    else if(pStateName.compare("UPDOWNHALT") == 0)
    {
        return ArrowUpDownhalt;
    }
    return ArrowUnknow;
}

typedef enum{
    AUDIO_DING=101,
    AUDIO_DINGDANG,
    AUDIO_DINGDANGDONG,
    AUDIO_DOOROPEN,
    AUDIO_DOORCLOSE,
    AUDIO_FUNCTION=200
}AUDIO_RC;

typedef enum{
    DoorUnknow = 0,
    DoorOpen,
    DoorClose
} DOOR_STATE;

typedef enum{
    FunctionUnknow = 0,
    Function1,
    Function2,
    Function3
} FUNCTION_STATE;

typedef enum{
    STATE_NORMAL = 0,
    STATE_PRESS,
    STATE_RELEASE,
    STATE_LIGHT,
    STATE_MOVE
} BUTTONSTATE;
/*************************************************************
//>@NFD
**************************************************************/
typedef struct{
    FRAME_TYPE  mCmd;
    quint8      mCmdPara;
    QByteArray  mData;
} NFDFRAME_STRUCT;

typedef enum{
    Flag_FileHeader = 0x01,
    Flag_FileData = 0x02,
    Flag_FileFooter = 0x04,
    Flag_Stop = 0x08,
    Flag_FileMD5 = 0x20
} FILETRANS_FLAG;

typedef enum{
    Conn_PHDisconn = 0,
    Conn_PHConn,
    Conn_SFDisconn,
    Conn_SFConn
} CONN_STATE;

typedef enum{
    State_App_PHConn,
    State_App_SFConn,
    State_App_DisConn
} COMM_STATE;

typedef enum{
    //>@InitEvent
    Event_Unknow = 0,
    //>@UnQueueEvent
    Event_SFConn,
    Event_SFDisconn,
    Event_HB,
    Event_Stop,       //>@ֹͣ��ǰ������ָ��
    Event_DevInfo,    //>@��ȡ�豸��Ϣ
    Event_Set,
    Event_Get,
    Event_Message,    //>@��Ϣ
    Event_Inform,     //>@�ź�֪ͨ
    Event_Command,    //>@�豸��ֱ��ִ�е�����
    //>@QueueEvent
    Event_SendFileTest,
    Event_StartSendFile,
    Event_GetFileTest,
    Event_StartGetFile,
    Event_Ls,
    Event_GrabScreen,
    Event_DelFile,
    Event_CreatFile,
    Event_MovePath,
    Event_DelPath,
    Event_CreatPath,
    Event_Compress,
    Event_Decompress,
    //>@FatherEvent
    Event_SendFile,
    Event_GetFile,
    Event_GetDesktop,
    Event_DownLoadTheme,
    Event_UpLoadTheme
}EVENT_TYPE;

inline EVENT_TYPE StrToEventType(QString pStr)
{
    if(pStr.compare("SFConn",Qt::CaseInsensitive) == 0)
        return Event_SFConn;
    else if(pStr.compare("SFDisconn",Qt::CaseInsensitive) == 0)
        return Event_SFDisconn;
    else if(pStr.compare("HB",Qt::CaseInsensitive) == 0)
        return Event_HB;
    else if(pStr.compare("DevInfo",Qt::CaseInsensitive) == 0)
        return Event_DevInfo;
    else if(pStr.compare("Stop",Qt::CaseInsensitive) == 0)
        return Event_Stop;
    else if(pStr.compare("Set",Qt::CaseInsensitive) == 0)
        return Event_Set;
    else if(pStr.compare("Get",Qt::CaseInsensitive) == 0)
        return Event_Get;
    else if(pStr.compare("Message",Qt::CaseInsensitive) == 0)
        return Event_Message;
    else if(pStr.compare("Inform",Qt::CaseInsensitive) == 0)
        return Event_Inform;
    else if(pStr.compare("Command",Qt::CaseInsensitive) == 0)
        return Event_Command;
    else if(pStr.compare("SendFileTest",Qt::CaseInsensitive) == 0)
        return Event_SendFileTest;
    else if(pStr.compare("StartSendFile",Qt::CaseInsensitive) == 0)
        return Event_StartSendFile;
    else if(pStr.compare("GetFileTest",Qt::CaseInsensitive) == 0)
        return Event_GetFileTest;
    else if(pStr.compare("StartGetFile",Qt::CaseInsensitive) == 0)
        return Event_StartGetFile;
    else if(pStr.compare("GrabScreen",Qt::CaseInsensitive) == 0)
        return Event_GrabScreen;
    else if(pStr.compare("DelFile",Qt::CaseInsensitive) == 0)
        return Event_DelFile;
    else if(pStr.compare("CreatFile",Qt::CaseInsensitive) == 0)
        return Event_CreatFile;
    else if(pStr.compare("MovePath",Qt::CaseInsensitive) == 0)
        return Event_MovePath;
    else if(pStr.compare("DelPath",Qt::CaseInsensitive) == 0)
        return Event_DelPath;
    else if(pStr.compare("CreatPath",Qt::CaseInsensitive) == 0)
        return Event_CreatPath;
    else if(pStr.compare("Compress",Qt::CaseInsensitive) == 0)
        return Event_Compress;
    else if(pStr.compare("Decompress",Qt::CaseInsensitive) == 0)
        return Event_Decompress;
    else if(pStr.compare("Ls",Qt::CaseInsensitive) == 0)
        return Event_Ls;
    else
        return Event_Unknow;
}

inline QString EventTypeToStr(EVENT_TYPE pType)
{
    switch(pType)
    {
        case Event_SFConn:return QString("SFConn");
        case Event_SFDisconn:return QString("SFDisconn");
        case Event_HB:return QString("HB");
        case Event_Stop:return QString("Stop");
        case Event_DevInfo:return QString("DevInfo");
        case Event_Set:return QString("Set");
        case Event_Get:return QString("Get");
        case Event_Message:return QString("Message");
        case Event_Inform:return QString("Inform");
        case Event_Command:return QString("Command");
        case Event_SendFileTest:return QString("SendFileTest");
        case Event_StartSendFile:return QString("StartSendFile");
        case Event_GetFileTest:return QString("GetFileTest");
        case Event_StartGetFile:return QString("StartGetFile");
        case Event_GrabScreen:return QString("GrabScreen");
        case Event_DelFile:return QString("DelFile");
        case Event_CreatFile:return QString("CreatFile");
        case Event_MovePath:return QString("MovePath");
        case Event_DelPath:return QString("DelPath");
        case Event_CreatPath:return QString("CreatPath");
        case Event_Compress:return QString("Compress");
        case Event_Decompress:return QString("Decompress");
        case Event_Ls:return QString("Ls");
        default:break;
    }
    return QString("Unknow");
}

typedef enum {
    MONITOR_AUDIO = 0,
    MONITOR_VIDEO,
    MONITOR_AV
}MONITOR_TYPE;

inline QString GetMonitorTypeString(MONITOR_TYPE pType)
{
    QString pAvType;
    if(pType == MONITOR_AUDIO)
        pAvType = QString("Audio");
    else if(pType == MONITOR_VIDEO)
        pAvType = QString("Video");
    else if(pType == MONITOR_AV)
        pAvType = QString("AV");
    return pAvType;
}

inline MONITOR_TYPE GetMonitorType(QString pTypeString)
{
    MONITOR_TYPE tmpAvType;
    if(pTypeString.compare(QString("Audio")) == 0)
        tmpAvType = MONITOR_AUDIO;
    else if(pTypeString.compare(QString("Video")) == 0)
        tmpAvType = MONITOR_VIDEO;
    else if(pTypeString.compare(QString("AV")) == 0)
        tmpAvType = MONITOR_AV;
    return tmpAvType;
}

//>@---------------��������-------------------

typedef void (*CallBackFunc)();

class PASSWD
{
public:
    PASSWD()
    {
        m_PassWD.clear();
    }
    PASSWD(QString pPassWD)
    {
        *this = pPassWD;
    }
public:
    QString m_PassWD;
public:
    bool operator==(const PASSWD &s)
    {
        if(this->m_PassWD.compare(s.m_PassWD) != 0)
            return false;
        return true;
    }
    bool operator!=(const PASSWD &s)  { return !operator==(s); }

    PASSWD & operator=(const PASSWD &s)
    {
        if(s.m_PassWD.length() < 8)
            m_PassWD.clear();
        m_PassWD = s.m_PassWD;
        return *this;
    }

    PASSWD & operator=(const QString &s)
    {
        if(s.length() < 8)
            m_PassWD.clear();
        m_PassWD = s;
        return *this;
    }
};

class ENET_ADDR
{
public:
    ENET_ADDR()
    {
        for(int i=0;i<4;i++)
            mAddr[i] = 0;
    }
    ENET_ADDR(QString pAddr)
    {
        *this = pAddr;
    }
    ENET_ADDR(quint8 *pAddr)
    {
        for(int i=0;i<4;i++)
            mAddr[i] = pAddr[i];
    }
    enum SUBMASK {SUBMASK_A=0, SUBMASK_B, SUBMASK_C};
public:
    quint8  mAddr[4];
public:
    QList<quint32> toQList()
    {
        QList<quint32> tmpList;
        tmpList << mAddr[0] << mAddr[1] << mAddr[2] << mAddr[3];
        return tmpList;
    }
    QString toQString()
    {
        return QString("%1.%2.%3.%4").arg(mAddr[0])
                                     .arg(mAddr[1])
                                     .arg(mAddr[2])
                                     .arg(mAddr[3]);
    }
    bool isValid()
    {
        for(int i=0;i<4;i++)
        {
            if(mAddr[i] != 0)
            {
                return true;
            }
        }
        return false;
    }
    static QString GetDefaultSubMask(QString pIP)
    {
        ENET_ADDR tmpIP = pIP;
        if(tmpIP.isValid() == false)
            return QString("0.0.0.0");
        if(tmpIP.mAddr[0] >= 1 && tmpIP.mAddr[0] <= 126 &&
           tmpIP.mAddr[1] >= 0 && tmpIP.mAddr[1] <= 255 &&
           tmpIP.mAddr[2] >= 0 && tmpIP.mAddr[2] <= 255 &&
           tmpIP.mAddr[3] >= 1 && tmpIP.mAddr[3] <= 254)
        {
            //>@A����
            return QString("255.0.0.0");
        }
        else if(tmpIP.mAddr[0] >= 128 && tmpIP.mAddr[0] <= 191 &&
                tmpIP.mAddr[1] >= 0 && tmpIP.mAddr[1] <= 255 &&
                tmpIP.mAddr[2] >= 0 && tmpIP.mAddr[2] <= 255 &&
                tmpIP.mAddr[3] >= 1 && tmpIP.mAddr[3] <= 254)
        {
            //>@B����
            return QString("255.255.0.0");
        }
        else if(tmpIP.mAddr[0] >= 192 && tmpIP.mAddr[0] <= 223 &&
                tmpIP.mAddr[1] >= 0 && tmpIP.mAddr[1] <= 255 &&
                tmpIP.mAddr[2] >= 0 && tmpIP.mAddr[2] <= 255 &&
                tmpIP.mAddr[3] >= 1 && tmpIP.mAddr[3] <= 254)
        {
            //>@C����
            return QString("255.255.255.0");
        }
        return QString("0.0.0.0");
    }
    bool isOnSameNet(QString pIP)
    {
        ENET_ADDR tmpIP = pIP;
        ENET_ADDR tmpSubmask = GetDefaultSubMask(pIP);
        if(isValid() && tmpIP.isValid() && tmpSubmask.isValid())
        {
            for(int i=0;i<4;i++)
            {
                quint8 tmpSubIP = tmpSubmask.mAddr[i];
                if(tmpSubIP == 0)
                    return true;
                quint8 tmp1 = mAddr[i] & tmpSubIP;
                quint8 tmp2 = tmpIP.mAddr[i] & tmpSubIP;
                if(tmp1 != tmp2)
                    return false;
            }
        }
        return false;
    }
    bool operator==(const ENET_ADDR &s)
    {
        for(int i=0;i<4;i++)
        {
            if(this->mAddr[i] != s.mAddr[i])
                return false;
        }
        return true;
    }
    bool operator!=(const ENET_ADDR &s)  { return !operator==(s); }

    ENET_ADDR & operator=(const ENET_ADDR &s)
    {
        for(int i=0;i<4;i++)
        {
            this->mAddr[i] = s.mAddr[i];
        }
        return *this;
    }
    ENET_ADDR & operator=(const QString &s)
    {
        QStringList tmpAddrList = s.split('.');
        if(tmpAddrList.count() != 4)
        {
            for(int i=0;i<4;i++)
                mAddr[i] = 0;
        }
        else
        {
            for(int i=0;i<4;i++)
            {
                bool ok = false;
                QString tmpString = tmpAddrList.at(i);
                mAddr[i] = tmpString.toInt(&ok);
                if(ok == false)
                {
                    mAddr[i] = 0;
                }
            }
        }
        return *this;
    }
};

class VERSION
{
public:
    VERSION()
    {
        for(int i=0;i<4;i++)
            mAddr[i] = 0;
    }
    VERSION(QString pAddr)
    {
        *this = pAddr;
    }
    VERSION(quint8 *pAddr)
    {
        for(int i=0;i<4;i++)
            mAddr[i] = pAddr[i];
    }

public:
    quint8  mAddr[4];
public:
    QString toQString()
    {
        return QString("%1.%2.%3.%4").arg(mAddr[0])
                                     .arg(mAddr[1])
                                     .arg(mAddr[2])
                                     .arg(mAddr[3]);
    }
    bool isValid()
    {
        for(int i=0;i<4;i++)
        {
            if(mAddr[i] != 0)
            {
                IDE_TRACE_INT(i);
                return true;
            }
        }
        return false;
    }

    bool operator==(const VERSION &s)
    {
        for(int i=0;i<4;i++)
        {
            if(this->mAddr[i] != s.mAddr[i])
                return false;
        }
        return true;
    }
    bool operator!=(const VERSION &s)  { return !operator==(s); }

    VERSION & operator=(const VERSION &s)
    {
        for(int i=0;i<4;i++)
        {
            this->mAddr[i] = s.mAddr[i];
        }
        return *this;
    }
    VERSION & operator=(const QString &s)
    {
        QStringList tmpAddrList = s.split('.');
        if(tmpAddrList.count() != 4)
        {
            for(int i=0;i<4;i++)
                mAddr[i] = 0;
        }
        else
        {
            for(int i=0;i<4;i++)
            {
                bool ok = false;
                QString tmpString = tmpAddrList.at(i);
                mAddr[i] = tmpString.toInt(&ok);
                if(ok == false)
                {
                    mAddr[i] = 0;
                }
            }
        }
        return *this;
    }
};

class RANKS  //>@����
{
public:
    RANKS()
    {
        mRow = mColumn = 0;
    }
    RANKS(QString pRanks)
    {
        *this = pRanks;
    }
    RANKS(quint32  pRow, quint32 pColumn)
    {
        mRow = pRow;
        mColumn = pColumn;
    }
public:
    quint32  mRow, mColumn;
public:
    QString toString()
    {
        return QString("%1x%2").arg(mRow).arg(mColumn);
    }
    bool operator==(const RANKS &s)
    {
        if(mRow != s.mRow)
            return false;
        if(mColumn != s.mColumn)
            return false;
        return true;
    }
    bool operator!=(const RANKS &s)  { return !operator==(s); }

    RANKS & operator=(const RANKS &s)
    {
        mRow = s.mRow;
        mColumn = s.mColumn;
        return *this;
    }
    RANKS & operator=(const QString &s)
    {
        QStringList tmpAddrList = s.split('x');
        if(tmpAddrList.count() != 2)
        {
            mRow = mColumn = 0;
        }
        else
        {
            bool ok = false;
            QString tmpString = tmpAddrList.at(0);
            mRow = tmpString.toInt(&ok);
            if(ok == false)
            {
                mRow = 0;
            }
            ok = false;
            tmpString = tmpAddrList.at(1);
            mColumn = tmpString.toInt(&ok);
            if(ok == false)
            {
                mColumn = 0;
            }
        }
        return *this;
    }
};

class RESOLUTION
{
public:
    RESOLUTION()
    {
        mWidth = mHeight = 0;
    }
    RESOLUTION(QString pResolution)
    {
        *this = pResolution;
    }
    RESOLUTION(quint32  pWidth, quint32 pHeight)
    {
        mWidth = pWidth;
        mHeight = pHeight;
    }
public:
    quint32  mWidth, mHeight;
public:
    QString toString()
    {
        return QString("%1x%2").arg(mWidth).arg(mHeight);
    }
    QSize toSize()
    {
        return QSize(mWidth, mHeight);
    }
    QSizeF toSizeF()
    {
        return QSizeF(mWidth, mHeight);
    }
    bool isValid()
    {
        if(mWidth <= 0)
            return false;
        if(mHeight <= 0)
            return false;
        return true;
    }
    bool operator==(const RESOLUTION &s)
    {
        if(mWidth != s.mWidth)
            return false;
        if(mHeight != s.mHeight)
            return false;
        return true;
    }
    bool operator!=(const RESOLUTION &s)  { return !operator==(s); }

    RESOLUTION & operator=(const RESOLUTION &s)
    {
        mWidth = s.mWidth;
        mHeight = s.mHeight;
        return *this;
    }
    RESOLUTION & operator=(const QString &s)
    {
        QStringList tmpAddrList = s.split('x');
        if(tmpAddrList.count() != 2)
        {
            mWidth = mHeight = 0;
        }
        else
        {
            bool ok = false;
            QString tmpString = tmpAddrList.at(0);
            mWidth = tmpString.toInt(&ok);
            if(ok == false)
            {
                mWidth = 0;
            }
            ok = false;
            tmpString = tmpAddrList.at(1);
            mHeight = tmpString.toInt(&ok);
            if(ok == false)
            {
                mHeight = 0;
            }
        }
        return *this;
    }
};

typedef enum{
    SLAVE_USBNET=0,
    SLAVE_STORAGE=1,
    SLAVE_INVALID
} USBSLAVE_TYPE;

inline USBSLAVE_TYPE GetUSBSlaveType(QString pSlaveName)
{
    if(pSlaveName.isEmpty())
        return SLAVE_INVALID;
    if(pSlaveName.compare("Net",Qt::CaseInsensitive) == 0)
        return SLAVE_USBNET;
    else if(pSlaveName.compare("Storage",Qt::CaseInsensitive) == 0)
        return SLAVE_STORAGE;
    return SLAVE_INVALID;
}

inline bool isNum(QString pString)
{
    bool ok=false;
    pString.toInt(&ok, 10);
    return ok;
}

class SYSTEM_CMD : public QObject
{
    Q_OBJECT
public:
#ifdef WINDOWS
    //>@ example�� GUID GUID_DEVINTERFACE_DISK ={ 0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b };
    //>@            &GUID_DEVINTERFACE_DISK
    static bool EnumDeviceInterface(const GUID * InterfaceClassGUID)
    {
        char pcstr[128];
        HDEVINFO DeviceInfoSet;
        HDEVINFO NewDeviceInfoSet;
        SP_DEVICE_INTERFACE_DATA DeviceInterfaceData;
        PSP_DEVICE_INTERFACE_DETAIL_DATA lpDeviceInterfaceDetailData;
        DWORD dwBufferSize = 0;
        DWORD i;

        DeviceInfoSet = SetupDiCreateDeviceInfoList(NULL,NULL);
        if(DeviceInfoSet == INVALID_HANDLE_VALUE)
        {
            IDE_DEBUG(QString("Create device interface failed.(%1)").arg(GetLastError()));
            return 0;
        }
        NewDeviceInfoSet = SetupDiGetClassDevsEx(InterfaceClassGUID,NULL,NULL,DIGCF_DEVICEINTERFACE|DIGCF_PRESENT,DeviceInfoSet,NULL,NULL);
        if(NewDeviceInfoSet == INVALID_HANDLE_VALUE)
        {
            IDE_DEBUG(QString("Get device interface infomation failed."));
            return 0;
        }
        DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);
        for(i=0;;i++)
        {
            BOOL bResult = SetupDiEnumDeviceInterfaces(NewDeviceInfoSet,NULL,InterfaceClassGUID,i,&DeviceInterfaceData);
            if(!bResult)
            {
                if(bResult != NO_ERROR && GetLastError()!=ERROR_NO_MORE_ITEMS)
                {
                    IDE_DEBUG(QString("ERROR:%1").arg(GetLastError()));
                    return false;
                }
                break;
            }
            else
            {
                lpDeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)HeapAlloc(GetProcessHeap(),0,sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA));
                lpDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
                dwBufferSize = lpDeviceInterfaceDetailData->cbSize;
                while(!SetupDiGetDeviceInterfaceDetail(NewDeviceInfoSet,&DeviceInterfaceData,lpDeviceInterfaceDetailData,dwBufferSize,&dwBufferSize,NULL))
                {
                    if(ERROR_INSUFFICIENT_BUFFER == GetLastError())
                    {
                        lpDeviceInterfaceDetailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)HeapReAlloc(GetProcessHeap(),0,lpDeviceInterfaceDetailData,dwBufferSize);
                        lpDeviceInterfaceDetailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
                    }
                }
                WideCharToMultiByte(CP_ACP,0,lpDeviceInterfaceDetailData->DevicePath,-1,pcstr,128,NULL,NULL);
                IDE_DEBUG(QString("DevicePath:%1").arg(QString(pcstr)));
                HeapFree(GetProcessHeap(),0,lpDeviceInterfaceDetailData);
            }
        }
        return true;
    }
#endif
    static bool ScanProcess(QString pProcess)
    {
#ifdef WINDOWS
        PROCESSENTRY32 pe32;
        // ��ʹ������ṹ֮ǰ�����������Ĵ�С
        pe32.dwSize = sizeof(PROCESSENTRY32);
        // ��ϵͳ�ڵ����н�����һ������
        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST | TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE, 0);
        if(hProcessSnap == INVALID_HANDLE_VALUE)
        {
            IDE_TRACE();
            return false;
        }
        // �������̿��գ�������ʾÿ�����̵���Ϣ
        BOOL bMore = Process32First(hProcessSnap, &pe32);
        char pcstr[128];
        QString m_processname = pProcess;
        QString procesname;
        while(bMore)
        {
            WideCharToMultiByte(CP_ACP,0,pe32.szExeFile,-1,pcstr,128,NULL,NULL);
            procesname = QString(pcstr);
            IDE_TRACE_STR(procesname);
            if(procesname.compare(m_processname,Qt::CaseInsensitive) == 0)
            {
                return true;
            }
            bMore = Process32Next(hProcessSnap, &pe32);
        }
        // ��Ҫ���������snapshot����
        CloseHandle(hProcessSnap);
        return false;
#else
        QString cmd = QString("ps aux | grep %1 | grep -v grep > scanProcess").arg(pProcess);
        system(cmd.toLatin1().data());
        IDE_TRACE_STR(cmd);
        QFile ProcessFile("scanProcess");
        if (!ProcessFile.exists())
        {
            IDE_TRACE();
            return false;
        }
        char ProcessString[1024];
        if (!ProcessFile.open(QFile::ReadOnly))
        {
            ProcessFile.remove();
            IDE_TRACE();
            return false;
        }
        ProcessFile.readLine(ProcessString, 1000);
        ProcessFile.close();
        ProcessFile.remove();
        QString ProcessInfo = QString(ProcessString);
        bool flag = (bool)(ProcessInfo.indexOf(pProcess, 0, Qt::CaseInsensitive) != -1);
        return flag;
#endif
    }
    //>@pProcess������ĳһ���ؼ��֣���һ���ǳ�����,��Ҫ�пո�
    static bool KillProcess(QString pProcess)
    {
#ifdef WINDOWS
        PROCESSENTRY32 pe32;
        // ��ʹ������ṹ֮ǰ�����������Ĵ�С
        pe32.dwSize = sizeof(PROCESSENTRY32);
        // ��ϵͳ�ڵ����н�����һ������
        HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPHEAPLIST | TH32CS_SNAPPROCESS | TH32CS_SNAPTHREAD | TH32CS_SNAPMODULE, 0);
        if(hProcessSnap == INVALID_HANDLE_VALUE)
            return false;
        // �������̿��գ�������ʾÿ�����̵���Ϣ
        BOOL bMore = Process32First(hProcessSnap, &pe32);
        char pcstr[128];
        QString m_processname = pProcess;
        QString procesname;
        while(bMore)
        {
            WideCharToMultiByte(CP_ACP,0,pe32.szExeFile,-1,pcstr,128,NULL,NULL);
            procesname = QString(pcstr);
            IDE_TRACE_STR(procesname);
            if(procesname.compare(m_processname,Qt::CaseInsensitive) == 0)
            {
                HANDLE hXplayer = OpenProcess(PROCESS_ALL_ACCESS, false, pe32.th32ProcessID);
                TerminateProcess(hXplayer, 0);
                CloseHandle(hXplayer);
                CloseHandle(hProcessSnap);
                return true;
            }
            bMore = Process32Next(hProcessSnap, &pe32);
        }
        // ��Ҫ���������snapshot����
        CloseHandle(hProcessSnap);
        return true;
#else
        QString cmd = QString("ps aux | grep %1 | grep -v grep > killProcess").arg(pProcess);
        system(cmd.toLatin1().data());
        IDE_TRACE_STR(cmd);
        QFile ProcessFile("killProcess");
        if (!ProcessFile.exists())
        {
            IDE_TRACE();
            return false;
        }
        char ProcessString[1024];
        if (!ProcessFile.open(QFile::ReadOnly))
        {
            ProcessFile.remove();
            IDE_TRACE();
            return false;
        }
        //>@��ȡ������ؽ��̵�PID
        while(!(ProcessFile.atEnd()))
        {
            ProcessFile.readLine(ProcessString, 1000);
            QString ProcessInfo = QString(ProcessString);
#ifdef LINUX
            QString tmpPidString = ProcessInfo.mid(0, 5);
#endif
#ifdef UBUNTU
            QString tmpPidString = ProcessInfo.mid(7, 7);
#endif
            if(tmpPidString.isEmpty())
                continue;
            IDE_TRACE_STR(tmpPidString);
            bool ok = false;
            int tmpPid = tmpPidString.toInt(&ok, 10);
            if(ok)
            {
                QString tmpCmd = QString("kill -9 %1").arg(tmpPid);
                system(tmpCmd.toLatin1().data());
            }
        }
        ProcessFile.close();
        ProcessFile.remove();
        return true;
#endif
    }
    static bool SetNFC(bool pEnable)
    {
        if(pEnable)
        {
            QString tmpCmd = D_PCSCA_PATH;
            IDE_TRACE_STR(tmpCmd);
#ifndef WINDOWS
            system(tmpCmd.toLatin1().data());
#endif
        }
        else
        {
            QString tmpCmd = QString("killall %1").arg(D_PCSCA_PATH);
            IDE_TRACE_STR(tmpCmd);
#ifndef WINDOWS
            system(tmpCmd.toLatin1().data());
#endif
        }
        return true;
    }
    static bool SetSMS(bool pEnable, QString pConfFile=QString())
    {
        if(pEnable)
        {
            QFile tmpFile(pConfFile);
            if(tmpFile.exists() == false)
                return false;
#ifdef WINDOWS
            QString tmpString = QString("start /b %1 -f %2").arg(D_FFSERVER_PATH).arg(pConfFile);
            system(tmpString.toLatin1().data());
            IDE_TRACE_STR(tmpString);
#else
            QString tmpString = QString("%1 -f %2 > %3ffserverInfo &").arg(D_FFSERVER_PATH).arg(pConfFile).arg(D_FSRCPATH);
            QProcess tmpProcess;
            tmpProcess.setProcessChannelMode(QProcess::MergedChannels);
            tmpProcess.startDetached(tmpString);
            IDE_TRACE_STR(tmpString);
            QtSleep(100);
            QFile ffserverFile(QString("%1ffserverInfo").arg(D_FSRCPATH));
            if (!ffserverFile.exists())
            {
                IDE_TRACE();
                return false;
            }
            char ffserverString[1024];
            if (!ffserverFile.open(QFile::ReadOnly))
            {
                ffserverFile.remove();
                return false;
            }
            ffserverFile.readLine(ffserverString, 1000);
            ffserverFile.close();
            QString ffserverinfo = QString(ffserverString);
            if(ffserverinfo.indexOf(QString("FFserver started"), Qt::CaseInsensitive) == -1)
            {
                ffserverFile.remove();
                return false;
            }
            ffserverFile.remove();
#endif
        }
        else
        {
#ifdef WINDOWS
            KillProcess(D_FFSERVER_PATH);
            IDE_TRACE_STR(D_FFSERVER_PATH);
#else
            QString tmpCmd = QString("killall %1").arg(D_FFSERVER_PATH);
            IDE_TRACE_STR(tmpCmd);
            system(tmpCmd.toLatin1().data());
#endif
        }
        return true;
    }
    static bool SetMonitor(bool pEnable, QString pCameraDev=QString(), int pFrameRate=10, RESOLUTION pSize=RESOLUTION())  //>@��������ͷ�����ɼ�
    {
        if(pEnable)
        {
            if(pCameraDev.isEmpty() || pSize.isValid()==false)
            {
                IDE_TRACE();
                return false;
            }
#ifdef WINDOWS
            QString tmpCmd;
            if(isNum(pCameraDev))
            {
                tmpCmd = QString("%1 -f vfwcap -s %2 -r %3 -i %4 http://127.0.0.1:8090/feed1.ffm")
                        .arg(D_FFMPEG_PATH)
                        .arg(pSize.toString())
                        .arg(pFrameRate)
                        .arg(pCameraDev);
            }
#else
            QFile tmpFile(pCameraDev);
            if(tmpFile.exists() == false)
            {
                IDE_TRACE();
                return false;
            }
            QString tmpCmd;
            if(pCameraDev.contains("/dev/video", Qt::CaseInsensitive))
            {
                tmpCmd = QString("%1 -f video4linux2 -s %2 -r %3 -i %4 http://127.0.0.1:8090/feed1.ffm < /dev/null > /dev/null &")
                        .arg(D_FFMPEG_PATH)
                        .arg(pSize.toString())
                        .arg(pFrameRate)
                        .arg(pCameraDev);
            }
#endif
            else
            {
#ifdef WINDOWS
                tmpCmd = QString("start /b %1 -s %2 -r %3 -i %4 http://127.0.0.1:8090/feed1.ffm")
                        .arg(D_FFMPEG_PATH)
                        .arg(pSize.toString())
                        .arg(pFrameRate)
                        .arg(pCameraDev);
#else
                tmpCmd = QString("%1 -s %2 -r %3 -i %4 http://127.0.0.1:8090/feed1.ffm < /dev/null > /dev/null &")
                        .arg(D_FFMPEG_PATH)
                        .arg(pSize.toString())
                        .arg(pFrameRate)
                        .arg(pCameraDev);
#endif
            }
            SetMonitor(false);
            QProcess tmpProcess;
            tmpProcess.setProcessChannelMode(QProcess::MergedChannels);
            tmpProcess.startDetached(tmpCmd);
            IDE_TRACE_STR(tmpCmd);
        }
        else
        {
#ifdef WINDOWS
            KillProcess(D_FFMPEG_PATH);
#else
            QString tmpCmd = QString("killall %1").arg(D_FFMPEG_PATH);
            IDE_TRACE_STR(tmpCmd);
            system(tmpCmd.toLatin1().data());
#endif
        }
        return true;
    }
    static QPixmap GetIdentifyPix()  //>@��������ͷ���βɼ����ں�����ʶ�����
    {

        return QPixmap();
    }
    static bool SetIP(QString pNetName, ENET_ADDR pIP)
    {
        if(pNetName.isEmpty() || pIP.isValid() == false)
        {
            IDE_TRACE();
            return false;
        }
        QString tmpInfo;
#ifndef WINDOWS
        QString cmd = QString("ifconfig %1 %2 up").arg(pNetName).arg(pIP.toQString());
        QProcess tmpProcess;
        tmpProcess.setProcessChannelMode(QProcess::MergedChannels);
        tmpProcess.start(cmd);
        IDE_TRACE_STR(cmd);
        tmpProcess.waitForFinished();
        tmpInfo = tmpProcess.readAllStandardOutput();
        tmpProcess.kill();
#endif
        return !(tmpInfo.contains(D_NETERROR,Qt::CaseInsensitive));
    }
    static bool SetNetmask(QString pNetName, ENET_ADDR pNetmask)
    {
        QString tmpInfo;
#ifndef WINDOWS
        QString cmd = QString("ifconfig %1 netmask %2").arg(pNetName).arg(pNetmask.toQString());
        QProcess tmpProcess;
        tmpProcess.setProcessChannelMode(QProcess::MergedChannels);
        tmpProcess.start(cmd);
        IDE_TRACE_STR(cmd);
        tmpProcess.waitForFinished();
        tmpInfo = tmpProcess.readAllStandardOutput();
        tmpProcess.kill();
#endif
        return !(tmpInfo.contains(D_NETERROR,Qt::CaseInsensitive));
    }
    static bool SetGateway(ENET_ADDR pGateway)
    {
        if(pGateway.isValid() == false)
            return false;
        QString tmpInfo;
#ifndef WINDOWS
        QString cmd = QString("route add default gw ") + pGateway.toQString();
        QProcess tmpProcess;
        tmpProcess.setProcessChannelMode(QProcess::MergedChannels);
        tmpProcess.start(cmd);
        IDE_TRACE_STR(cmd);
        tmpProcess.waitForFinished();
        tmpInfo = tmpProcess.readAllStandardOutput();
        tmpProcess.kill();
#endif
        return !(tmpInfo.contains(D_GATEWAYERROR,Qt::CaseInsensitive));
    }
    static bool SetDNS(ENET_ADDR pDNS)
    {
        if(pDNS.isValid() == false)
            return false;
#ifndef WINDOWS
        QString DNSString;
        QStringList strlis;
        DNSString = QString("nameserver ") + pDNS.toQString();
        QFile DNSconffile(D_DNSCONF);
        QTextStream FileStream(&DNSconffile);
        if(!DNSconffile.open(QFile::ReadOnly))
        {
            return false;
        }
        while(!FileStream.atEnd())
        {
            QString lineNDS=FileStream.readLine();
            strlis<<lineNDS;
        }
        DNSconffile.close();

        QFile tmpconffile(D_DNSCONF);
        QTextStream tmpFileStream(&tmpconffile);
        if(!tmpconffile.open(QFile::WriteOnly))
        {
            return false;
        }
        int flag = 0;
        for (int i = 0; i < strlis.size(); i++)
        {
            if (strlis.at(i).compare(DNSString) == 0)
            {
                flag = 1;
            }
            tmpFileStream<<strlis.at(i)<<"\n";
        }
        if(flag == 0)
            tmpFileStream<<DNSString<<"\n";
        tmpconffile.close();
#endif
        return true;
    }
    static bool SetUSBWIFI(bool pEnable)
    {
#ifndef WINDOWS
        QProcess tmpProcess;
        if(pEnable == true)
        {
            tmpProcess.startDetached("wifi-start &");
        }
        else
        {
            tmpProcess.startDetached("wifi-stop &");
        }
        tmpProcess.waitForFinished();
        tmpProcess.kill();
#endif
        return true;
    }
    static bool AddDefaultNet(QString pNetName)
    {
        if(pNetName.isEmpty())
            return false;
#ifndef WINDOWS
        QProcess tmpProcess;
        QString tmpString = QString("route add default dev %1").arg(pNetName);
        tmpProcess.start(tmpString);
        IDE_TRACE_STR(tmpString);
        tmpProcess.waitForFinished();
        tmpProcess.kill();
#endif
        return true;
    }
    static bool SetNetCard(bool pEnable, QString pNetCardName)
    {
#ifndef WINDOWS
        if(pEnable == true)
        {
            QString cmd = QString("ifconfig %1 up").arg(pNetCardName);
            system(cmd.toLatin1().data());
            IDE_TRACE_STR(cmd);
        }
        else
        {
            QString cmd = QString("ifconfig %1 down").arg(pNetCardName);
            system(cmd.toLatin1().data());
            IDE_TRACE_STR(cmd);
        }
#endif
        return true;
    }
    static bool SetGPRS(bool pEnable)
    {
#ifndef WINDOWS
        if(pEnable == true)
        {
            QProcess tmpProcess;
            tmpProcess.start("pppd call wcdma &");
            tmpProcess.waitForFinished();
            tmpProcess.start(QString("route add default dev ppp0"));
            tmpProcess.waitForFinished();
            tmpProcess.kill();
            return true;
        }
        else
        {
            system("killall pppd");
        }
#endif
        return true;
    }
    //>@pConfFile��Ҫ�пո�
    static bool SetDHCP(bool pDHCP, QString pConfFile)
    {
#ifndef WINDOWS
        if(pDHCP == true)
        {
            QFile tmpFile(pConfFile);
            if(tmpFile.exists() == false)
                return false;
            QProcess tmpProcess;
            QString cmd = QString("udhcpd %1 &").arg(pConfFile);
            tmpProcess.startDetached(cmd);
            IDE_TRACE_STR(cmd);
            tmpProcess.waitForFinished();
            tmpProcess.kill();
        }
        else
        {
            if(pConfFile.isEmpty())
                return false;
            KillProcess(pConfFile);
        }
#endif
        return true;
    }
    static bool SetFTP(bool pFTP)
    {
        return pFTP;
    }
    static bool SetTelnet(bool pTelnet)
    {
        return pTelnet;
    }
    static bool SetSSH(bool pSSH)
    {
#ifndef WINDOWS
        QProcess tmpProcess;
        if(pSSH == true)
        {
            tmpProcess.startDetached("/etc/init.d/dropbear start &");
        }
        else
        {
            tmpProcess.startDetached("/etc/init.d/dropbear stop &");
        }
        tmpProcess.waitForFinished();
        tmpProcess.kill();
#endif
        return true;
    }
    static bool SetUsbSlave(bool pEnable, USBSLAVE_TYPE tmpType, QString pPara=QString())
    {
#ifndef WINDOWS
        switch(tmpType)
        {
            case SLAVE_USBNET:       //>@pParaΪIP��ַ
            {
                if(pEnable)
                {
                    QProcess tmpProcess;
                    tmpProcess.startDetached("rmmod g_file_storage");
                    tmpProcess.waitForFinished();
                    tmpProcess.startDetached("modprobe g_ether");
                    tmpProcess.waitForFinished();
                    tmpProcess.kill();
                }
                else
                {
                    system("rmmod g_ether");
                }
                break;
            }
            case SLAVE_STORAGE:       //>@pParaΪ�����صĴ���������ַ, ����Ϊ��/dev/mmcblk0p1
            {
                if(pEnable)
                {
                    QProcess tmpProcess;
                    tmpProcess.startDetached("rmmod g_ether");
                    tmpProcess.waitForFinished();
                    tmpProcess.startDetached("rmmod g_file_storage");
                    tmpProcess.waitForFinished();
                    tmpProcess.startDetached(QString("modprobe g_file_storage file=%1 stall=0 removable=1").arg(pPara));
                    tmpProcess.waitForFinished();
                    tmpProcess.kill();
                }
                else
                {
                    system("rmmod g_file_storage");
                }
                break;
            }
            default:
                return false;
        }
#endif
        return true;
    }
    static QString CreateSDPFile(QString pIP, QString pVideoPort, QString pAudioPort)
    {
        QString tmpFile = D_GrabScreenPath + QString("%1_%2.sdp").arg(pVideoPort).arg(pAudioPort);
        QFile file1(tmpFile);
        if(file1.exists())
            file1.remove();
        if(!file1.open(QFile::WriteOnly))
        {
            IDE_TRACE();
            return QString();
        }
        QTextStream newInputStream(&file1);
        newInputStream<<"v=0"<<"\n";
        newInputStream<<"o=- 0 0 IN IP4 127.0.0.1"<<"\n";
        newInputStream<<"s=No Name"<<"\n";
        newInputStream<<"t=0 0"<<"\n";
        newInputStream<<"a=tool:libavformat 55.4.101"<<"\n";
        if(!pAudioPort.isEmpty())
        {
            newInputStream<<"m=audio "<< pAudioPort << " RTP/AVP 97" << "\n";
            newInputStream<<"c=IN IP4 "<< pIP << "\n";
            newInputStream<<"b=AS:128"<<"\n";
            newInputStream<<"a=rtpmap:97 MPEG4-GENERIC/44100/2"<<"\n";
            newInputStream<<"a=fmtp:97 profile-level-id=1;mode=AAC-hbr;sizelength=13;indexlength=3;indexdeltalength=3; config=121056E500"<<"\n";
        }
        if(!pAudioPort.isEmpty())
        {
            newInputStream<<"m=video " << pVideoPort <<" RTP/AVP 96"<<"\n";
            newInputStream<<"c=IN IP4 "<< pIP << "\n";
            newInputStream<<"b=AS:200"<<"\n";
            newInputStream<<"a=rtpmap:96 MP4V-ES/90000"<<"\n";
            newInputStream<<"a=fmtp:96 profile-level-id=1"<<"\n";
        }
        file1.close();
        return tmpFile;
    }
    static bool CreateDHCPConf(QString pConfFile, QString pNetName, QString pIP,
                               QString pSubmask, QString pGateway, QString pDNS)
    {
        QFile file1(pConfFile);
        if(file1.exists())
            file1.remove();
        if(!file1.open(QFile::WriteOnly))
        {
            IDE_TRACE();
            return false;
        }
        QTextStream newInputStream(&file1);
        //>@��������
        newInputStream<<"interface  "<<pNetName<<"  #"<<"\n";
        //>@����IP��Χ
        ENET_ADDR tmpIP = pIP;
        tmpIP.mAddr[3] = 200;
        newInputStream<<"start  "<<tmpIP.toQString()<<"  #"<<"\n";
        tmpIP.mAddr[3] = 240;
        newInputStream<<"end  "<<tmpIP.toQString()<<"  #"<<"\n";
        //>@����Submask
        newInputStream<<"option subnet  "<<pSubmask<<"  #"<<"\n";
        //>@����Gateway
        newInputStream<<"opt router  "<<pGateway<<"  #"<<"\n";
        //>@����DNS
        newInputStream<<"opt dns  "<<pDNS<<"  #"<<"\n";
        newInputStream<<"option		lease		864000"<<"\n";
        file1.close();
        return true;
    }
    static bool ChangeDHCPConf(QString pConfFile, QString str,QString content)
    {
        QFile file(pConfFile);
        if(!file.exists() || !file.open(QFile::ReadOnly))
        {
            IDE_TRACE();
            return false;
        }
        QTextStream userFileStream(&file);
        QStringList strlis;
        while(!userFileStream.atEnd())
        {
            QString lineIni=userFileStream.readLine();
            strlis<<lineIni;
        }
        file.close();
        file.remove();
        QFile file1(pConfFile);
        if(!file1.open(QFile::WriteOnly))
        {
            IDE_TRACE();
            return false;
        }
        QTextStream newInputStream(&file1);
        for (int i = 0;i < strlis.size();i++)
        {
            QString tmpstrlis = strlis.at(i);
            if(tmpstrlis.startsWith('#'))
                continue;
            if(tmpstrlis.startsWith(str))
            {
                newInputStream<<str<<" "<<content<<"\n";
            }
            else
            {
                newInputStream<<strlis.at(i)<<"\n";
            }
        }
        file1.close();
        return true;
    }
    static bool ChangeWifiConf(QString str,QString content)
    {
        QFile file(D_WIFICONF);
        if(!file.open(QFile::ReadWrite))
        {
            return false;
        }
        QTextStream userFileStream(&file);
        QStringList strlis;
        while(!userFileStream.atEnd())
        {
            QString lineIni=userFileStream.readLine();
            strlis<<lineIni;
        }
        file.close();
        file.remove();
        QFile file1(D_WIFICONF);
        if(!file1.open(QFile::WriteOnly))
        {
            return false;
        }
        QTextStream newInputStream(&file1);
        for (int i = 0;i < strlis.size();i++)
        {
            QString tmpstrlis = strlis.at(i);
            QStringList tmplist = tmpstrlis.split("=");
            if(tmplist.count() != 2)
            {
                IDE_TRACE();
                continue;
            }
            if (tmplist.at(0).compare(str) == 0)
            {
                newInputStream<<str<<"="<<content<<"\n";
            }
            else
            {
                newInputStream<<strlis.at(i)<<"\n";
            }
        }
        file1.close();
        return true;
    }
    static bool SetSSID(QString pSSID)
    {
        return ChangeWifiConf("SSID", pSSID);
    }
    static bool SetPassWD(QString pPassWD)
    {
        return ChangeWifiConf("WPAPSK", pPassWD);
    }
    static bool GetCpuLoad(double &pTotal, double &pUsage)
    {
#ifndef WINDOWS
        char tmpString[100];
        QFile tmpFile("/proc/stat");
        if(tmpFile.open(QFile::ReadOnly) == false)
            return false;
        tmpFile.readLine(tmpString,100);
        QString CpuInfo = QString(tmpString);
        QStringList CpuInfoList = CpuInfo.split(' ');
        double Total_1 = 0;
        for(int i=0;i<CpuInfoList.count();i++)
        {
            Total_1 = Total_1 + CpuInfoList.at(i).toInt();
        }
        double SYS_IDLE_1 = CpuInfoList.at(4).toInt();
        system("sleep 1");
        tmpFile.readLine(tmpString,100);
        CpuInfo = QString(tmpString);
        CpuInfoList = CpuInfo.split(" ");
        double Total_2 = 0;
        for(int i=0;i<CpuInfoList.count();i++)
        {
            Total_2 = Total_2 + CpuInfoList.at(i).toInt();
        }
        double SYS_IDLE_2 = CpuInfoList.at(4).toInt();
        pUsage = SYS_IDLE_2 - SYS_IDLE_1;
        pTotal =  Total_1 - Total_2;
#endif
        return true;
    }
    static bool SetLuminance(int pVaule)//>@pVaule ��0~100
    {
#ifndef WINDOWS
        QString tmpCmdString = QString("echo %1 > /sys/devices/platform/pwm-backlight/backlight/pwm-backligh/brightness").arg(pVaule);
        system(tmpCmdString.toAscii().data());
#endif
        return true;
    }
    static bool SetLED(int id, bool light)
    {
#ifndef WINDOWS
        QString tmpString = QString("echo %1 > /sys/class/leds/led%2/brightness").arg(int(light)).arg(id);
        system(tmpString.toAscii().data());
#endif
        return true;
    }
    static bool SetVolume(int pVaule) //>@0~127
    {
#ifndef WINDOWS
        QString tmpString = QString("amixer set PCM %1").arg(pVaule);
        system(tmpString.toAscii().data());
#endif
        return true;
    }
    static bool GetMemSpace(double &pTotal, double &pUsage, double &pFree)
    {
        bool ok1 = false, ok2 = false;
#ifndef WINDOWS
        system("free | grep 'buffers/cache' | awk '{print $3}'>tmpFile");
        system("free | grep 'buffers/cache' | awk '{print $4}'>>tmpFile");
        QFile tmpFile("tmpFile");
        if(!tmpFile.exists())
            return false;
        char tmpString[10];
        if(!tmpFile.open(QFile::ReadOnly))
        {
            IDE_TRACE_STR("Open tmpFile Failed !");
            tmpFile.remove();
            return false;
        }
        tmpFile.readLine(tmpString,10);
        QString Memory_Used = QString(tmpString);
        double tmpUsage = Memory_Used.toInt(&ok1, 10);
        if(ok1)
            pUsage = tmpUsage;
        tmpFile.readLine(tmpString,10);
        QString Memory_Free = QString(tmpString);
        double tmpFree = Memory_Free.toInt(&ok2, 10);
        if(ok2)
            pFree = tmpFree;
        if(ok1 && ok2)
            pTotal = pUsage +  pFree;
        tmpFile.remove();
#endif
        return (ok1 && ok2);
    }
    static bool GetDiskSpace(QString pDiskPath, double &pTotal, double &pUsage, double &pFree, double &pPercent)
    {
        bool ok1 = false, ok2 = false, ok3 = false;
#ifndef WINDOWS
        QString tmpCmdString = QString("df | grep '%1' | awk '{print $3}'>DiskInfo").arg(pDiskPath);
        system(tmpCmdString.toAscii().data());
        tmpCmdString = QString("df | grep '%1' | awk '{print $4}'>>DiskInfo").arg(pDiskPath);
        system(tmpCmdString.toAscii().data());
        tmpCmdString = QString("df | grep '%1' | awk '{print $5}'>>DiskInfo").arg(pDiskPath);
        system(tmpCmdString.toAscii().data());
        QFile tmpFile("DiskInfo");
        if(!tmpFile.exists())
            return false;
        char  tmpString[10];
        if(!tmpFile.open(QFile::ReadOnly))
        {
            IDE_TRACE_STR("Open DiskInfo Failed !");
            tmpFile.remove();
            return false;
        }
        tmpFile.readLine(tmpString,10);
        QString Disk_Used = QString(tmpString);
        double tmpUsage = Disk_Used.toInt(&ok1, 10);
        if(ok1)
            pUsage = tmpUsage;
        tmpFile.readLine(tmpString,10);
        QString Disk_Free = QString(tmpString);
        double tmpFree = Disk_Free.toInt(&ok2, 10);
        if(ok2)
            pFree = tmpFree;
        if(ok1 && ok2)
            pTotal = pUsage +  pFree;
        tmpFile.readLine(tmpString,10);
        QString Percent = QString(tmpString);
        if(Percent.endsWith("%\n"))
            Percent = Percent.left(Percent.lastIndexOf("%"));
        double tmpPercent = Percent.toInt(&ok3, 10);
        if(ok3)
            pPercent = tmpPercent;
        tmpFile.remove();
#endif
        return (ok1 && ok2 && ok3);
    }
};

typedef enum {
    EVENT_INVALID = 0,
    EVENT_FLOOR,
    EVENT_ARROW,
    EVENT_FUNCTION,
    EVENT_AUDIO,
    EVENT_TIMER,         //>@��ʱ�¼�
    EVENT_ALARM        //>@�����¼�
} MAP_EVENT;

inline MAP_EVENT GetMapEventType(QString pKey)
{
    if(!pKey.compare("Floor", Qt::CaseInsensitive))
        return EVENT_FLOOR;
    else if(!pKey.compare("Arrow", Qt::CaseInsensitive))
        return EVENT_ARROW;
    else if(!pKey.compare("Function", Qt::CaseInsensitive))
        return EVENT_FUNCTION;
    else if(!pKey.compare("Audio", Qt::CaseInsensitive))
        return EVENT_AUDIO;
    else if(!pKey.compare("Timer", Qt::CaseInsensitive))
        return EVENT_TIMER;
    else if(!pKey.compare("Alarm", Qt::CaseInsensitive))
        return EVENT_ALARM;
    return EVENT_INVALID;
}

inline QString GetMapEventTypeString(MAP_EVENT pKey)
{
    if(pKey == EVENT_FLOOR)
        return "Floor";
    else if(pKey == EVENT_ARROW)
        return "Arrow";
    else if(pKey == EVENT_FUNCTION)
        return "Function";
    else if(pKey == EVENT_AUDIO)
        return "Audio";
    else if(pKey == EVENT_TIMER)
        return "Timer";
    else if(pKey == EVENT_ALARM)
        return "Alarm";
    return QString();
}

//>@ CLOCK

enum _CLOCKLABEL{
    ClockMon = 10,
    ClockTue = 11,
    ClockWed = 12,
    ClockThu = 13,
    ClockFri = 14,
    ClockSat = 15,
    ClockSun = 16,
    ClockColon = 17,
    ClockMinus = 18,
    ClockHourPointer=19,
    ClockMinutePointer=20,
    ClockSecondPointer=21,
    ClockDot=22
};

typedef enum{
    Element_HourPointer = 0,
    Element_MinutePointer = 1,
    Element_SecondPointer = 2,
    Element_Dot = 3,
    Element_Year0 = 4,
    Element_Year1 = 5,
    Element_Year2 = 6,
    Element_Year3 = 7,
    Element_Minus0 = 8,//>@-
    Element_Month0 = 9,
    Element_Month1 = 10,
    Element_Minus1 = 11,//>@-
    Element_Day0 = 12,
    Element_Day1 = 13,
    Element_Week = 14,
    Element_Hour0 = 15,
    Element_Hour1 = 16,
    Element_Colon0 = 17,//>@:
    Element_Minute0 = 18,
    Element_Minute1 = 19,
    Element_Colon1 = 20,//>@:
    Element_Second0 = 21,
    Element_Second1 = 22
}CLOCKE_ELEMENT;

typedef enum{
    ANALOG = 0,
    DIGITAL = 1
}CLOCK_TYPE;

typedef struct{
    QRectF       mRect;
    bool        mAnimateFlag;
    RC_POINTER  mRcPointer;
}CLOCK_ELEMENTINFO;

typedef enum{
    PTN_V_YMDHMS = 0,  //>@��ֱ�ֲ�  YY-MM-SS MM-SS-YY SS-MM-YY ����ʱ���ʽ
    PTN_V_DMYHMS,
    PTN_V_MDYHMS,
    PTN_V_YMDWHMS,
    PTN_V_DMYWHMS,
    PTN_V_MDYWHMS,
    PTN_H_YMDHMS,  //>@ˮƽ�ֲ�
    PTN_H_MDYHM,
    PTN_H_DMYHMS,
    PTN_H_MDYHMS,
    PTN_H_YMDWHMS,
    PTN_H_DMYWHMS,
    PTN_H_MDYWHMS,
    PTN_MOJI_MDWHM  //>@��ī��ʱ������
}CLOCK_PATTERN;  //>@ʱ����ʽ

class CLOCK_INFO
{
public:
    CLOCK_INFO()
    {
        mYear = 0xff;
        mMonth = 0xff;
        mDay = 0xff;
        mHour = 0xff;
        mMinute = 0xff;
        mSecond = 0xff;
        mWeekDay = 0xff;
        mErrorFlag = true;
    }
    CLOCK_INFO(quint8 pYear, quint8 pMonth, quint8 pDay, quint8 pHour, quint8 pMinute, quint8 pSecond)
    {
        fromChar(pYear, pMonth, pDay, pHour, pMinute, pSecond);
    }
    CLOCK_INFO(quint32 &pTime)
    {
        fromInt(pTime);
    }
    CLOCK_INFO(int pTime)
    {
        fromInt((quint32 &)pTime);
    }
    CLOCK_INFO(QDateTime pTime)
    {
        int year = pTime.date().year();
        if(year>=2000)
            year-=2000;
        else if(year>=1000)
            year-=1000;
        fromChar(year, pTime.date().month(), pTime.date().day(), pTime.time().hour(), pTime.time().minute(), pTime.time().second());
    }
public:
    quint8  mYear;
    quint8  mMonth;
    quint8  mDay;
    quint8  mWeekDay;
    quint8  mHour;
    quint8  mMinute;
    quint8  mSecond;

    bool    mErrorFlag;
public:
    bool isValid()
    {
        return !mErrorFlag;
    }

    int dayOfWeek()
    {
        QDate tmpData(mYear, mMonth, mDay);
        return tmpData.dayOfWeek();
    }

    bool operator==(const CLOCK_INFO &s)
    {
        if(this->mYear != s.mYear)
            return false;
        if(this->mMonth != s.mMonth)
            return false;
        if(this->mDay != s.mDay)
            return false;
        if(this->mHour != s.mHour)
            return false;
        if(this->mMinute != s.mMinute)
            return false;
        if(this->mSecond != s.mSecond)
            return false;
        return true;
    }
    bool operator!=(const CLOCK_INFO &s)  { return !operator==(s); }

    bool toInt(quint32 &pTime)
    {
         if(isValid())
            pTime = (mYear << 26) + (mMonth << 22) + (mDay << 17) + (mHour << 12) + (mMinute << 6) + mSecond;
         return !mErrorFlag;
    }
    bool fromClock(CLOCK_INFO &s)
    {
        quint8 tmpYear = s.mYear;
        quint8 tmpMonth = s.mMonth;
        quint8 tmpDay = s.mDay;
        quint8 tmpHour = s.mHour;
        quint8 tmpMinute = s.mMinute;
        quint8 tmpSecond = s.mSecond;
        if(tmpYear<0 || tmpYear>63)
            goto exit;
        mYear = tmpYear;
        if(tmpMonth<1 || tmpMonth>12)
            goto exit;
        mMonth = tmpMonth;
        if(tmpDay<1 || tmpDay>31)
            goto exit;
        mDay = tmpDay;
        if(tmpHour<0 || tmpHour>23)
            goto exit;
        mHour = tmpHour;
        if(tmpMinute<0 || tmpMinute>59)
            goto exit;
        mMinute = tmpMinute;
        if(tmpSecond<0 || tmpSecond>59)
            goto exit;
        mSecond = tmpSecond;
        mWeekDay = dayOfWeek();
        mErrorFlag = false;
        return true;
    exit:
        CLOCK_INFO();
        return false;
    }
    bool fromInt(quint32 &s)
    {
        quint8 tmpYear = (s>>26) & 0x0000003f;
        quint8 tmpMonth = (s>>22) & 0x0000000f; //>4
        quint8 tmpDay = (s>>17) & 0x0000001f;   //>5
        quint8 tmpHour = (s>>12) & 0x0000001f;  //>5
        quint8 tmpMinute = (s>>6) & 0x0000003f; //>6
        quint8 tmpSecond = s & 0x0000003f;      //>6
        if(tmpYear<0 || tmpYear>63)
            goto exit;
        mYear = tmpYear;
        if(tmpMonth<1 || tmpMonth>12)
            goto exit;
        mMonth = tmpMonth;
        if(tmpDay<1 || tmpDay>31)
            goto exit;
        mDay = tmpDay;
        if(tmpHour<0 || tmpHour>23)
            goto exit;
        mHour = tmpHour;
        if(tmpMinute<0 || tmpMinute>59)
            goto exit;
        mMinute = tmpMinute;
        if(tmpSecond<0 || tmpSecond>59)
            goto exit;
        mSecond = tmpSecond;
        mWeekDay = dayOfWeek();
        mErrorFlag = false;
        return true;
    exit:
        CLOCK_INFO();
        return false;
    }
    bool fromChar(quint8 pYear, quint8 pMonth, quint8 pDay, quint8 pHour, quint8 pMinute, quint8 pSecond)
    {
        pYear = pYear & 0x3f;
        if(pYear<0 || pYear>63)
            goto exit;
        mYear = pYear;

        pMonth = pMonth & 0xf;
        if(pMonth<1 || pMonth>12)
            goto exit;
        mMonth = pMonth;

        pDay = pDay & 0x1f;
        if(pDay<1 || pDay>31)
            goto exit;
        mDay = pDay;

        pHour = pHour & 0x1f;
        if(pHour<0 || pHour>23)
            goto exit;
        mHour = pHour;

        pMinute = pMinute & 0x3f;
        if(pMinute<0 || pMinute>59)
            goto exit;
        mMinute = pMinute;

        pSecond = pSecond & 0x3f;
        if(pSecond<0 || pSecond>59)
            goto exit;
        mSecond = pSecond;

        mWeekDay = dayOfWeek();
        mErrorFlag = false;
        return true;
    exit:
        CLOCK_INFO();
        return false;
    }

    CLOCK_INFO & operator=(CLOCK_INFO &s)
    {
        fromClock(s);
        return *this;
    }
    CLOCK_INFO & operator=(quint32 &s)
    {
        fromInt(s);
        return *this;
    }
};

inline quint32 ParseTimeString(int pYear, int pMonth, int pDay, int pHour, int pMinute)
{
    quint32 tmpNum = 0;
    tmpNum += pYear<<20;
    tmpNum += pMonth<<16;
    tmpNum += pDay<<11;
    tmpNum += pHour<<6;
    tmpNum += pMinute;
    return tmpNum;
}

inline quint32 ParseTimeString(QString pYear, QString pMonth, QString pDay, QString pHour, QString pMinute)
{
    quint32 tmpNum = 0;
    bool ok = false;
    quint8 tmpYear = pYear.toInt(&ok, 10);
    if(ok)
        tmpNum += tmpYear<<20;
    else
        tmpNum += 0x3f<<20;
    quint8 tmpMonth = pMonth.toInt(&ok, 10); //>4
    if(ok)
        tmpNum += tmpMonth<<16;
    else
        tmpNum += 0x0f<<16;
    quint8 tmpDay = pDay.toInt(&ok, 10);   //>5
    if(ok)
        tmpNum += tmpDay<<11;
    else
        tmpNum += 0x1f<<11;
    quint8 tmpHour = pHour.toInt(&ok, 10);  //>5
    if(ok)
        tmpNum += tmpHour<<6;
    else
        tmpNum += 0x1f<<6;
    quint8 tmpMinute = pMinute.toInt(&ok, 10); //>6
    if(ok)
        tmpNum += tmpMinute;
    else
        tmpNum += 0x3f;
    return tmpNum;
}

//>@ FLOOR

#define FLOORSTART  1000
#define FLOORLEFTBTN  1001

//>@��ͼƬ���ת��Ϊ��ĸ
inline quint8 GetFloorRcText(quint8 pFloorRcIndex)
{
    if(pFloorRcIndex>=0 && pFloorRcIndex<=9)
    {
        return pFloorRcIndex+'0';
    }
    if(pFloorRcIndex>=10 && pFloorRcIndex<=35)
    {
        return pFloorRcIndex+'A';
    }
    return -1;  //>@��ʾû��ͼƬ��Դ�����ش�����
}
//>@����ĸת��ΪͼƬ���
inline int GetFloorRcIndex(quint8 pFloorText)
{
    if(pFloorText>='0' && pFloorText<='9')
    {
        return pFloorText-'0';
    }
    if(pFloorText>='A' && pFloorText<='Z')
    {
        return pFloorText+10-'A';
    }
    return -1;  //>@��ʾû��ͼƬ��Դ�����ش�����
}
class FLOOR_INFO
{
public:
    FLOOR_INFO()
    {
        mSingleBits = 0xff;
        mTenBits = 0xff;
        mHundredBits = 0xff;
        mReserve = 0xff;
    }
    FLOOR_INFO(quint8 pHundred, quint8 pTen, quint8 pSingle)
    {
        mSingleBits = pSingle;
        mTenBits = pTen;
        mHundredBits = pHundred;
        mReserve = 0xff;
    }
    FLOOR_INFO(quint32 pFloor)
    {
        *this = pFloor;
    }
public:
    quint8  mSingleBits;
    quint8  mTenBits;
    quint8  mHundredBits;
    quint8  mReserve;
public:
    bool operator==(const FLOOR_INFO &s)
    {
        if(this->mHundredBits != s.mHundredBits)
            return false;
        if(this->mTenBits != s.mTenBits)
            return false;
        if(this->mSingleBits != s.mSingleBits)
            return false;
        return true;
    }
    bool operator!=(const FLOOR_INFO &s)  { return !operator==(s); }

    FLOOR_INFO & operator=(const FLOOR_INFO &s)
    {
        this->mHundredBits = s.mHundredBits;
        this->mTenBits = s.mTenBits;
        this->mSingleBits = s.mSingleBits;
        return *this;
    }
    FLOOR_INFO & operator=(const quint32 &s)
    {
        this->mHundredBits = (s >> 16) & 0x000000ff;
        this->mTenBits = (s >> 8) & 0x000000ff;
        this->mSingleBits = s & 0x000000ff;
        this->mReserve = 0xff;
        return *this;
    }
    quint32 toInt()
    {
        return (0xff000000 + (mHundredBits << 16) + (mTenBits << 8) + mSingleBits);
    }
    quint32 toInteget()
    {
        return (mHundredBits*100 + mTenBits*10 + mSingleBits);
    }
};

inline quint32 ParseFloorString(QString pHundred, QString pTen, QString pUnit)
{
    quint32 tmpNum = 0;
    bool ok = false;
    quint8 tmpHundred = pHundred.toInt(&ok, 10);
    if(ok)
        tmpNum += tmpHundred<<16;
    else
        tmpNum += 0xff<<16;
    quint8 tmpTen = pTen.toInt(&ok, 10);
    if(ok)
        tmpNum += tmpTen<<8;
    else
        tmpNum += 0xff<<8;
    quint8 tmpUnit = pUnit.toInt(&ok, 10);
    if(ok)
        tmpNum += tmpUnit;
    else
        tmpNum += 0xff;
    return tmpNum;
}

//>@ MESSAGE

typedef enum{
    LEVEL_INVALID = 100,
    LEVEL_INFO = 0,
    LEVEL_WARN = 1,
    LEVEL_ERROR = 2
} MSG_LEVEL;

typedef struct{
    MSG_LEVEL mMsgLevel;
    QString   mMessage;
    int       mDelay;
} MSG_INFO;

//>@Animal

typedef enum{
    TypeFish=0,
    TypeInsect
}AnimalType;

typedef enum{
    StageBrith=0,
    StageYoung,
    StageMature,
    StageOld,
    StageDeath,
    StageUnknow=255
}AnimalStage;


//>@ SETBAR

typedef enum{
    ITEM_PREV = 0,
    ITEM_CUR = 1,
    ITEM_NEXT = 2,
    ITEM_HIDE = 3
} ITEM_LOCATION;

typedef enum{
    MOVE_NONE = 0,
    MOVE_LEFT = 1,
    MOVE_RIGHT = 2
} MOVE_DIRECTION;

typedef struct{
    QRect           mLocation;
    qreal           mTransparent;
    qreal           mZValue;
} ITEM_PARA;

typedef enum {
    ITEM_PERIPHERAL=0,
    ITEM_APPLICATION,
    ITEM_MONITOR,
    ITEM_LOGVIEWER,
    ITEM_UNKNOW
} ITEM_TYPE;

//>@FLOORBUTTON

#define TEXTRATIO   4.0
#define FLOORWIDTH  10.0

typedef enum{
    PIC_DARK=0,
    PIC_LIGHT=1,
    PIC_EFFECT=2,
    TEXT_DARK=3,
    TEXT_LIGHT=4
}BUTTON_RC;

typedef struct{
    qint8       mFadePointer;
    qint8       mEffectPointer;
    qint8       mTextPointer;
}BUTTON_POINTER;

typedef enum{
    PTN_FB_GRID = 0,    //>@������ʽ
    PTN_FB_ELLIPSE,     //>@��Բ��ʽ
    PTN_FB_GUIDE        //>@����ʽ
} FB_PATTERN;

typedef enum{
    PTN_KB_GRID_H = 0,    //>@���������
    PTN_KB_GRID_V,        //>@����������
    PTN_KB_QWERTY,
    PTN_KB_DISEN,
    PTN_KB_YUNGTAY
} KB_PATTERN;


typedef enum{
    PTN_SB_HOLLOW = 0,    //>@����Ч��
    PTN_SB_MENU           //>@�˵�Ч�����
} SB_PATTERN;

struct PortSettings
{
    BaudRateType    BaudRate;
    DataBitsType    DataBits;
    ParityType      Parity;
    StopBitsType    StopBits;
    FlowType        FlowControl;
    long            Timeout_Millisec;
};

#endif // DEFINE_H