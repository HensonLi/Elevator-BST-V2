#include "graphicssetbar.h"
#ifdef DISPLAY
#include "devicemanager.h"
#endif
GraphicsSetBar::GraphicsSetBar(QGraphicsItem *parent):
    GraphicsOperate(parent)
{
#ifdef DISPLAY
    m_DevManager = 0;
#endif
    m_Diff = 0;
    m_CurValue = 0;
    m_CurItemInfo = 0;
}

bool GraphicsSetBar::InitSubCommonPara(AREA_STYLE* pAreaStyle, QString pLabel, QString pContent)
{
    if(pLabel.compare(PARA_PATTERN, Qt::CaseInsensitive) == 0)
    {
        if(pContent == QString("HOLLOW"))
            m_Pattern = PTN_SB_HOLLOW;
        else if(pContent == QString("MENU"))
            m_Pattern = PTN_SB_MENU;
    }
    return true;
}

bool GraphicsSetBar::PaintEffect(QPainter *p)
{
    QPixmap tmpPixmap = GetPixmap(BGRC);
    if(!tmpPixmap.isNull())
    {
        QRect rect = geometry().toRect();
        p->save();
        p->setOpacity(0.6);
        p->drawPixmap(QRect(0,0,rect.width(),rect.height()), tmpPixmap);
        p->restore();
    }
    return true;
}

bool GraphicsSetBar::Start()
{
    if(!GraphicsOperate::Start())
        return false;
    if(!InitItems())
    {
        IDE_TRACE();
        return false;
    }
#ifndef IDE
    hide(); //>@Ĭ������
#endif
    updateEffect(m_ItemCount/2);
    return true;
}

//>@��ȡ�ɻ�������������С
bool GraphicsSetBar::GetValidRect(QRect &pRect)
{
    QRectF rect = geometry();
    AREA_ANIMATE *tmpAreaAnimate = m_EffectGroup.value(OPERATE_SLIP);
    if(tmpAreaAnimate)
    {
        switch(tmpAreaAnimate->mEffectType)
        {
            case EffectTypeTwirl:
            {
                qreal tmpHalfWidth = rect.width()/2.0;
                qreal tmpMinLen = (tmpHalfWidth>rect.height())?(rect.height()):(tmpHalfWidth);
                qreal tmpX = (tmpHalfWidth>rect.height())?((rect.width()-rect.height())/2):(0);
                qreal tmpY = (tmpHalfWidth>rect.height())?(0):((rect.height()-tmpHalfWidth)/2);
                pRect = QRect(QPoint(tmpX, tmpY), QSize(tmpMinLen*2, tmpMinLen));
                return true;
            }
            case EffectTypeGlide:
            {
                qreal tmpHalfWidth = rect.width()/2.0;
                qreal tmpMinLen = (tmpHalfWidth>rect.height())?(rect.height()):(tmpHalfWidth);
                qreal tmpX = (tmpHalfWidth>rect.height())?((rect.width()-rect.height())/2):(0);
                qreal tmpY = (tmpHalfWidth>rect.height())?(0):((rect.height()-tmpHalfWidth)/2);
                pRect = QRect(QPoint(tmpX, tmpY), QSize(tmpMinLen*2, tmpMinLen));
                return true;
            }
            default: //>@���ʹ�ò�ʶ�����Ч
            {
                return false;
            }
        }
    }
    //>@���ʹ�ò�ʶ�����Ч����ռ��������С
    pRect = rect.toRect();
    return true;
}

void GraphicsSetBar::ReleaseItems()
{
    for(int i=m_ItemList.count()-1;i>=0;i--)
    {
        SETITEM_INFO *tmpSetItem = m_ItemList.takeAt(i);
        if(tmpSetItem)
        {
            if(tmpSetItem->mItemWidget)
                tmpSetItem->mItemWidget->deleteLater();
            delete tmpSetItem;
        }
    }
    m_ItemList.clear();
    m_CurItemInfo = 0;
}

bool GraphicsSetBar::InitItems()
{
    ReleaseItems();
    //>@����ITEMs����������Ч����
    if(GetValidRect(m_ValidRect) == false)
    {
        IDE_TRACE();
        return false;
    }
    //>@����ITEM����
    m_ItemCount = m_RcList.count();
    if(m_RcList.contains(BGRC))
    {
        m_RcList.removeOne(BGRC);
        m_ItemCount -= 1;
    }
    if(m_ItemCount < 1)
        return false;
    IDE_TRACE_INT(m_ItemCount);
    //>@��ʼ��ITEM
    for(int i=0; i<m_ItemCount; i++)
    {
        int tmpKey = m_RcList.at(i);
        AddItem(i, (ITEM_TYPE)tmpKey, GetPixmap(tmpKey));
    }
    return true;
}

bool GraphicsSetBar::NeedReboot()
{
    return false;
}

void GraphicsSetBar::AddItem(int pIndex, ITEM_TYPE pType, QPixmap pPixmap)
{
    //>@��ʼ����Դ
    quint32 tmpMaxHeight=40;
    QVBoxLayout *tmpLayout = new QVBoxLayout;
    switch(pType)
    {
        case ITEM_PERIPHERAL:
        {
#ifdef DISPLAY
            if(m_DevManager)
            {
                QList<PH_Type> tmpList = m_DevManager->m_PHDevList.keys();
                for(int i=0;i<tmpList.count();i++)
                {
                    PhysicalDevice* tmpPHDevice = m_DevManager->m_PHDevList.value(tmpList.at(i));
                    if(tmpPHDevice && tmpPHDevice->m_SettingGroup)
                    {
                        tmpMaxHeight += tmpPHDevice->m_SettingGroup->height();
                        tmpLayout->addWidget(tmpPHDevice->m_SettingGroup);
                    }
                }
            }
#endif
            break;
        }
        case ITEM_APPLICATION:
        {
            tmpMaxHeight = 100;
            break;
        }
        case ITEM_MONITOR:
        {
            tmpMaxHeight = 100;
            break;
        }
        case ITEM_LOGVIEWER:
        {
            tmpMaxHeight = 100;
            break;
        }
        default:
            break;
    }
    SETITEM_INFO *tmpItemInfo = new SETITEM_INFO(pType);
    tmpItemInfo->mItemProxy = new QGraphicsProxyWidget(this);
    tmpItemInfo->mItemWidget = new SetBarItem(pPixmap, m_ValidRect);
    tmpItemInfo->mItemWidget->m_ParaUI->setLayout(tmpLayout);
    tmpItemInfo->mItemWidget->m_ParaUI->setMaximumHeight(tmpMaxHeight);
    tmpItemInfo->mItemWidget->m_ParaUI->setMinimumHeight(tmpMaxHeight);
    tmpItemInfo->mItemProxy->setWidget(tmpItemInfo->mItemWidget);
    tmpItemInfo->mCurParaIndex = pIndex;
    tmpItemInfo->mNextParaIndex = pIndex;
    m_ItemList.append(tmpItemInfo);
}

int GraphicsSetBar::GetCurItemIndex()
{
    int count = m_ItemList.count();
    for(int i=0;i<count;i++)
    {
        SETITEM_INFO* tmpSetItem = m_ItemList.at(i);
        if(tmpSetItem == 0)
            continue;
        if(tmpSetItem->mCurParaIndex == 0)
            return i;
    }
    return -1;
}

SETITEM_INFO* GraphicsSetBar::GetCurSetItem()
{
    int count = m_ItemList.count();
    for(int i=0;i<count;i++)
    {
        SETITEM_INFO* tmpSetItem = m_ItemList.at(i);
        if(tmpSetItem == 0)
            continue;
        if(tmpSetItem->mCurParaIndex == 0)
            return tmpSetItem;
    }
    return (SETITEM_INFO*)0;
}

//>@��ʾ��pIndex��ITEM������ǰ�棬Ҳ������λ��0
bool GraphicsSetBar::UpdateItems(int pIndex)
{
    int count = m_ItemList.count();
    if(pIndex < 0 || pIndex >= count)
    {
        IDE_TRACE();
        return false;
    }
    //>@ȷ�����������Լ��ƶ�����
    int tmpCurIndex = GetCurItemIndex();
    int tmpIndexDiff = tmpCurIndex - pIndex;
    m_ItemSlipCount = qAbs(tmpIndexDiff);
    IDE_TRACE_INT(m_ItemSlipCount);
    if(tmpIndexDiff == 0)
    {
        IDE_TRACE();
        return false;
    }
    //>@����Items
    for(int i=0;i<count;i++)
    {
        SETITEM_INFO* tmpSetItem = m_ItemList.at(i);
        if(tmpSetItem == 0)
            continue;
        int tmpValue = tmpSetItem->mCurParaIndex + tmpIndexDiff;
        tmpSetItem->mNextParaIndex = tmpValue;
    }
    //>@�޸���Чʱ��
    AREA_ANIMATE* tmpAreaAnimate = m_EffectGroup.value(OPERATE_SLIP);
    if(tmpAreaAnimate == 0)
    {
        IDE_TRACE();
        return true;  //>@���SLIP��ʹ����Ч����ֱ�ӷ�����
    }
    if(tmpIndexDiff > 0)
    {
        tmpAreaAnimate->mDirection = Horizontal;
        tmpAreaAnimate->mOrientation = Negative;
    }
    else if(tmpIndexDiff < 0)
    {
        tmpAreaAnimate->mDirection = Horizontal;
        tmpAreaAnimate->mOrientation = Positive;
    }
    //tmpAreaAnimate->mAnimateTime *= qAbs(tmpIndexDiff);
    return true;
}


void GraphicsSetBar::OperateItem(int pFrameNum)
{
    if(m_AreaAnimate == 0)
    {
        IDE_TRACE();
        return;
    }
    else
    {
        switch(m_AreaAnimate->mEffectType)
        {
            case EffectTypeTwirl:
            {
                static qreal tmpSingleAngelDiff = 2*PI/m_ItemCount;
                static qreal tmpTwirlA = m_ValidRect.width() / 3.0;   //>@ȡ��Բ�ĳ��뾶aΪ1/3�ĳ��ȣ�bΪ1/4�ĳ���
                static qreal tmpTwirlB = m_ValidRect.height() / 4.0;
                static qreal tmpMaxHeight = m_ValidRect.height()*7.0/10.0;//>@������ǰ������תItem�Ŀ�Ϊ�߶ȵ�2/3���߶�Ϊ��Ч����߶ȵ�7/10
                static QSizeF tmpMaxSize = QSize(tmpMaxHeight*2.0/3.0,  tmpMaxHeight);
                //>@�����ĵ�����1/8���������ÿ��ƫ�·�
                static QPointF tmpCentrePoint = QPointF(m_ValidRect.x()+m_ValidRect.width()/2.0,
                                                      m_ValidRect.y()+m_ValidRect.height()/2.0 - m_ValidRect.height()/8.0);
                qreal tmpAngelDiff = 2*PI*m_ItemSlipCount/m_ItemCount;
                m_CurValue = pFrameNum * m_Diff * tmpAngelDiff;
                int count = m_ItemList.count();
                for(int i=0; i< count; i++)
                {
                    SETITEM_INFO* tmpSetItemInfo = m_ItemList.at(i);
                    if(tmpSetItemInfo == 0)
                    {
                        IDE_TRACE();
                        continue;
                    }
                    qreal tmpBeginAngle = RegularAngle(3.0 * PI / 2.0 + tmpSetItemInfo->mCurParaIndex * tmpSingleAngelDiff);  //>@��270�ȿ�ʼ
                    qreal tmpAngle;
                    if(m_AreaAnimate->mOrientation == Positive)
                        tmpAngle = RegularAngle(tmpBeginAngle - m_CurValue);
                    else if(m_AreaAnimate->mOrientation == Negative)
                        tmpAngle = RegularAngle(tmpBeginAngle + m_CurValue);
                    qreal tmpHalfAngleRatio = 1.0 - CalDiffBeginAngle(tmpAngle)/PI;  //>@���ڼ�����������Ĳ���
                    QPointF tmpItemCentrePoint = tmpCentrePoint + QPointF(tmpTwirlA*qCos(tmpAngle), -tmpTwirlB*qSin(tmpAngle));
                    QSizeF tmpItemSize = tmpMaxSize * tmpHalfAngleRatio;
                    QRectF tmpRect = QRectF(tmpItemCentrePoint, tmpItemSize);
                    tmpRect.moveCenter(tmpItemCentrePoint);
                    //>@�˴��������ȻtmpRect��С����mProxy�����Ĵ�������С��С���ƴӶ���������mProxy�Ĵ�С����ΪtmpRect������
                    tmpSetItemInfo->mItemProxy->setGeometry(tmpRect);
                    //tmpSetItemInfo->mItemProxy->setTransform(QTransform().translate(width()/2, height() / 2).rotate(0, Qt::YAxis).translate(-width()/2, -height()/2));
                    //>@��С͸����Ϊ0.5�����Ϊ1
                    tmpSetItemInfo->mItemProxy->setOpacity(tmpHalfAngleRatio/2.0+0.5);
                    tmpSetItemInfo->mItemProxy->setZValue(zValue() + 100 * tmpHalfAngleRatio);  //>@�˴����������100��ITEM
                }
                break;
            }
            case EffectTypeGlide:  //>@���ĵ�������������߼�С��ʹ�ù�ʽY=1-|X/m_ItemCount|
            {
                static qreal tmpMaxHeight = m_ValidRect.height()*9.0/10.0;
                static QSizeF tmpMaxSize = QSize(tmpMaxHeight*2.0/3.0,  tmpMaxHeight);
                static QPointF tmpCentrePoint = QPointF(m_ValidRect.x()+m_ValidRect.width()/2.0,
                                                        m_ValidRect.y()+m_ValidRect.height()/2.0);
                qreal tmpXPosDiff = m_ValidRect.width()/(2.0*m_ItemCount);
                m_CurValue = pFrameNum * m_Diff * m_ItemSlipCount;
                int count = m_ItemList.count();
                for(int i=0; i< count; i++)
                {
                    SETITEM_INFO* tmpSetItemInfo = m_ItemList.at(i);
                    if(tmpSetItemInfo == 0)
                    {
                        IDE_TRACE();
                        continue;
                    }
                    qreal tmpX;
                    if(m_AreaAnimate->mOrientation == Positive)
                    {
                        tmpX = tmpSetItemInfo->mCurParaIndex - m_CurValue;
                    }
                    else if(m_AreaAnimate->mOrientation == Negative)
                    {
                        tmpX = tmpSetItemInfo->mCurParaIndex + m_CurValue;
                    }
                    qreal tmpCurRatio = 1-qAbs(tmpX/m_ItemCount);
                    qreal tmpXPos = tmpX*tmpXPosDiff;
                    QPointF tmpItemCentrePoint = QPointF(tmpCentrePoint.x() + tmpXPos, tmpCentrePoint.y());
                    QSizeF tmpItemSize = tmpMaxSize * tmpCurRatio;
                    QRectF tmpRect = QRectF(tmpItemCentrePoint, tmpItemSize);
                    tmpRect.moveCenter(tmpItemCentrePoint);
                    tmpSetItemInfo->mItemProxy->setGeometry(tmpRect);
                    tmpSetItemInfo->mItemProxy->setOpacity(tmpCurRatio);
                    tmpSetItemInfo->mItemProxy->setZValue(zValue() + 100 * tmpCurRatio);  //>@�˴����������100��ITEM
                }
                break;
            }
            case EffectTypeRotate:
            {
                if(m_CurItemInfo==0)
                    return;
                if(m_AreaAnimate->mOrientation == Negative)
                    m_CurValue = (20 - pFrameNum) * m_Diff * 180;
                else
                    m_CurValue = pFrameNum * m_Diff * 180;
                if(m_CurValue < 0 || m_CurValue > 180)
                {
                    IDE_TRACE();
                    return;
                }
                SetBarItem* tmpItemWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
                if(tmpItemWidget == 0)
                {
                    IDE_TRACE();
                    return;
                }
                if(m_CurValue > 90)
                {
                    tmpItemWidget->ShowUI();
                }
                else
                {
                    tmpItemWidget->HideUI();
                }
                QRectF r = m_CurItemInfo->mItemProxy->boundingRect();
                if(m_AreaAnimate->mDirection == Horizontal)
                    m_CurItemInfo->mItemProxy->setTransform(QTransform()
                                                    .translate(r.width() / 2, r.height() / 2)
                                                    .rotate(m_CurValue - 180 * tmpItemWidget->m_ItemStage, Qt::YAxis)
                                                    .translate(-r.width() / 2, -r.height() / 2));
                else
                    m_CurItemInfo->mItemProxy->setTransform(QTransform()
                                                    .translate(r.width() / 2, r.height() / 2)
                                                    .rotate(m_CurValue - 180 * tmpItemWidget->m_ItemStage, Qt::XAxis)
                                                    .translate(-r.width() / 2, -r.height() / 2));
                break;
            }
            case EffectTypeZoom:
            {
                if(m_CurItemInfo==0)
                    return;
                m_CurValue = pFrameNum * m_Diff * 100;
                if(m_CurValue < 0 || m_CurValue > 100)
                {
                    IDE_TRACE();
                    return;
                }
                SetBarItem* tmpItemWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
                if(tmpItemWidget == 0)
                {
                    IDE_TRACE();
                    return;
                }
                if(tmpItemWidget->m_ItemStage == SetBarItem::BEGIN && m_CurValue == 50)
                {
                    tmpItemWidget->HideUI();
                    tmpItemWidget->m_ItemStage = SetBarItem::END;
                }
                else if(tmpItemWidget->m_ItemStage == SetBarItem::END && m_CurValue == 50)
                {
                    tmpItemWidget->m_ItemStage = SetBarItem::BEGIN;
                }
                qreal ratio = (tmpItemWidget->m_ItemStage == SetBarItem::BEGIN)?m_CurValue:(100-m_CurValue);
                m_CurItemInfo->mItemProxy->setTransform(QTransform().scale(ratio, ratio));
                break;
            }
            default:
                break;
        }
    }
}

void GraphicsSetBar::updateEffect(AREA_OPERATE pOperate, QVariant pPara)
{
}

bool GraphicsSetBar::updateEffect(int pIndex)
{
    //>@�ȴ��ϴ���Ч���
    if(m_Animator.state() == QTimeLine::Running)
        return false;
    if(UpdateItems(pIndex) == false)
    {
        IDE_TRACE();
        return false;
    }
    m_OperateInfo[STEP0].mValid = false;
    m_OperateInfo[STEP1].mValid = false;
    m_Animator.stop();
    //>@Operate0
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpItemWidget && tmpItemWidget->m_ItemStage == SetBarItem::END)     //>@����������ô����У���ԭ����������
        {
            m_OperateInfo[STEP0].mValid = true;
            m_OperateInfo[STEP0].mOperate = OPERATE_KEYPRESS;
        }
    }
    //>@Operate1
    m_SlipOperateInfo.mValid = true;
    m_SlipOperateInfo.mOperate = OPERATE_SLIP;
    //>@Operate2
    m_OperateInfo[STEP1].mValid = false;
    m_OperateInfo[STEP1].mOperate = OPERATE_KEYPRESS;
    //>@exec
    Operate0();
    return true;
}

bool GraphicsSetBar::updateEffect(bool pFlag)
{
    //>@�ȴ��ϴ���Ч���
    if(m_Animator.state() == QTimeLine::Running)
        return false;
    m_OperateInfo[STEP0].mValid = false;
    m_OperateInfo[STEP1].mValid = false;
    m_SlipOperateInfo.mValid = false;
    m_Animator.stop();
    //>@Operate0
    //>@Operate2
    if(pFlag)
    {
        m_OperateInfo[STEP1].mValid = true;
        m_OperateInfo[STEP1].mOperate = OPERATE_KEYPRESS;
    }
    else
    {
        m_OperateInfo[STEP0].mValid = true;
        m_OperateInfo[STEP0].mOperate = OPERATE_KEYPRESS;
    }
    //>@exec
    Operate0();

    return true;
}

bool GraphicsSetBar::updateEffect(MOVE_DIRECTION pDirection)
{
    bool flag = false;
    int tmpCurIndex = GetCurItemIndex();
    if(pDirection == MOVE_LEFT && tmpCurIndex<m_ItemList.count()-1)
    {
        flag = updateEffect(tmpCurIndex += 1);
    }
    else if(pDirection == MOVE_RIGHT && tmpCurIndex>0)
    {
        flag = updateEffect(tmpCurIndex -= 1);
    }
    return flag;
}

//>@��ת����
void GraphicsSetBar::Operate0()
{
    if(m_EffectValid == false)
    {
        IDE_TRACE();
        return;
    }
    //>@ִ��STEP0�е����ݣ����ִ�в��ɹ�������ִ��STEP1�е�����
    if(m_OperateInfo[STEP0].mValid)
    {
        //>@��ȡ��ǰITEM
        m_CurItemInfo = GetCurSetItem();
        if(!(m_CurItemInfo && m_CurItemInfo->mItemProxy))
        {
            IDE_TRACE();
            return;
        }
        m_AreaAnimate = m_EffectGroup.value(m_OperateInfo[STEP0].mOperate);
        if(m_AreaAnimate)
        {
            m_AreaAnimate->mOrientation = Negative;
            //>@����ITEM��Ч��ص�ֵ, ��������һ�η�ת�Ƕ�Ϊ18������ת10��
            m_CurValue = 0;
            m_Diff = 1.0 / (qreal)(m_AreaAnimate->mFrameEnd - m_AreaAnimate->mFrameStart);
            disconnect(&m_Animator, SIGNAL(frameChanged(int)), 0, 0);
            disconnect(&m_Animator, SIGNAL(finished()), 0, 0);
            connect(&m_Animator, SIGNAL(frameChanged(int)), this, SLOT(OperateItem(int)));
            connect(&m_Animator, SIGNAL(finished()), this, SLOT(Operate1()));
            StartTimeline();
            return;
        }
        else
        {
            //>@ֱ������Ϊ��һ״ֵ̬
            if(m_CurItemInfo)
            {
                SetBarItem* tmpItemWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
                if(tmpItemWidget)
                    tmpItemWidget->HideUI();
            }
        }
    }
    Operate1();
}

void GraphicsSetBar::Operate1()
{
    if(m_EffectValid == false)
    {
        IDE_TRACE();
        return;
    }
    //>@ȷ����תΪ��UI״̬
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpItemWidget)
            tmpItemWidget->HideUI();
    }

    //>@ִ��STEP1�е����ݣ����ִ�в��ɹ�������ִ��STEP2�е�����
    if(m_SlipOperateInfo.mValid)
    {
        //>@��ȡ��ǰITEM
        m_CurItemInfo = GetCurSetItem();
        if(!(m_CurItemInfo && m_CurItemInfo->mItemProxy))
        {
            IDE_TRACE();
            return;
        }
        m_AreaAnimate = m_EffectGroup.value(m_SlipOperateInfo.mOperate);
        if(m_AreaAnimate)
        {
            m_CurValue = 0;
            m_Diff = 1.0 / (qreal)(m_AreaAnimate->mFrameEnd - m_AreaAnimate->mFrameStart);
            disconnect(&m_Animator, SIGNAL(frameChanged(int)), 0, 0);
            disconnect(&m_Animator, SIGNAL(finished()), 0, 0);
            connect(&m_Animator, SIGNAL(frameChanged(int)), SLOT(OperateItem(int)));
            connect(&m_Animator, SIGNAL(finished()), this, SLOT(Operate2()));
            StartTimeline();
            return;
        }
        else
        {
            //>@ֱ������Ϊ��һ״ֵ̬
            int count = m_ItemList.count();
            for(int i=0; i< count; i++)
            {
                SETITEM_INFO* tmpSetItemInfo = m_ItemList.at(i);
                if(tmpSetItemInfo == 0)
                    continue;
                if(tmpSetItemInfo->mNextParaIndex == 0)
                {
                    tmpSetItemInfo->mItemProxy->setGeometry(QRect(20,20,m_ValidRect.width()-40,m_ValidRect.height()-40));
                    tmpSetItemInfo->mItemProxy->setOpacity(1);
                    tmpSetItemInfo->mItemProxy->setZValue(zValue() + 100);
                }
                else
                {
                    tmpSetItemInfo->mItemProxy->setOpacity(0);
                    tmpSetItemInfo->mItemProxy->setZValue(zValue() + 50);
                }
            }
        }
    }
    Operate2();
}

void GraphicsSetBar::Operate2()
{
    if(m_EffectValid == false)
    {
        IDE_TRACE();
        return;
    }
    int count = m_ItemList.count();
    for(int i=0;i<count;i++)
    {
        SETITEM_INFO* tmpSetItem = m_ItemList.at(i);
        if(tmpSetItem == 0)
            continue;
        tmpSetItem->mCurParaIndex = tmpSetItem->mNextParaIndex;
    }
    if(m_OperateInfo[STEP1].mValid)
    {
        //>@��ȡ��ǰITEM
        m_CurItemInfo = GetCurSetItem();
        if(!(m_CurItemInfo && m_CurItemInfo->mItemProxy))
        {
            IDE_TRACE();
            return;
        }
        m_AreaAnimate = m_EffectGroup.value(m_OperateInfo[STEP1].mOperate);
        if(m_AreaAnimate)
        {
            m_AreaAnimate->mOrientation = Positive;
            //>@����ITEM��Ч��ص�ֵ, ��������һ�η�ת�Ƕ�Ϊ18������ת10��
            m_CurValue = 0;
            m_Diff = 1.0 / (qreal)(m_AreaAnimate->mFrameEnd - m_AreaAnimate->mFrameStart);
            disconnect(&m_Animator, SIGNAL(frameChanged(int)), 0, 0);
            disconnect(&m_Animator, SIGNAL(finished()), 0, 0);
            connect(&m_Animator, SIGNAL(frameChanged(int)), this, SLOT(OperateItem(int)));
            StartTimeline();
            return;
        }
        else
        {
            //>@ֱ������Ϊ��һ״ֵ̬
            if(m_CurItemInfo)
            {
                SetBarItem* tmpItemWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
                if(tmpItemWidget)
                    tmpItemWidget->ShowUI();
            }
        }
    }
}

void GraphicsSetBar::Initialize()
{
    show();
}

void GraphicsSetBar::Release()
{
    //>@
//    if(GlobalPara.m_MdpManager && GlobalPara.m_MdpManager->m_IsChanged)
//        GlobalPara.m_MdpManager->SaveMDP();
    hide();
}

bool GraphicsSetBar::GotoPage()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpItemWidget && tmpItemWidget->m_ItemStage == SetBarItem::END)     //>@����������ô����У���ԭ����������
        {
            QWidget* tmpItem = VAR_CAST<QWidget*>(tmpItemWidget->children().first());
            if(tmpItem)
            {
                tmpItem->setFocus();
                return true;
            }
        }
    }
    return false;
}

bool GraphicsSetBar::LeavePage()
{
    return true;
}

QWidget* GraphicsSetBar::GetFocusSubctrl()
{
    QWidget* subctrlWidget = 0;
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = m_CurItemInfo->GetWidget();
        if(tmpItemWidget && tmpItemWidget->m_ItemStage == SetBarItem::END)
        {
            subctrlWidget = tmpItemWidget->focusWidget();
        }
    }
    return subctrlWidget;
}

bool GraphicsSetBar::GotoModify()
{
    QWidget *tmpWidget = GetFocusSubctrl();
    if(tmpWidget == 0)
        return false;
    QMouseEvent *tmpEvnPress = new QMouseEvent(QEvent::MouseButtonDblClick, QPoint(10,10), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(tmpWidget,tmpEvnPress);
    return true;
}

bool GraphicsSetBar::LeaveModify()
{
    return true;
}

bool GraphicsSetBar::MoveLeft()
{
    return updateEffect(MOVE_LEFT);
}

bool GraphicsSetBar::MoveRight()
{
    return updateEffect(MOVE_RIGHT);
}

bool GraphicsSetBar::MoveFocusIn()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@����������ô����У���ԭ����������
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
            {
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Enter,Qt::NoModifier));
                return true;
            }
        }
    }
    return false;
}

bool GraphicsSetBar::MoveFocusOut()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@����������ô����У���ԭ����������
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
            {
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Escape,Qt::NoModifier));
                return true;
            }
        }
    }
    return false;
}

bool GraphicsSetBar::MoveFocusUp()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@����������ô����У���ԭ����������
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
            {
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Tab,Qt::ShiftModifier));
                return true;
            }
        }
    }
    return false;
}

bool GraphicsSetBar::MoveFocusDown()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = VAR_CAST<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@����������ô����У���ԭ����������
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
            {
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier));
                return true;
            }
        }
    }
    return false;
}

bool GraphicsSetBar::MoveFocusLoop()
{
    return true;
}

bool GraphicsSetBar::ModifyValueUp()
{
    QWidget *tmpWidget = GetFocusSubctrl();
    if(tmpWidget == 0)
        return false;
    QKeyEvent* tmpEvnUp = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QApplication::sendEvent(tmpWidget,tmpEvnUp);
    return true;
}

bool GraphicsSetBar::ModifyValueDown()
{
    QWidget *tmpWidget = GetFocusSubctrl();
    if(tmpWidget == 0)
        return false;
    QKeyEvent* tmpEvnUp = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    QApplication::sendEvent(tmpWidget,tmpEvnUp);
    return true;
}

SetBarItem::SetBarItem(QPixmap pPixmap, QRect rect, QWidget *parent) :
    QScrollArea(parent)
{
    setGeometry(rect);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidgetResizable(false);

    //>@��ʼ������
    m_ParaUI = 0;
    m_ItemStage = BEGIN;
    m_BgPixmap = pPixmap;
    m_ParaUI = new QWidget;
    setWidget(m_ParaUI);
    HideUI();
}

SetBarItem::~SetBarItem()
{
    if(m_ParaUI)
    {
        m_ParaUI->deleteLater();
        m_ParaUI = 0;
    }
}

void SetBarItem::ShowUI()
{
    m_ItemStage = END;
    if(m_ParaUI && !(m_ParaUI->isVisible()))
    {
        m_ParaUI->resize(width(), m_ParaUI->height());
        m_ParaUI->show();
        QPalette tmpPalette;
        tmpPalette.setBrush(QPalette::Window, QBrush(QColor(80, 80, 89, 255)));
        setPalette(tmpPalette);
    }
}

void SetBarItem::HideUI()
{
    m_ItemStage = BEGIN;
    if(m_ParaUI && m_ParaUI->isVisible())
    {
        m_ParaUI->hide();
        resizeEvent((QResizeEvent *)0);
    }
}

void SetBarItem::resizeEvent(QResizeEvent *e)
{
    if(!m_BgPixmap.isNull())
    {
        QPalette tmpPalette;
        tmpPalette.setBrush(QPalette::Window, QBrush(m_BgPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        setPalette(tmpPalette);
    }
}

DesignSetBar::DesignSetBar(QGraphicsItem *parent):
    GraphicsSetBar(parent)
{
    QAction *tmpDefault = m_ActionGroup->addAction(tr("Left"));
    m_ActionGroup->addAction(tr("Right"));
    tmpDefault->setChecked(true);
}

QList<QAction*> DesignSetBar::GetActionList()
{
    QList<QAction*> tmpList;
    if(m_ActionGroup)
    {
        tmpList = m_ActionGroup->actions();
        //>@���ݵ�ǰ���е���Դʹ����Ӧ����Action
        for(int i=0;i<tmpList.count();i++)
        {
            QAction *tmpAction = tmpList.at(i);
            if(tmpAction == 0)
                continue;
            QString tmpString = tmpAction->text();
            int tmpIndex = GetCurItemIndex();
            if(tmpString.compare("Left")==0 && tmpIndex==m_ItemCount-1)
            {
                tmpAction->setDisabled(true);
            }
            else if(tmpString.compare("Right")==0 && tmpIndex==0)
            {
                tmpAction->setDisabled(true);
            }
            else
                tmpAction->setEnabled(true);
        }
    }
    return tmpList;
}

void DesignSetBar::ExecAction(QAction *pAction)
{
    QString tmpString = pAction->text();
    if(tmpString.compare("Left")==0)
    {
        updateEffect(MOVE_LEFT);
    }
    else if(tmpString.compare("Right")==0)
    {
        updateEffect(MOVE_RIGHT);
    }
}