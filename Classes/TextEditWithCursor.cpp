#include "TextEditWithCursor.h"
#include"cocos2d.h"

USING_NS_CC;



bool TextEditWithCursor::init()
{
	if (!LayerColor::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	tec_TextField= TextField::create("input words here", "Arial", 20);
	tec_TextField->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	tec_TextField->addEventListener(CC_CALLBACK_2(TextEditWithCursor::textEditEvent, this));
	tec_TextField->setPlaceHolderColor(Color3B(74, 112, 139));
	this->addChild(tec_TextField);

	tec_Sprite = Sprite::create("textEidtline.png");
	tec_Sprite->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2-tec_TextField->getContentSize().height));
	this->addChild(tec_Sprite);
	
	addCursorSprite();
	return true;

}

void TextEditWithCursor::setTextEditSize(int x, int y)
{
	
}

bool TextEditWithCursor::setTextEditPasswordEnabled(bool isPassword)
{
	tec_TextField->setPasswordEnabled(isPassword);
	return isPassword;
}

void TextEditWithCursor::setTextEditPlaceHolder(const char * placeholder)
{
	tec_TextField->setPlaceHolder(placeholder);
}

std::string  TextEditWithCursor::getTextEditString()
{
	return tec_TextField->getStringValue();
}

TextEditWithCursor::TextEditWithCursor()
{
	tec_Sprite = NULL;
	tec_TextField = NULL;
}

TextEditWithCursor::~TextEditWithCursor()
{

}

void TextEditWithCursor::onEnter()
{
	LayerColor::onEnter();
}

void TextEditWithCursor::textEditEvent(Ref * pSender, TextField::EventType type)
{
	switch (type)
	{
	case TextField::EventType::ATTACH_WITH_IME:
	{
		cursorSprite->setVisible(true);
		cursorSprite->setPositionX(getContentWidth());
		break;
	}


	case TextField::EventType::DETACH_WITH_IME:
		cursorSprite->setVisible(false);
		cursorSprite->setPositionX(getContentWidth());
		break;

	case TextField::EventType::INSERT_TEXT:
	{
		cursorSprite->setVisible(true);
		cursorSprite->setPositionX(getContentWidth());
		break;
	}


	case TextField::EventType::DELETE_BACKWARD:
	{
		cursorSprite->setVisible(true);
		cursorSprite->setPositionX(getContentWidth());
		break;
	}

	default:
		break;
	}
}

void TextEditWithCursor::addCursorSprite()
{
	int column = 2;
	int height = 20;
	int pData[50][2];
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < column; j++)
		{
			pData[i][j] = 0xFFFFFFFF;
		}
	}
	Texture2D* texture = new Texture2D();
	texture->initWithData(pData, 20, Texture2D::PixelFormat::RGB888, 1, tec_TextField->getFontSize(), CCSizeMake(column, height));
	cursorSprite = Sprite::createWithTexture(texture);
	cursorSprite->setPositionY(tec_TextField->Node::getPositionY());

	texture->autorelease();

	this->addChild(cursorSprite);
	cursorSprite->setVisible(false);
	auto m_cursorAction = RepeatForever::create(Sequence::create(FadeOut::create(0.7f), FadeIn::create(0.7f), NULL));
	cursorSprite->runAction(m_cursorAction);
}

int TextEditWithCursor::getContentWidth()
{
	auto lable = Label::create();
	lable->setString(tec_TextField->getString());
	auto width = lable->getContentSize().width;
	return tec_TextField->getPosition().x + width-2;
	return 0;
}
