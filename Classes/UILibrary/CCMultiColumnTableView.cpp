/****************************************************************************
 Copyright (c) 2012 @hermanjakobi
 Copyright (c) 2010 Sangwoo Im
 
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#include "cocos2d.h"
#include "cocos-ext.h"
#include "CCMultiColumnTableView.h"
//#include "CCTableViewCell.h"
//#include "CCPointExtension.h"

using namespace cocos2d;

NS_CC_EXT_BEGIN

CCMultiColumnTableView* CCMultiColumnTableView::create(CCTableViewDataSource* dataSource,CCSize size){

 return CCMultiColumnTableView::create(dataSource, size, NULL);
  
}

CCMultiColumnTableView* CCMultiColumnTableView::create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container)
{
    CCMultiColumnTableView *table = new CCMultiColumnTableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateContentSize();
    
    return table;
}

CCMultiColumnTableView::CCMultiColumnTableView():m_colCount(1) 
{
	isPagingEnableX = true;
	m_intCountEachPage = 0;
}

void CCMultiColumnTableView::setColCount(unsigned int cols){
    m_colCount = cols;
    
    if (this->getDirection() == kCCScrollViewDirectionBoth) {
        this->_updateContentSize();
    }
}

int CCMultiColumnTableView::__indexFromOffset(CCPoint offset){
   
    int  index = 0;
	int page = 0;
    CCSize  cellSize;
    int  col, row;
    float    spaceWidth;
    
    cellSize = m_pDataSource->cellSizeForTable(this);
    
    switch (this->getDirection()) {
        //case kCCScrollViewDirectionHorizontal:
        //    spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
        //    col        = (offset.y - (spaceWidth - cellSize.height)*0.5)/spaceWidth;
        //    row        = offset.x / cellSize.width;    
        //    break;
	case kCCScrollViewDirectionHorizontal:
		{
			if (isPagingEnableX)
			{				
				page = (int)(offset.x / this->getViewSize().width);
				float fleft = fmod(offset.x,this->getViewSize().width);

				spaceWidth = this->getViewSize().width / m_colCount;
				col        = (fleft - (spaceWidth - cellSize.width)*0.5)/spaceWidth;
				row        = offset.y / cellSize.height;   
				break;
			}
			else 
			{
				spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
				col        = (offset.y - (spaceWidth - cellSize.height)*0.5)/spaceWidth;
				row        = offset.x / cellSize.width;    
				break;
			}
		}

        default:
            spaceWidth = this->getContainer()->getContentSize().width / m_colCount;
            col        = (offset.x - (spaceWidth - cellSize.width)*0.5)/spaceWidth;
            row        = offset.y / cellSize.height;
            break;
    }
    index = page * m_intCountEachPage + col + row * m_colCount;
    return index;
}

CCPoint CCMultiColumnTableView::__offsetFromIndex(unsigned int index){
  
    CCPoint offset;
    CCSize  cellSize;
    float    spaceWidth;
    int  col, row;
    
    cellSize = m_pDataSource->cellSizeForTable(this);
    switch (this->getDirection()) {
        //case kCCScrollViewDirectionHorizontal:
        //    row        = index / m_colCount;
        //    col        = index % m_colCount;
        //    spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
        //    offset     = ccp(row * cellSize.height,
        //                     col * spaceWidth + (spaceWidth - cellSize.width) * 0.5);
        //    break;
        case kCCScrollViewDirectionHorizontal:
			{
				if (isPagingEnableX)
				{
					int cPages = index / m_intCountEachPage;
					int cLeft = index % m_intCountEachPage;

					row        = cLeft / m_colCount;
					col        = cLeft % m_colCount;

					spaceWidth = this->getViewSize().width / m_colCount;
					offset     = ccp(cPages * this->getViewSize().width + col * spaceWidth + (spaceWidth - cellSize.width) * 0.5,
						row * cellSize.height);
				}
				else
				{
					row        = index / m_colCount;
					col        = index % m_colCount;
					spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
					offset     = ccp(row * cellSize.height,
						col * spaceWidth + (spaceWidth - cellSize.width) * 0.5);
				}
				break;
			}
        default:
			{
				row        = index / m_colCount;
				col        = index % m_colCount;
				spaceWidth = this->getContainer()->getContentSize().width / m_colCount;
				offset     = ccp(col * spaceWidth + (spaceWidth - cellSize.width) * 0.5,
								 row * cellSize.height);
				break;
			}
    }
    
    return offset;
    
}

void CCMultiColumnTableView::_updateContentSize(){
   
    CCSize     size, cellSize, viewSize;
    unsigned int cellCount, rows;
    
    cellSize  = m_pDataSource->cellSizeForTable(this);
    cellCount = m_pDataSource->numberOfCellsInTableView(this);
    viewSize  = CCSizeMake(getViewSize().width/getContainer()->getScaleX(), getViewSize().height/getContainer()->getScaleY());
    
    switch (this->getDirection())
    {
        case kCCScrollViewDirectionHorizontal:
			if (isPagingEnableX)
			{
				int _colCount1 = getViewSize().height / cellSize.height;
				int _colRow = getViewSize().height / cellSize.height;
				m_intCountEachPage = _colCount1 * _colRow;

                m_intPageCount = cellCount/m_intCountEachPage ;
                if (cellCount % m_intCountEachPage) {
                    m_intPageCount ++;
                }

                m_colCount = getViewSize().height / cellSize.height;
                rows     = ceilf(cellCount/((float)m_colCount));
//                size     = CCSizeMake(MAX(rows * cellSize.width, viewSize.width), m_colCount * cellSize.height);
                size     = CCSizeMake(MAX(m_intPageCount * viewSize.width, viewSize.width), m_colCount * cellSize.height);
			} else {
                m_colCount = getViewSize().height / cellSize.height;
                rows     = ceilf(cellCount/((float)m_colCount));
                size     = CCSizeMake(MAX(rows * cellSize.width, viewSize.width), m_colCount * cellSize.height);
            }

			break;
			

        default:
            if (getDirection() == kCCScrollViewDirectionVertical) {
                m_colCount = viewSize.width / cellSize.width;   
            }
            rows     = ceilf(cellCount/((float)m_colCount));
            size     = CCSizeMake(MAX(cellSize.width * m_colCount, viewSize.width), rows * cellSize.height);
            break;
    }
    this->setContentSize(size);
    
    //FIXME? unsure if that code makes sense
	if (m_eOldDirection != m_eDirection)
	{
		if (m_eDirection == kCCScrollViewDirectionHorizontal)
		{
			this->setContentOffset(ccp(0,0));
		}
		else
		{
			this->setContentOffset(ccp(0,this->minContainerOffset().y));
		}
		m_eOldDirection = m_eDirection;
	}
}

CCPoint CCMultiColumnTableView::getPositionByPaged(CCPoint point)
{
	if (isPagingEnableX)
	{
//		const CCSize cellSize = m_pDataSource->cellSizeForTable(this);
		unsigned int uCountOfItems = m_pDataSource->numberOfCellsInTableView(this);
		if (0 == uCountOfItems)
		{
			return point;
		}

		int eachnumber = point.x / getViewSize().width;
		float part = fmod(point.x,getViewSize().width);

        CCLOG("moveDistance.x=%0.2f",m_tScrollDistance1.x);

        if (m_tScrollDistance1.x > 5.0) {
//            eachnumber++;
        } else if(m_tScrollDistance1.x < -5.0) {
            if(abs(eachnumber)<m_intPageCount-1) {
                eachnumber--;
            }
        }
//		if (fabs(part)  > getViewSize().width * 0.1)
//		{
//			eachnumber--;
//		}

		return CCPointMake(eachnumber * getViewSize().width, point.y);
	}
	return point;
}

NS_CC_EXT_END
