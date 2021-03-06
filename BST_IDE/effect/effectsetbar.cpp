#include "effectsetbar.h"

EffectSetBar::EffectSetBar(QGraphicsItem *parent, QRectF pRect):
    EffectBaseItem(parent, pRect)
{
    m_Diff = 0;
    m_CurValue = 0;
    m_CurItemInfo = 0;
}

bool EffectSetBar::InitEffectRc(STATE_INFO* pEffect)
{
    QString tmpString = pEffect->StateName;
    if(tmpString.isEmpty())
    {
        return false;
    }
    if(tmpString.compare(QString("Common"), Qt::CaseInsensitive) == 0)
    {
        RESOURCE_INFO tmpRc;
        int index;
        int count = pEffect->Effect.RcFiles.count();
        for(int i=0;i<count;i++)
        {
            tmpRc = pEffect->Effect.RcFiles.at(i);
            index = GetKey(tmpRc.RcName);
            IDE_TRACE_INT(index);
            if(LoadPixmap(index, tmpRc.RcFile) == false)
            {
                IDE_TRACE_STR(tmpRc.RcFile);
            }
        }
    }
    else if(tmpString.compare(QString("Slip"), Qt::CaseInsensitive) == 0)
    {
        AREA_ANIMATE *tmpAreaAnimate = new  AREA_ANIMATE;
        if(pEffect->Effect.EffectType.compare(QString("Twirl"), Qt::CaseInsensitive) == 0)
        {
            tmpAreaAnimate->mEffectType = EffectTypeTwirl;
        }
        else if(pEffect->Effect.EffectType.compare(QString("Glide"), Qt::CaseInsensitive) == 0)
        {
            tmpAreaAnimate->mEffectType = EffectTypeGlide;
        }
        else
        {
            delete tmpAreaAnimate;
            return false;
        }
        analysisEffectPara(tmpAreaAnimate, pEffect->Effect.EffectPara);
        m_EffectGroup.insert(OPERATE_SLIP, tmpAreaAnimate);
    }
    else if(tmpString.compare(QString("Press"), Qt::CaseInsensitive) == 0)
    {
        AREA_ANIMATE *tmpAreaAnimate = new  AREA_ANIMATE;
        if(pEffect->Effect.EffectType.compare(QString("Zoom"), Qt::CaseInsensitive) == 0)
        {
            tmpAreaAnimate->mEffectType = EffectTypeZoom;
        }
        else if(pEffect->Effect.EffectType.compare(QString("Rotate"), Qt::CaseInsensitive) == 0)
        {
            tmpAreaAnimate->mEffectType = EffectTypeRotate;
        }
        else
        {
            delete tmpAreaAnimate;
            return false;
        }
        analysisEffectPara(tmpAreaAnimate, pEffect->Effect.EffectPara);
        m_EffectGroup.insert(OPERATE_KEYPRESS, tmpAreaAnimate);
    }
    else
    {
        return false;
    }
    return true;
}

bool EffectSetBar::analysisEffectParaItem(AREA_ANIMATE* pAreaEffect, QString pLabel, QString pContent)
{
    return EffectBaseItem::analysisEffectParaItem(pAreaEffect, pLabel, pContent);
}

void EffectSetBar::PaintEffect(QPainter *p)
{
    QPixmap tmpPixmap = m_EffectImage.value(BGIMG);
    if(tmpPixmap.isNull() == false)
    {
        QRect rect = geometry().toRect();
        p->drawPixmap(QRect(0,0,rect.width(),rect.height()), tmpPixmap);
    }
}

bool EffectSetBar::Start()
{
    EffectBaseItem::Start();
    if(InitItems() == false)
    {
        IDE_TRACE();
        return false;
    }
    updateEffect(m_ItemCount/2);
    return true;
}

bool EffectSetBar::NeedReboot()
{
    return false;
}

void EffectSetBar::AddItem(int pIndex, ITEM_TYPE pType, QPixmap pPixmap)
{
    SETITEM_INFO *tmpItemInfo = new SETITEM_INFO;
    tmpItemInfo->mProxy = new QGraphicsProxyWidget(this);
    SetBarItem *tmpItemWidget = new SetBarItem(pType, pPixmap, m_ValidRect);
    tmpItemInfo->mProxy->setWidget(tmpItemWidget);
    tmpItemInfo->mProxy->setOpacity(0);
    tmpItemInfo->mCurParaIndex = pIndex;
    tmpItemInfo->mNextParaIndex = pIndex;
    m_ItemList.append(tmpItemInfo);
}

//>@获取可绘制组件的区域大小
bool EffectSetBar::GetValidRect(QRect &pRect)
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
            default: //>@如果使用不识别的特效
            {
                return false;
            }
        }
    }
    //>@如果使用不识别的特效，则占据整个大小
    pRect = rect.toRect();
    return true;
}

bool EffectSetBar::InitItems()
{
    m_ItemList.clear();
    //>@计算ITEMs的正方形有效区域
    if(GetValidRect(m_ValidRect) == false)
    {
        IDE_TRACE();
        return false;
    }
    //>@计算ITEM个数
    QList<int> tmpList = m_EffectImage.keys();
    m_ItemCount = tmpList.count();
    if(tmpList.contains(BGIMG))
        m_ItemCount -= 1;
    if(m_ItemCount < 1)
        return false;
    IDE_TRACE_INT(m_ItemCount);
    //>@初始化ITEM
    for(int i=0; i<m_ItemCount; i++)
    {
        int tmpKey = tmpList.at(i);
        QPixmap tmpPixmap = m_EffectImage.value(tmpKey);
        if(tmpPixmap.isNull())
            continue;
        AddItem(i, (ITEM_TYPE)tmpKey, tmpPixmap);
    }
    return true;
}

int EffectSetBar::GetCurItemIndex()
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

SETITEM_INFO* EffectSetBar::GetCurSetItem()
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

//>@表示将pIndex的ITEM放在最前面，也即放在位置0
bool EffectSetBar::UpdateItems(int pIndex)
{
    int count = m_ItemList.count();
    if(pIndex < 0 || pIndex >= count)
    {
        IDE_TRACE();
        return false;
    }
    //>@确定左移右移以及移动个数
    int tmpCurIndex = GetCurItemIndex();
    int tmpIndexDiff = tmpCurIndex - pIndex;
    m_ItemSlipCount = qAbs(tmpIndexDiff);
    IDE_TRACE_INT(m_ItemSlipCount);
    if(tmpIndexDiff == 0)
    {
        IDE_TRACE();
        return false;
    }
    //>@规整Items
    for(int i=0;i<count;i++)
    {
        SETITEM_INFO* tmpSetItem = m_ItemList.at(i);
        if(tmpSetItem == 0)
            continue;
        int tmpValue = tmpSetItem->mCurParaIndex + tmpIndexDiff;
        tmpSetItem->mNextParaIndex = tmpValue;
    }
    //>@修改特效时间
    AREA_ANIMATE* tmpAreaAnimate = m_EffectGroup.value(OPERATE_SLIP);
    if(tmpAreaAnimate == 0)
    {
        IDE_TRACE();
        return true;  //>@如果SLIP不使用特效，则直接返回真
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


void EffectSetBar::OperateItem(int pFrameNum)
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
                static qreal tmpTwirlA = m_ValidRect.width() / 3.0;   //>@取椭圆的长半径a为1/3的长度，b为1/4的长度
                static qreal tmpTwirlB = m_ValidRect.height() / 4.0;
                static qreal tmpMaxHeight = m_ValidRect.height()*7.0/10.0;//>@设置最前方的旋转Item的宽为高度的2/3，高度为有效区域高度的7/10
                static QSizeF tmpMaxSize = QSize(tmpMaxHeight*2.0/3.0,  tmpMaxHeight);
                //>@将中心点上移1/8，否则设置框会偏下方
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
                    qreal tmpBeginAngle = RegularAngle(3.0 * PI / 2.0 + tmpSetItemInfo->mCurParaIndex * tmpSingleAngelDiff);  //>@从270度开始
                    qreal tmpAngle;
                    if(m_AreaAnimate->mOrientation == Positive)
                        tmpAngle = RegularAngle(tmpBeginAngle - m_CurValue);
                    else if(m_AreaAnimate->mOrientation == Negative)
                        tmpAngle = RegularAngle(tmpBeginAngle + m_CurValue);
                    qreal tmpHalfAngleRatio = 1.0 - CalDiffBeginAngle(tmpAngle)/PI;  //>@用于计算其它渐变的参数
                    QPointF tmpItemCentrePoint = tmpCentrePoint + QPointF(tmpTwirlA*qCos(tmpAngle), -tmpTwirlB*qSin(tmpAngle));
                    QSizeF tmpItemSize = tmpMaxSize * tmpHalfAngleRatio;
                    QRectF tmpRect = QRectF(tmpItemCentrePoint, tmpItemSize);
                    tmpRect.moveCenter(tmpItemCentrePoint);
                    //>@此处会出现虽然tmpRect很小，但mProxy代理的窗口有最小大小限制从而导致最终mProxy的大小并不为tmpRect的问题
                    tmpSetItemInfo->mProxy->setGeometry(tmpRect);
                    //tmpSetItemInfo->mProxy->setTransform(QTransform().translate(width()/2, height() / 2).rotate(0, Qt::YAxis).translate(-width()/2, -height()/2));
                    //>@最小透明度为0.5，最大为1
                    tmpSetItemInfo->mProxy->setOpacity(tmpHalfAngleRatio/2.0+0.5);
                    tmpSetItemInfo->mProxy->setZValue(zValue() + 100 * tmpHalfAngleRatio);  //>@此处限制最大有100个ITEM
                }
                break;
            }
            case EffectTypeGlide:  //>@中心点最大，依次往两边减小，使用公式Y=1-|X/m_ItemCount|
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
                    tmpSetItemInfo->mProxy->setGeometry(tmpRect);
                    tmpSetItemInfo->mProxy->setOpacity(tmpCurRatio);
                    tmpSetItemInfo->mProxy->setZValue(zValue() + 100 * tmpCurRatio);  //>@此处限制最大有100个ITEM
                }
                break;
            }
            case EffectTypeRotate:
            {
                if(m_CurItemInfo)
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
                SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
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
                QRectF r = m_CurItemInfo->mProxy->boundingRect();
                if(m_AreaAnimate->mDirection == Horizontal)
                    m_CurItemInfo->mProxy->setTransform(QTransform()
                                                    .translate(r.width() / 2, r.height() / 2)
                                                    .rotate(m_CurValue - 180 * tmpItemWidget->m_ItemStage, Qt::YAxis)
                                                    .translate(-r.width() / 2, -r.height() / 2));
                else
                    m_CurItemInfo->mProxy->setTransform(QTransform()
                                                    .translate(r.width() / 2, r.height() / 2)
                                                    .rotate(m_CurValue - 180 * tmpItemWidget->m_ItemStage, Qt::XAxis)
                                                    .translate(-r.width() / 2, -r.height() / 2));
                break;
            }
            case EffectTypeZoom:
            {
                if(m_CurItemInfo)
                    return;
                m_CurValue = pFrameNum * m_Diff * 100;
                if(m_CurValue < 0 || m_CurValue > 100)
                {
                    IDE_TRACE();
                    return;
                }
                SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
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
                m_CurItemInfo->mProxy->setTransform(QTransform().scale(ratio, ratio));
                break;
            }
            default:
                break;
        }
    }
}

void EffectSetBar::updateEffect(AREA_OPERATE pOperate, QVariant pPara)
{
    switch(pOperate)
    {
        case OPERATE_KEYPRESS:
        {
            //>@分解坐标，如果点击左半区域，则向左滚动
            QPoint tmpPoint = pPara.toPoint();
            QRectF tmpRect = this->geometry();
            if(tmpPoint.x() < tmpRect.width()/2)
            {
                updateEffect(MOVE_LEFT);
                IDE_TRACE();
            }
            else if(tmpPoint.x() > tmpRect.width()/2)
            {
                updateEffect(MOVE_RIGHT);
                IDE_TRACE();
            }
            break;
        }
        default:
            break;
    }
}

void EffectSetBar::updateEffect(int pIndex)
{
    //>@等待上次特效完成
    if(m_Animator.state() == QTimeLine::Running)
        return;
    if(UpdateItems(pIndex) == false)
    {
        IDE_TRACE();
        return;
    }
    m_OperateInfo[STEP0].mValid = false;
    m_OperateInfo[STEP1].mValid = false;
    m_Animator.stop();
    //>@Operate0
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpItemWidget && tmpItemWidget->m_ItemStage == SetBarItem::END)     //>@如果还在设置窗口中，则还原到背景窗口
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
}

void EffectSetBar::updateEffect(bool pFlag)
{
    //>@等待上次特效完成
    if(m_Animator.state() == QTimeLine::Running)
        return;
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
}

void EffectSetBar::updateEffect(MOVE_DIRECTION pDirection)
{
    int tmpCurIndex = GetCurItemIndex();
    if(pDirection == MOVE_LEFT && tmpCurIndex<m_ItemList.count()-1)
    {
        updateEffect(tmpCurIndex += 1);
    }
    else if(pDirection == MOVE_RIGHT && tmpCurIndex>0)
    {
        updateEffect(tmpCurIndex -= 1);
    }
}

//>@翻转操作
void EffectSetBar::Operate0()
{
    if(m_EffectValid == false)
    {
        IDE_TRACE();
        return;
    }
    //>@执行STEP0中的内容，如果执行不成功，尝试执行STEP1中的内容
    if(m_OperateInfo[STEP0].mValid)
    {
        //>@获取当前ITEM
        m_CurItemInfo = GetCurSetItem();
        if(!(m_CurItemInfo && m_CurItemInfo->mProxy))
        {
            IDE_TRACE();
            return;
        }
        m_AreaAnimate = m_EffectGroup.value(m_OperateInfo[STEP0].mOperate);
        if(m_AreaAnimate)
        {
            m_AreaAnimate->mOrientation = Negative;
            //>@计算ITEM特效相关的值, 建议设置一次翻转角度为18，共翻转10次
            m_CurValue = 0;
            m_Diff = 1.0 / (qreal)(m_AreaAnimate->mFrameEnd - m_AreaAnimate->mFrameStart);
            disconnect(&m_Animator, SIGNAL(frameChanged(int)), 0, 0);
            disconnect(&m_Animator, SIGNAL(finished()), 0, 0);
            connect(&m_Animator, SIGNAL(frameChanged(int)), this, SLOT(OperateItem(int)));
            connect(&m_Animator, SIGNAL(finished()), this, SLOT(Operate1()));
            StartTimeline(m_AreaAnimate->mFrameStart,
                          m_AreaAnimate->mFrameEnd,
                          m_AreaAnimate->mAnimateTime,
                          m_AreaAnimate->mAnimateType);
            return;
        }
        else
        {
            //>@直接设置为下一状态值
            if(m_CurItemInfo)
            {
                SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
                if(tmpItemWidget)
                    tmpItemWidget->HideUI();
            }
        }
    }
    Operate1();
}

void EffectSetBar::Operate1()
{
    if(m_EffectValid == false)
    {
        IDE_TRACE();
        return;
    }
    //>@确保翻转为无UI状态
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpItemWidget)
            tmpItemWidget->HideUI();
    }

    //>@执行STEP1中的内容，如果执行不成功，尝试执行STEP2中的内容
    if(m_SlipOperateInfo.mValid)
    {
        //>@获取当前ITEM
        m_CurItemInfo = GetCurSetItem();
        if(!(m_CurItemInfo && m_CurItemInfo->mProxy))
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
            StartTimeline(m_AreaAnimate->mFrameStart,
                          m_AreaAnimate->mFrameEnd,
                          m_AreaAnimate->mAnimateTime,
                          m_AreaAnimate->mAnimateType);
            return;
        }
        else
        {
            //>@直接设置为下一状态值
            int count = m_ItemList.count();
            for(int i=0; i< count; i++)
            {
                SETITEM_INFO* tmpSetItemInfo = m_ItemList.at(i);
                if(tmpSetItemInfo == 0)
                    continue;
                if(tmpSetItemInfo->mNextParaIndex == 0)
                {
                    tmpSetItemInfo->mProxy->setGeometry(QRect(20,20,m_ValidRect.width()-40,m_ValidRect.height()-40));
                    tmpSetItemInfo->mProxy->setOpacity(1);
                    tmpSetItemInfo->mProxy->setZValue(zValue() + 100);
                }
                else
                {
                    tmpSetItemInfo->mProxy->setOpacity(0);
                    tmpSetItemInfo->mProxy->setZValue(zValue() + 50);
                }
            }
        }
    }
    Operate2();
}

void EffectSetBar::Operate2()
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
        //>@获取当前ITEM
        m_CurItemInfo = GetCurSetItem();
        if(!(m_CurItemInfo && m_CurItemInfo->mProxy))
        {
            IDE_TRACE();
            return;
        }
        m_AreaAnimate = m_EffectGroup.value(m_OperateInfo[STEP1].mOperate);
        if(m_AreaAnimate)
        {
            m_AreaAnimate->mOrientation = Positive;
            //>@计算ITEM特效相关的值, 建议设置一次翻转角度为18，共翻转10次
            m_CurValue = 0;
            m_Diff = 1.0 / (qreal)(m_AreaAnimate->mFrameEnd - m_AreaAnimate->mFrameStart);
            disconnect(&m_Animator, SIGNAL(frameChanged(int)), 0, 0);
            disconnect(&m_Animator, SIGNAL(finished()), 0, 0);
            connect(&m_Animator, SIGNAL(frameChanged(int)), this, SLOT(OperateItem(int)));
            StartTimeline(m_AreaAnimate->mFrameStart,
                          m_AreaAnimate->mFrameEnd,
                          m_AreaAnimate->mAnimateTime,
                          m_AreaAnimate->mAnimateType);
            return;
        }
        else
        {
            //>@直接设置为下一状态值
            if(m_CurItemInfo)
            {
                SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
                if(tmpItemWidget)
                    tmpItemWidget->ShowUI();
            }
        }
    }
}

void EffectSetBar::Initialize()
{
    show();
}

void EffectSetBar::Release()
{
    hide();
}

void EffectSetBar::GotoPage()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpItemWidget && tmpItemWidget->m_ItemStage == SetBarItem::END)     //>@如果还在设置窗口中，则还原到背景窗口
        {
            QWidget* tmpItem = qobject_cast<QWidget*>(tmpItemWidget->children().first());
            if(tmpItem)
                tmpItem->setFocus();
        }
    }
}

void EffectSetBar::LeavePage()
{

}

QWidget* EffectSetBar::GetFocusSubctrl()
{
    QWidget* subctrlWidget = 0;
    if(m_CurItemInfo)
    {
        SetBarItem* tmpItemWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpItemWidget && tmpItemWidget->m_ItemStage == SetBarItem::END)     //>@如果还在设置窗口中，则还原到背景窗口
        {
            subctrlWidget = tmpItemWidget->focusWidget();
        }
    }
    return subctrlWidget;
}

void EffectSetBar::GotoModify()
{
    QWidget *tmpWidget = GetFocusSubctrl();
    if(tmpWidget == 0)
        return;
    QMouseEvent *tmpEvnPress = new QMouseEvent(QEvent::MouseButtonDblClick, QPoint(10,10), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
    QApplication::sendEvent(tmpWidget,tmpEvnPress);
}

void EffectSetBar::LeaveModify()
{

}

void EffectSetBar::MoveLeft()
{
    updateEffect(MOVE_LEFT);
}

void EffectSetBar::MoveRight()
{
    updateEffect(MOVE_RIGHT);
}

void EffectSetBar::MoveFocusIn()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@如果还在设置窗口中，则还原到背景窗口
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Enter,Qt::NoModifier));
        }
    }
}

void EffectSetBar::MoveFocusOut()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@如果还在设置窗口中，则还原到背景窗口
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Escape,Qt::NoModifier));
        }
    }
}

void EffectSetBar::MoveFocusUp()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@如果还在设置窗口中，则还原到背景窗口
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Tab,Qt::ShiftModifier));
        }
    }
}

void EffectSetBar::MoveFocusDown()
{
    if(m_CurItemInfo)
    {
        SetBarItem* tmpSetWidget = qobject_cast<SetBarItem*>(m_CurItemInfo->GetWidget());
        if(tmpSetWidget && tmpSetWidget->m_ItemStage == SetBarItem::END)     //>@如果还在设置窗口中，则还原到背景窗口
        {
            QWidget *tmpWidget = tmpSetWidget->focusWidget();
            if(tmpWidget)
                QApplication::sendEvent(tmpWidget, new QKeyEvent(QEvent::KeyPress,Qt::Key_Tab,Qt::NoModifier));
        }
    }
}

void EffectSetBar::MoveFocusLoop()
{

}

void EffectSetBar::ModifyValueUp()
{
    IDE_TRACE();
    QWidget *tmpWidget = GetFocusSubctrl();
    if(tmpWidget == 0)
        return;
    QKeyEvent* tmpEvnUp = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    QApplication::sendEvent(tmpWidget,tmpEvnUp);
}

void EffectSetBar::ModifyValueDown()
{
    IDE_TRACE();
    QWidget *tmpWidget = GetFocusSubctrl();
    if(tmpWidget == 0)
        return;
    QKeyEvent* tmpEvnUp = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
    QApplication::sendEvent(tmpWidget,tmpEvnUp);
}

SetBarItem::SetBarItem(ITEM_TYPE pType, QPixmap pPixmap, QRect rect, QWidget *parent) :
    QScrollArea(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidgetResizable(false);
    //>@初始化窗口
    m_ParaUI = 0;
    m_ItemRc = 0;
    m_ItemStage = BEGIN;
    m_ParaUIHeight = 0;
    setGeometry(rect);
    //>@初始化资源
    m_ItemRc = new ITEM_RC(pType, pPixmap);
    if(m_ItemRc->isValid() == false)
    {
        IDE_TRACE();
        return;
    }
    m_BgPixmap = m_ItemRc->GetBackgroundPixmap(rect);
    InitUI(rect.size());
    HideUI();
}

bool SetBarItem::InitUI(QSize pSize)
{
    //>@初始化界面
    if(m_ParaUI == 0)
    {
        m_ParaUI = new QWidget;
        m_ParaUI->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        setWidget(m_ParaUI);
        QVBoxLayout *tmpLayout = new QVBoxLayout(m_ParaUI);
        tmpLayout->setSpacing(15);
        m_ItemRc->CreateUi(tmpLayout, m_ParaUIHeight);
    }
    if(m_ParaUIHeight)
        pSize.setHeight(m_ParaUIHeight);
    m_ParaUI->resize(pSize);
    return true;
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
    if(m_ParaUI)
    {
        InitUI(size());
        m_ParaUI->show();
        QPalette tmpPalette;
        tmpPalette.setBrush(QPalette::Window, QBrush(Qt::lightGray));
        setPalette(tmpPalette);
    }
}

void SetBarItem::HideUI()
{
    m_ItemStage = BEGIN;
    if(m_ParaUI)
    {
        m_ParaUI->hide();
        QPalette tmpPalette;
        if(m_BgPixmap.isNull() == false)
            tmpPalette.setBrush(QPalette::Window, QBrush(m_BgPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        setPalette(tmpPalette);
    }
}

void SetBarItem::resizeEvent(QResizeEvent *e)
{
    if(m_BgPixmap.isNull() == false)
    {
        QPalette tmpPalette;
        tmpPalette.setBrush(QPalette::Window, QBrush(m_BgPixmap.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
        setPalette(tmpPalette);
    }
}



