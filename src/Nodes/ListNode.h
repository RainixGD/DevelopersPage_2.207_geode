#pragma once
#include "../includes.h"

class Cell : public CCClippingNode {
    CCLayerColor* backgroundLayer;
    virtual bool init(float width, float height, const ccColor4B& color) {
        if (!CCClippingNode::init()) return false;
        setContentSize({ width, height });

        auto mask = CCLayerColor::create({ 255, 255, 255, 255 }, width, height);
        mask->setAnchorPoint({ 0, 0 });
        this->setStencil(mask);

        backgroundLayer = CCLayerColor::create(color, width, height);
        backgroundLayer->setAnchorPoint({ 0, 0 });
        this->addChild(backgroundLayer);

        return true;
    }
public:
    void setColor(const ccColor3B& color) {
        backgroundLayer->setColor(color);
    }

    static Cell* create(float width, float height, const ccColor4B& color = { 255, 0, 0, 255 }) {
        Cell* ret = new Cell();
        if (ret && ret->init(width, height, color)) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

template <class VectorType>
class ListNode : public CCLayerColor {
protected:
    CCScrollView* scrollLayer;
    std::vector<VectorType> data;

    virtual bool init(float width, float height, float cellHeight, std::vector<VectorType> data, const ccColor4B& backgroundColor) {
        if (!CCLayerColor::initWithColor(backgroundColor, width, height)) return false;

        scrollLayer = CCScrollView::create(CCSize(width, height));
        scrollLayer->setDirection(kCCScrollViewDirectionVertical);
        scrollLayer->setPosition({ 0, 0 });
        scrollLayer->setBounceable(true);
        this->addChild(scrollLayer);

        auto container = CCLayer::create();
        scrollLayer->setContainer(container);

        float contentHeight = data.size() * cellHeight;
        container->setContentSize({ width, contentHeight });
        scrollLayer->setContentOffset({ 0, height - contentHeight });

        for (int i = 0; i < data.size(); i++) {
            auto cell = Cell::create(width, cellHeight);
            cell->setPosition({ 0, (data.size() - 1 - i) * cellHeight });
            container->addChild(cell);
            setupCell(cell, data[i], i);
        }

        return true;
    }

    virtual void setupCell(Cell* cell, VectorType cellData, int index) = 0;
};