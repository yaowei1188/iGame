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

CCMultiColumnTableView::CCMultiColumnTableView():m_colCount(1) {

}

void CCMultiColumnTableView::setColCount(unsigned int cols){
    m_colCount = cols;
    
    if (this->getDirection() == kCCScrollViewDirectionBoth) {
        this->_updateContentSize();
    }
}

int CCMultiColumnTableView::__indexFromOffset(CCPoint offset){
   
    int  index = 0;
    CCSize  cellSize;
    int  col, row;
    float    spaceWidth;
    
    cellSize = m_pDataSource->cellSizeForTable(this);
    
    switch (this->getDirection()) {
        case kCCScrollViewDirectionHorizontal:
            spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
            col        = (offset.y - (spaceWidth - cellSize.height)*0.5)/spaceWidth;
            row        = offset.x / cellSize.width;    
            break;
        default:
            spaceWidth = this->getContainer()->getContentSize().width / m_colCount;
            col        = (offset.x - (spaceWidth - cellSize.width)*0.5)/spaceWidth;
            row        = offset.y / cellSize.height;
            break;
    }
    index = col + row * m_colCount;
    return index;
    
}

CCPoint CCMultiColumnTableView::__offsetFromIndex(unsigned int index){
  
    CCPoint offset;
    CCSize  cellSize;
    float    spaceWidth;
    int  col, row;
    
    cellSize = m_pDataSource->cellSizeForTable(this);
    switch (this->getDirection()) {
        case kCCScrollViewDirectionHorizontal:
            row        = index / m_colCount;
            col        = index % m_colCount;
            spaceWidth = this->getContainer()->getContentSize().height / m_colCount;
            offset     = ccp(row * cellSize.height,
                             col * spaceWidth + (spaceWidth - cellSize.width) * 0.5);
            break;
        default:
            row        = index / m_colCount;
            col        = index % m_colCount;
            spaceWidth = this->getContainer()->getContentSize().width / m_colCount;
            offset     = ccp(col * spaceWidth + (spaceWidth - cellSize.width) * 0.5,
                             row * cellSize.height);
            break;
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
            m_colCount = getViewSize().height / cellSize.height;
            rows     = ceilf(cellCount/((float)m_colCount));
            size     = CCSizeMake(MAX(rows * cellSize.width, viewSize.width), m_colCount * cellSize.height);
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

NS_CC_EXT_END
